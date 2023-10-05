#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include <QTranslator>
#include "emp.h"
#include"employe.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    filename = "C:/Users/Khaled/Desktop/bgsound.mp3" ;

    ui->setupUi(this);
    med = new QMediaPlayer(this);
    connect(med , &QMediaPlayer::positionChanged, [&](qint64 pos){

        ui->avancement_media->setValue(pos);

    });

    connect(med , &QMediaPlayer::durationChanged, [&](qint64 dur){

        ui->avancement_media->setMaximum(dur);

    });
    ui->stackedWidget->setCurrentIndex(2);

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->Browse_img, SIGNAL(clicked()), this, SLOT(browse_img()));
    ui->lineEdit_Nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z- _]+"), this ));
    ui->lineEdit_Tel->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_Id->setValidator( new QIntValidator(0, 99999999, this));

    //youssef**************************************************************************************/
   // ui->setupUi(this);
    ui->line_ref->setValidator( new QIntValidator(0, 999999, this));
    ui->line_mont->setValidator( new QIntValidator(0, 999999999, this));
    ui->line_rem->setValidator(new QRegExpValidator( QRegExp("[%0-99]+"), this ));
   // ui->tableView222->setModel(f.afficher()) ;
   //ui->tableView222_3->setModel(f.afficher()) ;    // ajout
    ui->tableView222_2->setModel(f.afficher()) ;  //supp
    //ui->line_date2->setCurrentDate(QDate::currentDate());
    QDate datefact = QDate::currentDate();
    ui->line_date2->setDate(datefact);
    //ui->listView->( f.lister() );
   // ui->ref_comboBox->addItems(f.lister());
    ui->type_comboBox->addItem("") ;
    ui->type_comboBox->addItem("espece") ;
    ui->type_comboBox->addItem("cheque") ;
    ui->type_comboBox->addItem("autre") ;

    //QListView *listView = new QListView(this);
   // ui->listView->setModel(f.lister2());
    ui->listView->setModel(f.afficher()) ;
    //jawher
   // ui->tabWidget_j->setCurrentIndex(0);
    ui->lineEdit_num_formation_j->setValidator( new QIntValidator(0, 99999, this))       ; //
   ui->lineEdit_prix_j->setValidator( new QIntValidator(0, 999, this))                   ;
   ui->lineEdit_type_j->setValidator( new QRegExpValidator(QRegExp("[A-Za-z- _]+"),this));
    ui->lineEdit_date_j->setValidator( new QRegExpValidator(QRegExp("[/0-9999]+"),this));
     ui->lineEdit_duree_j->setValidator( new QRegExpValidator(QRegExp("[0-99a-z- _]+"),this));


    ui->Tab_Formation_j->setModel(F.afficher());



}

void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_Ajouter_clicked()
{

    QString ids = ui->lineEdit_Id->text()  ;
    int Id =ui->lineEdit_Id->text().toInt() ;
    QString Nom  = ui->lineEdit_Nom->text() ;
    QString Email  = ui->lineEdit_Email->text() ;
    int Tel =ui->lineEdit_Tel->text().toInt() ;
    QString image=ui->lineEdit_image->text();

    Client C(Id,Nom,Email,Tel,image) ;

    if (C.testmail(Email)==0)
    {
        QMessageBox::information(nullptr, QObject::tr("Not OK"),
             QObject::tr("Email Invalid .\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


    }

else if(C.ajouter())
  {
      H.set_event("Ajouter de Client "+ids) ;

     if( H.ajouter())

         ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));
      QMessageBox::information(nullptr, QObject::tr("Ok"),
           QObject::tr("Ajout effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
      ui->Tab_Client->setModel(C.afficher())    ;


         // ui->Tab_History->setModel(h.afficher())    ;



  }
  else
  {
      QMessageBox::information(nullptr, QObject::tr("Not Ok"),
           QObject::tr("Ajout non effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);}


}

void MainWindow::on_Tab_Client_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->Tab_Client->model()->data(index).toString();
      query.prepare("Select * from Client where Id=:Id");

      query.bindValue(":Id",val);




      if(query.exec())
         {

             while(query.next())
             {

                 ui->lineEdit_Id->setText(query.value(0).toString());
                 ui->lineEdit_Nom->setText(query.value(1).toString());
                 ui->lineEdit_Tel->setText(query.value(3).toString());
                 ui->lineEdit_Email->setText(query.value(2).toString());
                 ui->lineEdit_image->setText(query.value(4).toString())  ;
                 QString image=query.value(4).toString() ;
                 QString im = "C:/Users/Khaled/Documents/";//+image;
                 QPixmap px (im+image) ;
                 ui->label_img->setPixmap(px) ;
                 H.set_event("Selectionner  ID : "+query.value(0).toString()) ;
                 if (H.ajouter() )
                 {}
                 ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));


             }
         }



}

void MainWindow::on_modifier_bt_clicked()
{
    QString ids = ui->lineEdit_Id->text()  ;
     int Id = ui->lineEdit_Id->text().toInt();
     QString Nom= ui->lineEdit_Nom->text();
      QString Mail= ui->lineEdit_Email->text();
      int Tel = ui->lineEdit_Tel->text().toInt();

      QString image=ui->lineEdit_image->text();
 if(image=="")
     image = "1.png"  ;

     Client c(Id, Nom, Mail, Tel,image);
     bool test=c.modifier(Id) ;
     if(test)
     {

       //  Historique H ;
         H.set_event("Modification de "+ids) ;
         if (H.ajouter()  )
          ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));

          ui->Tab_Client->setModel(C.afficher())    ;
             //  ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));

               // ui->Tab_History->setModel(H.afficher())    ;

         ui->Tab_Client->setModel(c.afficher());//refresh

               QMessageBox::information(nullptr, QObject::tr("effectué"),
                     QObject::tr(" Modifié.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);


                ui->lineEdit_Id->clear();
                ui->lineEdit_Nom->clear();
                ui->lineEdit_Tel->clear();
                ui->lineEdit_Email->clear();


    }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                     QObject::tr("non modifié !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_Id->clear();
         ui->lineEdit_Nom->clear();
         ui->lineEdit_Tel->clear();
         ui->lineEdit_Email->clear();
     }
     ui->Tab_Client->setModel(c.afficher());//refresh
}

void MainWindow::on_Supprimer_bt_clicked()
{
    QString ids =ui->lineEdit_Id->text() ;
       // Client C1;
      // C1.set_id(ui->Id_supp->text().toInt())    ;

    int id=ui->lineEdit_Id->text().toInt()  ;
    Client C1;
    C1.set_id(id)    ;
      // if ( C1.chercherParCin () ==0 )

      // {
       bool test =C1.supprimer(id)    ;
       if(test)
       {
           H.set_event("Supression de "+ids) ;
            if(H.ajouter())
            {}
            ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));

           ui->Tab_Client->setModel(C.afficher())    ;

           QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
      ui->Tab_Client->setModel(C.afficher())    ;
       }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


       }




}

