#include "first.h"
#include "ui_first.h"

First::First(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
   // ui->lineEdit_4->setValidator(new QIntValidator(0,99999999999999,this)) ;


    //QPixmap pix("D:/Users/youss/Downloads/istockphoto-172759822-170667a") ;
    //ui->label_pic->setPixmap(pix) ;
    QPixmap pix("H:/Qt/work/projet/3") ;
    ui->label_5->setPixmap(pix) ;
    QPixmap pixq("H:/Qt/work/projet/111") ;
    ui->label_4->setPixmap(pixq) ;
}

First::~First()
{
    delete ui;
}

void First::on_ajout_button_3_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void First::on_ajout_button_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}
