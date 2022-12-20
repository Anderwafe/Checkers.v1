#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = new Board(ui->groupBox);
    ui->groupBox->setLayout(board->getBoard());
    connect(board, SIGNAL(messageCreated(QString)), this, SLOT(takeMessage(QString)));
    board->Show();
}

void GameWindow::takeMessage(QString message)
{
    this->ui->statusbar->showMessage(message, 0);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}
