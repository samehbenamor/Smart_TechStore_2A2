#include "gestion_emp.h"
#include "ui_gestion_emp.h"
#include "employees.h"

#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

Gestion_emp::Gestion_emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_emp)
{
    ui->setupUi(this);

    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees e(nom,  prenom, job, salaire);

    ui->table_emp->setModel(e.afficher_emp());

}

Gestion_emp::~Gestion_emp()
{
    delete ui;
}

void Gestion_emp::on_ajouter_emp_clicked()
{
    QString nom=ui->nom_input->text();
    QString prenom=ui->prenom_input->text();
    QString job=ui->job_input->text();
    int salaire=ui->salaire_input->text().toInt();


    Employees emp(nom,  prenom, job, salaire);

    bool test_ajout = emp.ajouter_emp();

    if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        ui->table_emp->setModel(emp.afficher_emp());

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
        ui->table_emp->setModel(emp.afficher_emp());
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

     ui->table_emp->setModel(emp.afficher_emp());
}

void Gestion_emp::on_modifier_btn_emp_2_clicked()
{
    QString nom=ui->nom_input->text();
    QString prenom=ui->prenom_input->text();
    QString job=ui->job_input->text();
    int salaire=ui->salaire_input->text().toInt();

    int id=ui->update_empInput->text().toInt();
    Employees emp(nom,  prenom, job, salaire);

    bool test_modifier = emp.updateEmp(id);

    if(test_modifier){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("Employee updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    ui->table_emp->setModel(emp.afficher_emp());
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
    ui->job_input->setText(empInfo.value(2).toString());
    ui->salaire_input->setText(empInfo.value(1).toString());
}

void Gestion_emp::on_clear_empBtn_clicked()
{
    ui->nom_input->setText("");
    ui->prenom_input->setText("");
    ui->job_input->setText("");
    ui->salaire_input->setText("");
    ui->update_empInput->setText("");
}
