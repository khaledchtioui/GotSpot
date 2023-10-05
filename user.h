#ifndef USER_H
#define USER_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QDateTime>

class user
{
    QString utilisateur ;
    QString psw ;
    QString mail ;
    QString Role ;
public:
    user()

    {
     utilisateur =" ";
     psw = " " ;
     mail =" " ;
     Role =" " ;
    }
    user(QString a,QString b,QString c,QString d)

    {
     utilisateur =a;
     psw = b ;
     mail =c ;
     Role =d ;

    }
    QString get_user()
    {
        return utilisateur ;
    }
    void set_user(QString ch)
    {
        utilisateur = ch ;
    }
    QString get_psw()
    {
        return psw ;
    }
    void set_pwd(QString ch )
    {
        psw =ch ;
    }
    QString get_mail ()
    {
return mail ;
    }
  void   set_mail (QString ch )
    {
       mail = ch ;

    }
  void   set_Role(QString ch)
    {
        Role = ch ;
    }
    QString  getRole()
    {
        return Role ;
    }


    bool   ajouter()
    {
    QSqlQuery query;

    query.prepare("INSERT INTO users (utilisateur,psw,mail,Role) " "   VALUES (:utilisateur,:psw,:mail,:Role)" );
    query.bindValue(":utilisateur",utilisateur);
    query.bindValue(":psw",psw);
    query.bindValue(":mail",mail);
    query.bindValue(":Role",Role);

    return query.exec() ;

    }


    QSqlQueryModel *  afficher()
    {
        QSqlQueryModel *  model = new QSqlQueryModel ()    ;
            model->setQuery("select * from users");
            model->setHeaderData(0, Qt::Horizontal,QObject :: tr("utilisateur"));
            model->setHeaderData(1, Qt::Horizontal, QObject :: tr("mdp"));
            model->setHeaderData(2, Qt::Horizontal, QObject :: tr("email"));
            model->setHeaderData(3, Qt::Horizontal, QObject :: tr("role"));

    return model ;
    }



    bool  supprimer()
    {
        QSqlQuery query;

        query.prepare("Delete from users ") ;
        query.bindValue(":utlisateur",utilisateur);


        query.exec();
        return query.exec() ;


    }

    bool sign_in(QString uname,QString pwd)
    {
        QSqlQuery qry;
        qry.prepare("SELECT * FROM USERS WHERE utilisateur=:utilisateur AND psw=:psw");
        qry.bindValue(":utilisateur",uname);
        qry.bindValue(":psw",pwd);

        //current_user=uname;

        return qry.exec() && qry.next();

    }
    QString fetch(QString uname,int x)
    {
        QSqlQuery qry;
        QString ROLE;


        qry.prepare("SELECT * FROM USERS WHERE utilisateur=:utilisateur");
        qry.bindValue(":utilisateur",uname);

        qry.first();
        qry.exec();

        while(qry.next())
        {
            ROLE=qry.value(x).toString();

        }
        return ROLE;


    }



    bool modifier_mdp(QString utilisateur,QString psw)
    {
        QSqlQuery qry;
       QString mail =fetch(utilisateur,2)   ;
       QString role =fetch(utilisateur,3);

        qry.prepare("UPDATE USERS SET utilisateur=:utilisateur,psw=:psw,mail=:mail,role=:role WHERE utilisateur=:utilisateur");
        qry.bindValue(":utilisateur",utilisateur);
        qry.bindValue(":psw",psw);
        qry.bindValue(":mail",mail);
        qry.bindValue(":role",role);


        return qry.exec();






    }

};

#endif // USER_H
