#ifndef EMP_H
#define EMP_H
#include <QString>
#include <QDate>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include <QWidget>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "smtp.h"
#include <QPainter>
//#include "stati1.h"
//#include "ui_stati1.h"

class emp
{
public:
    emp();
    //////////////////////////////////////////////////////////////////////////////
        /// getter
        //////////////////////////////////////////////////////////////////////////////
    int getCin(){return Cin;}
    int getAge(){return Age;}
    int getNum(){return Num;}
    QString getPrenom(){return Prenom;}
    QString getuser(){return user;}
    QString getNOM(){return Nom;}
    QString getNationalite(){return Nationalite;}
    QString getNved(){return Poste;}

        //////////////////////////////////////////////////////////////////////////////
        /// setter
        //////////////////////////////////////////////////////////////////////////////
    void setCin(int Cin){this->Cin= Cin;}
    void setuser(QString user){this->user=user;}
    void setAge(int Age){this->Age=Age;}
    void setNum(int Num){this->Num=Num;}
    void setPrenom(QString Prenom){this->Prenom=Prenom;}
    void setNOM(QString NOM){this->Nom= NOM;}
    void setNationalite(QString Nationalite){this->Nationalite= Nationalite;}
    void setNved(QString Poste){this->Poste= Poste;}
        //////////////////////////////////////////////////////////////////////////////
        /// Cruds
        //////////////////////////////////////////////////////////////////////////////
        ////////////afficher//////////
        QSqlQueryModel * afficher();
        ////////ajouter///////////
        bool ajouter(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Poste,QString user,QString Psw );
        ///////supprimer/////////
        bool supprimer(int);
        //////modifier//////////
        bool modifier(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Poste );
        //////////////////////////////////////////////////////////////////////////////
        bool verifage(int age);
        bool verifnom(QString ch_nom);
        bool verifNum(QString n);
        QSqlQueryModel * Rech(QString choix,QString ch);
        QSqlQueryModel * triID();
        QSqlQueryModel * triAGE();
        void convPDF ();
        bool chat (QString chat,QString USERNAME);
        QSqlQueryModel * trinom() ;
        int log(QString user,QString pass);
        QSqlQueryModel * affchat();
private:
        QString Nom, Prenom,Nationalite,Poste,user;
        int Cin ,Age ,Num;
      //  stati1 s;

};

#endif // EMP_H
