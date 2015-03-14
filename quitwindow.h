#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class quitwindow: public QWidget

{

    Q_OBJECT
public:
    explicit quitwindow(QWidget* parent = 0);
    ~quitwindow();



    QPushButton* quit_ok;
private:

    QLabel* quit_label;
    QPushButton* quit_cancel;

};

#endif // QUITWINDOW_H
