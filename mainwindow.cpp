#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "ui_gestion_emp.h"
#include "statistique_emp.h"
#include "arduino.h"
#include "produit.h"
#include "qrcode.h"
#include "excel.h"
#include "notification.h"
#include "reparation.h"
#include "smtp.h"
#include "client.h"
#include "facilter.h"
#include "gestion_emp.h"
#include "commandes.h"
#include "employees.h"
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include<QFileDialog>
#include <QTextStream>
#include <QTime>

#include "reparation.h"
#include <QMessageBox>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPainter>

#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>

#include <QApplication>
#include <QMessageBox>
#include <QDate>
#include <ctype.h>
#include <iostream>
#include <QImage>
#include <QBuffer>
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>

#include "coupon.h"

#include "arduino.h"
// Used to make Pie Charts

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->affichecommandes->setModel(com.afficher());
    ui->TableProduit->setModel(pro.afficher());
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
     //*******************add trie options**************************
         ui->empComboBox->addItem("par défaut");
         ui->empComboBox->addItem("nom");
         ui->empComboBox->addItem("prenom");
         ui->empComboBox->addItem("job");
         ui->empComboBox->addItem("salaire");
     //*******************add trie options***************************


         //*******************add ajouter emp job options**************************
         ui->jobComboBox->addItem("");
         ui->jobComboBox->addItem("Responsable commandes");
             ui->jobComboBox->addItem("Responsable reparations");
             ui->jobComboBox->addItem("Gestion des produits");
             ui->jobComboBox->addItem("service client");
         //*******************add ajouter emp job options***************************




     QString nom="";
     QString prenom="";
     QString job="";
     int salaire=0;


     Employees e(nom,  prenom, job, salaire);


     //ui->table_emp->setModel(e.afficher_emp());
     QString trieOption=ui->empComboBox->currentText();
      ui->table_emp->setModel(e.trierEmp(trieOption));


      ui->TableReparation->setModel(Reper.afficher());

      connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
      connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
      connect(ui->browseBtn_2, SIGNAL(clicked()), this, SLOT(browse()));
      connect(ui->browseBtn_3, SIGNAL(clicked()), this, SLOT(browse2()));


      /* *************CAMERA OPEN AND UPLOAD**************** */
      mCamera = new QCamera(this);
      mCameraViewfinder = new QCameraViewfinder(this);
      mCameraImageCapture = new QCameraImageCapture(mCamera, this);
      mLayout = new QVBoxLayout;
      mOptionMenu = new QMenu ("Opciones", this);
      mLancerAction = new QAction ("Lancer Camera", this);
      mStopperAction = new QAction ("Stopper Camera", this);
      mCapturerAction = new QAction ("Capturer", this);

      mOptionMenu->addActions({ mLancerAction,mStopperAction,
                                 mCapturerAction });
      ui->option_camera1->setMenu(mOptionMenu);
      mCamera->setViewfinder(mCameraViewfinder);
      mLayout->addWidget(mCameraViewfinder);
      ui->scrollArea1->setLayout(mLayout);

      connect(mLancerAction, &QAction::triggered, [&](){
          mCamera->start();
      });

      connect(mStopperAction, &QAction::triggered, [&](){
          mCamera->stop();
      });

      connect(mCapturerAction, &QAction::triggered, [&](){
          auto filename = QFileDialog::getSaveFileName(this, "Capturar", "/",
                                                       "Imagen (*.jpg;*.jpeg");
          if(filename.isEmpty()) {
              return;
          }
          mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
          QImageEncoderSettings imageEncoderSettings;
          imageEncoderSettings.setCodec("image/jpeg");
          imageEncoderSettings.setResolution(1600,1200);
          mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
          mCamera->setCaptureMode(QCamera::CaptureStillImage);
          mCamera->start();
          mCamera->searchAndLock();
          mCameraImageCapture->capture(filename);
          mCamera->unlock();
      });


}

MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie produit///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_produits_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_ajouterproduit_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_Recherche_pr_clicked()
{
    QString re = ui->recherche_prpr->text();
    ui->TableProduit->setModel(pro.afficherRecherche(re));
}

void MainWindow::on_StatsProduit_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_SupprimerProduit_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_ModifierProduit_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_yeah_clicked()
{
    int tabeq=ui->TableProduit->currentIndex().row();
               QVariant idd=ui->TableProduit->model()->data(ui->TableProduit->model()->index(tabeq,0));
               QString id= idd.toString();
               QSqlQuery qry;
               qry.prepare("select * from PRODUIT where ID_PR=:ID_PR");
               qry.bindValue(":ID_PR",id);
               qry.exec();
                  QString  ID_PR,nom,prix,stock,date_impo,description,idpr;

               while(qry.next()){

                   idpr=qry.value(0).toString();
                   nom=qry.value(1).toString();
                   prix=qry.value(2).toString();
                   stock=qry.value(4).toString();

                   date_impo=qry.value(6).toString();
                   description=qry.value(7).toString();



               }
               ID_PR=QString(ID_PR);
                      ID_PR="ID_PR:"+idpr+" NOM:"+nom+" PRIX:"+prix+" STOCK:"+stock+" DATE_IMPO:"+date_impo+" DESCRIPTION:"+description;
               QrCode qr = QrCode::encodeText(ID_PR.toUtf8().constData(), QrCode::Ecc::HIGH);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(300,300);
               ui->qrcodeoutput->setPixmap(QPixmap::fromImage(im));
               //QString path = idpr+".jpeg";
                    //QString imagePath(QStringLiteral("path/image.jpeg"));
                       QByteArray ba;
                       QBuffer buffer(&ba);
                       buffer.open(QIODevice::WriteOnly);
                       im.save(&buffer, "PNG"); // writes image into ba in PNG format
                       QSaveFile file("C:/Users/DELL/Desktop/Qt/qt/QrCode/"+idpr+".png");
                       file.open(QIODevice::WriteOnly);
                       file.write(ba);
                       // Calling commit() is mandatory, otherwise nothing will be written.
                       file.commit();
                       // Now save the directory into a QString and then into the database
                       QString directory = "C:/Users/DELL/Desktop/Qt/qt/QrCode/"+idpr+".png";
                       produit P;
                       bool qrqr = P.UpdateQrcodeLink(directory, id);
                       if (qrqr) {
                           QMessageBox::information(nullptr, QObject::tr("Qr code link succesfully added to the database"),
                                                    QObject::tr("Qr code effectué\n"
                                                                "Click cancel to exit."), QMessageBox::Cancel);
                           ui->TableProduit->setModel(pro.afficher());
                       } else
                       {
                       QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
                       }
}

void MainWindow::on_archiver_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->TableProduit);

        //colums to export
        obj.addField(0, "ID_PR", "char(20)");
        obj.addField(1, "NOM", "char(20)");
        obj.addField(2, "PRIX", "char(20)");
        obj.addField(3, "QR_CODE", "char(50)");
        obj.addField(4, "STOCK", "char(20)");
        obj.addField(4, "IMAGE", "char(20)");
        obj.addField(4, "DATE_IMPO", "char(20)");
        obj.addField(4, "DESCRIPTION", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QString text = "Archivé avec success!";
            QString titre = "Archivage complete!";
            notification c(text, titre);
            c.afficher();
        }
}

