#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reparation.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Reper.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ****************************************************************************************************** */
void MainWindow::on_Login_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_reparations_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_Retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Retour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_supprimer_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_Retour_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_ajouter1_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_Retour_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_modifier_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_Retour_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableView->setModel(Reper.afficher());
}

void MainWindow::on_Retour_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Reper.afficher());
}

/* ******************************************************************************************************************************************** */

void MainWindow::on_ajouter_btn_clicked()
{
    //qDebug("%s",qUtf8Printable(image_rep));
    //qDebug("%s", qUtf8Printable(date_end));
    //qDebug("%s", qUtf8Printable(date_start));


    //recupération des informations saisies dans les champs
            int id_rep =ui->id_rep_txt->text().toInt();
            int id_c=ui->id_c_txt->text().toInt();
            int id_em=ui->id_em_txt->text().toInt();
            int etat =ui->etat_txt->text().toInt();
            QString image_rep=ui->image_rep_lol->text();

    //dates*************************************************
            QDate dateend=ui->date_end_QDate->date();
            QDate datestart=ui->date_start_QDate->date();
            QString date_end = dateend.toString();
            QString date_start = datestart.toString();
    //******************************************************

            Reparation Rep( id_rep, etat, image_rep, date_end, date_start, id_em, id_c);

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

            }else if (image_rep==""){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer image\n"), QMessageBox::Cancel);

            }else if (image_rep!="oui" && image_rep!="non"){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("IMAGE : Entrer 'oui' si vouz avez entrer des images pour la reparation sinon 'non'\n"), QMessageBox::Cancel);

            }else{
                bool test=Rep.ajouter();
                if(test){
                        //refresh
                        ui->tableView->setModel(Reper.afficher());

                        QMessageBox :: information (nullptr, QObject::tr("ok"),
                                    QObject::tr("Ajout effectué\n"), QMessageBox::Cancel);

                        ui->stackedWidget->setCurrentIndex(2);

                    }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                                    QObject::tr("Ajout non effectué\n"), QMessageBox::Cancel);
            }
}


/* ******************************************************************************************************************************************** */


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
                 ui->tableView->setModel(Reper.afficher());

                 QMessageBox :: information (nullptr, QObject::tr("ok"),
                            QObject::tr("Suppression effectué\n"), QMessageBox::Cancel);

                 ui->stackedWidget->setCurrentIndex(2);

            }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                             QObject::tr("Suppression non effectué\n"), QMessageBox::Cancel);

            }else if(k==0){
                            QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                                        QObject::tr("ID REPARATION INTROUVABLE\n"), QMessageBox::Cancel);
            }
}


/* ******************************************************************************************************************************************** */



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
        ui->stackedWidget->setCurrentIndex(6);


        //afficher les infos du reparation avec l'id entrer en parametre
        query = Reper.rechercherReparation2(id_rep);
        query.first();
        ui->image_rep_lol_3->setText(query.value(1).toString());
        ui->etat_txt_3->setText(query.value(2).toString());
        ui->id_em_txt_3->setText(query.value(5).toString());
        ui->id_c_txt_3->setText(query.value(6).toString());
        //dates*********************************************************
        //ui->date_end_QDate_3->setDate(query.value(3).toString());
        //ui->date_start_QDate_3->setText(query.value(4).toString());


        //refresh
        ui->tableView->setModel(Reper.afficher());
    }

    return id_rep;
}


void MainWindow::on_modifier_btn_3_clicked()
{
    //recupération des informations saisies dans les champs
            int id_c=ui->id_c_txt_3->text().toInt();
            int id_em=ui->id_em_txt_3->text().toInt();
            int etat =ui->etat_txt_3->text().toInt();
            QString image_rep=ui->image_rep_lol_3->text();

    //dates*************************************************
            QDate dateend=ui->date_end_QDate_3->date();
            QDate datestart=ui->date_start_QDate_3->date();
            QString date_end = dateend.toString();
            QString date_start = datestart.toString();
    //******************************************************

            int id_rep=on_aller_modifier_clicked();
            Reparation Rep1( id_rep, etat, image_rep, date_end, date_start, id_em, id_c);
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

            }else if (image_rep==""){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("Entrer image\n"), QMessageBox::Cancel);

            }else if (image_rep!="oui" && image_rep!="non"){
                QMessageBox :: information (nullptr, QObject::tr("Probleme"),
                            QObject::tr("IMAGE : Entrer 'oui' si vouz avez entrer des images pour la reparation sinon 'non'\n"), QMessageBox::Cancel);

            }else{

                if(test){
                    //refresh
                    ui->tableView->setModel(Reper.afficher());

                    QMessageBox :: information (nullptr, QObject::tr("ok"),
                                QObject::tr("modification reussite\n"), QMessageBox::Cancel);

                    ui->stackedWidget->setCurrentIndex(2);
                }else QMessageBox::critical(nullptr, QObject::tr("non ok"),
                                QObject::tr("echec de modification\n"), QMessageBox::Cancel);
}
}
