 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "faciliter.h"
#include <iostream>
#include <QThread>
#include "notif.h"
#include <QApplication>
#include <QMessageBox>
#include "exportexcel.h"
#include <QFile>
#include <QFileDialog>
#include "arduino.h"
#include<QTimer>


QTimer *timerSerial = new QTimer();
QTimer *timer3 = new QTimer();//


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(cl.afficherClient());
   // ui->tableview->setModel(cl.afficherclient(0));
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

//         connect(timer3, SIGNAL(timeout()), this, SLOT(update_label()));
//             timer3->start(1500);


}
void MainWindow::update_label()
{
     data="";
while(A.getdata().size()<5)
{
     data=A.read_from_arduino();
}
qDebug() << data ;

 // data=A.read_from_arduino();
  int D=data.toInt();
//qDebug() << D ;

    if(A.chercherid_c(D)!="-1")
{
        QString nom=A.chercher(D);
        qDebug() << nom ;
        QByteArray x=nom.toUtf8();
        qDebug() << x ;
        A.write_to_arduino(x);
    }
    else
A.write_to_arduino("0");
data="";
}
////////////////////////// redeffffffffffffffffffffffffffff




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
    int points_merci = 0;
    client C(id_c, prenom, nom, address, points_merci);
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
        ui->PMERCI->setText(query.value(4).toString());
}
}


void MainWindow::on_modifier_btn_3_clicked()
{
    int id_c = ui->id_cl_mod->text().toInt();
    QString prenom = ui->pr_cl_mod->text();
    QString nom = ui->nom_cl_mod->text();
    QString address = ui->add_cl_mod->text();
    int points_merci = ui->PMERCI->text().toInt();
    client C(id_c, prenom, nom, address, points_merci);
    bool test = C.modifierClient();
  if(test==true)
  {
       ui->tableView->setModel(C.afficherClient());
    ui->stackedWidget->setCurrentIndex(3);

  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}

void MainWindow::on_Statistiques_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    QSqlQuery query;
    //nombres des clients
    query=cl.NbClient();
    query.first();
    ui->nbrclient->setText(query.value(0).toString());
    //Derniere client ajouté
    ui->clidernier->setModel(cl.afficherLatestCl());
}

void MainWindow::on_Retour_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_recherchecl_clicked()
{
    QString re = ui->recherche_cl->text();
    ui->tableView->setModel(cl.afficherRechercheCl(re));
}

void MainWindow::on_PM_clicked()
{
    int tabeq=ui->tableView->currentIndex().row();
               QVariant idd=ui->tableView->model()->data(ui->tableView->model()->index(tabeq,0));
               QString id= idd.toString();
               QSqlQuery qry;
               qry.prepare("select * from CLIENT where ID_C=:ID_C");
               qry.bindValue(":ID_C",id);
               qry.exec();
                  QString  ID_C,nom,prenom,address,points_merci;

               while(qry.next()){
                   id=qry.value(0).toString();
                   nom=qry.value(2).toString();
                   prenom=qry.value(1).toString();
                   //address=qry.value(4).toString();
                   //points_merci=qry.value(4).toString();
               }
               ui->stackedWidget->setCurrentIndex(8);
               ui->idclpm->setText(id);
                ui->PrenomCli->setText(prenom);
                ui->NomCli->setText(nom);
                //ui->Poim->setText(points_merci);
}



void MainWindow::on_Ajouter_clicked()
{
    int id_c = ui->idclpm->text().toInt();
    int pm = ui->merciajoute->text().toInt();
    /////
    QSqlQuery qry;
    qry.prepare("select * from CLIENT where ID_C=:ID_C");
    qry.bindValue(":ID_C",id_c);
    QString  nom,prenom,address;
    int ID_C, points_merci;
    qry.exec();
    qry.first();
    ID_C=qry.value(1).toInt();
    nom=qry.value(3).toString();
    prenom=qry.value(2).toString();
    address=qry.value(4).toString();
    points_merci=qry.value(5).toInt();
    /////
    client C(ID_C, prenom, nom, address, points_merci);
    /////
    QString pointNotif = QString::number(pm);
    QString text = pointNotif+" points ajouté";
    QString titre = "Les points merci on été ajouté avec success au client " + nom;
    notif c(text, titre);
    /////
    bool test=C.ajouterpm(id_c, pm);
    if (test) {
        //Refresh
        ui->messageajout->setText("Ajout avec success!");
        c.afficher();
        ui->tableView->setModel(cl.afficherClient());
    }
    else
    {
        ui->messageajout->setText("Echec");
    }
}


void MainWindow::on_Consommer_clicked()
{
    int id_c = ui->idclpm->text().toInt();
    int pm = ui->MerciConsommer->text().toInt();
    /////
    QSqlQuery qry;
    qry.prepare("select * from CLIENT where ID_C=:ID_C");
    qry.bindValue(":ID_C",id_c);
    QString  nom,prenom,address;
    int ID_C, points_merci;
    qry.exec();
    qry.first();
    ID_C=qry.value(1).toInt();
    nom=qry.value(3).toString();
    prenom=qry.value(2).toString();
    address=qry.value(4).toString();
    points_merci=qry.value(5).toInt();
    /////
    client C(ID_C, prenom, nom, address, points_merci);
    ////
    QString pointNotif = QString::number(pm);
    QString text = pointNotif+" points Consommer";
    QString titre = "Les points merci on été consommer avec success de client " + nom;
    notif c(text, titre);
    ////
    bool test=C.consommerpm(id_c, pm);
    if (test) {
        ui->messageecons->setText("Consommer avec success!");
        c.afficher();
        ui->tableView->setModel(cl.afficherClient());
    }
    else
    {
        ui->messageecons->setText("Echec");
    }
}

