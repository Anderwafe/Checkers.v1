#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = new Board();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}
