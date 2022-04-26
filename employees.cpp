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

    query.prepare("Insert into employee(nom, prenom, job, salaire, ancien)"
                  "Values( :nom, :prenom, :job, :salaire, :ancien)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":job", job);
    query.bindValue(":salaire", salaire);
    query.bindValue(":ancien", 0);

    return query.exec();
}


//********************************************
bool Employees::employeExists(int id_em)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_em FROM employee WHERE id_em =:id_em and ancien =0 ");
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
    }

        return success ;


}


QSqlQueryModel * Employees::afficher_emp()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from employee where ancien =0 ");

//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Job"));
//    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));

    return model ;
}



QSqlQuery Employees::afficherEmp(int id_em)
{
    QSqlQuery query;
    query.prepare("select * from employee where id_em=:id_em and ancien =0 ");
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


//**************************recherche*****************************
QSqlQueryModel * Employees::rechercherEmp(QString chaine)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from employee where ( salaire LIKE'%"+chaine+"%' OR prenom LIKE'%"+chaine+"%' OR nom LIKE'%"+chaine+"%' OR job LIKE'%"+chaine+"%')and (ancien =0)   ");


    return model ;
}

//**************************trie*******************************************
QSqlQueryModel * Employees::trierEmp(QString test)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    if(test == "par défaut"){
        model->setQuery("SELECT * from employee where ancien = 0");
    }
    else if(test =="nom")
    {
        model->setQuery("SELECT * from employee where ancien = 0 order by nom asc ");
    }
    else if(test =="salaire")
    {
        model->setQuery("SELECT * from employee where ancien = 0 order by salaire desc ");
    }
    else if(test =="prenom")
    {
        model->setQuery("SELECT * from employee where ancien = 0 order by prenom asc ");
    }
    else if(test =="job")
    {
        model->setQuery("SELECT * from employee where ancien = 0 order by job asc ");
    }
    return model;
}




bool Employees::archiver_emp(int id)
{

    bool success = false;

    QSqlQuery query;


    if (employeExists(id))
    {
        query.prepare("update employee set ancien=:ancien where id_em=:id_em");
        query.bindValue(":id_em",id);
        query.bindValue(":ancien",1);

        success = query.exec();

     }

        return success ;

}


QSqlQueryModel * Employees::afficherListe_empArchivee()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT id_em,salaire,job,prenom,nom from employee where ancien =1 ");

    return model ;
}


//*******************************statistique Emp********************************************************

int Employees::statistiqueEmp(QString job)
{
    QSqlQuery query;
    query.prepare("select count(*) from employee where ancien=0 and job=:job ");
    query.bindValue(":job",job);
    query.exec();

    int count =-1;

            while(query.next())
                    {
                        count = query.value(0).toInt() ;
                        //qDebug() << "count=" << count ;
                        return count;

                    }

    return count;

}
//arduino
/*
void Employees::verif_mdp_arduino()
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
}

*/
