#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commandes.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->affichecommandes->setModel(com.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_commandes_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ajouteCom_clicked()
{
 int id_co= ui->id_co->text().toInt();
 QString loc= ui->localisation->text();
 QString date= ui->dateCom->date().toString();
QSqlQuery query= com.rechercherCommandes(id_co);
query.first();
bool test2 = query.value(0).toBool();
if (id_co == NULL)
    QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ID"));
else if(test2 == true)
    QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ID EXISTE DEJA"));
else if (loc == NULL)
    QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ADRESSE"));
//else if ()

else {


Commandes c(id_co,date,loc,0,1);

bool test=c.AjouterCommandes();
if(test)
{
 QMessageBox::information(nullptr, QObject::tr("BING CHILLING"),QObject::tr("GUCCI"));
    ui->affichecommandes->setModel(com.afficher());
}
  else
     QMessageBox::information(nullptr, QObject::tr("NOT BING CHILLING"),QObject::tr("GUCCI'NTTTT"));
}
}
void MainWindow::on_deletebutton_clicked()
{
    int id_co= ui->idsup->text().toInt();
    QSqlQuery query= com.rechercherCommandes(id_co);
    query.first();
    bool test2 = query.value(0).toBool();
    if (id_co == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ID"));
    else if(test2 == false)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ID N'EXISTE PAS"));
    else{
    bool test=com.SupprimerCommandes(id_co);
    if(test)
     QMessageBox::information(nullptr, QObject::tr("HEHE"),QObject::tr("HANA FASA5NEHA"));
    else
     QMessageBox::information(nullptr, QObject::tr("HEHE"),QObject::tr("LALIIII MA NFASA5CHH"));
}
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void MainWindow::on_modifercom_clicked()
{
     QSqlQuery query;
    int id_co= ui->editcom->text().toInt();
    query=com.rechercherCommandes(id_co);
      query.first();
     bool test=query.value(0).toBool();
    if(test == false)
          QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("verifier votre id"));
    else
    {
    ui->stackedWidget->setCurrentIndex(6);
    ui->idcom->setText(query.value(0).toString());
    ui->date->setText(query.value(1).toString());
    ui->localisationM->setText(query.value(2).toString());
    ui->etatm->setText(query.value(3).toString());
    ui->idclientm->setText(query.value(4).toString());
}
}

void MainWindow::on_pushButton_15_clicked()
{
     int id_co= ui->idcom->text().toInt();
    int etat= ui->etatm->text().toInt();
    int idclientm= ui->idclientm->text().toInt();
    QString loca= ui->localisationM->text();
    QString date= ui->date->text();
    QSqlQuery query= com.rechercherCommandes(id_co);
    query.first();
    bool test2 = query.value(0).toBool();
    if (id_co == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ID"));
    else if(test2 == true)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ID EXISTE DEJA"));
    else if (loca == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ADRESSE"));
    else if ((etat!=0)||(etat!=1)||(etat!=2))
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ETAT VALIDE"));
    else if (etat == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ETAT"));
    else if(idclientm == null)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ETAT"));





    else {

bool test2= com.modifierCommandes(id_co,date,loca,etat,idclientm);
  if(test2==true)
  {
    ui->stackedWidget->setCurrentIndex(4);
     ui->affichecommandes->setModel(com.afficher());
  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}
}
