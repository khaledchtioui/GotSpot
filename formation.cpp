#include "formation.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
//#include<QMediaPlayer>

Formation::Formation()
{
    N_formation =0 ;
    Type_formation="" ;
    Date_formation="" ;
    Duree_formation="" ;
    Prix=0;
}

Formation::Formation(int N_formation,QString Type_formation, QString Date_formation, QString Duree_formation, int Prix )
{
    this->N_formation=N_formation ;
    this->Type_formation=Type_formation ;
    this->Date_formation=Date_formation ;
    this->Duree_formation=Duree_formation ;
    this->Prix=Prix;


}
int Formation :: get_N_formation()
{

    return N_formation    ;

}
int Formation :: get_Prix()
{
return Prix ;
};
 QString Formation ::  get_Type_formation()
 {
     return Type_formation  ;


 };
 QString Formation ::  get_Date_formation()
 {
     return Date_formation ;
 };
 QString Formation ::  get_Duree_formation()
 {return Duree_formation  ;

 };

 void  Formation ::  set_N_formation(int x)
 {N_formation=x;

 };
 void Formation ::  set_Prix(int x)
 {Prix = x ;

 };

 void Formation ::  set_Type_formation(QString ch)
 {Type_formation=ch ;

 };
 void Formation ::  set_Date_formation(QString ch)
 {Date_formation=ch ; };
 void Formation ::  set_duree_formation(QString ch)
 {

     Duree_formation=ch ;
 };

 bool Formation ::  ajouter()
 {
 QSqlQuery query;
 QString N_string =QString::number(N_formation) ;

 query.prepare("INSERT INTO Formation (N_formation, Type_formation, Date_formation,Duree_formation,Prix) " "   VALUES (:N_formation, :Type_formation, :Date_formation , :Duree_formation, :Prix)");
 query.bindValue(":N_formation", N_string);
 query.bindValue(":Type_formation", Type_formation);
 query.bindValue(":Date_formation", Date_formation);
 query.bindValue(":Duree_formation", Duree_formation);
 query.bindValue(":Prix", Prix);


     
 return query.exec() ;

 }

 QSqlQueryModel * Formation ::  afficher()
 {
     QSqlQueryModel *  model = new QSqlQueryModel ()    ;
         model->setQuery("select * from Formation");
         model->setHeaderData(0, Qt::Horizontal,QObject :: tr("N_formation"));
         model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Type_formation"));
         model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Date_formation"));
         model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Duree_formation"));
         model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Prix"));


 return model ;
 }
 bool Formation :: supprimer(int)
 {
     QSqlQuery query;

     query.prepare("Delete from Formation where N_formation=:N_formation ") ;
     query.bindValue(":N_formation",N_formation);


     
     return query.exec() ;


 }


 bool Formation :: modifier(int N_formation)
 {
      QSqlQuery query;



         QString res= QString::number(N_formation);
         query.prepare("UPDATE FORMATION SET N_formation=:N_formation,Type_formation=:Type_formation,Date_formation=:Date_formation ,Duree_formation=:Duree_formation,Prix=:Prix WHERE N_formation=:N_formation");
         query.bindValue(":N_formation", N_formation);
         query.bindValue(":Type_formation", Type_formation);
         query.bindValue(":Date_formation", Date_formation);
         query.bindValue(":Duree_formation", Duree_formation);
         query.bindValue(":Prix", Prix);



            return    query.exec();

 }




 QSqlQueryModel * Formation::trier(int choix)
 {
     QSqlQueryModel * model=afficher();
     QString ch;
     switch (choix)
     {
       case 1 :
         ch = "N_formation" ;
      break ;
       case 2 :
         ch= "Prix";
         break ;

     default:
         break ;

     }

     model->setQuery("SELECT * FROM FORMATION ORDER BY "+ch+" DESC");
     return model;
 }


 /* QSqlQueryModel * Formation::rechercher(int choix)
  {
         QSqlQueryModel * model=afficher();
         QString ch,val;
         switch (choix)
         {
         case 1 :
           ch = "N_formation" ;
            val = QString::number(N_formation) ;

        break ;
         case 2 :
           ch= "Type_formation";
           val ="'"+Type_formation+"'" ;
           break ;
         case 3 :
           ch= "Date_formation";
           val="'"+Date_formation+"'" ;
           break ;

       default:
           break ;
         }
    model->setQuery("SELECT * FROM FORMATION WHERE "+ch+"="+val);

          return model;

  }
*/

  QSqlQueryModel * Formation::rechercher(QString a)
  {
  QSqlQueryModel *model=new QSqlQueryModel();

  model->setQuery("select * from FORMATION where N_formation LIKE '%"+a+"%' OR Type_formation LIKE '%"+a+"%' OR Date_formation LIKE '%"+a+"%' "
      "OR Duree_formation LIKE '%"+a+"%' OR Prix LIKE '%"+ a +"%' ");  //comme un tableau de données en ligne , on l affiche sur table view
   //ajouter a à la requette a l'aide de + // colonne =a

  model->setHeaderData(0,Qt::Horizontal,QObject::tr("N_formation"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type_formation"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date_formation")); //set header data titre les colonnes
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Duree_formation"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prix"));

  return model ;

  }

  /*QMediaPlayer * music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
  music
  music->play();*/



