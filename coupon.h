#ifndef COUPON_H
#define COUPON_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class coupon
{
    QString id_coupon;
    int reduc;
public:
    coupon() {}
    coupon(QString, int);
    QString getIDC(){return id_coupon;}
    int getReduc(){return reduc;}
    void setIDC(QString idc){id_coupon = idc;}
    void setQR(int red){reduc = red;}

    int getreduction(QString);
};

#endif // COUPON_H
