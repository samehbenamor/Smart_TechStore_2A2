#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVBoxLayout>


class Employees
{
    int id_em;
    QString nom;
    QString prenom;
    QString job;
    int salaire;

public:
    Employees();
    Employees(QString nom, QString prenom, QString job, int salaire);

    int getId_em(){return id_em; }
    void setId_em(int id_em){ this->id_em = id_em; }

    bool ajouter_emp();
    QSqlQueryModel *afficher_emp();

    bool employeExists( int id_em);
    bool supprimer_emp(int id);


    QSqlQuery afficherEmp(int id_em);
    bool updateEmp(int id);

    QSqlQueryModel *rechercherEmp(QString chaine);
    QSqlQueryModel *trierEmp(QString test);
    bool archiver_emp(int id);
    QSqlQueryModel *afficherListe_empArchivee();
    int statistiqueEmp(QString job);
     void verif_mdp_arduino();



};

#endif // EMPLOYEES_H
