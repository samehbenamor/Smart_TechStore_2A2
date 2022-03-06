#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reparation.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    Reparation Reper;
};
#endif // MAINWINDOW_H
