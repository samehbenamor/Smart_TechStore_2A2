#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class client
{

    QString nom, prenom, address;
    int id_c, points_merci;

public:
    //Constructeurs
        client() {}
        client(int, QString, QString, QString, int);

    //Getters
        //Strings
        QString getNom_C(){return nom;}
        QString getPrenom(){return prenom;}
        QString getAddress(){return address;}

        //Int
        int getIdC(){return id_c;}
        int getPM(){return points_merci;}

    //Setters
        //Strings
        void setNom_C(QString nom2){nom = nom2;}
        void setPrenom(QString pr){prenom = pr;}
        void setAddress(QString add){address = add;}

        //Int
        void setIdC(int id){id_c = id;}
        void setPM(int PM){points_merci = PM;}


        //Float


    //Fonctionalités de Base relatives à l'entite Produit
        bool ajouterClient();
        QSqlQueryModel * afficherClient();
        bool supprimerClient(int);
        QSqlQuery rechercherClient(int);
        bool modifierClient();
        QSqlQuery NbClient(); //nombre clients
         QSqlQueryModel * afficherLatestCl(); //derniere client ajouté

         QSqlQueryModel * afficherRechercheCl(QString re); //aff tab de recherche



        bool ajouterpm(int id, int pm); //
        bool consommerpm(int id, int pm); //
};

#endif // PRODUIT_H
