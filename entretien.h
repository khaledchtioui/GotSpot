#ifndef ENTRETIEN_H
#define ENTRETIEN_H

#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTimeEdit>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
class Entretien
{
public:
    Entretien();
    Entretien(QString,QString,QString,int,int,int,QString,QString,QString,QDateTime);
    QString getID();
    QString getnom();
    QString getpre();
    int getage();
    int getcin();
    int getnum();
    QString getetat();
     QString getbloc();
    QString getpost();
    QDateTime getHeure();
    //QDateTime currentDateTime();
    void setID(QString id);
    void setnom(QString n);
    void setpre(QString p);
    void setage(int a );
    void setcin(int c);
    void setnum(int nu);
    void setetat(QString e);
    void setbloc(QString b);
    void setpost(QString po);
    void setHeure(QDateTime hor);
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool update(QString ID);
    bool supprimer(QString ID);
    bool chercherParCin()  ;
    int verificationID() ;
    QSqlQueryModel * trieid();
     QSqlQueryModel * trienom();
     QSqlQueryModel * triehorloge();


    QSqlQueryModel* Trier(QString critere) ;
    void  rechercher(Ui::MainWindow *ui) ;


private :
    int age ,num,cin;
    QString bloc ;
    QString ID,nom,pre,post,etat ;
    QDateTime hor;//=QDateTime::currentDateTime() ;
};

#endif // ENTRETIEN_H
