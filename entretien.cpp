
#include<QtDebug>
#include<QObject>
#include<QSqlQuery>
#include "ui_mainwindow.h"
#include <QDateTime>
#include<QDateTimeEdit>
#include "mainwindow.h"



Entretien::Entretien()
{
ID="" ; nom=" ";pre=" ";age=0;cin =0;num=0;etat=" ";bloc='0';post=" ";//hor=QDateTime::currentDateTime() ;
}

Entretien::Entretien(QString id,QString n,QString p,int a,int c,int nu,QString e,QString b,QString po,QDateTime h)
{   this->ID=id;
    this->nom=n;
    this->pre=p;
    this->age=a;
    this->cin=c ;
    this->num=nu;
    this->etat=e;
    this->bloc=b;
    this->post=po;
    this->hor=h;//QDateTime::currentDateTime();  }
}
QString Entretien::getID(){return ID;}
QString Entretien::getnom(){return nom ;}
QString Entretien::getpre (){return pre;}
int Entretien::getage(){return age ;}
int Entretien::getnum(){return num;}
int Entretien::getcin(){return cin;}
QString Entretien::getbloc(){return bloc ;}
QDateTime Entretien::getHeure() {return hor ;}
QString Entretien::getpost (){return post ;}
QString Entretien::getetat (){return etat ;}
void Entretien::setID(QString id){this->ID=id;}
void Entretien::setnum(int nu){this->num=nu;}
void Entretien::setnom(QString n){this->nom=n;}
void Entretien::setpre (QString p){this->pre=p;}
void Entretien::setage(int a){this->age=a;}
void Entretien::setcin(int c){this->cin=c;}
void Entretien::setbloc(QString b){this->bloc=b;}
void Entretien::setHeure(QDateTime h) {this->hor=h;}//QDateTime::currentDateTime(); }
void Entretien::setpost (QString po){this->post=po;}
void Entretien::setetat (QString e){this->etat=e;}
 bool Entretien :: ajouter()
 {




QString ID_string=(ID) ;
//QString num_string=QString::number(num);
     QSqlQuery query;

     query.prepare("INSERT INTO ENTRETIEN (ID,BLOC,NUM,NOM,POST,PRENOM,HEURE,AGE,ETAT,CIN) "
                   "VALUES (:ID,:bloc,:num,:nom,:post,:pre,:hor,:age,:etat,:cin)");

     query.bindValue(":ID", ID_string);
     query.bindValue(":bloc",bloc);
     query.bindValue(":num",num);
     query.bindValue(":nom",nom);
     query.bindValue(":post",post);

     query.bindValue(":pre",pre);
     query.bindValue(":hor",hor);
     query.bindValue(":age",age);
     query.bindValue(":etat",etat);
     query.bindValue(":cin",cin);
     //query.exec();
     return query.exec();



}


QSqlQueryModel* Entretien :: afficher()
{
         QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery("SELECT * from ENTRETIEN");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("BLOC"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("POST"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("AGE"));
         model->setHeaderData(8, Qt::Horizontal, QObject::tr("ETAT"));
         model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN"));
 return model;
}
bool Entretien::supprimer(QString ID)
{

    /*QSqlQuery query;

    query.prepare("Delete from ENTRETIEN where ID=:ID");
    query.bindValue(":ID", id);
    query.exec();
    return query.exec(); */
    QSqlQuery query;

       query.prepare("Delete from ENTRETIEN where ID=:ID");
       query.bindValue(0, ID);
       query.exec();

       return query.exec();
}

bool Entretien::update(QString ID)
{
QString res= (ID);




//:ID,:nom,:prenom,:age,:etat,:num,:bloc,:hor,:post)"

QSqlQuery query;
query.prepare("Update ENTRETIEN set ID = :ID , NOM = :nom , PRENOM = :pre , AGE = :age ,  ETAT = :etat ,NUM = :num ,BLOC=:bloc,HEURE=:hor,POST=:post,CIN=:cin  where ID = :ID ");
query.bindValue(":ID", res);
query.bindValue(":bloc",bloc );
query.bindValue(":num",num );
query.bindValue(":nom", nom);
query.bindValue(":post",post );
query.bindValue(":pre", pre);
query.bindValue(":hor",hor);
query.bindValue(":age", age);
query.bindValue(":etat", etat);
query.bindValue(":cin",cin );
//query.exec();
return    query.exec();


}



void Entretien::rechercher(Ui::MainWindow *ui)
{
    QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        QString mot =ui->lineEdit_recherche_y_2->text();
        q.prepare("select * from ENTRETIEN where (ID LIKE '%"+mot+"%' or NOM LIKE '%"+mot+"%' or PRENOM LIKE '%"+mot+"%' )");

        q.exec() ;
        modal->setQuery(q);
        ui->tab_y_2->setModel(modal);

}

/*void Entretien::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select ID  from ENTRETIEN");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
*/
QSqlQueryModel *Entretien:: trieid()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from ENTRETIEN order by ID" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("BLOC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("POST"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ETAT"));




    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN"));



 return model;

}

QSqlQueryModel *Entretien:: trienom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from ENTRETIEN order by NOM" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("BLOC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("POST"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ETAT"));




    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN"));

 return model;

}
QSqlQueryModel *Entretien:: triehorloge()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from ENTRETIEN order by HEURE" );


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("BLOC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("POST"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ETAT"));




    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN"));

 return model;

}

bool Entretien :: chercherParCin()
{

    QSqlQuery query;
    query.prepare("Select * from ENTRETIEN where ID=:ID");
    query.bindValue(":ID",ID);
    query.exec();

    if (query.next())
    {
        ID=(query.value(0).toString());


    }
    return query.exec();
}
QSqlQueryModel* Entretien::Trier(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel() ;
    QSqlQuery *query=new QSqlQuery;
    query->prepare(critere) ;
    query->exec() ;
    model->setQuery(*query) ;

 return model;
}
int Entretien ::verificationID()
{
  QSqlQuery query;

  query.prepare("select * from ENTRETIEN where ID=:ID");
  query.bindValue(":ID",this->ID);
  query.exec();

  int count_user = 0;
  while (query.next())
  {

      ID=(query.value(0).toString());
      bloc=(query.value(1).toString());
      num=(query.value(2).toInt());
      nom=(query.value(3).toString());
      post=(query.value(4).toString());
      pre=(query.value(5).toString());
      hor=(query.value(6).toDateTime());
      age=(query.value(7).toInt());
      etat=(query.value(8).toString());
      cin=(query.value(9).toInt());

      count_user ++ ;
  }
  if (count_user==1)
  {
      return 0;
  }
  else if(count_user > 1)
  {
      return 1;
  }
  else
  {
      return 2;
  }
}


