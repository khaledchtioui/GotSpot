#include "facteur.h"
#include<QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QDateEdit>
#include <iostream>
using namespace std;
Facteur::Facteur()
{
ref=0 ;
//id_employe=0 ;
//QDate date_fact(2000,1,1);
montant=0;
type="" ;
remise="" ;
}
Facteur::Facteur(int ref,QDate date_fact,QString typee ,QString remis ,float mont){
//this->id_employe=id ;
this->ref=ref ;
this->datefact=date_fact ;
this->type=typee ;
this->remise=remis ;
this->montant=mont;
}

bool Facteur::ajout()
{


    QSqlQuery query;
    QString ref_str=QString::number(ref) ;
    QString mont=QString::number(montant) ;

          query.prepare("INSERT INTO FACTURE  (ref, datefact, type ,remise, montant) "
                        "VALUES (:ref, :datefact ,:type ,:remise , :montant)");
          query.bindValue(":ref", ref_str);
          query.bindValue(":datefact",datefact);
          query.bindValue(":type",type);
          query.bindValue(":remise",remise);
          query.bindValue(":montant", mont);


         return query.exec();

}
QSqlQueryModel* Facteur::afficher()
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM FACTURE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("Date"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("Remise"));
          model->setHeaderData(4, Qt::Horizontal,QObject::tr("Montant"));

    return model ;
}

bool Facteur::supprimer(int){
    QSqlQuery query;

          query.prepare("Delete from FACTURE where ref=:ref");
          query.bindValue(0, ref);
         return query.exec();
}


bool Facteur :: modifier()
{
     QSqlQuery query;

       // QString res= QString::number(identifiant);
        QString ref_str=QString::number(ref) ;
        QString mont=QString::number(montant) ;
        //if(dbconopen()){ }
        query.prepare("UPDATE FACTURE SET  ref=:ref ,datefact=:datefact ,type =:type ,remise=:remise ,montant=:montant WHERE ref=:ref");
        query.bindValue(":ref" ,ref_str) ;
        query.bindValue(":datefact", datefact);
        query.bindValue(":type",type);
        query.bindValue(":remise",remise);
        query.bindValue(":montant", mont);



           return    query.exec();

}


bool Facteur::cherhceparef()
{
    QSqlQuery query;
    query.prepare("SELECT * from FACTURE where ref=:ref");
    query.bindValue(":ref", ref);
    query.exec();
    if (query.next())
        {
            ref=(query.value(0).toInt());

        }
        return query.exec();
}


QSqlQueryModel* Facteur::trier_date()
{
    QSqlQuery *q = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  FACTURE ORDER BY datefact ASC ");
    q->exec();
    model->setQuery(*q);
    return model;
}


QSqlQueryModel* Facteur::trier_type()
{
    QSqlQuery *q = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  FACTURE ORDER BY type ASC ");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel* Facteur::rechercher(int ref )
 {

     QSqlQueryModel *model=new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("Select * from FACTURE where ref =:ref");
     query.bindValue(":ref",ref);
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("REF"));

         return model;//*/
 }

QStringList Facteur::lister(){
QSqlQuery q;
q.prepare("select ref from FACTURE");
q.exec();
QStringList l;
while(q.next()){
l<<q.value(0).toString();
}
return l;
}


QSqlQueryModel* Facteur::calcul()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString ch="60%" ;

    ch.resize(ch.size() - 1);
    int i=ch.toInt() ;
    cout<<"ch= " << i <<endl ;
        /*  model->setQuery("SELECT * FROM FACTURE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("Date"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("Remise"));
          model->setHeaderData(4, Qt::Horizontal,QObject::tr("Montant"));*/

    return model ;
}




QSqlQueryModel* Facteur::lister2(){
QSqlQuery q;
q.prepare("select ref,remise,montant from FACTURE");
q.exec();
QStringList l;
while(q.next()){
    QString ch1,ch=q.value(1).toString() ;
    ch.resize(ch.size() - 1);
        int i=ch.toInt() ;
         float f;
         f=f+(f-(f*i)/100) ;
         ch1=f ;
l<<q.value(0).toString()<<q.value(1).toString()<<ch1;
QString str = l.join("");
str = l.join("\t");
QSqlQueryModel* model= new QSqlQueryModel();
//model->setQuery("SELECT ref,remise,montant FROM FACTURE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Remise"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Montant"));
return model ;
}


}
