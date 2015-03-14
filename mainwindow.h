#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include <QRadioButton>
#include "quitwindow.h"

class GameBoard;


class MainWindow : public QMainWindow
{
    Q_OBJECT

 public slots:


public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);
    ~MainWindow();

    void setGameBoard(GameBoard* game_board);
    void setQuitwindow(quitwindow* quit_window);

private:

    //QuitWidget* qwidget;
    GameBoard* board;
    quitwindow* qwindow;

    QLabel* instruction2;
    QLabel* instruction1;
    QLabel* mode_label;

    QPushButton* instruction;
    QPushButton* mode1;
    QPushButton* mode2;
    QPushButton* mode3;

    QVBoxLayout* mode_vlayout;
    QVBoxLayout* instructon_vlayout;
    QHBoxLayout* final_layout;
    QWidget* central;
};

#endif // MAINWINDOW_H
