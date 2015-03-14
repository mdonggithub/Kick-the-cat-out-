#include "gameboard.h"
#include "ui_gameboard.h"
#include "quitwindow.h"


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),board_size(10)

{

    Top = new QWidget; Bottom=new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");
    Bottom->setStyleSheet("QLabel { background-color : black; color : white; }");
    QHBoxLayout *top_bar = new QHBoxLayout(Top);
    QHBoxLayout *top_bar2=new QHBoxLayout(Bottom);
    QLabel* pointsLabel1 = new QLabel("Cat hp ");
    QLabel* pointsLabel2 = new QLabel("Dog hp ");
    bar1=new QProgressBar;
    bar2=new QProgressBar;
    //levels
    level_label=new QLabel("Level:");
    level_number=new QLabel;
    level_number->setText(QString::number(levels));
    dog_hp_label=new QLabel();
    cat_hp_label=new QLabel();

    //bullets appearance setting
    bullets_label=new QLabel("Bullets Left");
    bullets_number=new QLabel;
    bullets_number->setText(QString::number(bullets_left));

    //points appearance setting
    /*dog_points_label->setText(QString::number(dog_points));
    cat_points_label->setText(QString::number(cat_points));
    dog_points_label->setMinimumSize(70,70);
    dog_points_label->setMaximumSize(70,70);
    cat_points_label->setMinimumSize(70,70);
    cat_points_label->setMaximumSize(70,70);*/
    pointsLabel1->setMinimumSize(120,70);
    pointsLabel1->setMaximumSize(120,70);
    pointsLabel2->setMinimumSize(120,70);
    pointsLabel2->setMaximumSize(120,70);


    level_label->setMinimumSize(120,70);
    level_label->setMaximumSize(120,70);
    level_number->setMinimumSize(70,70);
    level_number->setMaximumSize(70,70);
    bullets_number->setMinimumSize(70,70);
    bullets_number->setMaximumSize(70,70);
    bullets_label->setMinimumSize(160,70);
    bullets_label->setMaximumSize(160,70);

    bar1->setMinimumSize(200,50);
    bar1->setMaximumSize(200,50);
    bar2->setMinimumSize(200,50);
    bar2->setMaximumSize(200,50);

    level_label->setStyleSheet("QLabel { background-color : grey; color : white; }");
    level_number->setStyleSheet("QLabel { background-color : grey; color : white; }");

    bullets_label->setStyleSheet("QLabel { background-color : grey; color : white; }");
    bullets_number->setStyleSheet("QLabel { background-color : grey; color : white; }");
    pointsLabel1->setStyleSheet("QLabel { background-color : grey; color : white; }");
    pointsLabel2->setStyleSheet("QLabel { background-color : grey; color : white; }");
    /*cat_points_label->setStyleSheet("QLabel { background-color : grey; color : white; }");
    dog_points_label->setStyleSheet("QLabel { background-color : grey; color : white; }");*/

    //progress bars

    bar1->setRange(0,100);
    bar1->setValue(cat_hp);

    bar2->setRange(0,100);
    bar2->setValue(dog_hp);
    top_bar->addWidget(pointsLabel1);
    top_bar->addWidget(bar1);
    top_bar->addWidget(bar2);
    //top_bar->addWidget(cat_points_label);
    top_bar->addWidget(pointsLabel2);
    //top_bar->addWidget(dog_points_label);

    top_bar2->addWidget(level_label);
    top_bar2->addWidget(level_number);
    top_bar2->addWidget(bullets_label);
    top_bar2->addWidget(bullets_number);




    //import images of cat and dog
    QString fileName1("/Users/Marshall Dong/Desktop/3.2/PIC 10C/PIC 10C/Project/Project/dog_image");
    dog_image = new QPixmap(fileName1);
    QString fileName2("/Users/Marshall Dong/Desktop/3.2/PIC 10C/PIC 10C/Project/Project/cat_image");
    cat_image = new QPixmap(fileName2);
    QString fileName3("/Users/Marshall Dong/Desktop/3.2/PIC 10C/PIC 10C/Project/Project/dog_bark.wav");
    dog_bark=new QSound(fileName3);
    QString fileName4("/Users/Marshall Dong/Desktop/3.2/PIC 10C/PIC 10C/Project/Project/cat_meow.wav");
    cat_meow=new QSound(fileName4);

    // coordinates

    dog_position = new QPoint(board_size-1,board_size-1);
    cat_positions = new QPoint(0,0);
    //board
    board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    QGridLayout *squareGrid = new QGridLayout(board);

    squareGrid->setGeometry(QRect());
    squareGrid->setSpacing(0);

    //lables for the board
    for(int i=0;i<board_size;i++) {
        for(int j=0;j<board_size;j++) {

            // Create label and set properties.
            labels[i*board_size+j] = new QLabel;
            labels[i*board_size+j]->setMinimumSize(100,100);
            labels[i*board_size+j]->setMaximumSize(100,100);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color : grey; color : white; }");
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);
            //labels[i*board_size+j]->show();
            // Add label to the layout
            squareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }

    //initialize cat and dog positions

    //show the picture

    labels[0]->setPixmap(*cat_image);
    labels[0]->setScaledContents(true);
    labels[board_size*board_size-1]->setPixmap(*dog_image);
    labels[board_size*board_size-1]->setScaledContents(true);
    /*labels[0]->setStyleSheet("QLabel { background-color : red; color : white; }");
    labels[board_size*board_size-1]->setStyleSheet("QLabel { background-color : black; color : white; }");  */

    board->setFixedSize(1000,1000);
    setFixedSize(1200,1300);

    //Piece Top, Board, buttom together
    QVBoxLayout *piece_together = new QVBoxLayout();
      piece_together->addWidget(Top,0,Qt::AlignCenter);
      piece_together->addWidget(board,0,Qt::AlignCenter);
      piece_together->addWidget(Bottom,0,Qt::AlignCenter);



    this->setLayout(piece_together);
    this->setStyleSheet("QLabel { background-color : black; color : white; }");

    //timer for update cats
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCat()));
    timer->start(cat_move_speed);

    this->setWindowTitle("Attack on Cats");


}

