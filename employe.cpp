#include "employe.h"
//#include "ui_employe.h"
#include<QSqlQuery>

Employe::Employe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Employe)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1,&s);
}

Employe::~Employe()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////////////////////
/// \brief Employe::on_Actualiser_clicked
//////////////////
///
void Employe::on_Actualiser_seif_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView_seif->setModel(e.afficher());
}

void Employe::on_Supprimer_seif_clicked()
{

    int cin=ui->Supp->text().toInt();
    e.supprimer(cin);
    ui->tableView_seif->setModel(e.afficher());
    ui->stackedWidget->setCurrentIndex(1);
}

void Employe::on_Ajouter_seif_clicked()
{
    int cin=ui->Cin_A->text().toInt();
    QString nom=ui->Nom_A->text();
    int age=ui->Age_A->text().toInt();
    int num=ui->Tele_A->text().toInt();
    QString nationalite = ui->Nationalite_A->text();
    QString prenom = ui->Prenom_A->text();
    QString poste = ui->Poste_A->text();
    QString username = ui->username->text();
    QString password = ui->password->text();

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
    test=e.ajouter(cin ,age,num,prenom ,nom ,nationalite,poste,username,password );
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
    ui->stackedWidget->setCurrentIndex(1);
}

void Employe::on_Modifier_seif_clicked()
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
    ui->stackedWidget->setCurrentIndex(1);
}


void Employe::on_recherche_seif_clicked()
{
            QString choix = ui->comboBox_seif->currentText();
            QString ch = ui->rech->text();
            ui->tableView_seif->setModel(e.Rech(choix,ch));
            ui->stackedWidget->setCurrentIndex(1);


}

void Employe::on_tri_seif_clicked()
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

void Employe::on_CV_PDF_clicked()
{
    e.convPDF();
    ui->stackedWidget->setCurrentIndex(1);
}

void Employe::on_sendBtn_clicked()
{
    QString mail = ui->rcpt->text();
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

    if(    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)))
)
    {
        QMessageBox::critical(this, "envoyer un mail", "Message non Envoyé (probleme de connexion)");
    }
    else
    {
        QMessageBox::information(this, "envoyer un mail", "Message envoyé avec succès.");
    }

    ui->server->setPlaceholderText("smtp.gmail.com");
    ui->port->setPlaceholderText("465");
    ui->stackedWidget->setCurrentIndex(1);
}


/*void Employe::on_pushButton_clicked()
{
    hide();
}*/


void Employe::on_rech_textChanged(const QString &arg1)
{
    QString choix = ui->comboBox_seif->currentText();
    QString ch = ui->rech->text();
    ui->tableView_seif->setModel(e.Rech(choix,ch));
    ui->stackedWidget->setCurrentIndex(1);
}


void Employe::on_comboBox_2_currentIndexChanged(const QString &arg1)
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


void Employe::on_tabWidget_tabBarClicked(int index)
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Employe::on_envoyer_seif_clicked()
{
    QString msg=ui->chat1->text();
    QString user=ui->username_3->text();
    QString password=ui->password_2->text();
    int test1= e.log(user,password);
    if (test1==1){
    bool test=e.chat(msg,user);
    if (!test)
    {
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                 QObject::tr("message non effectuee! \n"
                                              "click Cancel to exit"),QMessageBox::Cancel);

    }
    ui->tableView_2->setModel(e.affchat());
}




}


void Employe::on_tableView_seif_activated(const QModelIndex &index)
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