void MainWindow::on_Trier_bt_clicked()
{
    QString type = ui->comboBox->currentText();
    QString critere ="select * from CLIENT ORDER BY "+type;
    ui->Tab_Client->setModel(C.Trier(critere));
    H.set_event("Tri Par "+type ) ;
  if(H.ajouter())
  {
   //  critere ="select * from Historique ORDER BY Time ";
      ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));
  // ui->Tab_History->setModel(H.afficher())    ;

  }
}



void MainWindow::on_pushButton_2_clicked()
{



    QString key = ui->lineEdit_rech->text();
        int index = ui->comboBox->currentIndex();
        QString tri ;
        switch(index)
        {case 0 : tri ="ID" ;
            break ;
        case 1 :
            tri = "Nom"  ;

            break  ;
        case 2 :
            tri = "Email" ;

            break ;
        case 3 :
            tri = "Telephone" ;

            break ;
        default:
            tri="NULL" ;
        }
//QString ids = ui->lineEdit_Id->text();

        Client * C = new Client();
        QSqlQueryModel * q = C->search(index, key);
        if(q != nullptr){
            ui->Tab_Client->setModel(q);
            Historique h ;
            h.set_event("Rechercher "+key + " Par "+tri) ;
    if (h.ajouter() )
             ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));
  // ui->Tab_Client->setModel(C.afficher())    ;
                // ui->Tab_History->setModel(h.afficher())    ;
        }else
        {
            QMessageBox::critical(nullptr, QObject::tr("Warning"),
              QObject::tr("Client non trouvé."), QMessageBox::Cancel);
        }


}

void MainWindow::on_Delete_button_clicked()
{
    if(H.supprimer())
    {
        ui->Tab_History->setModel(H.Trier("select * from Historique ORDER BY TIME DESC" ));

    }
}

void MainWindow::on_lineEdit_rech_textChanged(const QString &arg1)
{

    ui->Tab_Client->setModel((C.Recherche(arg1)));
    if(ui->lineEdit_rech->text().isEmpty())
    {
        ui->Tab_Client->setModel(C.afficher());
    }

}

void MainWindow::on_Gestiondeclient_bt_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(8);



}
// Youssef
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
            //  ui->tableView222_3->setModel(f.afficher()) ;    // ajout
             // ui->tableView222->setModel(f.afficher()) ;
             // ui->tableView222_3->setModel(f.afficher()) ;    // ajout
              ui->tableView222_2->setModel(f.afficher()) ;  //supp
              QMessageBox::information(nullptr, QObject::tr("Ok :)"),
                   QObject::tr("Ajout effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

              ui->line_ref->clear() ;
              ui->line_mont->clear() ;
              ui->line_rem->clear() ;
              //ui->ref_comboBox->clear() ;
             // ui->ref_comboBox->addItems(f.lister());
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


          }

}