void MainWindow::on_coupon_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

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

    if (id_pr == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un id."), QMessageBox::Cancel);
    } else if (stock == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un stock."), QMessageBox::Cancel);
    } else if (prix == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un prix."), QMessageBox::Cancel);
    } else if (nom_pr == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un nom."), QMessageBox::Cancel);
    } else if (date_impo == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un date."), QMessageBox::Cancel);
    } else if (description == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un description."), QMessageBox::Cancel);
    }

    produit P(id_pr, nom_pr, prix, Qr_code, stock, image, date_impo, description);
    bool test = P.ajouterProduit();
    if (test) {
        //Refresh
        ui->LatestPr->setModel(pro.afficherLatest());
        ui->TableProduit->setModel(pro.afficher());
        ui->Restock->setModel(pro.afficherRestock());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_SuppProd_clicked()
{
    int id =ui->id_pr_del->text().toInt();
    bool test=pro.supprimerProduit(id);
    if (test) {
        //Refresh
        ui->TableProduit->setModel(pro.afficher());
        ui->LatestPr->setModel(pro.afficherLatest());
        ui->Restock->setModel(pro.afficherRestock());
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

void MainWindow::on_modifierproduit_clicked()
{
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


    if (id_pr == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un id."), QMessageBox::Cancel);
    } else if (stock == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un stock."), QMessageBox::Cancel);
    } else if (prix == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un prix."), QMessageBox::Cancel);
    } else if (nom == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un nom."), QMessageBox::Cancel);
    } else if (date_impo == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un date."), QMessageBox::Cancel);
    } else if (description == NULL) {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Saisie un description."), QMessageBox::Cancel);
    }


  if(test==true)
  {
      ui->LatestPr->setModel(pro.afficherLatest());
       ui->TableProduit->setModel(pro.afficher());
       ui->Restock->setModel(pro.afficherRestock());
    ui->stackedWidget->setCurrentIndex(4);

  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}


void MainWindow::on_couponre_clicked()
{
    QString id_coupon = ui->couponinput->text();
    coupon c;
    int reduc = c.getreduction(id_coupon);
    QByteArray reduction;
    reduction.setNum(reduc);
    A.write_to_arduino(reduction);
    ui->stackedWidget->setCurrentIndex(2);
}
/*void Employees::verif_mdp_arduino()
{

    data= A.read_from_arduino();
    if (data.length()>=5){
qDebug() << data ;
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from EMPLOYE where IDE="+data);
if (model->rowCount()==0){
    A.write_to_arduino("0");
    data="";
}else{
    QByteArray nom = model->data(model->index(0,1)).toByteArray();
 //   A.write_to_arduino("1");
    A.write_to_arduino("select NOM from EMPLOYE where IDE+="+data);

data="";
}
}
}*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie Client////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::on_AjouterClient_clicked()
{
ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_SuppClient_clicked()
{
ui->stackedWidget->setCurrentIndex(11);
}
void MainWindow::on_clients_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}
void MainWindow::on_ModClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}
void MainWindow::on_Retour_pms_clicked()
{
    ui->messageecons->setText("");
    ui->messageajout->setText("");
    ui->stackedWidget->setCurrentIndex(9);
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
        ui->TableClient->setModel(cl.afficherClient());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimerClient_clicked()
{
    int id =ui->id_cli_supp->text().toInt();
    bool test=cl.supprimerClient(id);
    if (test) {
        //Refresh
        ui->TableClient->setModel(cl.afficherClient());
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
        ui->stackedWidget->setCurrentIndex(13);
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
       ui->TableClient->setModel(C.afficherClient());
    ui->stackedWidget->setCurrentIndex(3);

  }
   else
      QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}


void MainWindow::on_AjouterPM_clicked()
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
    notification c(text, titre);
    /////
    bool test=C.ajouterpm(id_c, pm);
    if (test) {
        //Refresh
        ui->messageajout->setText("Ajout avec success!");
        c.afficher();
        ui->TableClient->setModel(cl.afficherClient());
    }
    else
    {
        ui->messageajout->setText("Echec");
    }
}

void MainWindow::on_PM_clicked()
{
    int tabeq=ui->TableClient->currentIndex().row();
               QVariant idd=ui->TableClient->model()->data(ui->TableClient->model()->index(tabeq,0));
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

void MainWindow::on_ConsommerPM_clicked()
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
    notification c(text, titre);
    ////
    bool test=C.consommerpm(id_c, pm);
    if (test) {
        ui->messageecons->setText("Consommer avec success!");
        c.afficher();
        ui->TableClient->setModel(cl.afficherClient());
    }
    else
    {
        ui->messageecons->setText("Echec");
    }
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie Employee//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_ajouter_emp_clicked()
{
    QString nom=ui->nom_input->text();
    QString prenom=ui->prenom_input->text();
    //QString job=ui->job_input->text();
    int salaire=ui->salaire_input->text().toInt();

    QString job=ui->jobComboBox->currentText();


    Employees emp(nom,  prenom, job, salaire);

    bool test_ajout = emp.ajouter_emp();

    if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        QString trieOption=ui->empComboBox->currentText();
         ui->table_emp->setModel(emp.trierEmp(trieOption));

    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("non effectue\n"
                                               "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_supprimer_emp_clicked()
{
    int id=ui->id_suppInput->text().toInt();

    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees emp(nom,  prenom, job, salaire);


    bool test_supprimer = emp.supprimer_emp(id);
    if(test_supprimer)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" employee successfully deleted\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        QString trieOption=ui->empComboBox->currentText();
         ui->table_emp->setModel(emp.trierEmp(trieOption));
    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("Error deleting employee: employee does not exist\n"
                                               "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_modifier_btnSet_clicked()
{
    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    int id=ui->update_empInput->text().toInt();
    Employees emp(nom,  prenom, job, salaire);

    QSqlQuery empInfo = emp.afficherEmp(id);
    empInfo.next();
    ui->nom_input->setText(empInfo.value(4).toString());
    ui->prenom_input->setText(empInfo.value(3).toString());
//    ui->job_input->setText(empInfo.value(2).toString());
    ui->jobComboBox->setCurrentText(empInfo.value(2).toString());
    ui->salaire_input->setText(empInfo.value(1).toString());
}

void MainWindow::on_modifier_btn_emp_2_clicked()
{
    QString nom=ui->nom_input->text();
    QString prenom=ui->prenom_input->text();
   // QString job=ui->job_input->text();
    int salaire=ui->salaire_input->text().toInt();
    QString job=ui->jobComboBox->currentText();

    int id=ui->update_empInput->text().toInt();
    Employees emp(nom,  prenom, job, salaire);

    bool test_modifier = emp.updateEmp(id);

    if(test_modifier){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("Employee updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        QString trieOption=ui->empComboBox->currentText();
         ui->table_emp->setModel(emp.trierEmp(trieOption));
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Employee not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_clear_empBtn_clicked()
{
    ui->nom_input->setText("");
    ui->prenom_input->setText("");
    //ui->job_input->setText("");
    ui->jobComboBox->setCurrentText("");
    ui->salaire_input->setText("");
    ui->update_empInput->setText("");
}

void MainWindow::on_excelBtn_clicked()
{
    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;

    Employees emp(nom,  prenom, job, salaire);

    QTableView *table= new QTableView;
    table->setModel(emp.afficherListe_empArchivee());


               QString filters("CSV files (*.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");//
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);//d:fenetre d'enrgtr
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {//tc:type de fch
                   QTextStream data(&file);
                   QStringList strList;//separation des chaines


                   for (int i = 0; i < model->columnCount(); i++)
                   {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }

                   data << strList.join(";") << "\n";


                   for (int i = 0; i < model->rowCount(); i++)
                   {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++)
                       {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                   data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                             QObject::tr("Export avec succes .\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }
}

void MainWindow::on_Statistiques_empBtn_clicked()
{
    //Statistique_emp *statistique = new Statistique_emp();

     //statistique->show();
}

void MainWindow::on_recherche_emp_textChanged(const QString &arg1)
{
    QString chaine_c=ui->recherche_emp->text();

    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;

    Employees emp(nom,  prenom, job, salaire);

    if(chaine_c !="")
    {
    ui->table_emp->setModel(emp.rechercherEmp(chaine_c));
    }
    else
    {
        QString trieOption=ui->empComboBox->currentText();
         ui->table_emp->setModel(emp.trierEmp(trieOption));
    }

}

void MainWindow::on_trier_empBtn_clicked()
{
    on_voir_btnemp_clicked();
}

void MainWindow::on_voir_btnemp_clicked()
{
    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees emp(nom,  prenom, job, salaire);

    QString trieOption=ui->empComboBox->currentText();
     ui->table_emp->setModel(emp.trierEmp(trieOption));
}

void MainWindow::on_archiver_emp_clicked()
{
    int id=ui->id_suppInput->text().toInt();

    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees emp(nom,  prenom, job, salaire);


    bool test_archiver = emp.archiver_emp(id);

    if(test_archiver)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("archivage avec succes\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        QString trieOption=ui->empComboBox->currentText();
         ui->table_emp->setModel(emp.trierEmp(trieOption));
    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("Error archivage employee: employee does not exist\n"
                                               "click cancel to exit."),QMessageBox::Cancel);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie commandes///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



void MainWindow::on_ajouterco_clicked()
{
    ui->stackedWidget->setCurrentIndex(17);
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
       //ui->stats->setModel(com.StatsCommandes(1));
       ui->stackedWidget->setCurrentIndex(1);

   }
     else
        QMessageBox::information(nullptr, QObject::tr("NOT BING CHILLING"),QObject::tr("Erreur !"));
   }
}

void MainWindow::on_SuppProd_2_clicked()
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

void MainWindow::on_SuppProd_3_clicked()
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
   ui->stackedWidget->setCurrentIndex(20);
   ui->idcom->setText(query.value(0).toString());
   ui->date->setText(query.value(1).toString());
   ui->localisationM->setText(query.value(2).toString());
   ui->etatm->setText(query.value(3).toString());
   ui->idclientm->setText(query.value(4).toString());
}
}
void MainWindow::on_pushButton_58_clicked()
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

void MainWindow::on_localisation_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_modifercommande_clicked()
{
    ui->stackedWidget->setCurrentIndex(19);
}

void MainWindow::on_statistiquebutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::on_Anuller_clicked()
{
    ui->stackedWidget->setCurrentIndex(16);
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

void MainWindow::on_commandes_clicked()
{
    ui->stackedWidget->setCurrentIndex(16);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie reparation///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(22);
}


void MainWindow::on_ajouter1_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(23);
}

void MainWindow::on_ajouter_btn_clicked()
{
    int id_rep =ui->id_rep_txt->text().toInt();
    int id_c=ui->id_c_txt->text().toInt();
    int id_em=ui->id_em_txt->text().toInt();
    int etat =ui->etat_txt->text().toInt();
    //QString image_rep=ui->image_rep_lol->text();

//dates*************************************************
    QDate dateend=ui->date_end_QDate->date();
    QDate datestart=ui->date_start_QDate->date();
    QString date_end = dateend.toString();
    QString date_start = datestart.toString();
//******************************************************

    Reparation Rep( id_rep, etat, date_end, date_start, id_em, id_c);

    QSqlQuery query;


    if(id_rep==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer id reparation\n"), QMessageBox::Cancel);

    }else if (Rep.rechercherReparation(id_rep)==true){
                    QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                QObject::tr("ID Reparation : existe\n"), QMessageBox::Cancel);

    }else if (id_em==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer id employé\n"), QMessageBox::Cancel);

    }else if (Rep.rechercherEmploye(id_em)==false){
                    QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                QObject::tr("ID Employé : id non existante\n"), QMessageBox::Cancel);

    }else if (id_c==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer id client\n"), QMessageBox::Cancel);

    }else if (Rep.rechercherClients(id_c)==false){
                    QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                QObject::tr("ID Client : id non existante\n"), QMessageBox::Cancel);

    }else if ((etat!=0) && (etat!=1 )){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer etat\n"), QMessageBox::Cancel);

    }else if (etat!=1 && etat!=0){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ETAT: Entrer 0 si la reparation en cours sinon 1\n"), QMessageBox::Cancel);

    }else if (date_end==""){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer date end\n"), QMessageBox::Cancel);

    }else if (date_start==""){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer date start\n"), QMessageBox::Cancel);

    }/*else if (image_rep==""){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("Entrer image\n"), QMessageBox::Cancel);

    }else if (image_rep!="oui" && image_rep!="non"){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("IMAGE : Entrer 'oui' si vouz avez entrer des images pour la reparation sinon 'non'\n"), QMessageBox::Cancel);

    }*/else{
        bool test=Rep.ajouter();
        if(test){
                //refresh
                ui->TableReparation->setModel(Reper.afficher());

                QMessageBox :: information (nullptr, QObject::tr("ok"),
                            QObject::tr("Ajout effectué\n"), QMessageBox::Cancel);

                ui->stackedWidget->setCurrentIndex(22);

            }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                            QObject::tr("Ajout non effectué\n"), QMessageBox::Cancel);
    }
}

void MainWindow::on_Rechercher_btn_4_clicked()
{
    QString type= ui->recherche_text->text();
        if(type !=NULL)
        {
           if(ui->ParEtat->isChecked())
               ui->TableReparation->setModel(Reper.Recherche(3,type));
           else if(ui->ParClient->isChecked())
               ui->TableReparation->setModel(Reper.Recherche(2,type));
           else if(ui->ParId->isChecked())
               ui->TableReparation->setModel(Reper.Recherche(1,type));
        }else if(type==NULL){
            //afficher tous les reparations
            ui->TableReparation->setModel(Reper.afficher());

        }else
            ui->TableReparation->setModel(Reper.afficher());
}

void MainWindow::on_supprimer_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(24);
}

void MainWindow::on_supprimer_btn_2_clicked()
{
    int k=0;
    QSqlQuery query;
    int id_rep=ui->id_rep_suppr->text().toInt();
    bool test=Reper.supprimer(id_rep);


    if(id_rep==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ENTRER ID REPARATION\n"), QMessageBox::Cancel);
    }else if (id_rep==query.prepare("select id_rep from Reparation where id_rep=:id_rep")){
        k=1;
    if(test){
         //refresh
         ui->TableReparation->setModel(Reper.afficher());

         QMessageBox :: information (nullptr, QObject::tr("ok"),
                    QObject::tr("Suppression effectué\n"), QMessageBox::Cancel);

         ui->stackedWidget->setCurrentIndex(22);

    }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                     QObject::tr("Suppression non effectué\n"), QMessageBox::Cancel);

    }else if(k==0){
                    QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                QObject::tr("ID REPARATION INTROUVABLE\n"), QMessageBox::Cancel);
    }
}

