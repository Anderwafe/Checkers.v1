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
    this->ui->statusbar->showMessage("White turn", 0);

    connect(board, SIGNAL(turnComplete(turn)), this, SLOT(takeTurnInfo(turn)));
    board->Show();
}

void GameWindow::takeMessage(QString message)
{
    this->ui->statusbar->showMessage(message, 0);
}

void GameWindow::takeTurnInfo(turn info)
{
    this->ui->listWidget->addItem(QString(QString::number(info.start.x()) + "x" + QString::number(info.start.y()) + "; Weight: " + QString::number(info.weight)));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}
