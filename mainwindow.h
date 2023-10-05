#ifndef MainWindow_H
#define MainWindow_H
#include"ddt.h"
#include <QTranslator>
#include "smtp.h"
#include"arduino.h"
#include "presence.h"
#include "client.h"
#include <QMainWindow>
#include <QSound>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtWidgets/QMessageBox>
#include <QString>
#include "historique.h"
#include <QFileDialog>
#include "user.h"
#include "mailing.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QtDebug>
#include<QObject>
#include"smtp.h"
#include "facteur.h"
#include <QSqlRecord>
#include <QDesktopServices>
#include "piechartwidget.h"
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
#include <QPdfWriter>
#include <formation.h>
#include<QPrinter>
#include <QPrintDialog>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include"employe.h"
#include"emp.h"
#include "entretien.h"
#include"exportexcelobject.h"
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
int indexx,ccc;
QString  userrr;

private slots:
    void sendMail();
    void mailSent(QString);
    void browse();

    void browse_img()
    {
        filesim.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            filesim = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, filesim)
            fileListString.append(  QFileInfo(file).fileName());

        ui->lineEdit_image->setText( fileListString );

    }

    void on_bt_Ajouter_clicked();

    void on_Tab_Client_activated(const QModelIndex &index);

    void on_modifier_bt_clicked();

    void on_Supprimer_bt_clicked();

    void on_Trier_bt_clicked();

    void on_pushButton_2_clicked();

    void on_Delete_button_clicked();

    void on_lineEdit_rech_textChanged(const QString &arg1);

    void on_Gestiondeclient_bt_clicked();
    //youssef
    void on_ajout_button_clicked();


    void on_button_supp_clicked();

    void on_modifier_button_clicked();

    void on_pardate_clicked();

    void on_partype_clicked();

    void on_actualiser_clicked();


    void on_exel_clicked();

//    void on_aaaaaaa_clicked();

  //  void on_tableView222_activated(const QModelIndex &index);

   // void on_line_date2_modif_userDateChanged(const QDate &date);

    void on_clear_clicked();

    void on_listView_activated(const QModelIndex &index);

    void on_actualiser_stat_clicked();


    void on_Gestiondefacture_bt_clicked();

    //jawher

    void on_Supp_Button_j_clicked();

    void on_botton_modifier_j_clicked();




    void on_button_tri_j_clicked();

   // void on_button_recherche_clicked();

    void on_pushButton_j_clicked();

    void on_bt_catalogue_j_clicked();

    void on_bt_impression_j_clicked();

    void on_pushButton_2_j_clicked();

    void on_Tab_Formation_j_clicked(const QModelIndex &index);

    void on_lineEdit_recherche_j_textChanged(const QString &arg1);


    void on_pushLien_j_clicked();

    void on_pushCat_j_clicked();



    void on_GestiondeFormation_clicked();

    void on_bt_Ajouter_j_clicked();

    void on_return_client_to_home_clicked();

    void on_return_formation_to_home_clicked();

    void on_return_facture_to_home_clicked();

    void on_rech_textChanged(const QString &arg1);


    void on_tableView222_2_activated(const QModelIndex &index);

    void on_pushButton_calcul_y_clicked();

    void on_return_home_y_calcul_clicked();


    void on_pushButton_stat_youssef_clicked();

    void on_return_home_y_stat_clicked();
//raouf
    void on_Supprimer_r_clicked();

    void on_Actualiser_r_clicked() ;

    void on_Ajouter_r_clicked();

//    void on_Modifier_r_clicked();

    void on_rech_r_clicked();

    void on_tri_r_clicked();

    void on_pushButton_r_clicked();


    void on_clear_r_clicked();

//    void on_rech_2_r_returnPressed();

    void on_rech_2_r_textChanged(const QString &arg1);

    void on_comboBox_2_r_currentIndexChanged(const QString &arg1);



//    void on_comboBox_r_currentIndexChanged(const QString &arg1);






    void on_modifier_r_clicked();

    void on_tableView_r_activated(const QModelIndex &index);

    void on_Notification_r_clicked();

    void on_Return_home_demande_r_clicked();


    void on_Gestiondedemandedetravail_clicked();

    void on_Return_home_r_clicked();

    void on_login_button_l_clicked();

    void on_mdp_oublier_clicked();

    void on_Admin_ajout_clicked();

    void on_pushButton_compte_clicked();

    void on_Return_toadminlist_clicked();

    void on_confirmer_langue_clicked();

    void on_pushButton_param_clicked();

    void on_radioButton_nuit_toggled(bool checked);

    void on_radioButton_jour_toggled(bool checked);


    void on_tableView_seif_activated(const QModelIndex &index);

    void on_Ajouter_seif_clicked();

    void on_Modifier_seif_clicked();

    void on_tri_seif_clicked();

    void on_Supprimer_seif_clicked();

    void on_CV_PDF_clicked();

    void on_recherche_seif_clicked();

    void on_comboBox_2_seif_tri_currentIndexChanged(const QString &arg1);

 //   void on_comboBox_seif_currentIndexChanged(const QString &arg1);


    void on_Actualiser_seif_clicked();

    void on_tab_y_2_activated(const QModelIndex &index);

    void on_Update_2_y_2_clicked();

    void on_pushButton_y_2_clicked();

    void on_pushButton_3_y_2_clicked();

    void on_pushButton_4_y_2_clicked();

    void on_pushButton_2_y_2_clicked();

    void on_comboBox_y_2_currentIndexChanged(int index);

    void on_Valider_y_2_clicked();

    void on_pushButton_historique_k_clicked();

    void on_pushButton_mail_k_clicked();

    void on_pushButton_r_m_k_clicked();

    void on_pushButton_return_his_k_clicked();

    void on_pushButton_entretient_y_clicked();

    void on_pushButton_employee_s_clicked();

    void on_pushButton_param_gestion_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_param_gestion_10_clicked();

    void on_pushButton_param_gestion_3_clicked();

    void on_pushButton_param_gestion_4_clicked();

    void on_pushButton_param_gestion_5_clicked();

    void on_pushButton_param_gestion_6_clicked();

    void on_pushButton_param_gestion_7_clicked();

    void on_pushButton_param_gestion_8_clicked();

    void on_pushButton_param_gestion_9_clicked();

    void on_pushButton_12_clicked();
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    void on_pushButton_5aa_clicked();

    void on_Update_y_2_clicked();

    void on_pushButton_3_execl_clicked();

    void on_confirmer_chan_mdp_clicked();

    void on_ouvrir_media_clicked();

    void on_play_media_clicked();

    void on_pause_media_clicked();

    void on_stop_media_clicked();

    void on_mute_media_clicked();

    void on_volume_media_valueChanged(int value);

private:
    QTranslator *translator=new QTranslator;
    presence P       ;

    Ui::MainWindow *ui;

    QByteArray data,ba; // variable contenant les données reçues

    Arduino A;
    Client C ;
    Historique H ;
    //Ui::MainWindow *ui;
    QStringList files;
    QStringList filesim ;
    Facteur f ;
    PieChartWidget p ;
    Formation F ;
    QString Nom, Prenom,Nationalite,nved;
    int Cin ,Age ,Num;
   // QByteArray data;
    Ddt d;
    user us ;
    QMediaPlayer *med    ;
    emp Employe_P;
Entretien ent ;
    emp e;
    QString filename;
   //  Mailing ml ;
   // Mailing mailing ;
   // Smtp smtp ;
   // QMediaPlayer *player = new QMediaPlayer;
};

#endif // MainWindow_H
