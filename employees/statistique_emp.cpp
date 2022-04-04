#include "statistique_emp.h"
#include "ui_statistique_emp.h"
#include "employees.h"


Statistique_emp::Statistique_emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistique_emp)
{
    ui->setupUi(this);

    on_statEmp_clicked();
}

Statistique_emp::~Statistique_emp()
{
    delete ui;
}


//********************************afficher statistique graphe***************************************************


void Statistique_emp::on_statEmp_clicked()
{

    QBarSet *set1 = new QBarSet("Nombre des employés");

    QString nom="";
    QString prenom="";
    QString job="";
    int salaire=0;


    Employees emp(nom,  prenom, job, salaire);

    *set1 <<  emp.statistiqueEmp("Responsable commandes")
          <<  emp.statistiqueEmp("Responsable reparations")
          <<  emp.statistiqueEmp("Gestion des produits")
          <<  emp.statistiqueEmp("service client") ;

      //  qDebug()<< emp.statistiqueEmp("Responsable commandes");



        QBarSeries *series = new QBarSeries();

        series->append(set1);

        QColor color(0x6568F3);//*******************
        set1->setColor(color);


        QChart *chart = new QChart();




            chart->addSeries(series);
            chart->setTitle("");
            chart->setAnimationOptions(QChart::SeriesAnimations);

            QColor bgColor(Qt::white);
               chart->setBackgroundBrush(QBrush(QColor(bgColor)));

               chart->setBackgroundVisible(true);

          //     chart->setBackgroundVisible(false);




            QStringList categories;
            categories << "R.commandes" << "R.réparations" << "G.produits" << "service client" ;
            QBarCategoryAxis *axis = new QBarCategoryAxis();


            axis->append(categories);

            chart->createDefaultAxes();
            chart->setAxisX(axis, series);

            chart->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);



            QChartView *chartView = new QChartView(chart);

            chartView->setRenderHint(QPainter::Antialiasing);
            QPalette pal = qApp->palette();
            pal.setColor(QPalette::WindowText, QRgb(0x6568F3));
            pal.setColor(QPalette::Window, QRgb(0x6568F3));
            qApp->setPalette(pal);

            chartView->setMaximumWidth(550);
            chartView->setMaximumHeight(290);



            chartView->setParent(ui->horizontalFrame);
         //   chartView->update();
            chartView->show();

     //end statistique

}

