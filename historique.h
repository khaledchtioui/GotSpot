#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QDateTime>
class Historique
{ private :
    QString event;
  QTime Time ;

public:
    Historique()
    {
        event="  ";
    }
    QString get_event()
    {
        return event ;
    }
    void set_event(QString ch)
    {
        event = ch ;
    }
  //  Historique();
    bool   ajouter()
    {
    QSqlQuery query;
   // QString id_string =QString::number(Id) ;

    query.prepare("INSERT INTO Historique (event,Time) " "   VALUES (:event,:Time)");
    query.bindValue(":event", event);
    query.bindValue(":Time",QTime::currentTime());




    return query.exec() ;

    }


    QSqlQueryModel *  afficher()
    {
        QSqlQueryModel *  model = new QSqlQueryModel ()    ;
            model->setQuery("select * from Historique");
            model->setHeaderData(0, Qt::Horizontal,QObject :: tr("EVENT"));
          //  model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
          //  model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Email"));
          //  model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Tel"));

    return model ;
    }

    QSqlQueryModel* Trier(QString critere)
    {
        QSqlQueryModel* model=new QSqlQueryModel() ;
        QSqlQuery *query=new QSqlQuery;
        query->prepare(critere) ;
        query->exec() ;
        model->setQuery(*query) ;

     return model;
    }

    bool  supprimer()
    {
        QSqlQuery query;

        query.prepare("Delete from Historique ") ;
        query.bindValue(":Event",event);


        query.exec();
        return query.exec() ;


    }


};

#endif // HISTORIQUE_H