void MainWindow::on_notifier_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(27);
}


void MainWindow::on_exitBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::on_ajouter_image_clicked()
{
    ui->stackedWidget->setCurrentIndex(29);
}

void MainWindow::on_done_btn_clicked()
{
        ui->stackedWidget->setCurrentIndex(30);
        ui->TableReparation->setModel(Reper.afficher());

}
void MainWindow::browse2()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_3->setText( fileListString );
}
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_2->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname_2->text(), ui->paswd_2->text(), ui->server_2->text(), ui->port_2->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_Ajouter_clicked()
{
    //********************************************
    int id_rep=on_suivant_clicked();
    QString image_rep=ui->file_3->text();
    Reparation Rep(id_rep,image_rep);
    bool test=Reper.ajouterimage(id_rep,image_rep);
    //********************************************

    if(test){
            //refresh
            ui->TableReparation->setModel(Reper.afficher());

            QMessageBox :: information (nullptr, QObject::tr("ok"),
                        QObject::tr("Ajout effectué\n"), QMessageBox::Cancel);

            ui->stackedWidget->setCurrentIndex(22);

        }else {QMessageBox::critical(nullptr, QObject::tr("non ok"),
                        QObject::tr("Ajout non effectué\n"), QMessageBox::Cancel);
        }
}

