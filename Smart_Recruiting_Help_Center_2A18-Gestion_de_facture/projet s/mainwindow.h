#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <facteur.h>
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

private:
    Ui::MainWindow *ui;
        Facteur f ;
};
#endif // MAINWINDOW_H