GameBoard::~GameBoard()
{

    delete[]  cat_positions;
    delete[]  dog_position;

}
//KeyPressEvents
void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = dog_position->rx();
    int y = dog_position->ry();


    // Keys to move dots
    switch (event->key()) {
    case Qt::Key_Left:
        if((dog_position->rx()-1) >= 0)
            updateDog(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if((dog_position->rx()+1) <= board_size-1)
            updateDog(x,y,x+1,y);

        break;

    //Attack Key:space
    case Qt::Key_Space:
        dogAttack();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    QCoreApplication::processEvents();
    repaint();
    return;
}

void GameBoard::paintEvent(QPaintEvent *e) {

    int x = dog_position->rx();
    int y = dog_position->ry();


    if ((x<board_size && x>=0)&& (y<board_size && y>=0))
    {
        labels[y*board_size+x]->setPixmap(*dog_image);
        labels[y*board_size+x]->setScaledContents(true);
    /*labels[y*board_size+x]->setStyleSheet("QLabel { background-color : black; color : white; }");*/
    }

    int px = cat_positions->rx();
    int py = cat_positions->ry();

    if(px >= 0 && py >= 0 && px < board_size && py < board_size) {
    labels[py*board_size+px]->setPixmap(*cat_image);
    labels[py*board_size+px]->setScaledContents(true);
        /*labels[py*board_size+px]->setStyleSheet("QLabel { background-color : red; color : white; }");*/
        }
}




void GameBoard::updateDog(int px, int py, int nx, int ny) {

    labels[py*board_size+px]->clear();

    dog_position->setX(nx);
    dog_position->setY(ny);

}

void GameBoard::updateCat() {

    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);





    int sx = cat_positions->rx();
    int sy = cat_positions->ry();


    if(sx>=0 && sy >= 0 && sx<board_size && sy<board_size)
    {
    labels[sy*board_size+sx]->clear();
    }

        int nx = sx;
        int ny = sy;

    // randomly move cat
        if(p(generator) < 0.5) {

            if(x_or_y(generator) == 0) {
                nx = sx + 2*increment(generator)-1;
                if(nx >= 0 && nx < board_size)
                    cat_positions->setX(nx);
            }
            /*else {
                ny = sy + 2*increment(generator)-1;
                if(ny >= -1 && ny <= board_size)
                    cat_positions->setY(ny);

            }*/

    if(cat_positions->rx()==dog_position->rx())
    {
        catAttack();
       /*double temp1=attack(generator)*10;
       int temp2=static_cast<int>(temp1);
       double attacks=static_cast<double>(temp2);
       cat_points=cat_points+attacks;
       cat_points_label->setText(QString::number(cat_points));*/
    }



    QCoreApplication::processEvents();
    repaint();

}
}