void MainWindow::on_button_supp_clicked()
{
    Facteur f ;
    //f.setid_employe(ui->line_idsupp->text().toInt()) ;
    f.setref(ui->line_ref->text().toInt()) ;
   // int previousIndex = ui->ref_comboBox->currentText().toInt() ;
    // f.setref(previousIndex) ;
    bool test=f.supprimer(f.getref()) ;
    QMessageBox msgBox ;
    if(test)
       {

        ui->tableView222_2->setModel(f.afficher()) ;  //supp
     //   ui->tableView222->setModel(f.afficher()) ;
       // ui->tableView222_3->setModel(f.afficher()) ;    // ajout
        ui->tableView222_2->setModel(f.afficher()) ;  //supp
        msgBox.setText("supprision avec succes.") ;
        QMessageBox::information(nullptr, QObject::tr("Ok :)"),
             QObject::tr("Suppression effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


     //    ui->line_idsupp->clear() ;
     //    ui->ref_comboBox->clear() ;
      //   ui->ref_comboBox->addItems(f.lister());

       }
       else
       {
        msgBox.setText("Echec de supprision.") ;
        QMessageBox::critical(nullptr, QObject::tr("Ok :("),
             QObject::tr("Suppression non effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
       //  ui->line_idsupp->clear() ;

       }
}

void MainWindow::on_modifier_button_clicked()
{

    //int id_employe=ui->line_id_modif->text().toInt() ;
    int ref =ui->line_ref->text().toInt();
    QDate datefact=ui->line_date2->date() ;
    float montant=ui->line_mont->text().toFloat() ;
    QString remise =ui->line_rem->text() ;
    //QString type =ui->line_id_modif->text() ;
    QString type=ui->type_comboBox->currentText() ;
    Facteur f(ref,datefact,type,remise,montant);

    bool test=f.modifier() ;
    if(test && type!="")
    {
        ui->tableView222_2->setModel(f.afficher()) ;


        //ui->Tab_Client->setModel(c.afficher());
      //  ui->tableView222_3->setModel(f.afficher()) ;    // ajout
        ui->tableView222_2->setModel(f.afficher()) ;  //supp
               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

               ui->line_ref->clear() ;
               ui->line_mont->clear() ;
               ui->line_rem->clear() ;
             //  ui->ref_comboBox->clear() ;
              // ui->ref_comboBox->addItems(f.lister());
               ui->type_comboBox->setCurrentIndex(-1) ;
  }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->line_ref->clear() ;
        ui->line_mont->clear() ;
        ui->line_rem->clear() ;


    }
}


void MainWindow::on_pardate_clicked()
{
        ui->tableView222_2->setModel(f.trier_date());
}

void MainWindow::on_partype_clicked()
{
    ui->tableView222_2->setModel(f.trier_type());
}

void MainWindow::on_actualiser_clicked()
{
    ui->tableView222_2->setModel(f.afficher()) ;
    f.calcul() ;
}



void MainWindow::on_rech_textChanged(const QString &arg1)
{
    ui->tableView222_2->setModel((f.rechercher(arg1))) ;
          if (ui->rech->text().isEmpty())
          {
              ui->tableView222_2->setModel(f.afficher());
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

//****




void MainWindow::on_clear_clicked()
{
    ui->line_ref->clear() ;

    QDate datefact = QDate::currentDate();
    ui->line_date2->setDate(datefact);
    ui->type_comboBox->setCurrentIndex(-1) ;

    ui->line_rem->clear() ;
    ui->line_mont->clear() ;
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



void MainWindow::on_tableView222_2_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->tableView222_2->model()->data(index).toString();
      query.prepare("Select * from FACTURE where ref=:ref");

      query.bindValue(":ref",val);


      if(query.exec())
         {
             while(query.next())
             {


                 ui->line_ref->setText(query.value(0).toString());
                 ui->line_date2->setDate(query.value(1).toDate()) ;
                 ui->type_comboBox->setCurrentText(query.value(2).toString());
                 ui->line_rem->setText(query.value(3).toString());
                 ui->line_mont->setText(query.value(4).toString());

             }
         }

}


//****



//jawher---------------------------------------------------------------------------------------------


void MainWindow::on_botton_modifier_j_clicked()
{

    int N_formation = ui->lineEdit_num_formation_j->text().toInt();
        QString Type_formation= ui->lineEdit_type_j->text();
         QString Date_formation= ui->lineEdit_date_j->text();
        QString Duree_formation = ui->lineEdit_duree_j->text();
        int Prix = ui->lineEdit_prix_j->text().toInt();

        Formation M (N_formation,Type_formation,Date_formation,Duree_formation,Prix );
        bool test=M.modifier(N_formation);
        if(test)
        {

            ui->Tab_Formation_j->setModel(M.afficher());

                   QMessageBox::information(nullptr, QObject::tr("effectué"),
                        QObject::tr(" Modifié.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
                                                   ui->lineEdit_num_formation_j->clear();
                                                   ui->lineEdit_type_j->clear();
                                                   ui->lineEdit_date_j->clear();
                                                   ui->lineEdit_duree_j->clear();
                                                    ui->lineEdit_prix_j->clear();
                                       }
                                        else
                                        {
                                            QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                                                        QObject::tr("non modifié !.\n"
                                                                    "Click Cancel to exit."), QMessageBox::Cancel);
                                           ui->lineEdit_num_formation_j->clear();
                                            ui->lineEdit_type_j->clear();
                                            ui->lineEdit_date_j->clear();
                                            ui->lineEdit_duree_j->clear();
                                             ui->lineEdit_prix_j->clear();


                                        }

        }
void MainWindow::on_Tab_Formation_j_clicked(const QModelIndex &index)
{


    ui->lineEdit_num_formation_j->setText(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(index.row(),0)).toString());
    ui->lineEdit_type_j->setText(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(index.row(),1)).toString());
    ui->lineEdit_date_j->setText(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(index.row(),2)).toString());
    ui->lineEdit_duree_j->setText(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(index.row(),3)).toString());
     ui->lineEdit_prix_j->setText(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(index.row(),4)).toString());
}





void MainWindow::on_button_tri_j_clicked()
{
    int choix;
     if (ui->comboBox_j->currentText()=="N°Formation")

         choix = 1 ;


     else
         choix = 2 ;


    ui->Tab_Formation_j->setModel(F.trier(choix));


}

/*void MainWindow::on_button_recherche_clicked()
{
    int choix;
     if (ui->comboBox_2->currentText()=="N°formation")
{
            choix = 1 ;

        F.set_N_formation(ui->lineEdit_recherche->text().toInt());
}
     else
         if (ui->comboBox_2->currentText()=="Type de formation")
{
         choix = 2 ;
          F.set_Type_formation(ui->lineEdit_recherche->text());
}
     else
     {
         choix = 3 ;
          F.set_Date_formation(ui->lineEdit_recherche->text());
        }

     ui->Tab_Formation->setModel(F.rechercher(choix));


       ui->lineEdit_recherche->clear();



}
*/
void MainWindow::on_pushButton_j_clicked()
{
    ui->Tab_Formation_j->setModel(F.afficher())    ;

    ui->lineEdit_num_formation_j->clear();
     ui->lineEdit_type_j->clear();
     ui->lineEdit_date_j->clear();
     ui->lineEdit_duree_j->clear();
      ui->lineEdit_prix_j->clear();
}




void MainWindow::on_bt_catalogue_j_clicked()
{
    //int i = 4000;
   // QDesktopServices::openUrl(QUrl("file:///X:/test/docs/myFile.html"), "iexplorer.exe" );
   // QDesktopServices::openUrl("C:/Users/jo/Desktop/cataloque.pdf");

  /* QPdfWriter pdf("C:/Users/jo/Desktop/cataloque.pdf");
    QPainter painter(&pdf);


    painter.drawPixmap(QRect(4600,70,2000,2600),QPixmap("C:/Users/jo/Desktop/form1.jpg"));

    painter.drawPixmap(QRect(1000,70,2000,2600),QPixmap("C:/Users/jo/Desktop/form2.jpg"));  // 7600 70 2000 2600
    painter.drawPixmap(QRect(1000,2800,2000,2600),QPixmap("C:/Users/jo/Desktop/form3.jpg"));
    painter.drawPixmap(QRect(4600,2800,2000,2600),QPixmap("C:/Users/jo/Desktop/form4.jpg"));


QDesktopServices::openUrl(QUrl("file:///C:/Users/jo/Desktop/cataloque.pdf", QUrl::TolerantMode));*/

    ui->stackedWidget_2->setCurrentIndex(1);



 //ui->tabWidget->setCurrentIndex(1);

}



void MainWindow::on_bt_impression_j_clicked()
{

    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->Tab_Formation_j->model()->rowCount();
                const int columnCount = ui->Tab_Formation_j->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title> LISTE DES FORMATIONS<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ***LISTE DES FORRMATIONS *** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->Tab_Formation_j->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->Tab_Formation_j->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->Tab_Formation_j->isColumnHidden(column)) {
                            QString data =ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(row, column)).toString().simplified();
                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                        }
                    }
                    out << "</tr>\n";
                }
                out <<  "</table>\n"
                    "</body>\n"
                    "</html>\n";

                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);

                QPrinter printer;

                QPrintDialog *test = new QPrintDialog(&printer, NULL);
                if (test->exec() == QDialog::Accepted) {
                    document->print(&printer);
                }

                delete document;

 }









