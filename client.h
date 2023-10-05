#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
//#include "ui_mainwindow.h"


class Client
{
    int Id ,Tel;
    QString Nom , Email,Prenom,image;
 //   Ui::MainWindow *ui;

public:
    Client();
     Client(int Id,QString Nom,QString Email,int Tel,QString image )    ;
    int get_id();
    int get_tel() ;
    QString get_nom()  ;
    QString get_prenom() ;
    QString get_email() ;
    void set_id(int x)  ;
    void set_tel(int x)  ;

    void set_prenom(QString ch)  ;
    void set_nom(QString ch)  ;
    void set_email(QString ch)  ;
    bool ajouter() ;
    QSqlQueryModel *  afficher()  ;
bool supprimer(int);
bool chercherParCin()  ;
int verificationID() ;
bool modifier(int id)    ;
QSqlQueryModel* Trier(QString critere) ;
QSqlQueryModel * rechercher(int id)     ;//OK
QSqlQueryModel *search (int type, QString key)   ;
QSqlQueryModel * Recherche(QString a);

bool testmail(QString mail) ;

private slots:
void on_Browse_img_clicked();
};

#endif // CLIENT_H
