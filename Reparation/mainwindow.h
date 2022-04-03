#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reparation.h"
#include "smtp.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets/QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* *************CAMERA STUFF**************** */
    class QCamera;
    class QCameraViewfinder;
    class QCameraImageCapture;
    class QVBoxLayout;
    class QMenu;
    class QAction;
/* **************************************** */


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

/* *************Email STUFF**************** */
    void sendMail();
    void mailSent(QString);
    void browse();
    void browse2();
/* **************************************** */


    void on_Login_3_clicked();

    void on_reparations_clicked();

    void on_Retour_clicked();

    void on_Retour_2_clicked();

    void on_ajouter_btn_clicked();

    void on_supprimer_btn_clicked();

    void on_supprimer_btn_2_clicked();

    void on_Retour_4_clicked();

    void on_ajouter1_btn_clicked();

    void on_Retour_3_clicked();

    void on_modifier_btn_3_clicked();

    void on_modifier_btn_clicked();

    void on_Retour_9_clicked();

    void on_Retour_11_clicked();

    int on_aller_modifier_clicked();

    void on_Rechercher_btn_clicked();

    void on_Retour_5_clicked();

    void on_Statistiques_btn_clicked();

    void on_notifier_client_clicked();

    void on_ajouter_image_clicked();

    void on_traduire_clicked();

    void on_Retour_10_clicked();

    void on_Retour_12_clicked();

    void on_Retour_13_clicked();

    void on_telecharger_image_btn_clicked();

    void on_Retour_14_clicked();

    int on_suivant_clicked();

    void on_done_btn_clicked();

    void on_Ajouter_clicked();

    void on_Retour_15_clicked();

    void on_francais_clicked();

    void on_English_clicked();

private:
    Ui::MainWindow *ui;

    /* *************CAMERA STUFF************* */
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionMenu;
    QAction *mLancerAction;
    QAction *mStopperAction;
    QAction *mCapturerAction;
    /* *************************************** */

    Reparation Reper;
    QStringList files;
};
#endif // MAINWINDOW_H