QT_CHARTS_USE_NAMESPACE

void MainWindow::on_pushButton_2_j_clicked()
{
   // Piechartwidget_j *p=new Piechartwidget_j;
   // p->show();


      QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("select * from FORMATION where PRIX < 100 ");
      float NF1=model->rowCount();

      model->setQuery("select * from FORMATION where PRIX  between 100 and 500 ");
      float NF2=model->rowCount();

      model->setQuery("select * from FORMATION where PRIX >500 ");
      float NF3=model->rowCount();

      float total=NF1+NF2+NF3;

      QString a=QString("moins de 100 dt . "+QString::number((NF1*100)/total,'f',2)+"%" );
      QString b=QString("entre 100 et 500 dt .  "+QString::number((NF2*100)/total,'f',2)+"%" );
      QString c=QString("plus de 500 dt."+QString::number((NF3*100)/total,'f',2)+"%" );


      QPieSeries *series = new QPieSeries();

      series->append(a,NF1);
      series->append(b,NF2);
      series->append(c,NF3);

      if (NF1!=0)
      {QPieSlice *slice = series->slices().at(0);
          slice->setLabelVisible();
          slice->setPen(QPen());
      }

      if ( NF2!=0)
      {

          QPieSlice *slice1 = series->slices().at(1);
          //slice1->setExploded();
          slice1->setLabelVisible();
      }
      if(NF3!=0)
      {

          QPieSlice *slice2 = series->slices().at(2);

          slice2->setLabelVisible();
      }

      QChart *chart = new QChart();


      chart->addSeries(series);
      chart->setTitle("formations par Prix :Nombre Des Formations "+ QString::number(total));

     // chart->legend()->hide();

      QChartView *chartView = new QChartView(chart);
     // chartView->setRenderHint(QPainter::Antialiasing);
      chartView->resize(1000,500);
      chartView->show();

}

void MainWindow::on_lineEdit_recherche_j_textChanged(const QString &arg1)
{
     ui->Tab_Formation_j->setModel((F.rechercher(arg1))) ;
     if (ui->lineEdit_recherche_j->text().isEmpty())
     {
         ui->Tab_Formation_j->setModel(F.afficher());
     }


}


void MainWindow::on_pushLien_j_clicked()
{
    QString txt = ui->linePath_j->text();
       QSqlQuery query;
       query.prepare("INSERT INTO PATHS (PATH)" "VALUES (:path)");
       query.bindValue(":path", txt);
       if(query.exec())
       {
                  QMessageBox::information(nullptr, QObject::tr("effectué"),
                       QObject::tr(" Insertion avec succés./n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
                                      }
                                       else
                                       {
                                           QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                                                       QObject::tr("Insertion échoué!./n"
                                                                   "Click Cancel to exit."), QMessageBox::Cancel);
                                       }
}

void MainWindow::on_pushCat_j_clicked()
{
    QPdfWriter pdf("C:/Users/Khaled/Downloads/Documents/Smart_Recruiting_Help_Center_2A18/catalogue.pdf");
    QPainter painter(&pdf);
    int x = 0;
    int y = 0;
    QSqlQuery query;
    query.prepare("SELECT PATH FROM PATHS");
    query.exec();
    while(query.next()){
        if(x == 2){
           x = 0;
           y++;
        }
        QString str = query.value(0).toString();
        qDebug() << str;
        painter.drawPixmap(QRect(1000+3600*x,70+2730*y,2000,2600),QPixmap(str));
        x++;
    }
    QDesktopServices::openUrl(QUrl("C:/Users/Khaled/Downloads/Documents/Smart_Recruiting_Help_Center_2A18/catalogue.pdf", QUrl::TolerantMode));
}

void MainWindow::on_GestiondeFormation_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(10);


}

void MainWindow::on_Gestiondefacture_bt_clicked()
{
   indexx=1;
    ui->stackedWidget->setCurrentIndex(11);


}

