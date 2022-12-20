#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "board.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void takeMessage(QString message);
    void takeTurnInfo(turn info);

private:
    Ui::GameWindow *ui;
    Board* board;
};

#endif // GAMEWINDOW_H
