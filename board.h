#ifndef BOARD_H
#define BOARD_H

#include <QGridLayout>
#include "cell.h"

class Board
{
protected:

public:
    Board(QWidget *parent = nullptr);
    void Show();
    ~Board();
    QGridLayout* getBoard();
};

#endif // BOARD_H