void MainWindow::on_Supp_Button_j_clicked()
{
    if(ui->Tab_Formation_j->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir une formation du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {
      Formation F1;
      F1.set_N_formation(ui->Tab_Formation_j->model()->data(ui->Tab_Formation_j->model()->index(ui->Tab_Formation_j->currentIndex().row(),0)).toInt())    ;
      bool test =F1.supprimer(F1.get_N_formation())    ;
      if(test)
      {
          QMessageBox::information(nullptr, QObject::tr("Ok"),
               QObject::tr("Suppression effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
     ui->Tab_Formation_j->setModel(F.afficher())    ;

     ui->lineEdit_num_formation_j->clear();
      ui->lineEdit_type_j->clear();
      ui->lineEdit_date_j->clear();
      ui->lineEdit_duree_j->clear();
       ui->lineEdit_prix_j->clear();
      }
      else
      {
          QMessageBox::information(nullptr, QObject::tr("Not Ok"),
               QObject::tr("Suppression non effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


      }
   }
}


void MainWindow::on_bt_Ajouter_j_clicked()
{

    int N_formation =ui->lineEdit_num_formation_j->text().toInt() ;
    QString Type_formation  = ui->lineEdit_type_j->text() ;
    QString Date_formation  = ui->lineEdit_date_j->text() ;
    QString Duree_formation  = ui->lineEdit_duree_j->text() ;
    int Prix =ui->lineEdit_prix_j->text().toInt() ;

    Formation F(N_formation,Type_formation,Date_formation,Duree_formation,Prix) ;
  bool test=F.ajouter();

  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("Ok"),
           QObject::tr("Ajout effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);

      ui->Tab_Formation_j->setModel(F.afficher())    ;
       ui->lineEdit_num_formation_j->clear();
       ui->lineEdit_type_j->clear();
       ui->lineEdit_date_j->clear();
       ui->lineEdit_duree_j->clear();
        ui->lineEdit_prix_j->clear();

  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
           QObject::tr("Ajout non effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);


  }


}


void MainWindow::on_return_client_to_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_return_formation_to_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_return_facture_to_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}






void MainWindow::on_pushButton_calcul_y_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(3) ;
}

void MainWindow::on_return_home_y_calcul_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0) ;

}



void MainWindow::on_pushButton_stat_youssef_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1) ;


}

void MainWindow::on_return_home_y_stat_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0) ;

}
//raouf



void MainWindow::on_Actualiser_r_clicked()
{
    ui->tableView_r->setModel(d.afficher());

}

void MainWindow::on_Ajouter_r_clicked()
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






void MainWindow::on_rech_r_clicked()
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

void MainWindow::on_tri_r_clicked()
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

void MainWindow::on_pushButton_r_clicked()
{
    d.convPDF();
    d.ajnot("convertion PDF");
    ui->label_8->setText("convertion PDF") ;
    ui->tableView_2_r->setModel(d.affnot());
}

void MainWindow::on_clear_r_clicked()
{
    d.clear();
    ui->label_8->setText("Notification est vide") ;
    ui->tableView_2_r->setModel(d.affnot());
}





void MainWindow::on_rech_2_r_textChanged(const QString &arg1)
{
    QString choix = ui->comboBox_r->currentText();

    QString ch = ui->rech_2_r->text();
    ui->tableView_r->setModel(d.Rech(choix,ch));
    d.ajnot("recherche au "+choix);
    ui->label_8->setText("recherche au "+choix);
    ui->tableView_2_r->setModel(d.affnot());
}

void MainWindow::on_comboBox_2_r_currentIndexChanged(const QString &arg1)
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



void MainWindow::on_modifier_r_clicked()
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


void MainWindow::on_Supprimer_r_clicked()
{
    int cin=ui->Cin_A_r->text().toInt();
   if (d.supprimer(cin))
    ui->tableView_r->setModel(d.afficher());
    d.ajnot("supprimer demande de travail de cin : "+QString::number(cin));
    ui->label_8->setText("supprimer demande de travail de cin : "+QString::number(cin)) ;
    ui->tableView_2_r->setModel(d.affnot());
}

void MainWindow::on_tableView_r_activated(const QModelIndex &index)
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

void MainWindow::on_Notification_r_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1) ;

}

void MainWindow::on_Return_home_demande_r_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0) ;

}

void MainWindow::on_Gestiondedemandedetravail_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(0) ;

}

void MainWindow::on_Return_home_r_clicked()
{
    ui->stackedWidget->setCurrentIndex(1) ;

}


void MainWindow::on_login_button_l_clicked()
{
    QString role ;

    if (us.sign_in(ui->usernameLineEdit_login_l->text(),ui->passwordLineEdit_login_l->text()))
    {
        userrr = us.fetch(ui->usernameLineEdit_login_l->text(),0)    ;
        indexx=2;
        role = us.fetch(ui->usernameLineEdit_login_l->text(),3) ;

if(role=="admin")
        ui->stackedWidget->setCurrentIndex(1) ;
else if(role=="Responsable  client")
    ui->stackedWidget->setCurrentIndex(8) ;
else if(role=="Responsable  finace")
    ui->stackedWidget->setCurrentIndex(11) ;
else if(role=="Responsable  formation")
    ui->stackedWidget->setCurrentIndex(10) ;
else if(role=="Responsable  demande de travail")
    ui->stackedWidget->setCurrentIndex(0) ;
else if(role=="Responsable  de entretient")
    ui->stackedWidget->setCurrentIndex(12) ;
else if(role=="Responsable employee")
    ui->stackedWidget->setCurrentIndex(7) ;


    }

}




