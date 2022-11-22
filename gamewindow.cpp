#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = new Board(ui->groupBox);
    ui->groupBox->setLayout(board->getBoard());
    board->Show();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}
