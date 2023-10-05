#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include <QWidget>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "smtp.h"
#include <QPainter>
//#include "stati1.h"
//#include "ui_stati1.h"
#include "emp.h"

namespace Ui {
class Employe;
}

class Employe : public QWidget
{
    Q_OBJECT

public:


    explicit Employe(QWidget *parent = nullptr);
    ~Employe();

private slots:
        void on_Actualiser_seif_clicked();

        void on_Supprimer_seif_clicked();

        void on_Ajouter_seif_clicked();

        void on_Modifier_seif_clicked();

        void on_recherche_seif_clicked();

        void on_tri_seif_clicked();

        void on_CV_PDF_clicked();

        void on_sendBtn_clicked();

       // void on_pushButton_clicked();

        void on_rech_textChanged(const QString &arg1);

        void on_comboBox_2_currentIndexChanged(const QString &arg1);

        void on_tabWidget_tabBarClicked(int index);

        void on_envoyer_seif_clicked();

        void on_tableView_seif_activated(const QModelIndex &index);

private:
    Ui::Employe *ui;
    //stati1 s;
    emp e;
};

#endif // EMPLOYE_H