int MainWindow::on_suivant_clicked()
{
    int id_rep =ui->id_rep_2->text().toInt();

    QSqlQuery query;

    if(id_rep==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ENTRER ID REPARATION\n"), QMessageBox::Cancel);

    }else if (Reper.rechercherReparation(id_rep)==false){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ID REPARATION INTROUVABLE\n"), QMessageBox::Cancel);

    }else {
        //aller au page suivante pour modifier
        ui->stackedWidget->setCurrentIndex(28);

        //refresh
        ui->TableReparation->setModel(Reper.afficher());
    }

    return id_rep;
}

void MainWindow::on_reparations_clicked()
{
    ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::on_modifier_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(25);
}


int MainWindow::on_aller_modifier_clicked()
{
    int id_rep =ui->id_rep_modifier->text().toInt();

    QSqlQuery query;

    if(id_rep==NULL){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ENTRER ID REPARATION\n"), QMessageBox::Cancel);

    }else if (Reper.rechercherReparation(id_rep)==false){
        QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                    QObject::tr("ID REPARATION INTROUVABLE\n"), QMessageBox::Cancel);

    }else {
        //aller au page suivante pour modifier
        ui->stackedWidget->setCurrentIndex(26);


        //afficher les infos du reparation avec l'id entrer en parametre
        query = Reper.rechercherReparation2(id_rep);
        query.first();
        ui->etat_txt_3->setText(query.value(2).toString());
        ui->id_em_txt_3->setText(query.value(5).toString());
        ui->id_c_txt_3->setText(query.value(6).toString());
        //dates*********************************************************
        //ui->date_end_QDate_3->setDate(query.value(3).toString());
        //ui->date_start_QDate_3->setText(query.value(4).toString());


        //refresh
        ui->TableReparation->setModel(Reper.afficher());
    }

    return id_rep;
}

