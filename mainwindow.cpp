#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <iostream>

#include <QApplication>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(cl.afficherClient());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter1_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ajouter_client_clicked()
{
    int id_c = ui->idclient->text().toInt();
    QString nom=ui->nomclient->text();
    QString prenom=ui->prenomclient->text();
    QString address=ui->addressclient->text();
    client C(id_c, prenom, nom, address);
    bool test = C.ajouterClient();
    if (test) {
        //Refresh
        ui->tableView->setModel(cl.afficherClient());
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
    int id =ui->id_cli_supp->text().toInt();
    bool test=cl.supprimerClient(id);
    if (test) {
        //Refresh
        ui->tableView->setModel(cl.afficherClient());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Suppression non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_aller_modifier_client_clicked()
{
    QSqlQuery query;
        int id_c= ui->id_client_mod->text().toInt();
        query=cl.rechercherClient(id_c);
          query.first();
         bool test=query.value(0).toBool();
        if(test == false)
              QMessageBox::information(nullptr, QObject::tr("Attention!"),QObject::tr("Saisie l'id correcte"));
        else
        {
        ui->stackedWidget->setCurrentIndex(6);
        ui->id_cl_mod->setText(query.value(0).toString());
        ui->pr_cl_mod->setText(query.value(1).toString());
        ui->nom_cl_mod->setText(query.value(2).toString());
        ui->add_cl_mod->setText(query.value(3).toString());
}
}


void MainWindow::on_modifier_btn_3_clicked()
{
    int id_c = ui->id_cl_mod->text().toInt();
    QString prenom = ui->pr_cl_mod->text();
    QString nom = ui->nom_cl_mod->text();
    QString address = ui->add_cl_mod->text();
    client C(id_c, prenom, nom, address);
    bool test = C.modifierClient();
  if(test==true)
  {
       ui->tableView->setModel(C.afficherClient());
    ui->stackedWidget->setCurrentIndex(3);

  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}
