#include "ddt.h"
#include<QSqlQuery>
#include <QComboBox>
#include <QDebug>
#include <QSound>
#include <QtMultimedia/QMediaPlayer>
Ddt::Ddt()
{
}
///afficher///
QSqlQueryModel * Ddt::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from DEMMANDE_DE_TRAVAIL");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NVED"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NATIONALITE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM"));
    return model;
}
////////ajouter///////////
bool Ddt::ajouter(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Nved )
{
    QSqlQuery query;
    query.prepare("INSERT INTO DEMMANDE_DE_TRAVAIL(CIN,NOM,PRENOM,AGE,NATIONALITE,NVED,NUM)"
                  "VALUES (:cin,:nom,:prenom, :age,:nationalite,:nved,:num)");

                        query.bindValue(":cin",Cin);
                        query.bindValue(":nom",NOM );
                        query.bindValue(":prenom",Prenom);
                        query.bindValue(":age", Age);
                        query.bindValue(":nationalite", Nationalite);
                        query.bindValue(":nved", Nved);
                        query.bindValue(":num", Num);



    return query.exec();
}
///////supprimer/////////
bool Ddt::supprimer(int Cin)
{
    QSqlQuery query;
    query.prepare("delete from DEMMANDE_DE_TRAVAIL where (CIN=:cin)");
    query.bindValue(":cin",Cin);

    return query.exec();
}
//////modifier//////////
bool Ddt::modifier(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Nved )
{
    QSqlQuery query;

      // QString res= QString::number(identifiant);
    query.prepare("UPDATE DEMMANDE_DE_TRAVAIL SET NOM=:nom,PRENOM=:prenom,AGE=:age ,NATIONALITE=:nationalite, NVED=:nved ,NUM=:num WHERE CIN=:cin");
    query.bindValue(":cin",Cin);
    query.bindValue(":nom",NOM);
    query.bindValue(":prenom", Prenom);
    query.bindValue(":age", Age);
    query.bindValue(":nationalite", Nationalite);
    query.bindValue(":nved", Nved);
    query.bindValue(":num", Num);


    return query.exec();

}
bool Ddt::verifage(int age)
{
    bool test = true;
    if (age < 18 ){
        test = false;
    }
    return test;
}
bool Ddt::verifNum(QString n)
{
    bool test = true;
    int i;
    for(i=0;i<n.length();i++)
    {
        if (!(n[i]=="0")&&!(n[i]=="1")&&!(n[i]=="2")&&!(n[i]=="3")&&!(n[i]=="4")&&!(n[i]=="5")&&!(n[i]=="6")&&!(n[i]=="7")&&!(n[i]=="8")&&!(n[i]=="9"))
    {
            test = false;
        }
    }
    return test;
}
bool Ddt::verifnom(QString ch_nom){
    bool test=true;
        int i;
        if(true)
        {
            for(i=0;i<ch_nom.length();i++){
                if(!(ch_nom[i]=='A')&&!(ch_nom[i]=='B')&&!(ch_nom[i]=='C')&&!(ch_nom[i]=='D')&&!(ch_nom[i]=='E')&&!(ch_nom[i]=='F')&&!(ch_nom[i]=='G')&&!(ch_nom[i]=='H')&&!(ch_nom[i]=='I')&&!(ch_nom[i]=='J')&&!(ch_nom[i]=='K')&&!(ch_nom[i]=='L')&&!(ch_nom[i]=='M')&&!(ch_nom[i]=='N')&&!(ch_nom[i]=='O')&&!(ch_nom[i]=='P')&&!(ch_nom[i]=='Q')&&!(ch_nom[i]=='R')&&!(ch_nom[i]=='S')&&!(ch_nom[i]=='T')&&!(ch_nom[i]=='U')&&!(ch_nom[i]=='V')&&!(ch_nom[i]=='W')&&!(ch_nom[i]=='Y')&&!(ch_nom[i]=='Z')&&!(ch_nom[i]=='a')&&!(ch_nom[i]=='b')&&!(ch_nom[i]=='c')&&!(ch_nom[i]=='d')&&!(ch_nom[i]=='e')&&!(ch_nom[i]=='f')&&!(ch_nom[i]=='g')&&!(ch_nom[i]=='h')&&!(ch_nom[i]=='i')&&!(ch_nom[i]=='j')&&!(ch_nom[i]=='k')&&!(ch_nom[i]=='l')&&!(ch_nom[i]=='m')&&!(ch_nom[i]=='n')&&!(ch_nom[i]=='o')&&!(ch_nom[i]=='p')&&!(ch_nom[i]=='q')&&!(ch_nom[i]=='r')&&!(ch_nom[i]=='s')&&!(ch_nom[i]=='t')&&!(ch_nom[i]=='u')&&!(ch_nom[i]=='v')&&!(ch_nom[i]=='w')&&!(ch_nom[i]=='y')&&!(ch_nom[i]=='z')){
                    test=false;
                    return  test;
            }
        }
        }
        return  test;
    }


