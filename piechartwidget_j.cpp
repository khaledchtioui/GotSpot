#include "Piechartwidget_j.h"
#include <QPainter>
#include "formation.h"
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QtWidgets/QGridLayout>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
QT_CHARTS_USE_NAMESPACE
Piechartwidget_j::Piechartwidget_j(QWidget *parent) : QWidget(parent)
{

}

void Piechartwidget_j::paintEvent(QPaintEvent *)
{

    QSqlQuery query;
      QVector <QPieSlice *> tab;
         QPieSeries *series = new QPieSeries();
    int Type_formation=0;
    int graphique_Design=0;
    int coding=0;
    int RH=0;
    int autre=0;

    query.prepare("select * from FORMATION ");
    if (query.exec())
    {

        while (query.next())
        {

Type_formation++;
if (query.value(1)=="graphique Design")
{
graphique_Design++;
}
else if (query.value(1)=="coding")
{
  coding++;
}
else if (query.value(1)=="RH")
{
  RH++;
}
else
{
  autre++;
}


        }
    }
    qDebug () <<graphique_Design ;
        qDebug () <<coding ;
        float testing1 =(graphique_Design*100)/Type_formation;
        QString pleasework = QString::number(testing1);


        float testing2 =(coding*100)/Type_formation;
        QString pleasework1 = QString::number(testing2);

         float testing3 =(RH*100)/Type_formation;
          QString pleasework2 = QString::number(testing3);

          float testing4 =(autre*100)/Type_formation;
           QString pleasework3 = QString::number(testing4);

            series ->append("Graphique Design :"+pleasework+"%",(graphique_Design));
            series ->append("Coding :"+pleasework1+"%",(coding));
            series ->append("Coding :"+pleasework2+"%",(RH));
            series ->append("Coding :"+pleasework3+"%",(autre));


            QPieSlice * slice0= series->slices().at(0);
            slice0->setLabelVisible();
            QPieSlice * slice1= series->slices().at(1);
            slice1->setLabelVisible();
            QPieSlice * slice2= series->slices().at(2);
            slice1->setLabelVisible();
            QPieSlice * slice3= series->slices().at(3);
            slice1->setLabelVisible();



            if (Type_formation>coding)
            {

               slice0->setExploded();
                slice0->setPen(QPen(Qt::white,2));
               slice0->setBrush(Qt::red);

            }
            else
            {

         slice1->setExploded();
          slice1->setPen(QPen(Qt::white,2));
         slice1->setBrush(Qt::red);
            }





            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Formation : ");
            chart->legend()->hide();
            chart->setBackgroundBrush(QColor(Qt::transparent));



                        QChartView *chartview = new QChartView (chart);
                chartview->setRenderHint(QPainter::Antialiasing);
                QGridLayout *mainLayout = new QGridLayout;
                    mainLayout->addWidget(chartview, 1, 1);
                    setLayout(mainLayout);
                     chartview->setBackgroundBrush(QColor(255, 255, 255, 0));

}
