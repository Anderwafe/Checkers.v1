#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "figure.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = new Board(this);
    ui->groupBox->setLayout(board->getBoard());
    board->Show();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}