void MainWindow::on_mdp_oublier_clicked()
{

    QString email ,mdp;
    email = us.fetch(ui->usernameLineEdit_login_l->text(),2) ;
    mdp = us.fetch(ui->usernameLineEdit_login_l->text(),1) ;
    if (mdp!="")

    {
        QMessageBox::information(this, tr("Mot de passe oublié"), tr("Un code de vérification a été envoyé à votre adresse e-mail."));


       Mailing* ml = new Mailing("khaledchtioui02@gmail.com", "tony stark123", "smtp.gmail.com", 465);
       ml->sendMail("khaledchtioui02@gmail.com",email, "Recuperation de Mot de Passe ",mdp);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                                 QObject::tr("username n'existe pas.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }




}

void MainWindow::on_Admin_ajout_clicked()
{


        QString username = ui->usernameLineEdit_signup->text()  ;
        QString psw  = ui->passwordLineEdit_signup->text() ;
        QString c_psw  = ui->confimerMotDePasseLineEdit_signup->text() ;
        QString mail =ui->eMailLineEdit_signup->text() ;
        QString Role=ui->comboBox_role_admin->currentText();
        if(c_psw==psw)
        {
            user us(username,psw,mail,Role) ;
            if(us.ajouter())
            {
                //H.set_event("Ajouter de Client "+ids) ;

                Mailing* ml = new Mailing("khaledchtioui02@gmail.com", "tony stark123", "smtp.gmail.com", 465);
                ml->sendMail("khaledchtioui02@gmail.com",mail, "Mot de Passe ",psw);
                QMessageBox::information(nullptr, QObject::tr("Ok"),
                                         QObject::tr("Ajout effectué.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);



            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                                         QObject::tr("Ajout non effectué.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);}
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                                     QObject::tr("pasword n est pas identique.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);


        }




}

void MainWindow::on_pushButton_compte_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(5) ;

}

void MainWindow::on_Return_toadminlist_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_confirmer_langue_clicked()
{
    QTranslator t ;

    if (ui->comboBox_langue->currentText()=="English")
      {
    qApp->removeTranslator(&t);

        t.load("C:/Users/Khaled/Desktop/anglais.qm")        ;
          qApp->installTranslator(&t);
          ui->retranslateUi(this);
//ui->comboBox_langue->setCurrentText("Francais");
       }
else
    {
        qApp->removeTranslator(&t);

            t.load("C:/Users/Khaled/Desktop/french.qm")        ;
              qApp->installTranslator(&t);
              ui->retranslateUi(this);
   // ui->comboBox_langue->setCurrentText("English");


    }
}

void MainWindow::on_pushButton_param_clicked()
{
    ui->stackedWidget->setCurrentIndex(ccc);

}

void MainWindow::on_radioButton_nuit_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

     QFile styleSheetFile("C:/Users/Khaled/Documents/untitled11/2.qss")    ;
     styleSheetFile.open(QFile::ReadOnly) ;
     QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
       widgets.at(0)->setStyleSheet(styleSheet);

}

void MainWindow::on_radioButton_jour_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

     QFile styleSheetFile("C:/Users/Khaled/Documents/untitled11/1.qss")    ;
     styleSheetFile.open(QFile::ReadOnly) ;
     QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
       widgets.at(0)->setStyleSheet(styleSheet);

}

void MainWindow::on_tableView_seif_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->tableView_seif->model()->data(index).toString();
      query.prepare("Select * from EMPLOYE where CIN=:CIN");

      query.bindValue(":CIN",val);


      if(query.exec())
         {
             while(query.next())
             {
              //      Nationalite_M  // frame_38 // Tele_M   Poste_M


                 ui->Nom_M->setText(query.value(1).toString());
                 ui->Prenom_M->setText(query.value(2).toString());
                 ui->Cin_M ->setText(query.value(0).toString());
                 ui->Nationalite_M->setText(query.value(4).toString());
                 ui->Tele_M->setText(query.value(5).toString());
                 ui->Poste_M->setText(query.value(6).toString());

             }
         }
}

void MainWindow::on_Ajouter_seif_clicked()
{
    int cin=ui->Cin_M->text().toInt();
    QString nom=ui->Nom_M->text();
    int age=ui->Age_M->text().toInt();
    int num=ui->Tele_M->text().toInt();
    QString nationalite = ui->Nationalite_M->text();
    QString prenom = ui->Prenom_M->text();
    QString poste = ui->Poste_M->text();
  //  QString username = ui->username->text();
   // QString password = ui->password->text();

    bool test1 = e.verifage(age);
    bool test2 = e.verifnom(prenom);
    bool test3 = e.verifnom(nom);
    bool t=true;
    if (num<=0)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("num tele numerique\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test2)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("prenom invalid\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test3)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("nom invalid\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test1)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("age should >18\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    bool test=true;
    if (t){
    test=e.ajouter(cin ,age,num,prenom ,nom ,nationalite,poste,poste,poste );
    }
    if (test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("ajout effectue\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_seif->setModel(e.afficher());

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                 QObject::tr("ajout non effectuee! \n"
                                              "click Cancel to exit"),QMessageBox::Cancel);

    }
   // ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Modifier_seif_clicked()
{

    int cin=ui->Cin_M->text().toInt();
    QString nom=ui->Nom_M->text();
    int age=ui->Age_M->text().toInt();
    int num=ui->Tele_M->text().toInt();
    QString nationalite = ui->Nationalite_M->text();
    QString prenom = ui->Prenom_M->text();
    QString poste = ui->Poste_M->text();
    bool test1 = e.verifage(age);
    bool test2 = e.verifnom(prenom);
    bool test3 = e.verifnom(nom);
    bool t=true;
    if (num<=0)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("num tele numerique\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test2)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("prenom invalid\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test3)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("nom invalid\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    if (!test1)
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                QObject::tr("age should >18\n""click cancel to exit."),QMessageBox::Cancel);
        t=false;
    }
    bool test=true;
    if (t){
    test=e.modifier(cin ,age,num,prenom ,nom ,nationalite,poste );
    }
    if (test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("modifier effectue\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_seif->setModel(e.afficher());

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                 QObject::tr("modifier non effectuee! \n"
                                              "click Cancel to exit"),QMessageBox::Cancel);

    }
   // ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tri_seif_clicked()
{
    QString choix = ui->comboBox_2_seif_tri->currentText();
        if (choix =="cin" ){
            ui->tableView_seif->setModel(e.triID());
        }else if(choix=="age") {
            ui->tableView_seif->setModel(e.triAGE());
        }else{
            ui->tableView_seif->setModel(e.trinom());
        }
     //   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Supprimer_seif_clicked()
{
    int cin=ui->Cin_M->text().toInt();
    e.supprimer(cin);
    ui->tableView_seif->setModel(e.afficher());
   // ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_CV_PDF_clicked()
{

    e.convPDF();


}

void MainWindow::on_recherche_seif_clicked()
{
    QString choix = ui->comboBox_seif->currentText();
    QString ch = ui->rech->text();
    ui->tableView_seif->setModel(e.Rech(choix,ch));
}








void MainWindow::on_comboBox_2_seif_tri_currentIndexChanged(const QString &arg1)
{
    QString choix = ui->comboBox_2_seif_tri->currentText();
        if (choix =="cin" ){
            ui->tableView_seif->setModel(e.triID());
        }else if(choix=="age") {
            ui->tableView_seif->setModel(e.triAGE());
        }else{
            ui->tableView_seif->setModel(e.trinom());
        }
        ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_Actualiser_seif_clicked()
{
    //ui->stackedWidget->setCurrentIndex(1);
    ui->tableView_seif->setModel(e.afficher());
}
//yassine

void MainWindow::on_Valider_y_2_clicked()
{

    QString ID=ui->lineEdit_id_y_2->text();
   int num=ui->lineEdit_num_y_2->text().toInt();
    int age=ui->spinBox_age_y_2->text().toInt();
   int cin=ui->lineEdit_cin_y_2->text().toInt();
   QString nom=ui->lineEdit_nom_y_2->text();
   QString pre=ui->lineEdit_pre_y_2->text();
   QString post=ui->comboBox_po_y_2->currentText();
    QString etat=ui->comboBox_etat_y_2->currentText();
    QString bloc=ui->comboBox_bloc_y_2->currentText();
    QDateTime hor=ui->dateTimeEdit_2->dateTime();

   Entretien ent(ID, nom, pre, age, cin, num, etat, bloc, post,hor)  ;
   bool test=ent.ajouter();
   QMessageBox msgBox;
   if(test)
   {
      msgBox.setText("ajouter avec succés");
   ui->tab_y_2->setModel(ent.afficher());
   }
   else {
       msgBox.setText("echec d'ajout");
   msgBox.exec();
}


}


/*void MainWindow::on_tab_clicked(const QModelIndex &index)
{
    ui->tab->setModel(ent.afficher());
}*/



void MainWindow::on_Update_2_y_2_clicked()
{
    /*QString id=ui->lineEdit_id_y->text() ;
    Entretien ent;
    ent.setID(id)    ;
       if ( ent.chercherParCin () ==0 )

       {
       bool test =ent.supprimer(id)    ;
       if(test)
       {
           ui->tab->setModel(ent.afficher())    ;

           QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab->setModel(ent.afficher())    ;
       }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


       }

}*/
    Entretien ent ;
        ent.setID(ui->lineEdit_id_y_2->text());
        bool test=ent.supprimer(ent.getID());
        QMessageBox msgBox;
        if(test)
        {
             ui->tab_y_2->setModel(ent.afficher());
            msgBox.setText("suppression avec succés");
        }
        else{
            msgBox.setText("echeck de suppression");
        msgBox.exec();
}
}
void MainWindow::on_pushButton_2_y_2_clicked()
{
    ui->tab_y_2->setModel(ent.trieid());


}

void MainWindow::on_comboBox_y_2_currentIndexChanged(int index)
{
    QString critere;
       if(index==0)
       {
           critere ="select * from ENTRETIEN ORDER BY ID ASC ";
       ui->tab_y_2->setModel(ent.trieid());
       ui->tab_y_2->setModel(ent.afficher())    ;

       }

       if(index==1)
       {
            critere="select * from ENTRETIEN ORDER BY NOM ASC";
       ui->tab_y_2->setModel(ent.trienom());
       ui->tab_y_2->setModel(ent.afficher())    ;

       }
       if(index==2)
       {critere="select * from ENTRETIEN ORDER BY HEURE ASC";
           ui->tab_y_2->setModel(ent.triehorloge());
           ui->tab_y_2->setModel(ent.afficher())    ;
       }
}

void MainWindow::on_pushButton_y_2_clicked()
{
    /*QString id=ui->lineEdit_recherche->text();
    ui->tab->setModel(ent.rechercher());*/
    class Entretien ent ;
        ui->tab_y_2->setModel(ent.afficher());


           ent.rechercher(ui);
}

void MainWindow::on_pushButton_3_y_2_clicked()
{
     ui->tab_y_2->setModel(ent.trienom());
}

void MainWindow::on_pushButton_4_y_2_clicked()
{
     ui->tab_y_2->setModel(ent.triehorloge());
}



void MainWindow::on_tab_y_2_activated(const QModelIndex &index)
{
    QSqlQuery query;

    QString val=ui->tab_y_2->model()->data(index).toString();
      query.prepare("Select * from ENTRETIEN where ID=:ID");

      query.bindValue(":ID",val);


      if(query.exec())
         {
             while(query.next())
             {

                 ui->lineEdit_id_y_2->setText(query.value(0).toString());
                 ui->comboBox_bloc_y_2->setCurrentText(query.value(1).toString());
                 ui->lineEdit_num_y_2->setText(query.value(2).toString());
                 ui->lineEdit_nom_y_2->setText(query.value(3).toString());
                 ui->comboBox_po_y_2->setCurrentText(query.value(4).toString());
                 ui->lineEdit_pre_y_2->setText(query.value(5).toString());
                 ui->dateTimeEdit_2->setDateTime(query.value(6).toDateTime());
                 ui->spinBox_age_y_2->setSuffix(query.value(7).toString());
                 ui->comboBox_etat_y_2->setCurrentText(query.value(8).toString());
                 ui->lineEdit_cin_y_2->setText(query.value(9).toString());







             }

}
}

void MainWindow::on_pushButton_historique_k_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(2);
}

void MainWindow::on_pushButton_mail_k_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);

}

void MainWindow::on_pushButton_r_m_k_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);

}

void MainWindow::on_pushButton_return_his_k_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);

}

void MainWindow::on_pushButton_entretient_y_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(12);

}

