

#pragma once

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>


namespace qrcodegen {


class QrSegment final {


    public: class Mode final {



        public: static const Mode NUMERIC;
        public: static const Mode ALPHANUMERIC;
        public: static const Mode BYTE;
        public: static const Mode KANJI;
        public: static const Mode ECI;





        private: int modeBits;


        private: int numBitsCharCount[3];




        private: Mode(int mode, int cc0, int cc1, int cc2);


        public: int getModeBits() const;


        public: int numCharCountBits(int ver) const;

    };




    public: static QrSegment makeBytes(const std::vector<std::uint8_t> &data);



    public: static QrSegment makeNumeric(const char *digits);



    public: static QrSegment makeAlphanumeric(const char *text);



    public: static std::vector<QrSegment> makeSegments(const char *text);


    public: static QrSegment makeEci(long assignVal);



    public: static bool isAlphanumeric(const char *text);



    public: static bool isNumeric(const char *text);




    private: Mode mode;


    private: int numChars;


    private: std::vector<bool> data;


    public: QrSegment(Mode md, int numCh, const std::vector<bool> &dt);



    public: QrSegment(Mode md, int numCh, std::vector<bool> &&dt);


    public: Mode getMode() const;



    public: int getNumChars() const;



    public: const std::vector<bool> &getData() const;



    public: static int getTotalBits(const std::vector<QrSegment> &segs, int version);



    private: static const char *ALPHANUMERIC_CHARSET;

};




class QrCode final {


    public: enum class Ecc {
        LOW = 0 ,  // The QR Code can tolerate about  7% erroneous codewords
        MEDIUM  ,  // The QR Code can tolerate about 15% erroneous codewords
        QUARTILE,  // The QR Code can tolerate about 25% erroneous codewords
        HIGH    ,  // The QR Code can tolerate about 30% erroneous codewords
    };



    private: static int getFormatBits(Ecc ecl);




    public: static QrCode encodeText(const char *text, Ecc ecl);



    public: static QrCode encodeBinary(const std::vector<std::uint8_t> &data, Ecc ecl);



    public: static QrCode encodeSegments(const std::vector<QrSegment> &segs, Ecc ecl,
        int minVersion=1, int maxVersion=40, int mask=-1, bool boostEcl=true);  // All optional parameters




    private: int version;

    private: int size;

    /* The error correction level used in this QR Code. */
    private: Ecc errorCorrectionLevel;

    private: int mask;


    private: std::vector<std::vector<bool> > modules;

    // Indicates function modules that are not subjected to masking. Discarded when constructor finishes.
    private: std::vector<std::vector<bool> > isFunction;




    public: QrCode(int ver, Ecc ecl, const std::vector<std::uint8_t> &dataCodewords, int msk);



    /*---- Public instance methods ----*/

    /*
     * Returns this QR Code's version, in the range [1, 40].
     */
    public: int getVersion() const;


    /*
     * Returns this QR Code's size, in the range [21, 177].
     */
    public: int getSize() const;


    /*
     * Returns this QR Code's error correction level.
     */
    public: Ecc getErrorCorrectionLevel() const;


    /*
     * Returns this QR Code's mask, in the range [0, 7].
     */
    public: int getMask() const;


    /*
     * Returns the color of the module (pixel) at the given coordinates, which is false
     * for white or true for black. The top left corner has the coordinates (x=0, y=0).
     * If the given coordinates are out of bounds, then false (white) is returned.
     */
    public: bool getModule(int x, int y) const;


    /*
     * Returns a string of SVG code for an image depicting this QR Code, with the given number
     * of border modules. The string always uses Unix newlines (\n), regardless of the platform.
     */
    public: std::string toSvgString(int border) const;



    /*---- Private helper methods for constructor: Drawing function modules ----*/

    // Reads this object's version field, and draws and marks all function modules.
    private: void drawFunctionPatterns();


    // Draws two copies of the format bits (with its own error correction code)
    // based on the given mask and this object's error correction level field.
    private: void drawFormatBits(int msk);


    // Draws two copies of the version bits (with its own error correction code),
    // based on this object's version field, iff 7 <= version <= 40.
    private: void drawVersion();


    // Draws a 9*9 finder pattern including the border separator,
    // with the center module at (x, y). Modules can be out of bounds.
    private: void drawFinderPattern(int x, int y);


    // Draws a 5*5 alignment pattern, with the center module
    // at (x, y). All modules must be in bounds.
    private: void drawAlignmentPattern(int x, int y);


    // Sets the color of a module and marks it as a function module.
    // Only used by the constructor. Coordinates must be in bounds.
    private: void setFunctionModule(int x, int y, bool isBlack);


    // Returns the color of the module at the given coordinates, which must be in range.
    private: bool module(int x, int y) const;


    /*---- Private helper methods for constructor: Codewords and masking ----*/

    // Returns a new byte string representing the given data with the appropriate error correction
    // codewords appended to it, based on this object's version and error correction level.
    private: std::vector<std::uint8_t> addEccAndInterleave(const std::vector<std::uint8_t> &data) const;


