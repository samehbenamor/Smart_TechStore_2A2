#ifndef GESTION_EMP_H
#define GESTION_EMP_H

#include <QDialog>
#include <QVBoxLayout>
#include "employees.h"


namespace Ui {
class Gestion_emp;
}

class Gestion_emp : public QDialog
{
    Q_OBJECT

public:
    explicit Gestion_emp(QWidget *parent = nullptr);
    ~Gestion_emp();

private slots:
    void on_ajouter_emp_clicked();

    void on_supprimer_emp_clicked();

    void on_voir_btnemp_clicked();

    void on_modifier_btn_emp_2_clicked();

    void on_modifier_btnSet_clicked();

    void on_clear_empBtn_clicked();

    void on_excelBtn_clicked();

    void on_recherche_emp_textChanged(const QString &arg1);

    void on_trier_empBtn_clicked();

    void on_Statistiques_empBtn_clicked();

    void on_archiver_emp_clicked();

    void on_FR_clicked();

    void on_EN_clicked();

private:
    Ui::Gestion_emp *ui;
   // Employees e;
};

#endif // GESTION_EMP_H


