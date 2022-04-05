#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QApplication>
#include <QMessageBox>
#include <QDate>
#include <ctype.h>
#include <iostream>
#include <QImage>
#include "qrcode.h"
#include "excel.h"
#include "notification.h"
#include <QBuffer>
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
QT_CHARTS_USE_NAMESPACE

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


void MainWindow::on_ajouter_pro_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
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
        ui->tableView->setModel(pro.afficher());
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


void MainWindow::on_supprimer_btn_2_clicked()
{
    int id =ui->id_pr_del->text().toInt();
    bool test=pro.supprimerProduit(id);
    if (test) {
        //Refresh
        ui->tableView->setModel(pro.afficher());
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

void MainWindow::on_Statistiques_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    //Total number of produits
    QSqlQuery query;
    query=pro.NbProduit();
    query.first();
    ui->nb_pr->setText(query.value(0).toString());
    //Latest produit ajouté
    ui->LatestPr->setModel(pro.afficherLatest());
    //Products to restock
    ui->Restock->setModel(pro.afficherRestock());

}


void MainWindow::on_Recherche_pr_clicked()
{
    QString re = ui->recherche_prpr->text();
    ui->tableView->setModel(pro.afficherRecherche(re));
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
          ui->tableView->setModel(pro.afficher());
          ui->Restock->setModel(pro.afficherRestock());
       ui->stackedWidget->setCurrentIndex(4);

     }
      else
         QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
}


void MainWindow::on_ajouter1_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_ajouter_pro_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_yeah_clicked()
{
    int tabeq=ui->tableView->currentIndex().row();
               QVariant idd=ui->tableView->model()->data(ui->tableView->model()->index(tabeq,0));
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
                           ui->tableView->setModel(pro.afficher());
                       } else
                       {
                       QMessageBox::information(nullptr, QObject::tr("Error"),QObject::tr("failed"));
                       }
}


void MainWindow::on_en_clicked()
{
    ui->ajouter1_btn->setText("Add Product");
    ui->Statistiques_btn->setText("Statistics");
    ui->Recherche_pr->setText("Search");
    ui->supprimer_btn->setText("Delete");
    ui->modifier_btn->setText("Modify");
    ui->les_id->setText("Product name");
    ui->label_3->setText("Import date");
    ui->label->setText("Price");
    ui->ajouter_pro->setText("Add");
    ui->les_id_2->setText("Add a Product");
    ui->suppressionreparation->setText("Delete a product");
    ui->les_id_3->setText("Enter the product's ID to delete");
    ui->supprimer_btn_2->setText("Delete the product");
    ui->modifier_text->setText("Modify a product");
    ui->entrer_id_txt->setText("Enter the product's ID to modify");
    ui->modifier_pr_go->setText("Modify Product");
    ui->Modifier_text->setText("Modify product");
    ui->label_6->setText("Product name");
    ui->label_8->setText("Import date");
    ui->dates_3->setText("Product price");
    ui->modifier_btn_3->setText("Modify");
    ui->yeah->setText("generate QR code");
}

void MainWindow::on_fr_clicked()
{
    ui->ajouter1_btn->setText("Ajouter");
    ui->Statistiques_btn->setText("Statistiques");
    ui->Recherche_pr->setText("Recherche");
    ui->supprimer_btn->setText("Supprimer");
    ui->modifier_btn->setText("Modifier");
    ui->les_id->setText("Nom");
    ui->label_3->setText("Date d'importation");
    ui->label->setText("Prix");
    ui->ajouter_pro->setText("Ajouter");
    ui->les_id_2->setText("Ajouter un produit");
    ui->suppressionreparation->setText("Supprimer un produit");
    ui->les_id_3->setText("Entrer l'id du produit a supprimer");
    ui->supprimer_btn_2->setText("Supprimer le produit");
    ui->modifier_text->setText("Modifier un produit");
    ui->entrer_id_txt->setText("Entrer l'id du produit a modifer");
    ui->modifier_pr_go->setText("Modifier");
    ui->Modifier_text->setText("Modifier");
    ui->label_6->setText("Nom");
    ui->label_8->setText("Date d'importation");
    ui->dates_3->setText("Prix");
    ui->modifier_btn_3->setText("Modifier");
    ui->yeah->setText("Generer QR code");
}

void MainWindow::on_archiver_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tableView);

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
