#ifndef Piechartwidget_j_H
#define Piechartwidget_j_H

#include <QWidget>

class Piechartwidget_j : public QWidget
{
    Q_OBJECT
public:
    explicit Piechartwidget_j(QWidget *parent = nullptr);
protected:
    void paintEvent (QPaintEvent *);
signals:

};

#endif // Piechartwidget_j_H
