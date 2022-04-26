#include "coupon.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
coupon::coupon(QString id_coupon, int reduc)
{
    this->id_coupon=id_coupon;
    this->reduc=reduc;
}

int coupon::getreduction(QString id_coupon) {
    QSqlQuery query;
    query.prepare("select reduction from coupon where id_coupon=:id_coupon");
    query.bindValue(":id_coupon",id_coupon);
    query.exec();
    query.first();
    int reduction = query.value(0).toInt();
    return   reduction;
}
