#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "first.h"
#include <facteur.h>
#include <QDate>
#include <QMessageBox>
#include <QIntValidator>
#include <QDateEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDesktopServices>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->recherche->setIcon(QIcon("H:/Qt/work/projet/111.png")) ;
    //ui->line_date2->setCurrentDate(QDate::currentDate());
    QDate datefact = QDate::currentDate();
    ui->line_date2->setDate(datefact);
    //ui->listView->( f.lister() );
    ui->ref_comboBox->addItems(f.lister());
    ui->type_comboBox->addItem("") ;
    ui->type_comboBox->addItem("espece") ;
    ui->type_comboBox->addItem("cheque") ;
    ui->type_comboBox->addItem("autre") ;
    ui->type_comboBox_2->addItem("") ;
    ui->type_comboBox_2->addItem("espece") ;
    ui->type_comboBox_2->addItem("cheque") ;
    ui->type_comboBox_2->addItem("autre") ;
    //QListView *listView = new QListView(this);
   // ui->listView->setModel(f.lister2());
    ui->listView->setModel(f.afficher()) ;

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
   // QString type =ui->line_id->text() ;
    QString type=ui->type_comboBox->currentText() ;
    Facteur f(ref,datefact,type,remise,montant);

        bool test=f.ajout();

          if(test && type!="")
          {
              ui->tableView222_3->setModel(f.afficher()) ;    // ajout
              ui->table_facteur->setModel(f.afficher()) ;
              ui->tableView222->setModel(f.afficher()) ;
              ui->tableView222_3->setModel(f.afficher()) ;    // ajout
              ui->tableView222_2->setModel(f.afficher()) ;  //supp
              QMessageBox::information(nullptr, QObject::tr("Ok :)"),
                   QObject::tr("Ajout effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

              ui->line_ref->clear() ;
              ui->line_mont->clear() ;
              ui->line_rem->clear() ;
              ui->line_id->clear() ;
              ui->ref_comboBox->clear() ;
              ui->ref_comboBox->addItems(f.lister());
              ui->type_comboBox->setCurrentIndex(-1) ;


          }
          else
          {
              QMessageBox::critical (nullptr, QObject::tr("Not Ok!!"),
                   QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
              ui->line_ref->clear() ;
              ui->line_mont->clear() ;
              ui->line_rem->clear() ;
              ui->line_id->clear() ;


          }
    }


void MainWindow::on_button_supp_clicked()
{
    Facteur f ;
    //f.setid_employe(ui->line_idsupp->text().toInt()) ;
    f.setref(ui->line_idsupp->text().toInt()) ;
    int previousIndex = ui->ref_comboBox->currentText().toInt() ;
     f.setref(previousIndex) ;
    bool test=f.supprimer(f.getref()) ;
    QMessageBox msgBox ;
    if(test)
       {

        ui->tableView222_2->setModel(f.afficher()) ;  //supp
        ui->table_facteur->setModel(f.afficher()) ;
        ui->tableView222->setModel(f.afficher()) ;
        ui->tableView222_3->setModel(f.afficher()) ;    // ajout
        ui->tableView222_2->setModel(f.afficher()) ;  //supp
        msgBox.setText("supprision avec succes.") ;
        QMessageBox::information(nullptr, QObject::tr("Ok :)"),
             QObject::tr("Suppression effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


         ui->line_idsupp->clear() ;
         ui->ref_comboBox->clear() ;
         ui->ref_comboBox->addItems(f.lister());

       }
       else
       {
        msgBox.setText("Echec de supprision.") ;
        QMessageBox::critical(nullptr, QObject::tr("Ok :("),
             QObject::tr("Suppression non effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
         ui->line_idsupp->clear() ;

       }
}

void MainWindow::on_modifier_button_clicked()
{

    //int id_employe=ui->line_id_modif->text().toInt() ;
    int ref =ui->line_ref_modif->text().toInt();
    QDate datefact=ui->line_date2_modif->date() ;
    float montant=ui->line_mont_modif->text().toFloat() ;
    QString remise =ui->line_rem_modif->text() ;
    //QString type =ui->line_id_modif->text() ;
    QString type=ui->type_comboBox_2->currentText() ;
    Facteur f(ref,datefact,type,remise,montant);

    bool test=f.modifier() ;
    if(test && type!="")
    {
        ui->tableView222->setModel(f.afficher()) ;


        //ui->Tab_Client->setModel(c.afficher());
        ui->table_facteur->setModel(f.afficher()) ;//refresh
        ui->tableView222_3->setModel(f.afficher()) ;    // ajout
        ui->tableView222_2->setModel(f.afficher()) ;  //supp
               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

               ui->line_ref_modif->clear() ;
               ui->line_mont_modif->clear() ;
               ui->line_rem_modif->clear() ;
               ui->line_id_modif->clear() ;
               ui->ref_comboBox->clear() ;
               ui->ref_comboBox->addItems(f.lister());
               ui->type_comboBox_2->setCurrentIndex(-1) ;
  }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->line_ref_modif->clear() ;
        ui->line_mont_modif->clear() ;
        ui->line_rem_modif->clear() ;
        ui->line_id_modif->clear() ;


    }
}


void MainWindow::on_pardate_clicked()
{
        ui->table_facteur->setModel(f.trier_date());
}

void MainWindow::on_partype_clicked()
{
    ui->table_facteur->setModel(f.trier_type());
}

void MainWindow::on_actualiser_clicked()
{
    ui->table_facteur->setModel(f.afficher()) ;
    f.calcul() ;
}

void MainWindow::on_recherche_clicked()
{
    int ref;
        ref=ui->rech->text().toInt();


       bool test= true;
        if(test==(true))
        {
          ui->table_facteur->setModel(f.rechercher(ref)) ;
          ui->rech->clear() ;
         // ui->rech->setModel(f.rechercher(ref));
    }
}





void MainWindow::on_exel_clicked()
{
    QString filters("CSV files (*.csv);;All files (*.*)");
       QString defaultFilter("CSV files (*.csv)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                          filters, &defaultFilter);

       QFile file(fileName);

       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
           QStringList strList;
           QFile data("output.csv");
           if (data.open(QFile::WriteOnly)) {
               QTextStream outTxt(&file);
               QSqlQuery query;
               bool firstLine=true;
               query.prepare("SELECT * FROM FACTURE");
               if(query.exec()){
                   while (query.next()) {
                       const QSqlRecord recrd= query.record();
                       if(firstLine){
                           for(int i=0;i<recrd.count();++i)
                               outTxt << recrd.fieldName(i)<< ','; //Headers
                       }
                       firstLine=false;
                       outTxt << "\r\n";
                       for(int i=0;i<recrd.count();++i)
                           outTxt << recrd.value(i).toString() << ',';
                   }
               }
               data.close();
       }
   }
       QDesktopServices::openUrl(QUrl(fileName, QUrl::TolerantMode));

}


/*void MainWindow::on_aaaaaa_clicked()
{

    PieChartWidget *p = new PieChartWidget();
        p->setWindowModality(Qt::ApplicationModal);
       // p->showMaximized();
        p->showMinimized() ;

   } */

void MainWindow::on_tableView222_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->table_facteur->model()->data(index).toString();
      query.prepare("Select * from FACTURE where ref=:ref");

      query.bindValue(":ref",val);


      if(query.exec())
         {
             while(query.next())
             {


                 ui->line_ref_modif->setText(query.value(0).toString());
                 ui->line_date2_modif->setDate(query.value(1).toDate()) ;
                 ui->type_comboBox_2->setCurrentText(query.value(2).toString());
                 ui->line_rem_modif->setText(query.value(3).toString());
                 ui->line_mont_modif->setText(query.value(4).toString());

             }
         }


}


void MainWindow::on_clear_clicked()
{
    ui->line_ref_modif->clear() ;

    QDate datefact = QDate::currentDate();
    ui->line_date2_modif->setDate(datefact);
    ui->type_comboBox_2->setCurrentIndex(-1) ;

    ui->line_rem_modif->clear() ;
    ui->line_mont_modif->clear() ;
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    QSqlQuery query ;

    QString val=ui->listView->model()->data(index).toString();
      query.prepare("Select ref,remise,montant from FACTURE where ref=:ref");

      query.bindValue(":ref",val);


      if(query.exec())
         {
             while(query.next())
             {
                 QString ch1,ch=query.value(1).toString() ;
                 ch.resize(ch.size() - 1);
                     int i=ch.toInt() ;
                     float f, ff=query.value(2).toFloat() ;
                      f=(ff-(ff*i)/100) ;
                   //   ch1=f ;


                 ui->lineEdit_ref->setText(query.value(0).toString());
                 ui->lineEdit_rem->setText(query.value(1).toString());
                 ui->lineEdit_mont->setText(query.value(2).toString());
              //  f= ui->lineEdit_globe->text().toFloat() ;//->setText(query.value(3).toString());
                cout <<"f=========="<<f<<endl ;
                  ch1=f ;
               ui->lineEdit_globe-> QLineEdit::setText(QString::number(f)) ;


             }
         }

}



void MainWindow::on_actualiser_stat_clicked()
{
    PieChartWidget *p = new PieChartWidget();
        p->setWindowModality(Qt::ApplicationModal);
       // p->showMaximized();
        p->showMinimized() ;
}
