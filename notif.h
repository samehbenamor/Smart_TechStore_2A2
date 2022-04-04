#ifndef NOTIF_H
#define NOTIF_H
#include <QSystemTrayIcon>
#include<QString>

class notif
{
public:
    notif();
    notif(QString,QString);
    void afficher();
private:
    int num;
    QString text,titre;
};

#endif // NOTIF_H

