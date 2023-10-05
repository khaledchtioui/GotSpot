#include "emp.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
emp::emp()
{

}
//////////////////////////////////////////////////////////////////////////////
/// Cruds
//////////////////////////////////////////////////////////////////////////////
/////////afficher//////////
QSqlQueryModel * emp::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NATIONALITE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSTE"));
    return model;
}
////////ajouter///////////
bool emp::ajouter(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Poste,QString user,QString psw )
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE(CIN,NOM,PRENOM,AGE,NATIONALITE,POSTE,NUM,USERNAME,PASSWORD)"
                  "VALUES (:cin,:nom,:prenom, :age,:nationalite,:poste,:num,:username,:psd)");

                        query.bindValue(":cin",Cin);
                        query.bindValue(":nom", NOM );
                        query.bindValue(":prenom",Prenom);
                        query.bindValue(":age", Age);
                        query.bindValue(":nationalite", Nationalite);
                        query.bindValue(":poste", Poste);
                        query.bindValue(":num", Num);
                        query.bindValue(":psd", psw);
                        query.bindValue(":username", user);



    return query.exec();
}
///////supprimer/////////
bool emp::supprimer(int Cin)
{
    QSqlQuery query;
    query.prepare("delete from EMPLOYE where (CIN=:cin)");
    query.bindValue(":cin",Cin);

    return query.exec();
}
////control saisir////
bool emp::verifage(int age)
{
    bool test = true;
    if (age < 18 ){
        test = false;
    }
    return test;
}
bool emp::verifnom(QString ch_nom){
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
bool emp::verifNum(QString n)
{
    bool test = true;
    int i;
    for(i=0;i<n.length();i++)
    {
        if (!(n[i]=='0')&&!(n[i]=='1')&&!(n[i]=='2')&&!(n[i]=='3')&&!(n[i]=='4')&&!(n[i]=='5')&&!(n[i]=='6')&&!(n[i]=='7')&&!(n[i]=='8')&&!(n[i]=='9'))
    {
            test = false;
            return test;
        }
    }
    if ((n.length()<8)&&(n.length()>8)){
            test=false;
            return test;
}
    return test;
}
//////modifier//////////
bool emp::modifier(int Cin ,int Age,int Num, QString Prenom ,QString NOM ,QString Nationalite,QString Poste )
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:nom,PRENOM=:prenom,AGE=:age ,NATIONALITE=:nationalite, POSTE=:poste ,NUM=:num WHERE CIN=:cin");
    query.bindValue(":cin",Cin);
    query.bindValue(":nom",NOM);
    query.bindValue(":prenom", Prenom);
    query.bindValue(":age", Age);
    query.bindValue(":nationalite", Nationalite);
    query.bindValue(":poste", Poste);
    query.bindValue(":num", Num);


    return query.exec();

}
QSqlQueryModel * emp::Rech(QString choix,QString ch)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    if (choix == "cin"){
    model->setQuery("select * from EMPLOYE where CIN like '"+ch+"%'");
    }
    else if (choix =="age")
    {
        model->setQuery("select * from EMPLOYE where AGE like '"+ch+"%'");
    }
    else if (choix =="num")
    {
        model->setQuery("select * from EMPLOYE where NUM like '"+ch+"%'");
    }
    if (choix == "nom"){
    model->setQuery("select * from EMPLOYE where NOM like '"+ch+"%'");
    }
    else if (choix == "prenom"){
        model->setQuery("select * from EMPLOYE where PRENOM like '"+ch+"%'");
    }
    else if  (choix =="nationalite" ){
        model->setQuery("select * from EMPLOYE where NATIONALITE like '"+ch+"%'");
    }
    else if  (choix =="poste" ){
        model->setQuery("select * from EMPLOYE where POSTE like '"+ch+"%'");
    }
    return model;
}
QSqlQueryModel * emp::triID()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE order by CIN");
    return model;
}
/////////////////////////////////////
QSqlQueryModel * emp::triAGE()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE order by AGE");
    return model;
}

QSqlQueryModel * emp::trinom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE order by NOM");
    return model;
}



////////////////////////////////
void emp::convPDF (){
    QString str;
               str.append("<!DOCTYPE html><html lang='en'><head><style>#ipi-table > thead > tr, #ipi-table > thead > tr > td {font-size: .9em;font-weight: 400;background: #51596a;text-transform: uppercase;color: #ffffff;}#ipi-table > tbody > tr > td {max-height: 200px;vertical-align: middle!important;}</style></head><body><div class='container'><div class='row'><div class='col-md-12'><p>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp; &nbsp; &nbsp; TABLEAU GESTION EMPLOYE  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</p></div></div></div><div class='container'><div class='card' id='TableSorterCard'><div class='row'><div class='col-12'><div><table class='table table tablesorter' id='ipi-table'><thead class='thead-dark'><tr><th>CIN &nbsp; &nbsp;</th><th class='filter-false'>NOM &nbsp; &nbsp;</th><th class='filter-false'>PRENOM &nbsp; &nbsp;</th><th class='filter-false sorter-false'>AGE &nbsp; &nbsp;</th><th class='filter-false sorter-false'>NATIONALITE &nbsp; &nbsp;</th><th class='filter-false sorter-false'>NUMERO &nbsp; &nbsp;</th><th class='filter-false sorter-false'>POSTE &nbsp; &nbsp;</th></tr></thead><tbody>");



               QSqlQuery* query=new QSqlQuery();
               query->exec("SELECT * FROM EMPLOYE");

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
            str.append("</tbody></table></div></div></div></div></body></html>") ;

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
bool emp::chat(QString chat,QString USERNAME)
{

    QSqlQuery query;
    query.prepare("INSERT INTO CHAT(MSG,USERNAME)"
                  "VALUES (:chat,:username)");

    query.bindValue(":chat",chat);
    query.bindValue(":username",USERNAME);



    return query.exec();
}

int emp::log(QString user,QString pass)
{
    QSqlQuery query;
    int count = 0 ;
    query.prepare("SELECT * FROM EMPLOYE  WHERE USERNAME='"+user+"' AND PASSWORD= '"+pass+"'");
    query.exec();
    while(query.next())
    {
        count++;

    }
    return count;
}
QSqlQueryModel * emp::affchat()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from CHAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MSG"));

    return model;
}
