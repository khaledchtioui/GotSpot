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

private:
    Ui::First *ui;
};

#endif // FIRST_H
