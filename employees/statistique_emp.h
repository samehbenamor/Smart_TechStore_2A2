#ifndef STATISTIQUE_EMP_H
#define STATISTIQUE_EMP_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

namespace Ui {
class Statistique_emp;
}

class Statistique_emp : public QDialog
{
    Q_OBJECT

public:
    explicit Statistique_emp(QWidget *parent = nullptr);
    ~Statistique_emp();

private slots:
    void on_statEmp_clicked();

private:
    Ui::Statistique_emp *ui;
};

#endif // STATISTIQUE_EMP_H
