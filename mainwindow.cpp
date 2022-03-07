#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QApplication>
#include <QMessageBox>
#include <QDate>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(pro.afficher());

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


void MainWindow::on_modifier_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_supprimer_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_ajouter_pro_clicked()
{

    int id_pr=ui->idproduit_txt->text().toInt();
    int stock=ui->stock->text().toInt();
    int prix=ui->prix_pr->text().toInt();

    QString nom_pr=ui->nom_pr->text();
    QString date_impo = ui->date_impo->date().toString();
    QString description=ui->description->text();
    QString Qr_code = "";
    QString image = "";



    produit P(id_pr, nom_pr, prix, Qr_code, stock, image, date_impo, description);
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
}

void MainWindow::on_supprimer_btn_2_clicked()
{
    int id =ui->id_pr_del->text().toInt();
    bool test=pro.supprimerProduit(id);
    if (test) {
        //Refresh
        ui->tableView->setModel(pro.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Suppression non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_modifier_pr_go_clicked()
{
    QSqlQuery query;
        int id_pr= ui->id_pr_modifier->text().toInt();
        query=pro.rechercherProduit(id_pr);
          query.first();
         bool test=query.value(0).toBool();
        if(test == false)
              QMessageBox::information(nullptr, QObject::tr("Attention!"),QObject::tr("Saisie l'id correcte"));
        else
        {
        ui->stackedWidget->setCurrentIndex(6);
        ui->id_pr_mod->setText(query.value(0).toString());
        ui->nom_pr_mod->setText(query.value(1).toString());
        ui->prix_pr_mod->setText(query.value(2).toString());
        ui->stock_pr_mod->setText(query.value(4).toString());
        ui->date_pr_mod->setText(query.value(6).toString());
        ui->desc_pr_mod->setText(query.value(7).toString());
    }
}

void MainWindow::on_modifier_btn_3_clicked()
{
    /*int id_pr=ui->idproduit_txt->text().toInt();
    QString nom_pr=ui->nom_pr->text();
    int stock=ui->stock->text().toInt();
    int prix=ui->prix_pr->text().toInt();
    //QString date_impo = ui->date_impo->text();
    QString date_impo = ui->date_impo->date().toString();
    QString description=ui->description->text();
    QString Qr_code = "";
    QString image = "";*/
       int id_pr = ui->id_pr_mod->text().toInt();
       int stock = ui->stock_pr_mod->text().toInt();
       int prix = ui->prix_pr_mod->text().toInt();
       QString nom = ui->nom_pr_mod->text();
       QString description = ui->desc_pr_mod->text();
       QString date_impo = ui->date_pr_mod->text();
       QString Qr_code = "";
       QString image = "";
       produit P(id_pr, nom, prix, Qr_code, stock, image, date_impo, description);
       bool test = P.modifierProduit();
     if(test==true)
     {
          ui->tableView->setModel(pro.afficher());
       ui->stackedWidget->setCurrentIndex(3);

     }
      else
         QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}

