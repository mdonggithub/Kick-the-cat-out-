#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //this->setStyleSheet("background-image: ./Users/Marshall Dong/Desktop/3.2/PIC 10C/PIC 10C/Project/Project/dogvscat");
    //this->setStyleSheet(" background-color: yellow");
    //this->setFixedSize(300,500);
    mode_label = new QLabel("Modes");
    instruction1=new QLabel("Cats are the most evil species in the world. We gotta kick them out!\nPress Left or Right to move your dog.Press Space to attack. \nThe cat will be hurt if it is in the same vertical direction as you. The cat will hurt you as well.");
    instruction1->textFormat();
    instruction1->textFormat();


    instruction=new QPushButton("instruction");
    final_layout = new QHBoxLayout;
    mode1=new QPushButton("Stage Mode");
    mode2=new QPushButton("Survival Mode");
    mode3=new QPushButton("Schrödinger Mode");

    mode_vlayout=new QVBoxLayout;
    mode_vlayout->addWidget(mode_label);
    mode_vlayout->addWidget(mode1);
    mode_vlayout->addWidget(mode2);
    mode_vlayout->addWidget(mode3);
    QObject::connect(instruction,SIGNAL(clicked()),instruction1,SLOT(show()));



    final_layout->addLayout(mode_vlayout);
    final_layout->addWidget(instruction);

    central = new QWidget;
    central->setLayout(final_layout);

    this->setCentralWidget(central);

}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *e) {

    e->ignore();
    qwindow->show();

}

void MainWindow::setGameBoard(GameBoard* game_board) {
    board = game_board;

    QObject::connect(mode1, SIGNAL(clicked()), board, SLOT(show()));
    QObject::connect(mode2, SIGNAL(clicked()), board, SLOT(show()));
    QObject::connect(mode3, SIGNAL(clicked()), board, SLOT(show()));
}

void MainWindow::setQuitwindow(quitwindow* quit_window)
{
    qwindow = quit_window;

}
