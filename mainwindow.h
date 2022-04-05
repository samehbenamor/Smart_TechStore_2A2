#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produit.h"
#include "qrcode.h"
QT_BEGIN_NAMESPACE
using namespace qrcodegen;
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

    void on_produits_clicked();

    void on_ajouter_pro_clicked();

    void on_supprimer_btn_2_clicked();

    void on_aller_modifier_clicked();

    void on_modifier_pr_go_clicked();

    void on_modifier_btn_3_clicked();

    void on_modifier_btn_clicked();

    void on_supprimer_btn_clicked();

    void on_ajouter1_btn_clicked();

    void on_Statistiques_btn_clicked();

    void on_ajouter_pro_4_clicked();

    void on_ajouter_pro_3_clicked();

    void on_Recherche_pr_clicked();

    void on_yeah_clicked();

    void on_en_clicked();

    void on_fr_clicked();

    void on_archiver_clicked();

private:
    Ui::MainWindow *ui;
    produit pro;

};
#endif // MAINWINDOW_H
