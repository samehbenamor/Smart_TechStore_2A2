#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commandes.h"
#include "arduino.h"
#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->affichecommandes->setModel(com.afficher());
    ui->stats->setModel(com.StatsCommandes(1));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_8_clicked()
{

}
void MainWindow::on_pushButton_9_clicked()
{

}
void MainWindow::on_supprimer_clicked()
{

}
void MainWindow::on_commandes_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ajouteCom_clicked()
{
 int id_co= ui->id_co->text().toInt();
 int id_Client= ui->idClient->text().toInt();
 int idProduit= ui->IdProduits->text().toInt();
 int quntite= ui->quantitee->text().toInt();
 QString coupon= ui->couponn->text();
 QString loc= ui->localisation->text();
 QString date= ui->dateCom->date().toString();
 QString ville= ui->villee->currentText();
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
int coupo=com.getCoupon(coupon);
qDebug()<<coupo;
float price=com.getPrice(idProduit);
price = price*quntite;
if(coupo!=0)
    price= (price*coupo)/100;
Commandes c(id_co,date,loc,0,id_Client,ville);
bool test=c.AjouterCommandes();
bool k=c.ajoutecontenir(id_co,idProduit,quntite,price);
if(test)
{
 QMessageBox::information(nullptr, QObject::tr("BING CHILLING"),QObject::tr("Ajouté !"));
    ui->affichecommandes->setModel(com.afficher());
    ui->stats->setModel(com.StatsCommandes(1));
    ui->stackedWidget->setCurrentIndex(1);

}
  else
     QMessageBox::information(nullptr, QObject::tr("NOT BING CHILLING"),QObject::tr("Erreur !"));
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
    QString etat1= ui->etatm->text();
    int idclientm= ui->idclientm->text().toInt();
    QString loca= ui->localisationM->text();
    QString date= ui->date->text();
    QSqlQuery query= com.rechercherCommandes(id_co);
    query.first();
    bool test2 = query.value(0).toBool();
    if (id_co == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ID"));
    else if((test2 == true)&&(id_co!=query.value(0)))
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ID EXISTE DEJA"));
    else if (loca == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UNE ADRESSE"));
    else if ((etat!=0)&&(etat!=1)&&(etat!=2))
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ETAT VALIDE"));
    else if (etat1 == "")
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ETAT"));
    else if(idclientm == NULL)
        QMessageBox::information(nullptr, QObject::tr("ERROR"),QObject::tr("ENTRER UN ID CILENT"));
    else {

bool test2= com.modifierCommandes(id_co,date,loca,etat,idclientm);
  if(test2==true)
  {
    ui->stackedWidget->setCurrentIndex(1);
     ui->affichecommandes->setModel(com.afficher());
  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}
}


void MainWindow::on_Anuller_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ajouterco_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_statistiquebutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stats->setModel(com.StatsCommandes(1));
}

void MainWindow::on_modifercommande_clicked()
{
      ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_retourStats_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_StatisqueQP_clicked()
{
    ui->stats->setModel(com.StatsCommandes(2));
}

void MainWindow::on_StatisqueClient_clicked()
{
    ui->stats->setModel(com.StatsCommandes(1));
}

void MainWindow::on_StatisquePlace_clicked()
{
    ui->stats->setModel(com.StatsCommandes(3));
}

void MainWindow::on_rechercheN_clicked()
{

}

void MainWindow::on_rechercher_clicked()
{
   QString type= ui->recherche->text();
   if(type !=NULL)
   {
  if(ui->RechercherParVille->isChecked())
      ui->affichecommandes->setModel(com.Recherche(3,type));
  else if(ui->RechercherParClient->isChecked())
      ui->affichecommandes->setModel(com.Recherche(2,type));
  else if(ui->RechercheParId->isChecked())
      ui->affichecommandes->setModel(com.Recherche(1,type));
    }
   else
       ui->affichecommandes->setModel(com.afficher());
}

void MainWindow::on_pdf_clicked()
{
  // QModelIndex index= ui->affichecommandes->currentIndex();
    //QString html = ui->affichecommandes->model()->data(index).toString();
    QString html="<h1>FACTURE !</h1><br>";
    int rowidx = ui->affichecommandes->selectionModel()->currentIndex().row();
     html+= "ID :";
     html+= ui->affichecommandes->model()->index(rowidx , 0).data().toString();
     html+= "<br>"
            "DATE SORTIE : ";
     html+= ui->affichecommandes->model()->index(rowidx , 1).data().toString();
     html+= "<br>"
            "ADRESSE : ";
     html+= ui->affichecommandes->model()->index(rowidx , 2).data().toString();
     html+= "<br>"
            "ID CLIENT : ";
     html+= ui->affichecommandes->model()->index(rowidx , 3).data().toString();
     html+= "<br>"
            "VILLE: ";
     html+= ui->affichecommandes->model()->index(rowidx , 4).data().toString();
   QTextDocument document;
   document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("facture.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));
    document.print(&printer);
    QMessageBox::information(nullptr, QObject::tr("Succès"),QObject::tr("Facture crée"));

}

void MainWindow::on_affichecommandes_activated(const QModelIndex &index)
{

}

void MainWindow::on_localisation_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_retourStats_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_retourStats_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_enfr_clicked()
{
    QString test= ui->command->text();
    if(test=="Commandes")
   {
    ui->ajouterco->setText("Add");
    ui->modifercommande->setText("Modify");
    ui->pushButton_2->setText("Delete");
    ui->statistiquebutton->setText("Statistics");
    ui->localisation_2->setText("Location");
    ui->RechercherParVille->setText("City");
    ui->RechercherParClient->setText("Client");
    ui->command->setText("Orders");
    ui->ville->setText("City");
    ui->adress->setText("Adress");
    ui->date_2->setText("Dilevery date");
    ui->ajouteCom->setText("Add");
    ui->Anuller->setText("Cancel");
    ui->addcoma->setText("Add command");
    ui->addcomaaddcoma->setText("Stats");
    ui->StatisqueQP->setText("Most ordered products");
    ui->StatisqueClient->setText("Clients that order the most");
    ui->StatisquePlace->setText("Places with the most orders");
    ui->villet->setText("City");
    ui->etat->setText("State");
    ui->adresset->setText("Adress");
    ui->dateSt->setText("Delevery date");
    }
     else{
        ui->ajouterco->setText("Ajouter");
        ui->modifercommande->setText("Modifer");
        ui->pushButton_2->setText("Supprimer");
        ui->statistiquebutton->setText("Statistique");
        ui->localisation_2->setText("Localisation");
        ui->RechercherParVille->setText("Ville");
        ui->RechercherParClient->setText("Client");
        ui->command->setText("Commandes");
        ui->ville->setText("Ville");
        ui->adress->setText("Adresse");
        ui->date_2->setText("Date Sortie");
        ui->ajouteCom->setText("Ajouter");
        ui->Anuller->setText("Anuller");
        ui->addcoma->setText("Ajouter Commmande");
        ui->addcomaaddcoma->setText("Statistique");
        ui->StatisqueQP->setText("Les produis les plus comandes");
        ui->StatisqueClient->setText("Les client qui commande le plus");
        ui->StatisquePlace->setText("Les villes qui commande le plus");
        ui->villet->setText("ville");
        ui->etat->setText("Etat");
        ui->adresset->setText("adresse");
        ui->dateSt->setText("Date sortie");
    }
}

void MainWindow::on_retourStats_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_Tataouine_clicked()
{
    int count=0;

   QSqlQuery k=com.Recherche2("Tataouine");
    while (k.next()) {
    count++;
    }

   QString idk="Le nombre de commande est  ";
     idk += QString::number(count);
    ui->nombre->setText(idk);
}

void MainWindow::on_Medine_clicked()
{
            int count=0;

           QSqlQuery k=com.Recherche2("Medine");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Kebili_clicked()
{
    int count=0;

   QSqlQuery k=com.Recherche2("Kebili");
    while (k.next()) {
    count++;
    }
    QString idk="Le nombre de commande est  ";
      idk += QString::number(count);
    ui->nombre->setText(idk);
}

void MainWindow::on_Tozer_clicked()
{
            int count=0;

           QSqlQuery k=com.Recherche2("Tozeur");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Gafsa_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Gafsa");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_gebes_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Gébes");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Sidibouzid_clicked()
{
            int count=0;

           QSqlQuery k=com.Recherche2("Sidi bouzid");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Gasrine_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Gasrine");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Sfax_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Sfax");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Mahdiya_clicked()
{


            int count=0;

           QSqlQuery k=com.Recherche2("Mahdiya");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Kairaoun_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Kairaoun");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Mestir_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Mestir");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Sousa_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Sousse");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Siliana_clicked()
{

            int count=0;

           QSqlQuery k=com.Recherche2("Siliana");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Zagouhen_clicked()
{


            int count=0;

           QSqlQuery k=com.Recherche2("Zagouhen");
            while (k.next()) {
            count++;
            }
            QString idk="Le nombre de commande est  ";
              idk += QString::number(count);
            ui->nombre->setText(idk);
}

void MainWindow::on_Kef_clicked()
{
    int count=0;

   QSqlQuery k=com.Recherche2("Kef");
    while (k.next()) {
    count++;
    }
    QString idk="Le nombre de commande est  ";
      idk += QString::number(count);
    ui->nombre->setText(idk);
}

void MainWindow::on_Beja_clicked()
{
     int count=0;

    QSqlQuery k=com.Recherche2("Beja");
     while (k.next()) {
     count++;
     }
     QString idk="Le nombre de commande est  ";
       idk += QString::number(count);
     ui->nombre->setText(idk);
}

void MainWindow::on_Jandouba_clicked()
{
      int count=0;

    QSqlQuery k=com.Recherche2("Jandouba");
     while (k.next()) {
     count++;
     }
     QString idk="Le nombre de commande est  ";
       idk += QString::number(count);
     ui->nombre->setText(idk);
}


void MainWindow::on_Nabeul_clicked()
{
        int count=0;

    QSqlQuery k=com.Recherche2("Nabel");
     while (k.next()) {
     count++;
     }
     QString idk="Le nombre de commande est  ";
       idk += QString::number(count);
     ui->nombre->setText(idk);
}


void MainWindow::on_bizerte_clicked()
{
     int count=0;

    QSqlQuery k=com.Recherche2("Bizerte");
     while (k.next()) {
     count++;
     }
     QString idk="Le nombre de commande est  ";
       idk += QString::number(count);
     ui->nombre->setText(idk);
}

void MainWindow::on_GTunis_clicked()
{
    int count=0;

   QSqlQuery k=com.Recherche2("Tunis");
    while (k.next()) {
    count++;
    }
    k=com.Recherche2("Ben Arous");
     while (k.next()) {
     count++;
     }
     k=com.Recherche2("Ariana");
      while (k.next()) {
      count++;
      }
    QString idk="Le nombre de commande est  ";
      idk += QString::number(count);
    ui->nombre->setText(idk);
}


void MainWindow::on_stat_clicked()
{
   // stats();
}

void MainWindow::update_label()
{
   /* data=A.read_from_arduino();
    QString idk=data;
    idk= idk.remove(' ');
    qDebug()<<data;
    //A.write_to_arduino("1");*/
}
void MainWindow::on_arduino_clicked()
{
    QSqlQuery query;
    data=A.read_from_arduino();
QString idk=data;
idk= idk.remove(' ');
qDebug()<<"data "<<idk;
int f=idk.toInt();
QString ohr="05196168172";
com.RechercheEmp(f);
query.first();
qDebug()<< query.value(5).toInt();

if(query.value(5).toInt()==1)
{

    qDebug()<< "Autorisé";
    A.write_to_arduino("1");
}
else
A.write_to_arduino("0");

   // A.write_to_arduino("1");
}
