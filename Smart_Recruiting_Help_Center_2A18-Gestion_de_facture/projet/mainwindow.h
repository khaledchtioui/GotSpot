#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <facteur.h>
 #include "piechartwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajout_button_clicked();


    void on_button_supp_clicked();

    void on_modifier_button_clicked();

    void on_pardate_clicked();

    void on_partype_clicked();

    void on_actualiser_clicked();

    void on_recherche_clicked();

    void on_exel_clicked();

    void on_aaaaaaa_clicked();

    void on_tableView222_activated(const QModelIndex &index);

    void on_line_date2_modif_userDateChanged(const QDate &date);

    void on_clear_clicked();

    void on_listView_activated(const QModelIndex &index);

    void on_actualiser_stat_clicked();

private:
    Ui::MainWindow *ui;
        Facteur f ;
        PieChartWidget p ;
};
#endif // MAINWINDOW_H
