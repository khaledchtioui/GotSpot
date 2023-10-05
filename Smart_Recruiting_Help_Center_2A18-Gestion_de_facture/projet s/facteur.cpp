#include "facteur.h"
#include<QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QDateEdit>
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
    //QString id_str=QString::number(id_employe) ;
    QString ref_str=QString::number(ref) ;
    QString mont=QString::number(montant) ;
    //QString date_stry=QString::number(date_fact.year()) ;
    //QString date_strm=QString::number(date_fact.month()) ;
    //QString date_strd=QString::number(date_fact.day()) ;

          query.prepare("INSERT INTO GESTION_FACTURE_5  (ref, datefact, type ,remise, montant) "
                        "VALUES (:ref, :datefact ,:type ,:remise , :montant)");
          query.bindValue(":ref", ref_str);
          //query.bindValue(":id_employe", id_str);
          query.bindValue(":datefact",datefact);
          query.bindValue(":type",type);
          query.bindValue(":remise",remise);
          query.bindValue(":montant", mont);


         return query.exec();

}
QSqlQueryModel* Facteur::afficher()
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM GESTION_FACTURE_5");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("Date"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("Remise"));
          model->setHeaderData(4, Qt::Horizontal,QObject::tr("Montant"));

    return model ;
}

bool Facteur::supprimer(int){
    QSqlQuery query;

          query.prepare("Delete from GESTION_FACTURE_5 where ref=:ref");
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
        query.prepare("UPDATE GESTION_FACTURE_5 SET  ref=:ref ,datefact=:datefact ,type =:type ,remise=:remise ,montant=:montant WHERE ref=:ref");
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
    query.prepare("SELECT * from GESTION_FACTURE_5 where ref=:ref");
    query.bindValue(":ref", ref);
    query.exec();
    if (query.next())
        {
            ref=(query.value(0).toInt());
           /*Nom=(query.value(1).toString());
           Email=(query.value(2).toString());
           Tel=(query.value(3).toInt());*/

        }
        return query.exec();
}


/*QSqlQueryModel* Forfait::rechercher(QString desgination)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from FORFAIT where designation LIKE '"+desgination+"%'");


     model->setHeaderData(0, Qt::Horizontal,QObject :: tr("Designation"));
     model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Code"));
    model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Date"));
     model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Prix"));
     return model;
     }*/

