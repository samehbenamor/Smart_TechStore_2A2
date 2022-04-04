#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
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
    void on_ajouter1_btn_clicked();

    void on_ajouter_client_clicked();

    void on_supprimer_btn_2_clicked();

    void on_aller_modifier_client_clicked();

    void on_modifier_btn_3_clicked();

    void on_Statistiques_btn_clicked();

    void on_Retour_5_clicked();

    void on_recherchecl_clicked();

    void on_PM_clicked();

    void on_Ajouter_clicked();

    void on_Consommer_clicked();

    void on_Retour_pms_clicked();

    void on_pushButton_clicked();

    void on_Excelexport_clicked();

    void on_changelanguage_clicked();

    void on_changefr_clicked();

private:
    Ui::MainWindow *ui;
    client cl;
};
#endif // MAINWINDOW_H
