#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commandes.h"
#include <QMainWindow>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void update_label();
    void on_commandes_clicked();

    void on_ajouteCom_clicked();

    void on_deletebutton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_modifercom_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_9_clicked();

    void on_Anuller_clicked();

    void on_ajouterco_clicked();

    void on_statistiquebutton_clicked();

    void on_modifercommande_clicked();

    void on_retourStats_clicked();

    void on_StatisqueQP_clicked();

    void on_StatisqueClient_clicked();

    void on_StatisquePlace_clicked();

    void on_supprimer_clicked();

    void on_rechercheN_clicked();

    void on_rechercher_clicked();

    void on_pdf_clicked();

    void on_affichecommandes_activated(const QModelIndex &index);

    void on_localisation_2_clicked();

    void on_retourStats_2_clicked();

    void on_retourStats_5_clicked();

    void on_enfr_clicked();

    void on_retourStats_3_clicked();

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

    void on_stat_clicked();

    void on_arduino_clicked();


private:
    Ui::MainWindow *ui;
    Commandes com;
    QByteArray data;

    Arduino A;
};
#endif // MAINWINDOW_H
