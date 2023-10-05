#include "mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include <QDebug>
#include "first.h"
#include <QMessageBox>
#include <connection.h>
#include <facteur.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c ;
    Facteur fact;
    bool test=c.createconnect() ;
    MainWindow w;
    //w.show();
    First f;
    if(test){
        w.show();
        QMessageBox::information(nullptr,QObject::tr("database is open"),QObject::tr("connection successful\n""Click Cancel to exit."), QMessageBox::Cancel );

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("database is open"),QObject::tr("connection failed\n""Click Cancel to exit."), QMessageBox::Cancel );
    }


    return a.exec();
}
