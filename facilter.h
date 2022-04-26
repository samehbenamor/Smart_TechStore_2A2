#ifndef FACILITER_H
#define FACILITER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class faciliter
{
    int janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre;
public:
    faciliter() {}
    faciliter(int, int, int, int, int, int, int, int, int, int, int, int);

    int getjan(){return janvier;}
    int getfev(){return fevrier;}
    int getmars(){return mars;}
    int getavril(){return avril;}
    int getmai(){return mai;}
    int getjuin(){return juin;}
    int getjuillet(){return juillet;}
    int getaout(){return aout;}
    int getsept(){return septembre;}
    int getoct(){return octobre;}
    int getnov(){return novembre;}
    int getdec(){return decembre;}

    void setjan(int ja){janvier = ja;}
    void setfev(int fe){fevrier = fe;}
    void setmars(int ma){mars = ma;}
    void setav(int av){avril = av;}
    void setmai(int ma){mai = ma;}
    void setjui(int ju){juin = ju;}
    void setjuillet(int jui){juillet = jui;}
    void setaout(int ao){aout = ao;}
    void setsept(int sep){septembre = sep;}
    void setoct(int oc){octobre = oc;}
    void setnov(int no){novembre = no;}
    void setdec(int de){decembre = de;}


    bool ajouterFacil();
    QSqlQueryModel * afficherFaciliter();
    bool supprimerFaciliter(int);
};

#endif // FACILITER_H
