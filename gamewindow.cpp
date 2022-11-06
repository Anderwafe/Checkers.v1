#include "gamewindow.h"
#include "ui_gamewindow.h"
//#include "Figure.cpp"
#include "Board.cpp"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    Board* board = new Board(10, 10, 20);
    board->getBoard()->setParent(ui->gridLayout_groupbox_playground);
    delete board;
}

GameWindow::~GameWindow()
{
    delete ui;
}
