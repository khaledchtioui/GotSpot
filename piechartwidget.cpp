#include "piechartwidget.h"
#include <QPainter>
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
#include "facteur.h"
QT_CHARTS_USE_NAMESPACE
PieChartWidget::PieChartWidget(QWidget *parent) : QWidget(parent)
{

}

void PieChartWidget::paintEvent(QPaintEvent *)
{

    QSqlQuery query;
      QVector <QPieSlice *> tab;
         QPieSeries *series = new QPieSeries();
    int tous=0;
    int cheque=0;
    int espece=0;
    int ch=0 ;
    query.prepare("select * from FACTURE ");
    if (query.exec())
    {

        while (query.next())
        {

tous++;
if (query.value(2) =="cheque")
{
 cheque++;
}
else if(query.value(2)=="espece")
{
  espece++;
}
else {
ch++ ;
}
        }
    }

qDebug () << "payment par cheque" << cheque;
       qDebug () << "payment par espece" << espece;
       qDebug () << "autre payment" << ch;
       float testing1 =(cheque*100)/tous;
       QString pleasework = QString::number(testing1);
       float testing2 =(espece*100)/tous;
       QString pleasework1 = QString::number(testing2);
        float testing3 ;
       if(ch==0){
           testing3 =0 ;
       }else {
           testing3 =100-(testing1+testing2) ;//(ch*100)/tous;
        }

       QString pleasework2 = QString::number(testing3);
       series ->append("Payment par cheque: "+pleasework+"%",(cheque));
           series ->append(" Payment par espece: "+pleasework1+"%",(espece));
           series ->append("Autre payment: "+pleasework2+"%",(ch));
           QPieSlice * slice0= series->slices().at(0);
           slice0->setLabelVisible();
           QPieSlice * slice1= series->slices().at(1);
           slice1->setLabelVisible();
           QPieSlice * slice2= series->slices().at(2);
           slice2->setLabelVisible();
           if (cheque>espece)
           {

              slice0->setExploded();
               slice0->setPen(QPen(Qt::white,3));
              slice0->setBrush(Qt::red);

           }
           else if(cheque<espece)
           {

        slice1->setExploded();
         slice1->setPen(QPen(Qt::white,3));
        slice1->setBrush(Qt::red);
           }
           else if((cheque>ch)){
               slice0->setExploded();
                slice0->setPen(QPen(Qt::white,3));
               slice0->setBrush(Qt::red);
           }
           else if (cheque<ch){
               slice2->setExploded();
                slice2->setPen(QPen(Qt::white,3));
               slice2->setBrush(Qt::red);
           }
           else if (espece<ch){
               slice2->setExploded();
                slice2->setPen(QPen(Qt::white,3));
               slice2->setBrush(Qt::red);
           }
           else if(ch<espece){
               slice1->setExploded();
                slice1->setPen(QPen(Qt::white,3));
               slice1->setBrush(Qt::red);
           }





           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setTitle("FACTURE : ");
           chart->legend()->hide();
           chart->setBackgroundBrush(QColor(Qt::transparent));



                       QChartView *chartview = new QChartView (chart);
               chartview->setRenderHint(QPainter::Antialiasing);
               QGridLayout *mainLayout = new QGridLayout;
                   mainLayout->addWidget(chartview, 1, 1);
                   setLayout(mainLayout);
                    chartview->setBackgroundBrush(QColor(255, 255, 255, 0));

}

