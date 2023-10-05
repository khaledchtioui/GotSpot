#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "first.h"
#include <facteur.h>
#include <QDate>
#include <QMessageBox>
#include <QIntValidator>
#include <QDateEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->line_id->setValidator( new QIntValidator(0, 9999, this));
    ui->line_ref->setValidator( new QIntValidator(0, 999999, this));
    ui->line_idsupp->setValidator( new QIntValidator(0, 999999, this));
    ui->line_id->setValidator(new QRegExpValidator( QRegExp("[A-Za-z- _]+"), this ));
    ui->line_id->setValidator(new QRegExpValidator( QRegExp("[A-Za-z- _]+"), this ));
    ui->line_rem->setValidator(new QRegExpValidator( QRegExp("[%0-99]+"), this ));
    ui->line_rem_modif->setValidator(new QRegExpValidator( QRegExp("[%0-99]+"), this ));
    ui->table_facteur->setModel(f.afficher()) ;
    ui->tableView222->setModel(f.afficher()) ;
    ui->tableView222_3->setModel(f.afficher()) ;    // ajout
    ui->tableView222_2->setModel(f.afficher()) ;  //supp
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_button_clicked()
{


    int ref =ui->line_ref->text().toInt() ;
    QDate datefact = ui->line_date2->date() ;
    float montant=ui->line_mont->text().toFloat() ;
    QString remise =ui->line_rem->text() ;
    QString type =ui->line_id->text() ;

    Facteur f(ref,datefact,type,remise,montant);

        bool test=f.ajout();

          if(test)
          {
              ui->tableView222_3->setModel(f.afficher()) ;
              QMessageBox::information(nullptr, QObject::tr("Ok :)"),
                   QObject::tr("Ajout effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
              ui->table_facteur->setModel(f.afficher()) ;
              ui->tableView222_2->setModel(f.afficher()) ;
              ui->tableView222->setModel(f.afficher()) ;



          }
          else
          {
              QMessageBox::critical (nullptr, QObject::tr("Not Ok!!"),
                   QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);


          }
    }


void MainWindow::on_button_supp_clicked()
{
    Facteur f ;
    //f.setid_employe(ui->line_idsupp->text().toInt()) ;
    f.setref(ui->line_idsupp->text().toInt()) ;
    bool test=f.supprimer(f.getref()) ;
    QMessageBox msgBox ;
    if(test)
       {
        ui->tableView222_2->setModel(f.afficher()) ;
        msgBox.setText("supprision avec succes.") ;
        QMessageBox::information(nullptr, QObject::tr("Ok :)"),
             QObject::tr("Suppression effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);

        ui->table_facteur->setModel(f.afficher()) ;
        ui->tableView222_3->setModel(f.afficher()) ;
        ui->tableView222->setModel(f.afficher()) ;

       }
       else
       {
        msgBox.setText("Echec de supprision.") ;
        QMessageBox::critical(nullptr, QObject::tr("Ok :("),
             QObject::tr("Suppression non effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);

       }
}

void MainWindow::on_modifier_button_clicked()
{

    //int id_employe=ui->line_id_modif->text().toInt() ;
    int ref =ui->line_ref_modif->text().toInt();
    QDate datefact=ui->line_date2_modif->date() ;
    float montant=ui->line_mont_modif->text().toFloat() ;
    QString remise =ui->line_rem_modif->text() ;
    QString type =ui->line_id_modif->text() ;
    Facteur f(ref,datefact,type,remise,montant);

    bool test=f.modifier() ;
    //bool test2=f.cherhceparef() ;
    if(test)
    {

       // if(test2){
        //ui->Tab_Client->setModel(c.afficher());
        ui->table_facteur->setModel(f.afficher()) ;//refresh

               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

               ui->tableView222->setModel(f.afficher()) ;
               ui->tableView222_3->setModel(f.afficher()) ;
               ui->tableView222_2->setModel(f.afficher()) ;
       // }else{QMessageBox::critical(nullptr, QObject::tr("facture déja existant !!!"),
                   //                 QObject::tr("non modifié !.\n"
                      //                          "Click Cancel to exit."), QMessageBox::Cancel) ;}
  }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}


