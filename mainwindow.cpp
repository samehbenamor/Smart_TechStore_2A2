#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QApplication>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_produits_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
/*
void MainWindow::on_pushButton_ajouter_clicked()
{
    //récuperation des informations saisies dans les 3 champs
    int id=ui->lineEdit_ID->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    produit P(id, ...);
    bool test = P.ajouterProduit();
    if (test) {
        //Refresh
        ui->tableView->setModel(pro.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}*/
/*
void MainWindow::on_pushButton_supprimer_clicked()
{
    int id =ui->lineEdit_IDS->text().toInt();
    bool test=pro.supprimer(id);
    if (test) {
        //Refresh
        ui->tableView->setModel(pro.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

    }
}*/
/*
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(pro.afficher());
}
*/
