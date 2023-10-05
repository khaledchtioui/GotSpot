#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QSqlQueryModel>

class Formation
{
    int N_formation ,Prix;
    QString Type_formation , Date_formation,Duree_formation;

public:

    Formation();
    Formation(int,QString,QString,QString,int)  ;

    int get_N_formation();
    int get_Prix();
     QString get_Type_formation();
     QString get_Date_formation();
     QString get_Duree_formation();

     void set_N_formation(int x)  ;
     void set_Prix(int x)  ;

     void set_Type_formation(QString ch)  ;
     void set_Date_formation(QString ch)  ;
     void set_duree_formation(QString ch)  ;

     bool ajouter() ;
     QSqlQueryModel *  afficher()  ;
   bool supprimer(int);
   bool modifier(int N_formation);

     QSqlQueryModel * trier(int choix);
     QSqlQueryModel * rechercher(QString a);
};

#endif // FORMATION_H
