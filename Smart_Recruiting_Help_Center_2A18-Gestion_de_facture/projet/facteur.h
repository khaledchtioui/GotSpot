#ifndef FACTEUR_H
#define FACTEUR_H

#include<QDate>
#include<QSqlQueryModel>
#include <QDateEdit>
#include <QString>
class Facteur
{
public:
    Facteur();
    Facteur(int,QDate,QString,QString,float);
    int getref(){
        return ref ;
    }
    /*int getid_empl(){
        return id_employe ;
    }*/
    QString getid_rem(){
        return remise ;
    }
    QString getid_type(){
        return type ;
    }
    QDate getdate(){
        return datefact ;
    }
    float getmontant(){
        return montant;
    }
    void setref(int reference){
        ref=reference ;
    }
    /*void setid_employe(int id_emp){
        id_employe=id_emp ;
    }*/
    void setremise(QString remis){
         remise=remis ;
    }
    void settype(QString typee){
         type=typee ;
    }
    void setdate(QDate Date){
        datefact=Date ;
    }
    void setmontant(float mon){
        montant=mon ;
    }
    bool ajout() ;
    QSqlQueryModel* afficher() ;
    bool supprimer(int) ;
    bool modifier() ;
    bool cherhceparef() ;
    QSqlQueryModel* trier_date() ;
    QSqlQueryModel* trier_type() ;
    QSqlQueryModel* rechercher(int) ;
    QSqlQueryModel* calcul() ;
    QSqlQueryModel* lister2() ;
    QStringList lister() ;
    QStringList lister_type() ;



private:
    int ref ;
    QDate datefact ;
    float montant ;
    QString remise ;
    QString type ; // type
};

#endif // FACTEUR_H