QSqlQueryModel * Ddt::Rech(QString choix,QString ch)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    if (choix == "cin"){
    model->setQuery("select * from DEMMANDE_DE_TRAVAIL where CIN like '"+ch+"%'");
    }
    else if (choix =="age")
    {
        model->setQuery("select * from DEMMANDE_DE_TRAVAIL where AGE like '"+ch+"%'");
    }
    else if (choix =="telephone")
    {
        model->setQuery("select * from DEMMANDE_DE_TRAVAIL where NUM like '"+ch+"%'");
    }
    if (choix == "nom"){
    model->setQuery("select * from DEMMANDE_DE_TRAVAIL where NOM like '"+ch+"%'");
    }
    else if (choix == "prenom"){
        model->setQuery("select * from DEMMANDE_DE_TRAVAIL where PRENOM like '"+ch+"%'");
    }
    else if  (choix =="niveau educative" ){
        model->setQuery("select * from DEMMANDE_DE_TRAVAIL where NVED like '"+ch+"%'");
    }
    return model;
}
QSqlQueryModel * Ddt::triCin()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from DEMMANDE_DE_TRAVAIL order by CIN");
    return model;
}
/////////////////////////////////////
QSqlQueryModel * Ddt::triAGE()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from DEMMANDE_DE_TRAVAIL order by AGE");
    return model;
}



QSqlQueryModel * Ddt::trinom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from DEMMANDE_DE_TRAVAIL order by NOM");
    return model;
}

////////////////////////////////
void Ddt::convPDF (){
    QString str;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int Month = 1 + ltm->tm_mon;

    int Day= ltm->tm_mday ;
               str.append("<!DOCTYPE html><html lang='en'><head><style>#ipi-table > thead > tr, #ipi-table > thead > tr > td {font-size: .9em;font-weight: 400;background: #51596a;text-transform: uppercase;color: #ffffff;}#ipi-table > tbody > tr > td {max-height: 200px;vertical-align: middle!important;}</style></head><body><div class='container'><div class='row'><div class='col-md-12'><img src='C:/Users/Raouf/Desktop/Raouf/esprit.png'><h1>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp; &nbsp; &nbsp; GESTION DEMMANDE DE TRAVAIL  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</h1> </div></div></div><div class='container'><div class='card' id='TableSorterCard'><div class='row'><div class='col-12'><div><table class='table table tablesorter' id='ipi-table'><thead class='thead-dark'><tr><th>CIN &nbsp; &nbsp;</th><th class='filter-false'>NOM &nbsp; &nbsp;</th><th class='filter-false'>PRENOM &nbsp; &nbsp;</th><th class='filter-false sorter-false'>AGE &nbsp; &nbsp;</th><th class='filter-false sorter-false'>NIVEAU EDUCATIVE &nbsp; &nbsp;</th><th class='filter-false sorter-false'>NATIONALITE &nbsp; &nbsp;</th><th class='filter-false sorter-false'>NUMERO &nbsp; &nbsp;</th></tr></thead><tbody>");




               QSqlQuery* query=new QSqlQuery();
               query->exec("SELECT * FROM DEMMANDE_DE_TRAVAIL");

               while(query->next())
               {
               str.append("<tr><td>");
               str.append(query->value(0).toString()) ;
               str.append("</td><td>") ;
               str.append(query->value(1).toString());
               str.append("</td><td>") ;
               str.append(query->value(2).toString());
               str.append("</td><td>") ;
               str.append(query->value(3).toString());
               str.append("</td><td>") ;
               str.append(query->value(4).toString());
               str.append("</td><td>") ;
               str.append(query->value(5).toString());
               str.append("</td><td>") ;
               str.append(query->value(6).toString());
               str.append("</td><td>") ;






               }
            str.append("</tbody></table></div></div></div></div><p><h3>"+  QString::number(Day)+"/"+QString::number(Month)+"/"+QString::number(year)+"</h3></body></html>") ;

            QPrinter printer ;
            printer.setOrientation(QPrinter::Portrait);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4) ;

            QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","..","PDF(*.pdf)");

            if (path.isEmpty()) return ;
            printer.setOutputFileName(path) ;

            QTextDocument doc;
            doc.setHtml(str) ;
            doc.print(&printer);
}
/////////////////////////////NOTIFICATION////////////////////////////////////////////////
/// \brief DemandeTravail::affhis
/// \return
///
QSqlQueryModel * Ddt::affnot()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from NOTIFICATION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOTIFICATION"));
    return model;
}

bool Ddt::ajnot(QString ch )
{
    QSqlQuery query;
    query.prepare("INSERT INTO NOTIFICATION(NOTIF)"
                  "VALUES (:not)");

    query.bindValue(":not",ch);
    return query.exec();
}
bool Ddt::clear(){
    QSqlQuery query;
    query.prepare("delete from NOTIFICATION ");
    return query.exec();

}