void GameBoard::setMainWindow(MainWindow* main_window) {
    mw = main_window;
}

void GameBoard::dogAttack(){
    dog_bark->play();
if (bullets_left>=0)
{
    // update bullets
   bullets_left-=1;bullets_number->setText(QString::number(bullets_left));
   //dog effeect
   labels[(dog_position->ry())*10+dog_position->rx()]->setMinimumSize(150,150);
   labels[(dog_position->ry())*10+dog_position->rx()]->setMaximumSize(150,150);
   labels[(dog_position->ry()-1)*10+dog_position->rx()]->setText("Bark!!");
   QTimer* t=new QTimer(this);
   connect (t,SIGNAL(timeout()),this,SLOT(dog_attack_end()));t->start(100);

   //get points
   if (cat_positions->rx()==dog_position->rx()){
       cat_hp--;
       if (cat_hp<=0) {win(this);nextLevel(this);}
       cat_hp_label->setText(QString::number(cat_hp));
       bar1->setValue(cat_hp);
   }
}
}
void GameBoard::catAttack() {
    cat_meow->play();
    std::uniform_real_distribution<double> attack(0,1);

    double temp1=attack(generator)*cat_attack_speed ;
    int temp2=static_cast<int>(temp1);
    for (int i=0;i<=temp1;i++)
    {
        labels[(cat_positions->ry())*10+cat_positions->rx()]->setMinimumSize(150,150);
        labels[(cat_positions->ry())*10+cat_positions->rx()]->setMaximumSize(150,150);
        labels[(cat_positions->ry()+1)*10+cat_positions->rx()]->setText("Meow!!");
        QTimer* t=new QTimer(this);
        connect (t,SIGNAL(timeout()),this,SLOT(cat_attack_end()));t->start(100);
    }
    double attacks=static_cast<double>(temp2);
    if (dog_hp-1<=0) {lose(this);retry(this);}
    dog_hp=dog_hp-attacks;
      if (dog_hp>0)  {bar2->setValue(dog_hp);}
}

void GameBoard::setQuitwindow(quitwindow* quit_window)
{
    qwindow=quit_window;

}

void lose(GameBoard* b)
{
    b->close();

    if (!b->lose_window_showed){
    QWidget* lose_window=new QWidget;

    QLabel* you_lose=new QLabel("Ahhh!! You Lose! YOU STUPID DOG");
    QLabel* lose_cat_pic=new QLabel;

    //set cat picture
    lose_cat_pic->setPixmap(*(b->cat_image));

    lose_cat_pic->setMinimumSize(200,200);
    lose_cat_pic->setMaximumSize(200,200);
    lose_cat_pic->setScaledContents(true);

    QVBoxLayout* lose_layout=new QVBoxLayout;
    lose_layout->addWidget(you_lose);
    lose_layout->addWidget(lose_cat_pic);
    lose_window->setLayout(lose_layout);
    lose_window->show();
    b->lose_window_showed=true;
    }

}

