#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produit.h"
#include "qrcode.h"
#include "commandes.h"
#include "arduino.h"
#include "client.h"
#include "reparation.h"
#include "smtp.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets/QMessageBox>
QT_BEGIN_NAMESPACE
using namespace qrcodegen;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_produits_clicked();

    void on_ajouterproduit_clicked();

    void on_Recherche_pr_clicked();

    void on_StatsProduit_clicked();

    void on_SupprimerProduit_clicked();

    void on_ModifierProduit_clicked();

    void on_yeah_clicked();

    void on_archiver_clicked();

    void on_coupon_clicked();

    void on_ajouter_pro_clicked();

    void on_SuppProd_clicked();

    void on_modifier_pr_go_clicked();

    void on_modifierproduit_clicked();

    void on_couponre_clicked();

    void on_AjouterClient_clicked();

    void on_clients_clicked();

    void on_ajouter_client_clicked();

    void on_supprimerClient_clicked();

    void on_SuppClient_clicked();

    void on_aller_modifier_client_clicked();

    void on_ModClient_clicked();

    void on_modifier_btn_3_clicked();

    void on_Retour_pms_clicked();

    void on_AjouterPM_clicked();

    void on_PM_clicked();

    void on_ConsommerPM_clicked();

    void on_Excelexport_clicked();

    void on_ajouter_emp_clicked();

    void on_supprimer_emp_clicked();

    void on_modifier_btnSet_clicked();

    void on_modifier_btn_emp_2_clicked();

    void on_clear_empBtn_clicked();

    void on_excelBtn_clicked();

    void on_Statistiques_empBtn_clicked();

    void on_recherche_emp_textChanged(const QString &arg1);

    void on_trier_empBtn_clicked();

    void on_voir_btnemp_clicked();

    void on_archiver_emp_clicked();



    void on_ajouterco_clicked();

    void on_ajouteCom_clicked();

    void on_SuppProd_2_clicked();

    void on_SuppProd_3_clicked();

    void on_pushButton_58_clicked();

    void on_pdf_clicked();

    void on_localisation_2_clicked();

    void on_modifercommande_clicked();

    void on_statistiquebutton_clicked();

    void on_Anuller_clicked();

    void on_Tataouine_clicked();

    void on_Medine_clicked();

    void on_Kebili_clicked();

    void on_Tozer_clicked();

    void on_Gafsa_clicked();

    void on_gebes_clicked();

    void on_Sidibouzid_clicked();

    void on_Gasrine_clicked();

    void on_Sfax_clicked();

    void on_Mahdiya_clicked();

    void on_Kairaoun_clicked();

    void on_Mestir_clicked();

    void on_Sousa_clicked();

    void on_Siliana_clicked();

    void on_Zagouhen_clicked();

    void on_Kef_clicked();

    void on_Beja_clicked();

    void on_Jandouba_clicked();

    void on_Nabeul_clicked();

    void on_bizerte_clicked();

    void on_GTunis_clicked();

    void on_commandes_clicked();

    void on_pushButton_2_clicked();

    void on_ajouter1_btn_clicked();

    void on_ajouter_btn_clicked();

    void on_Rechercher_btn_4_clicked();

    void on_supprimer_btn_clicked();

    void on_supprimer_btn_2_clicked();

    void on_modifier_btn_clicked();

    int on_aller_modifier_clicked();

    void on_notifier_client_clicked();

    void on_sendBtn_clicked();

    void on_exitBtn_clicked();

    void on_ajouter_image_clicked();

    void on_done_btn_clicked();

    void browse2();

    void browse();

    void sendMail();

    void mailSent(QString status);

    void on_Ajouter_clicked();

    int on_suivant_clicked();

    void on_reparations_clicked();

    void on_modifier_btn_4_clicked();

    void on_arduino_clicked();

private:
    Ui::MainWindow *ui;
    produit pro;
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
    QStringList files;
    client cl;
    Reparation Reper;
    QByteArray data; // variable contenant les données reçues
    Commandes com;
    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
