#include "quitwindow.h"
#include "ui_quitwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

quitwindow::quitwindow(QWidget *parent):
    QWidget(parent)
{
    quit_label=new QLabel("Do you really really wanna quit this fantastic game?????");
    QHBoxLayout* quit_window_layout=new QHBoxLayout();
    QVBoxLayout* quit_window_layout2=new QVBoxLayout();
    quit_cancel = new QPushButton("Cancel");
    quit_ok = new QPushButton("OK");
    quit_window_layout->addWidget(quit_ok);
    quit_window_layout->addWidget(quit_cancel);
    quit_window_layout2->addWidget(quit_label);
    quit_window_layout2->addLayout(quit_window_layout);
    this->setLayout(quit_window_layout2);

    QObject::connect(quit_cancel, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(quit_ok, SIGNAL(clicked()), this, SLOT(close()));

}

quitwindow::~quitwindow()
{}