void MainWindow::on_Retour_pms_clicked()
{
    ui->messageecons->setText("");
    ui->messageajout->setText("");
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_Excelexport_clicked()
{

    int prix = ui->prixaexport->text().toInt();
    int nvprix = prix / 12;
    //int fac[12] = {nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix};
    faciliter f(nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix, nvprix);
    bool test = f.ajouterFacil();
    if (test) {
        ui->faciliter->setModel(f.afficherFaciliter());
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->faciliter);
//janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre;
        //colums to export
        obj.addField(0, "janvier", "char(20)");
        obj.addField(1, "fevrier", "char(20)");
        obj.addField(2, "mars", "char(20)");
        obj.addField(3, "avril", "char(20)");
        obj.addField(4, "mai", "char(20)");
        obj.addField(5, "juin", "char(20)");
        obj.addField(6, "juillet", "char(20)");
        obj.addField(7, "aout", "char(20)");
        obj.addField(8, "septembre", "char(20)");
        obj.addField(9, "octobre", "char(20)");
        obj.addField(10, "novembre", "char(20)");
        obj.addField(11, "decembre", "char(20)");





        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("Exportation paiement par facilité avec succée")).arg(retVal)
                                     );
            bool test2 = f.supprimerFaciliter(nvprix);
            if (test2) {

            }
        }

}


void MainWindow::on_changelanguage_clicked()
{
    ui->ajouter1_btn->setText("Add client");
    ui->Statistiques_btn->setText("Statistics");
    ui->recherchecl->setText("Search");
    ui->supprimer_btn->setText("Delete a client");
    ui->modifier_btn->setText("Modify a client");
    ui->PM->setText("Thank you points");
    ui->Excelexport->setText("Export to excel");
    ui->les_id->setText("Client first name");
    ui->label_4->setText("Address");
    ui->label->setText("Client second name");
    ui->ajouter_client->setText("Add client");
    ui->les_id_2->setText("Add a client");
    ui->suppressionreparation->setText("Delete a client");
    ui->les_id_3->setText("Enter the client's ID to delete");
    ui->supprimer_btn_2->setText( "Delete the client");
    ui->modifier_text->setText("Modify a client");
    ui->entrer_id_txt->setText("Enter the client's ID to modify");
    ui->aller_modifier_client->setText("Modify client");
    ui->Modifier_text->setText("Modify client");
    ui->dates_3->setText("Client first name");
    ui->etat_3->setText("Client second name");
    ui->label_11->setText("TY points");
    ui->modifier_text_2->setText("Statistics");
    ui->entrer_id_txt_2->setText("Total number of clients");
    ui->label_8->setText("Last client added");
    ui->Retour_5->setText("Back");
    ui->pm_management->setText("Thank you points");
    ui->entrer_id_txt_3->setText("TY points to add");
    ui->label_9->setText("TY points to consume");
    ui->Ajouter->setText("ADD");
    ui->Consommer->setText("CONSUME");
    ui->Retour_pms->setText("Back");
    ui->modifier_btn_3->setText("Modify");
}

void MainWindow::on_changefr_clicked()
{
    ui->ajouter1_btn->setText("Ajouter");
    ui->Statistiques_btn->setText("Statistiques");
    ui->recherchecl->setText("Recherche");
    ui->supprimer_btn->setText("Supprimer");
    ui->modifier_btn->setText("Modifer");
    ui->PM->setText("Points merci");
    ui->Excelexport->setText("Expoter a excel");
    ui->les_id->setText("Nom");
    ui->label_4->setText("Address");
    ui->label->setText("Prenom");
    ui->ajouter_client->setText("Ajouter un client");
    ui->les_id_2->setText("Ajouter");
    ui->suppressionreparation->setText("Supprimer un client");
    ui->les_id_3->setText("Entrer l'id du client a supprimer");
    ui->supprimer_btn_2->setText("Supprimer");
    ui->modifier_text->setText("Modifier un client");
    ui->entrer_id_txt->setText("Entrer l'id du client a modifier");
    ui->aller_modifier_client->setText("Modifier");
    ui->Modifier_text->setText("Modifier le client");
    ui->dates_3->setText("Nom");
    ui->etat_3->setText("Prenom");
    ui->label_11->setText("Points merci:");
    ui->modifier_text_2->setText("Statistiques");
    ui->entrer_id_txt_2->setText("Nombre total des clients");
    ui->label_8->setText("Derniere client ajouté");
    ui->Retour_5->setText("Retour");
    ui->pm_management->setText("Points merci");
    ui->entrer_id_txt_3->setText("Points merci a ajouter");
    ui->label_9->setText("Points merci a consommer");
    ui->Ajouter->setText("Ajouter!");
    ui->Consommer->setText("Consommer!");
    ui->Retour_pms->setText("Retour");
    ui->modifier_btn_3->setText("Modifier");
}
