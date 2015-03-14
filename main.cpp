#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QGridLayout>
#include <random>
#include "mainwindow.h"
#include "gameboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    GameBoard* b = new GameBoard;
    quitwindow* q = new quitwindow;
    w->setQuitwindow(q);
    b->setQuitwindow(q);
    w->setGameBoard(b);
    b->setMainWindow(w);
    w->show();
    QObject::connect(q->quit_ok, SIGNAL(clicked()), &a, SLOT(quit()));


    return a.exec();
}
