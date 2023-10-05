#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "first.h"
#include <facteur.h>
#include <QDate>
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_id->setValidator( new QIntValidator(0, 9999, this));
    ui->table_facteur->setModel(f.afficher()) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_button_clicked()
{
    //Facteur ff ;
    int id_employe =ui->line_id->text().toInt() ;
    int ref =ui->line_ref->text().toInt() ;
    QDate date=QDate::fromString(ui->line_date->text()) ;
    //QString date=ui->line_date->date().toString() ;
    float montant=ui->line_mont->text().toFloat() ;
    Facteur f(ref,id_employe,date,montant);
        bool test=f.ajout();

          if(test)
          {
              QMessageBox::information(nullptr, QObject::tr("Ok"),
                   QObject::tr("Ajout effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
              ui->table_facteur->setModel(f.afficher()) ;


          }
          else
          {
              QMessageBox::information(nullptr, QObject::tr("Not Ok"),
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
        msgBox.setText("supprision avec succes.") ;

        ui->table_facteur->setModel(f.afficher()) ;
       }
       else
       {
        msgBox.setText("Echec de supprision.") ;

       }
}
