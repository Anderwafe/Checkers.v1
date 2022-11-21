#ifndef BOARD_H
#define BOARD_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include "cell.h"
#include "figure.h"

class Board
{
protected:
    unsigned int h, w;
    unsigned int figuresCount;
    Cell **cells;
    Figure **figures;
    QVBoxLayout *layout;
    QHBoxLayout **columnLayouts;


public:
    Board(QWidget *parent = nullptr, unsigned int h = 10, unsigned int w = 10, unsigned int countOfFigures = 20);
    void Show();
    ~Board();
    QLayout* getBoard();
};

#endif // BOARD_H