void MainWindow::on_pushButton_employee_s_clicked()
{
    indexx=1;
    ui->stackedWidget->setCurrentIndex(7);

}

void MainWindow::on_pushButton_param_gestion_clicked()
{
    ccc=1;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(indexx);

}

void MainWindow::on_pushButton_param_gestion_10_clicked()
{
    ccc=2;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_3_clicked()
{
    ccc=7;
    ui->stackedWidget->setCurrentIndex(6);

}


void MainWindow::on_pushButton_param_gestion_4_clicked()
{
    ccc=8;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_5_clicked()
{
    ccc=9;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_6_clicked()
{
    ccc=10;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_7_clicked()
{
    ccc=11;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_8_clicked()
{
    ccc=12;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_param_gestion_9_clicked()
{
    ccc=0;
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")
{
   P.set_event("Khaled est entré ")  ;
   if(P.ajouter())
       ui->tableView_presence->setModel(P.Trier("select * from Presence ORDER BY TIME DESC" ));

    // alors afficher ON
}
 else   if (data=="2")
{

        P.set_event("Yassine est entré ")  ;
        if(P.ajouter())
            ui->tableView_presence->setModel(P.Trier("select * from Presence ORDER BY TIME DESC" ));


}
 else   if (data=="3")
{

        P.set_event("Wassim est entré ")  ;
        if(P.ajouter())
            ui->tableView_presence->setModel(P.Trier("select * from Presence ORDER BY TIME DESC" ));


}
    else

        ui->label_3->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher OFF





    data=A.read_from_arduino();

    if(data=="4")

ui->label_33->setText("QUELQ'UN EST VENU !");
        // alors afficher ON
}




/*void MainWindow::on_pushButton_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}
void MainWindow::on_pushButton_2_clicked()  // implémentation du slot bouton off
{
     A.write_to_arduino("0");  //envoyer 0 à arduino
}
void MainWindow::on_pushButton_3_clicked()  // implémentation du slot bouton +
{
    A.write_to_arduino("2");   //envoyer 2 à arduino
}
/*void MainWindow::on_pushButton_4_clicked() // implémentation du slot bouton -
{
    A.write_to_arduino("3");  //envoyer 3 à arduino
}*/




void MainWindow::on_pushButton_5aa_clicked()
{
    QByteArray ba ="";

    ba += ui->lineEdit_aaaa->text();
     A.write_to_arduino(ba);
    qDebug()<< ba ;

    //QByteArray ba =QByteArrayLiteral("\x12\x00\xa4\x42\x51\x00\x00\x99") ;
    ui->lineEdit_aaaa->clear();
}

void MainWindow::on_Update_y_2_clicked()
{
    QString id=ui->lineEdit_id_y_2->text();
          int nu=ui->lineEdit_num_y_2->text().toInt();
           int a=ui->spinBox_age_y_2->text().toInt();
         int c=ui->lineEdit_cin_y_2->text().toInt();
          QString n=ui->lineEdit_nom_y_2->text();
          QString p=ui->lineEdit_pre_y_2->text();
          QString po=ui->comboBox_po_y_2->currentText();
           QString e=ui->comboBox_etat_y_2->currentText();
           QString b=ui->comboBox_bloc_y_2->currentText();
           QDateTime hor=ui->dateTimeEdit_2->dateTime();
      Entretien ent( id, n, p, a, c, nu, e, b,po,hor)  ;
           bool test=ent.update(id);
           if(test)
         {
              ui->tab_y_2->setModel(ent.afficher());

         QMessageBox::information(nullptr, QObject::tr("modifier un entretien"),
                           QObject::tr("entretien modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);




         }
           else
               QMessageBox::critical(nullptr, QObject::tr("modifier un entretien"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

              ui->tab_y_2->setModel(ent.afficher());
}

void MainWindow::on_pushButton_3_execl_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),

                                                          tr("Excel Files (*.xls)"));

          if (fileName.isEmpty())

              return;



          ExportExcelObject obj(fileName, "mydata", ui->tab_y_2);


          //colums to export

          obj.addField(0, "ID", "char(20)");

          obj.addField(1, "BLOC", "char(20)");

          obj.addField(2, "NUM", "char(20)");
          obj.addField(3, "NOM", "char(20)");
          obj.addField(4, "POST", "char(20)");
          obj.addField(5, "PRENOM", "char(20)");
          obj.addField(6, "HEURE", "char(20)");
          obj.addField(7, "AGE", "char(20)");
          obj.addField(8, "ETAT", "char(20)");
          obj.addField(9, "CIN", "char(20)");






          int retVal = obj.export2Excel();

          if( retVal > 0)

          {

              QMessageBox::information(this, tr("Done"),

                                       QString(tr("%1 records exported!")).arg(retVal)

                                       );

          }
}


void MainWindow::on_confirmer_chan_mdp_clicked()
{
    QString mdp;
    mdp = us.fetch(userrr,1) ;
    if(ui->ancienMotDePasseLineEdit->text()==mdp)
    {
        us.modifier_mdp(userrr,ui->nouveauMotDePasseLineEdit->text())  ;
        QMessageBox::information(nullptr, QObject::tr("modifier un entretien"),
                          QObject::tr("Mot de passe modifié.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


    }
}


void MainWindow::on_ouvrir_media_clicked()
{
     filename = QFileDialog::getOpenFileName(this, "ouvrir");

        if (filename.isEmpty())

        {

            return;

        }

        med->setMedia(QUrl::fromLocalFile(filename));

        med->setVolume(ui->volume_media->value());

        on_play_media_clicked();
}

void MainWindow::on_play_media_clicked()
{
    med->setMedia(QUrl::fromLocalFile(filename));

    med->setVolume(ui->volume_media->value());
   // med->setMedia(QUrl::fromLocalFile("C:/Users/Khaled/Desktop/bgsound.mp3"));
   // med->setVolume(ui->volume_media->value());

    med->play();
}

void MainWindow::on_pause_media_clicked()
{
    med->pause();
}

void MainWindow::on_stop_media_clicked()
{
    med->stop();
}

void MainWindow::on_mute_media_clicked()
{
    if (ui->mute_media->text() == "Mute")

        {

            med->setMuted(true);

            ui->mute_media->setText("Unmute");

        }

        else {

            med->setMuted(false);

            ui->mute_media->setText("Mute");

        }
}

void MainWindow::on_volume_media_valueChanged(int value)
{
    med->setVolume(value);
}


