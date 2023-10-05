#include "client.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
//#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QPixmap>

Client::Client()
{
    Id=0;
    Prenom="/"   ;
    Nom="/" ;
    Email = "/" ;
    Tel = 0 ;

}

Client::Client(int Id,QString Nom,QString Email,int Tel,QString image )
{
this->Id=Id ;
  this->Nom=Nom ;
    this->Email=Email ;
    this->Tel=Tel ;
    this->image=image;

}
int Client :: get_id()
{
    return Id ;
}
int Client :: get_tel()
{
    return Tel ;
}
QString Client :: get_nom()
{ return Nom ;
}
QString Client :: get_prenom()
{return Prenom ;

}
QString Client :: get_email()
{
    return Email ;
}
void Client :: set_id(int x)
{
   Id = x ;

}
void Client :: set_tel(int x)
{
    Tel = x ;
}

void Client :: set_prenom(QString ch)
{
  Prenom = ch ;
}
void Client :: set_nom(QString ch)
{
    Nom = ch ;
}
void Client :: set_email(QString ch)
{

    Email = ch ;

}
bool Client ::  ajouter()
{
QSqlQuery query;
QString id_string =QString::number(Id) ;

query.prepare("INSERT INTO Client (Id, Nom, Email,Tel,image) " "   VALUES (:Id, :forename, :Email , :Tel,:image)");
query.bindValue(":Id", id_string);
query.bindValue(":forename",Nom);
query.bindValue(":Email", Email);
query.bindValue(":Tel", Tel);
query.bindValue(":image", image);


return query.exec() ;

}

QSqlQueryModel * Client :: afficher()
{
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
        model->setQuery("select * from Client");
        model->setHeaderData(0, Qt::Horizontal,QObject :: tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Email"));
        model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Tel"));


return model ;
}
bool Client :: supprimer(int)
{

    QSqlQuery query;

    query.prepare("Delete from Client where Id=:Id ") ;
    query.bindValue(":Id",Id);


    query.exec();
    return query.exec() ;


}

bool Client :: chercherParCin()
{

    QSqlQuery query;
    query.prepare("Select * from Client where Id:=Id");
    query.bindValue(":Id",Id);
    query.exec();
     //   int       count_user
    if (query.next())
    {
        Id=(query.value(0).toInt());
       /*Nom=(query.value(1).toString());
       Email=(query.value(2).toString());
       Tel=(query.value(3).toInt());*/
     //   count_user++;

    }
    return query.exec();

}


int Client ::verificationID()
{
  QSqlQuery query;

  query.prepare("select * from Clients where Id=:Id");
  query.bindValue(":Id",this->Id);
  query.exec();

  int count_user = 0;
  while (query.next())
  {
      Id=(query.value(0).toInt());
      Nom=(query.value(1).toString());
      Email=(query.value(2).toString());
      Tel=(query.value(3).toInt());
      count_user++;
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


bool Client::testmail(QString mail)
{
    int test=0;
    int position=0;

    if(mail[0]=='@') //le premier caractère est un @
    {
        return false;
    }
    for(int i = 1; i < mail.size(); i++)
    {
        if(mail[i]=='@')
        {
            test++;
            position=i; //recupérer la position du @

        }
    }
    if(test!=1) //il y'a plusieurs @ ou il n'ya pas de @
    {
        return false;
    }

    if(mail[position+1]=='.') //on a le piont juste après le @
    {
        return false;
    }
    for(int i = position+1; i < mail.size(); i++)
    {

        if(mail[i]=='.')
        {
            if(mail.size()>i+1) //S'il y'a des caractère après le point
                return true;
        }
    }
    return false;
}

bool Client :: modifier(int id)
{
     QSqlQuery query;

       // QString res= QString::number(identifiant);

        QString res= QString::number(id);
        query.prepare("UPDATE Client SET  Nom=:Nom,Email=:Email,Tel=:Tel ,image=:image WHERE Id=:Id");
        query.bindValue(":Id", Id);
        query.bindValue(":Nom", Nom);
        query.bindValue(":Email", Email);
        query.bindValue(":Tel", Tel);
        query.bindValue(":image", image);




           return    query.exec();

}



QSqlQueryModel* Client::Trier(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel() ;
    QSqlQuery *query=new QSqlQuery;
    query->prepare(critere) ;
    query->exec() ;
    model->setQuery(*query) ;

 return model;
}


QSqlQueryModel * Client::rechercher(int id)   //OK
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    QString id_string=QString::number(id);


    query.prepare("Select * from CLIENT where Id=:Id");
    query.bindValue(":Id",id_string);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    return model;

}


QSqlQueryModel * Client :: search (int type, QString key)
{
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();
    int k ;
    switch(type){
        case 0:

            k = key.toInt();
            query.prepare("Select * from Client where ID = :id");
            query.bindValue(":id", k);
           query.exec();
           model->setQuery(query);
         //  if(model->record(0).isEmpty() == true){ return model = nullptr;}
        break;
    case 1:

        query.prepare("Select * from Client where NOM = :nom");
        query.bindValue(":nom", key);
       query.exec();
       model->setQuery(query);
      // if(model->record(0).isEmpty() == true){ return model = nullptr;}
        break;
    case 2:

        query.prepare("Select * from Client where Email = :Email");
        query.bindValue(":Email", key);
       query.exec();
       model->setQuery(query);
       //if((model->record(0)).isEmpty() == true){return model = nullptr;}
        break;
    case 3:
        k=key.toInt()    ;
        query.prepare("Select * from Client where Tel = :Tel");
        query.bindValue(":Tel", k);
       query.exec();
       model->setQuery(query);
 break ;
    default:
        model = nullptr;
        break;
    }
    return model;
}


QSqlQueryModel * Client ::Recherche(QString a)//cls=ASC ou DESC
{
QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from CLIENT WHERE Id LIKE '%"+a+"%' OR Nom LIKE '%"+a+"%' OR Email LIKE '%"+a+"%' "
    "OR Tel LIKE '%"+a+"%' OR Image LIKE '%"+ a +"%' ");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));//set header data titre les colonnes
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Tel"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Image"));
return model ;

}

