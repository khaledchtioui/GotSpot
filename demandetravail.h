#ifndef Mainwindow_H
#define Mainwindow_H
#include <QString>
#include <QDate>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include <QWidget>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QComboBox>
//#include "arduino.h"
#include "ddt.h"
#include <QMediaPlayer>

#include <QDialog>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
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
        QSqlQueryModel * triID();
        QSqlQueryModel * triAGE();
        QSqlQueryModel * trinom() ;
        void convPDF ();
        QSqlQueryModel * affhis();
        bool ajhis(QString ch );
        void on_Actualiser_r_clicked();
        bool clear();


private slots:
        void on_Supprimer_r_clicked();



        void on_Ajouter_r_clicked();

    //    void on_Modifier_r_clicked();

        void on_rech_r_clicked();

        void on_tri_r_clicked();

        void on_pushButton_r_clicked();


        void on_clear_r_clicked();

    //    void on_rech_2_r_returnPressed();

        void on_rech_2_r_textChanged(const QString &arg1);

        void on_comboBox_2_r_currentIndexChanged(const QString &arg1);



    //    void on_comboBox_r_currentIndexChanged(const QString &arg1);






        void on_modifier_r_clicked();

        void on_tableView_r_activated(const QModelIndex &index);

private:
    Ui::Mainwindow *ui;
    QString Nom, Prenom,Nationalite,nved;
    int Cin ,Age ,Num;
    QByteArray data;
    Ddt d;
    QMediaPlayer *player = new QMediaPlayer;

};
#endif // Mainwindow_H
