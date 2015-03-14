#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "mainwindow.h"

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
#include <QWidget>
#include <QProgressBar>
#include <QSound>




class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
       void updateCat();
       void dog_attack_end()
       {
           labels[(dog_position->ry()-1)*10+dog_position->rx()]->clear();
           labels[(dog_position->ry())*10+dog_position->rx()]->setMinimumSize(100,100);
           labels[(dog_position->ry())*10+dog_position->rx()]->setMaximumSize(100,100);
       };
       void cat_attack_end()
       {
           labels[(cat_positions->ry()+1)*10+cat_positions->rx()]->clear();
           labels[(cat_positions->ry())*10+cat_positions->rx()]->setMinimumSize(100,100);
           labels[(cat_positions->ry())*10+cat_positions->rx()]->setMaximumSize(100,100);
       }
    friend void lose(GameBoard* b);
    friend void retry(GameBoard* b);
    friend void win(GameBoard* b);
    friend void nextLevel(GameBoard* b);
public:
    explicit GameBoard(QWidget *parent = 0);

    ~GameBoard();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    void setMainWindow(MainWindow* main_window);
    void setQuitwindow(quitwindow* quit_window);
    void updateDog(int px, int py, int nx, int ny);
    void dogAttack();
    void catAttack();



private:
    quitwindow* qwindow;
    GameBoard *ui;
    //dog and cat properties
    QPixmap* dog_image;
    QPixmap* cat_image;
    bool lose_window_showed=false;
    bool retry_window_showed=false;
    QPoint *dog_position;
    QPoint *cat_positions;

    //board properties
    QWidget *board;
    int board_size;
    QLabel** labels;

    // points
    QLabel* dog_hp_label;
    QLabel* cat_hp_label;

    //levels
    QLabel* level_label;
    QLabel* level_number;
    int levels=1;
    double cat_move_speed=60;
    double cat_attack_speed=2.2;
    // bullets
    int bullets_left=300;
    QLabel* bullets_label;
    QLabel* bullets_number;
    MainWindow* mw;
    QWidget* Top;
    QWidget* Bottom;
    double cat_hp=25, dog_hp=25;

    QProgressBar* bar1;
    QProgressBar* bar2;

    QSound* dog_bark;
    QSound* cat_meow;

};

#endif // GAMEBOARD_H
