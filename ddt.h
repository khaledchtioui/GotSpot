#ifndef DDT_H
#define DDT_H
#include <QString>
#include <QDate>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include <QWidget>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QComboBox>

class Ddt
{
public:
    Ddt();
    //////////////////////////////////////////////////////////////////////////////
        /// getter
        //////////////////////////////////////////////////////////////////////////////
    int getCin(){return Cin;}
    int getAge(){return Age;}
    int getNum(){return Num;}
    QString getPrenom(){return Prenom;}
    QString getNOM(){return Nom;}
    QString getNationalite(){return Nationalite;}
    QString getNved(){return nved;}

        //////////////////////////////////////////////////////////////////////////////
        /// setter
        //////////////////////////////////////////////////////////////////////////////
    void setCin(int Cin){this->Cin= Cin;}
    void setAge(int Age){this->Age=Age;}
    void setNum(int Num){this->Num=Num;}
    void setPrenom(QString Prenom){this->Prenom=Prenom;}
    void setNOM(QString NOM){this->Nom= NOM;}
    void setNationalite(QString Nationalite){this->Nationalite= Nationalite;}
    void setNved(QString nved){this->nved=nved;}
        //////////////////////////////////////////////////////////////////////////////
        /// Cruds
        //////////////////////////////////////////////////////////////////////////////
        ////////////afficher//////////
        QSqlQueryModel * afficher();
        ///ajouter///
        bool ajouter(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString nved );
        ///supprimer///
        bool supprimer(int);
      ///modifier///
        bool modifier(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString nved );

        bool verifage(int age);
        bool verifnom(QString);
        bool verifNum(QString n);
        QSqlQueryModel * Rech(QString choix,int id);
        QSqlQueryModel * Rech(QString choix,QString ch);
        QSqlQueryModel * triCin();
        QSqlQueryModel * triAGE();
        QSqlQueryModel * trinom() ;
        void convPDF ();
        QSqlQueryModel * affnot();
        bool ajnot(QString ch );
        void on_Actualiser_clicked();
        bool clear();
private:
    QString Nom, Prenom,Nationalite,nved;
    int Cin ,Age ,Num;
    QByteArray data;
};

#endif // DDT_H
