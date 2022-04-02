#ifndef COMMANDES_H
#define COMMANDES_H
#include <QDate>
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
using namespace std;
class Commandes
{
    int id_co,etatc,id_c;
    QString datec;
    QString localisation;
    QString ville;
public:
    // functions
    Commandes(){};
    Commandes(int,QString,QString,int,int,QString);
   bool AjouterCommandes();
   bool SupprimerCommandes(int);
   QSqlQueryModel * afficher();
   bool modifierCommandes(int,QString,QString,int,int);
   QSqlQueryModel * StatsCommandes(int);
   bool coupon();
   void facture();
   QSqlQuery rechercherCommandes(int);
   QSqlQuery rechercherCommandesByAdresse(QString);
   bool rechercherClients(int);
   QSqlQueryModel * Recherche(int,QString);
   //getters
   int getId_co(){return this->id_co;};
   int getId_C(){return this->id_c;};
   int Etatc(){return this->etatc;};
   QString Datec(){return this->datec;};
   QString Localisation(){return this->localisation;};
   //setters
   void setId_co(int id){this->id_co=id;};
   void setId_C(int id){this->id_c=id;};
   void setEtatc(int etat){this->etatc=etat;};
   void setDatec(QString d){this->datec=d;};
   void setLocalisation(QString l){this->localisation=l;};
};

#endif // COMMANDES_H
