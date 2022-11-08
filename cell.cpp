#include "cell.h"

Cell::Cell(QWidget *parent, bool isWhite, Figure *figureOnCell) : QLabel(parent)
{
    this->isWhite = isWhite;
    this->setMinimumSize(25, 25);
    this->setAutoFillBackground(true);
    if(isWhite) this->setPalette(QPalette(Qt::GlobalColor::blue));
            else this->setPalette(QPalette(Qt::GlobalColor::yellow));
    figure = figureOnCell;
}

