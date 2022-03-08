#include "employees.h"

Employees::Employees(QString nom, QString prenom, QString job, int salaire)
{
    this->nom=nom;
    this->prenom=prenom;
    this->job=job;
    this->salaire=salaire;

}

bool Employees::ajouter_emp()
{
    QSqlQuery query;

    query.prepare("Insert into employee(nom, prenom, job, salaire)"
                  "Values( :nom, :prenom, :job, :salaire)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":job", job);
    query.bindValue(":salaire", salaire);

    return query.exec();
}


//********************************************
bool Employees::employeExists(int id_em)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_em FROM employee WHERE id_em =:id_em");
    checkQuery.bindValue(":id_em", id_em);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        //qDebug() << "Employee not found";
    }

    return exists;
}//************************************************






bool Employees::supprimer_emp(int id)
{

    bool success = false;

    QSqlQuery query;
    QString id_emp = QString::number(id);



    if (employeExists(id))
    {
    query.prepare("Delete from employee where id_em=:id_em");
    query.bindValue(":id_em",id);
    success = query.exec();
    //if(!success)
             //  qDebug() << "Delete employee failure";
          // else
             //  qDebug() << "employee successfully deleted" << id;
    }
    else
        {
            //qDebug() << "Error deleting employee: employee does not exist";
        }

        return success;


}


QSqlQueryModel * Employees::afficher_emp()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from employee ");

//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Job"));
//    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));

    return model ;
}

//update_empInput




QSqlQuery Employees::afficherEmp(int id_em)
{
    QSqlQuery query;
    query.prepare("select * from employee where id_em=:id_em");
    query.bindValue(":id_em",id_em);

    query.exec();
    return query;
}

bool Employees::updateEmp(int id_em)
{
    QSqlQuery query;
    query.prepare("update employee set nom=:nom, prenom=:prenom, job=:job, salaire=:salaire where id_em=:id_em");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":job",job);
    query.bindValue(":salaire",salaire);
    query.bindValue(":id_em",id_em);

    return query.exec();


}



