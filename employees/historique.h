#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

class historique
{
public:
    historique();
    historique(QString);
        void setEtat(QString);

        void ajouter_historique();
        QSqlQueryModel * afficherHistorique();

    private:
        QString etat;
        QDateTime date;

};


#endif // HISTORIQUE_H

