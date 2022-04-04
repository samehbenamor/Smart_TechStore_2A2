#include "gestion_emp.h"
#include "ui_gestion_emp.h"
#include "employees.h"
#include "statistique_emp.h"
#include "historique.h"

#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include<QFileDialog>
#include <QTextStream>
historique H ;
Gestion_emp::Gestion_emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_emp)
{
    ui->setupUi(this);

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


}

Gestion_emp::~Gestion_emp()
{
    delete ui;
}

void Gestion_emp::on_ajouter_emp_clicked()
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

void Gestion_emp::on_supprimer_emp_clicked()
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

void Gestion_emp::on_voir_btnemp_clicked()
{
    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees emp(nom,  prenom, job, salaire);

    QString trieOption=ui->empComboBox->currentText();
     ui->table_emp->setModel(emp.trierEmp(trieOption));
}


void Gestion_emp::on_modifier_btn_emp_2_clicked()
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


void Gestion_emp::on_modifier_btnSet_clicked()
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


void Gestion_emp::on_clear_empBtn_clicked()
{
    ui->nom_input->setText("");
    ui->prenom_input->setText("");
    //ui->job_input->setText("");
    ui->jobComboBox->setCurrentText("");
    ui->salaire_input->setText("");
    ui->update_empInput->setText("");
}


void Gestion_emp::on_excelBtn_clicked()
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




void Gestion_emp::on_recherche_emp_textChanged(const QString &arg1)
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



void Gestion_emp::on_trier_empBtn_clicked()
{
    on_voir_btnemp_clicked();
}

void Gestion_emp::on_Statistiques_empBtn_clicked()
{

   Statistique_emp *statistique = new Statistique_emp();

    statistique->show();
}

void Gestion_emp::on_archiver_emp_clicked()
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

/*void Gestion_emp::on_pb_historique_clicked()
{
    {
        QString searchString = ui->Historique->text();
           QTextDocument *document = ui->texthistor->document();
          ouvriremploye();
           bool found = false;

           document->undo();

           if (searchString.isEmpty()) {
               QMessageBox::information(this, tr("Empty Search Field"),
                                        tr("The search field is empty. "
                                           "Please enter a word and click Find."));
           } else {
               QTextCursor highlightCursor(document);
               QTextCursor cursor(document);

               cursor.beginEditBlock();


               QTextCharFormat plainFormat(highlightCursor.charFormat());
               QTextCharFormat colorFormat = plainFormat;
               colorFormat.setForeground(Qt::red);

               while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
                   highlightCursor = document->find(searchString, highlightCursor,
                                                    QTextDocument::FindWholeWords);

                   if (!highlightCursor.isNull()) {
                       found = true;
                       highlightCursor.movePosition(QTextCursor::WordRight,
                                                    QTextCursor::KeepAnchor);
                       highlightCursor.mergeCharFormat(colorFormat);

                   }
               }


               cursor.endEditBlock();

    }
}
}*/

void Gestion_emp::on_Franais_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->ajouter_emp->setText ("Ajouter");
    ui->voir_btnemp->setText ("voir");
    ui->clear_empBtn->setText ("effacer");
     ui->recherche_emp->setText ("Recherche");
      ui->modifier_btnSet->setText ("modifier");
       ui->supprimer_emp->setText ("supprimer");
       ui->trier_empBtn->setText ("trier");

       ui->Historique->setText ("historique");
         ui->ajouter_emp->setText ("statistique");


}

void Gestion_emp::on_English_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->ajouter_emp->setText ("ADD");
    ui->voir_btnemp->setText ("SEE");
    ui->clear_empBtn->setText ("CLEAR");
     ui->recherche_emp->setText ("SEARCH");
      ui->modifier_btnSet->setText ("UPDATE");
       ui->supprimer_emp->setText ("DELETE");
       ui->trier_empBtn->setText ("SORT");

       ui->Historique->setText ("history");
         ui->ajouter_emp->setText ("statistics");
}

void Gestion_emp::on_texthistor_activated(const QModelIndex &index)
{
    // ui->table-emp->setModel(tmpclient.recherche(arg1));
}


