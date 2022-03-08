#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commandes.h"
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
    void on_commandes_clicked();

    void on_ajouteCom_clicked();

    void on_deletebutton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_modifercom_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::MainWindow *ui;
    Commandes com;
};
#endif // MAINWINDOW_H