    // Draws the given sequence of 8-bit codewords (data and error correction) onto the entire
    // data area of this QR Code. Function modules need to be marked off before this is called.
    private: void drawCodewords(const std::vector<std::uint8_t> &data);


    // XORs the codeword modules in this QR Code with the given mask pattern.
    // The function modules must be marked and the codeword bits must be drawn
    // before masking. Due to the arithmetic of XOR, calling applyMask() with
    // the same mask value a second time will undo the mask. A final well-formed
    // QR Code needs exactly one (not zero, two, etc.) mask applied.
    private: void applyMask(int msk);


    // Calculates and returns the penalty score based on state of this QR Code's current modules.
    // This is used by the automatic mask choice algorithm to find the mask pattern that yields the lowest score.
    private: long getPenaltyScore() const;



    /*---- Private helper functions ----*/

    // Returns an ascending list of positions of alignment patterns for this version number.
    // Each position is in the range [0,177), and are used on both the x and y axes.
    // This could be implemented as lookup table of 40 variable-length lists of unsigned bytes.
    private: std::vector<int> getAlignmentPatternPositions() const;


    // Returns the number of data bits that can be stored in a QR Code of the given version number, after
    // all function modules are excluded. This includes remainder bits, so it might not be a multiple of 8.
    // The result is in the range [208, 29648]. This could be implemented as a 40-entry lookup table.
    private: static int getNumRawDataModules(int ver);


    // Returns the number of 8-bit data (i.e. not error correction) codewords contained in any
    // QR Code of the given version number and error correction level, with remainder bits discarded.
    // This stateless pure function could be implemented as a (40*4)-cell lookup table.
    private: static int getNumDataCodewords(int ver, Ecc ecl);


    // Returns a Reed-Solomon ECC generator polynomial for the given degree. This could be
    // implemented as a lookup table over all possible parameter values, instead of as an algorithm.
    private: static std::vector<std::uint8_t> reedSolomonComputeDivisor(int degree);


    // Returns the Reed-Solomon error correction codeword for the given data and divisor polynomials.
    private: static std::vector<std::uint8_t> reedSolomonComputeRemainder(const std::vector<std::uint8_t> &data, const std::vector<std::uint8_t> &divisor);


    // Returns the product of the two given field elements modulo GF(2^8/0x11D).
    // All inputs are valid. This could be implemented as a 256*256 lookup table.
    private: static std::uint8_t reedSolomonMultiply(std::uint8_t x, std::uint8_t y);


    // Can only be called immediately after a white run is added, and
    // returns either 0, 1, or 2. A helper function for getPenaltyScore().
    private: int finderPenaltyCountPatterns(const std::array<int,7> &runHistory) const;


    // Must be called at the end of a line (row or column) of modules. A helper function for getPenaltyScore().
    private: int finderPenaltyTerminateAndCount(bool currentRunColor, int currentRunLength, std::array<int,7> &runHistory) const;


    // Pushes the given value to the front and drops the last value. A helper function for getPenaltyScore().
    private: void finderPenaltyAddHistory(int currentRunLength, std::array<int,7> &runHistory) const;


    // Returns true iff the i'th bit of x is set to 1.
    private: static bool getBit(long x, int i);


    /*---- Constants and tables ----*/

    // The minimum version number supported in the QR Code Model 2 standard.
    public: static constexpr int MIN_VERSION =  1;

    // The maximum version number supported in the QR Code Model 2 standard.
    public: static constexpr int MAX_VERSION = 40;


    // For use in getPenaltyScore(), when evaluating which mask is best.
    private: static const int PENALTY_N1;
    private: static const int PENALTY_N2;
    private: static const int PENALTY_N3;
    private: static const int PENALTY_N4;


    private: static const std::int8_t ECC_CODEWORDS_PER_BLOCK[4][41];
    private: static const std::int8_t NUM_ERROR_CORRECTION_BLOCKS[4][41];

};



/*---- Public exception class ----*/

/*
 * Thrown when the supplied data does not fit any QR Code version. Ways to handle this exception include:
 * - Decrease the error correction level if it was greater than Ecc::LOW.
 * - If the encodeSegments() function was called with a maxVersion argument, then increase
 *   it if it was less than QrCode::MAX_VERSION. (This advice does not apply to the other
 *   factory functions because they search all versions up to QrCode::MAX_VERSION.)
 * - Split the text data into better or optimal segments in order to reduce the number of bits required.
 * - Change the text or binary data to be shorter.
 * - Change the text to fit the character set of a particular segment mode (e.g. alphanumeric).
 * - Propagate the error upward to the caller/user.
 */
class data_too_long : public std::length_error {

    public: explicit data_too_long(const std::string &msg);

};



/*
 * An appendable sequence of bits (0s and 1s). Mainly used by QrSegment.
 */
class BitBuffer final : public std::vector<bool> {

    /*---- Constructor ----*/

    // Creates an empty bit buffer (length 0).
    public: BitBuffer();



    /*---- Method ----*/

    // Appends the given number of low-order bits of the given value
    // to this buffer. Requires 0 <= len <= 31 and val < 2^len.
    public: void appendBits(std::uint32_t val, int len);

};

}
