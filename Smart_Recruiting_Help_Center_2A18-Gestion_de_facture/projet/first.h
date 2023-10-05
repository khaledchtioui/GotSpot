#ifndef FIRST_H
#define FIRST_H

#include <QDialog>

namespace Ui {
class First;
}

class First : public QDialog
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = nullptr);
    ~First();

private slots:
    void on_ajout_button_3_clicked();

    void on_ajout_button_2_clicked();

private:
    Ui::First *ui;
};

#endif // FIRST_H