void MainWindow::on_modifier_btn_4_clicked()
{
    //recupération des informations saisies dans les champs
            int id_c=ui->id_c_txt_3->text().toInt();
            int id_em=ui->id_em_txt_3->text().toInt();
            int etat =ui->etat_txt_3->text().toInt();


    //dates*************************************************
            QDate dateend=ui->date_end_QDate_3->date();
            QDate datestart=ui->date_start_QDate_3->date();
            QString date_end = dateend.toString();
            QString date_start = datestart.toString();
    //******************************************************

            int id_rep=on_aller_modifier_clicked();
            Reparation Rep1( id_rep, etat, date_end, date_start, id_em, id_c);
            bool test=Rep1.modifier();
            QSqlQuery query;


            if (id_em==NULL){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer id employé\n"), QMessageBox::Cancel);

            }else if (Reper.rechercherEmploye(id_em)==false){
                            QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                        QObject::tr("ID Employé : id non existante\n"), QMessageBox::Cancel);

            }else if (id_c==NULL){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer id client\n"), QMessageBox::Cancel);

            }else if (Reper.rechercherClients(id_c)==false){
                            QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                        QObject::tr("ID Client : id non existante\n"), QMessageBox::Cancel);

            }else if ((etat!=0) && (etat!=1 )){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer etat\n"), QMessageBox::Cancel);

            }else if (etat!=1 && etat!=0){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("ETAT: Entrer 0 si la reparation en cours sinon 1\n"), QMessageBox::Cancel);

            }else if (date_end==""){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer date end\n"), QMessageBox::Cancel);

            }else if (date_start==""){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer date start\n"), QMessageBox::Cancel);

            }/*else if (image_rep==""){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer image\n"), QMessageBox::Cancel);

            }else if (image_rep!="oui" && image_rep!="non"){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("IMAGE : Entrer 'oui' si vouz avez entrer des images pour la reparation sinon 'non'\n"), QMessageBox::Cancel);

            }*/else{

                if(test){
                    //refresh
                    ui->TableReparation->setModel(Reper.afficher());

                    QMessageBox :: information (nullptr, QObject::tr("ok"),
                                QObject::tr("modification reussite\n"), QMessageBox::Cancel);

                    ui->stackedWidget->setCurrentIndex(22);
                }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                                QObject::tr("echec de modification\n"), QMessageBox::Cancel);
}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Partie Arduino///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

}
