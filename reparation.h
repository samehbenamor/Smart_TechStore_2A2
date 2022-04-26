#ifndef REPARATION_H
#define REPARATION_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QString>

class Reparation
{
private:

    int id_rep,etat;
    QString image_rep,date_start,date_end;

    //FOREIGN KEYS
    int id_em,id_c;

public:

    //CONSTRUCTEURS
    Reparation(){};
    Reparation(int id_rep,int etat,QString image_rep,QString date_end,QString date_start,int id_em,int id_c);
    Reparation(int id_rep,int etat,QString date_end,QString date_start,int id_em,int id_c);
    Reparation(int id_rep,QString image_rep);




    //GETTERS*********************************
    QString getdate_end(){return date_end;}
    QString getdate_start(){return date_start;}
    QString getimage_rep(){return image_rep;}
    int getid_rep(){return id_rep;}
    int getetat(){return etat;}

    int getid_em(){return id_em;}
    int getid_c(){return id_c;}
    //****************************************




    //SETTERS***********************************************************
    void setdate_end(QString date_end){this->date_end=date_end;}
    void setdate_start(QString date_start){this->date_end=date_start;}
    void setimage_rep(QString image_rep){this->image_rep= image_rep;}
    void setid_rep(int id_rep){this->id_rep=id_rep;}
    void setetat(int etat){this->etat=etat;}

    void setid_em(int id_em){this->id_em=id_em;}
    void setid_c(int id_c){this->id_c=id_c;}
    //******************************************************************




    //FONCTIONS
    bool ajouter();
    bool supprimer(int id_rep);
    QSqlQueryModel * afficher();
    bool modifier();
    bool rechercherClients(int i);
    bool rechercherEmploye(int e);
    bool rechercherReparation(int r);
    QSqlQuery rechercherReparation2(int i);
    QSqlQueryModel * rechercher(int id_rep);
    QSqlQueryModel * statistic1();
    QSqlQueryModel * statistic2();
    QSqlQueryModel * statistic3();
    QSqlQueryModel * Recherche(int k,QString type);
    bool ajouterimage(int id_rep,QString image_rep);



};

#endif // REPARATION_H