void retry(GameBoard* b){
    if(!b->retry_window_showed){
    QWidget* retry_window=new QWidget;
    QLabel* retry_words=new QLabel("Do you wanna be defeated again? You stupid dog!");
    QPushButton* retry_button=new QPushButton("retry");
    QPushButton* retry_button2=new QPushButton("No, I render");
    QVBoxLayout* retry_layout=new QVBoxLayout;
    retry_layout->addWidget(retry_words);
    retry_layout->addWidget(retry_button);
    retry_layout->addWidget(retry_button2);
    retry_window->setLayout(retry_layout);
    retry_window->show();

    GameBoard* s=new GameBoard();
    s->setMainWindow(b->mw);
    s->setQuitwindow(b->qwindow);
    QObject::connect (retry_button,SIGNAL(clicked()),s,SLOT(show()));
    QObject::connect (retry_button2,SIGNAL(clicked()),retry_window,SLOT(hide()));
    QObject::connect (retry_button2,SIGNAL(clicked()),s,SLOT(deleteLater()));
    b->retry_window_showed=true;
}
}

/*
void GameBoard::win()
{
    this->close();  GameBoard* b=new GameBoard();
    b->updateLevel();
    b->show();

    QWidget* win_window=new QWidget;
    QVBoxLayout* win_layout=new QVBoxLayout;
    QLabel* you_win=new QLabel("You win! You can now get to the next level!");
    QLabel* win_dog_pic=new QLabel;
    win_dog_pic->setPixmap(*dog_image);
    win_dog_pic->setMinimumSize(200,200);
    win_dog_pic->setMaximumSize(200,200);
    win_dog_pic->setScaledContents(true);
    win_layout->addWidget(you_win);
    win_layout->addWidget(win_dog_pic);
    win_window->setLayout(win_layout);
    win_window->show();
    QTimer* t=new QTimer(win_window);
    connect (t,SIGNAL(timeout()),win_window,SLOT(close()));t->start(1000);



    delete this;

}*/

/*
void GameBoard::updateLevel()
{
  this->levels+=1; level_number->setText(QString::number(levels));
  this->cat_attack_speed=cat_attack_speed+0.15;
  if(cat_move_speed>=0) this->cat_move_speed-5;
}
*/

void win(GameBoard* b)
{
   b->close();
   b->lose_window_showed=true;
   b->retry_window_showed=true;
}

void nextLevel(GameBoard* b)
{
    QWidget* win_window=new QWidget;
    QVBoxLayout* win_layout=new QVBoxLayout;
    QHBoxLayout* win_layout2=new QHBoxLayout;
    QLabel* you_win=new QLabel("You win! You can now get to the next level!");
    QLabel* win_dog_pic=new QLabel;
    QPushButton* next_level_button=new QPushButton("Next Level");
    win_dog_pic->setPixmap(*(b->dog_image));
    win_dog_pic->setMinimumSize(200,200);
    win_dog_pic->setMaximumSize(200,200);
    win_dog_pic->setScaledContents(true);
    win_layout->addWidget(you_win);
    win_layout2->addWidget(win_dog_pic);
    win_layout2->addWidget(next_level_button);
    win_layout->addLayout(win_layout2);
    win_window->setLayout(win_layout);
    win_window->show();

    //create a new gameboard
    GameBoard* s=new GameBoard();
    s->setMainWindow(b->mw);
    s->setQuitwindow(b->qwindow);

    //make the game harder
    s->levels=b->levels+1; s->level_number->setText(QString::number(s->levels));
    s->cat_attack_speed=b->cat_attack_speed+0.15;
    if(s->cat_move_speed>=0) s->cat_move_speed=b->cat_move_speed-5;


    QObject::connect(next_level_button,SIGNAL(clicked()),win_window,SLOT(close()));
    QObject::connect(next_level_button,SIGNAL(clicked()),s,SLOT(show()));

}

