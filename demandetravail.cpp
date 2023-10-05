#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QSqlQuery>
Mainwindow::Mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_Supprimer_r_clicked()
{
    int cin=ui->Supp_r->text().toInt();
    bool test=d.supprimer(cin);
    ui->tableView_r->setModel(d.afficher());
    d.ajnot("supprimer demande de travail de cin : "+QString::number(cin));
    ui->label_8->setText("supprimer demande de travail de cin : "+QString::number(cin)) ;
    ui->tableView_2_r->setModel(d.affnot());
}

void Mainwindow::on_Actualiser_r_clicked()
{
    ui->tableView_r->setModel(d.afficher());

}

void Mainwindow::on_Ajouter_r_clicked()
{
    int cin=ui->Cin_A_r->text().toInt();
    QString nom=ui->Nom_A_r->text();
    int age=ui->Age_A_r->text().toInt();
    int num=ui->Tele_A_r->text().toInt();
    QString nationalite = ui->Nationalite_A_r->text();
    QString prenom = ui->Prenom_A_r->text();
    QString nved = ui->nved_A_r->text();
    bool  tes = d.verifnom(nom);
    bool  tes2 = d.verifnom(prenom);
    bool tes1 = d.verifage(age);
    bool t=true;
    if (num<=0){
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("tele only number"),QMessageBox::Cancel);
        t=false;
    }
    if (!tes){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("nom invalid"),QMessageBox::Cancel);
        t=false;

    }
    if (!tes2){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("prenom invalid"),QMessageBox::Cancel);
        t=false;

    }
    if (!tes1){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("age <18"),QMessageBox::Cancel);
        t=false;


    }
    if (t){
    bool test=d.ajouter(cin,age,num,prenom,nom ,nationalite,nved);
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("ajout effectue\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_r->setModel(d.afficher());
        d.ajnot("ajouter un nouveau demande de travail de cin : "+QString::number(cin));
        ui->label_8->setText("ajouter un nouveau demande de travail de cin : "+QString::number(cin));
        ui->tableView_2_r->setModel(d.affnot());

    }
    else
{
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                 QObject::tr("ajout non effectuee! \n"
                                              "click Cancel to exit"),QMessageBox::Cancel);
}
    }

}






void Mainwindow::on_rech_r_clicked()
{
    QString choix = ui->comboBox_r->currentText();
    if (choix == "nom"||choix == "prenom"||choix == "niveau educative"){
        QString ch = ui->rech_2_r->text();
        ui->tableView_r->setModel(d.Rech(choix,ch));
        ui->tableView_2_r->setModel(d.affnot());
    }
    else {
          QString ch = ui->rech_2_r->text();
        ui->tableView_r->setModel(d.Rech(choix,ch));
    }
    d.ajnot("recherche au "+choix);
    ui->label_8->setText("nouveau notification") ;
    ui->tableView_2_r->setModel(d.affnot());

}

void Mainwindow::on_tri_r_clicked()
{
    QString choix = ui->comboBox_2_r->currentText();
    if (choix =="cin" ){
        ui->tableView_r->setModel(d.triCin());
    }
    else if(choix=="age")
    {
        ui->tableView_r->setModel(d.triAGE());
    }
    else
         ui->tableView_r->setModel(d.trinom());
    d.ajnot("tri au "+choix);
    ui->label_8->setText("tri au "+choix);
    ui->tableView_2_r->setModel(d.affnot());
}

void Mainwindow::on_pushButton_r_clicked()
{
    d.convPDF();
    d.ajnot("convertion PDF");
    ui->label_8->setText("convertion PDF") ;
    ui->tableView_2_r->setModel(d.affnot());
}

void Mainwindow::on_clear_r_clicked()
{
    d.clear();
    ui->label_8->setText("Notification est vide") ;
    ui->tableView_2_r->setModel(d.affnot());
}





void Mainwindow::on_rech_2_r_textChanged(const QString &arg1)
{
    QString choix = ui->comboBox_r->currentText();

    QString ch = ui->rech_2_r->text();
    ui->tableView_r->setModel(d.Rech(choix,ch));
    d.ajnot("recherche au "+choix);
    ui->label_8->setText("recherche au "+choix);
    ui->tableView_2_r->setModel(d.affnot());
}

void Mainwindow::on_comboBox_2_r_currentIndexChanged(const QString &arg1)
{
    QString choix = ui->comboBox_2_r->currentText();
    if (choix =="cin" ){
        ui->tableView_r->setModel(d.triCin());
    }
    else if(choix=="age")
    {
        ui->tableView_r->setModel(d.triAGE());
    }
    else
         ui->tableView_r->setModel(d.trinom());
    d.ajnot("tri au "+choix);
    ui->label_8->setText("tri au "+choix);
    ui->tableView_2_r->setModel(d.affnot());
}



void Mainwindow::on_modifier_r_clicked()
{
    int cin=ui->Cin_A_r->text().toInt();
    QString nom=ui->Nom_A_r->text();
    int age=ui->Age_A_r->text().toInt();
    int num=ui->Tele_A_r->text().toInt();
    QString nationalite = ui->Nationalite_A_r->text();
    QString prenom = ui->Prenom_A_r->text();
    QString nved = ui->nved_A_r->text();
    bool  tes = d.verifnom(nom);
    bool  tes2 = d.verifnom(prenom);
    bool tes1 = d.verifage(age);
    bool t=true;
    if (num<=0){
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("tele only number"),QMessageBox::Cancel);
        t=false;
    }
    if (!tes){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("nom invalid"),QMessageBox::Cancel);
        t=false;

    }
    if (!tes2){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("prenom invalid"),QMessageBox::Cancel);
        t=false;

    }
    if (!tes1){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("age <18"),QMessageBox::Cancel);
        t=false;


    }
    if (t){t
    bool test=d.modifier(cin ,age,num,prenom ,nom ,nationalite,nved );
    if (test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("modifier effectue\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_r->setModel(d.afficher());
        ui->label_8->setText("modifier un demande de travail de cin : "+QString::number(cin));
        d.ajnot("modifier un demande de travail de cin : "+QString::number(cin));
        ui->tableView_2_r->setModel(d.affnot());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                 QObject::tr("modifier non effectuee! \n"
                                              "click Cancel to exit"),QMessageBox::Cancel);
}
    }
}

void Mainwindow::on_tableView_r_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->tableView_r->model()->data(index).toString();
      query.prepare("Select * from Demmande_de_travail where Cin=:cin");

      query.bindValue(":cin",val);


      if(query.exec())
         {
             while(query.next())
             {


                 ui->Cin_A_r->setText(query.value(0).toString());
                 ui->Nom_A_r->setText(query.value(1).toString());

                 ui->Prenom_A_r->setText(query.value(2).toString());
                 ui->Age_A_r->setSuffix(query.value(3).toString());

                 ui->nved_A_r->setText(query.value(4).toString());
                 ui->Nationalite_A_r->setText(query.value(5).toString());
                 ui->Tele_A_r->setText(query.value(6).toString());



             }
         }
}
