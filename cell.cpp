#include "cell.h"

Cell::Cell(QWidget *parent, bool isWhite, Figure *figureOnCell) : QLabel(parent)
{
    this->isWhite = isWhite;
    this->setMinimumSize(25, 25);
    this->setAutoFillBackground(true);
    if(isWhite) this->setPalette(QPalette(Qt::GlobalColor::white));
            else this->setPalette(QPalette(Qt::GlobalColor::black));
    figure = figureOnCell;
    figureOnCell->setParent(this);
    figureOnCell->move(this->pos() - figureOnCell->pos());
}

bool Cell::setFigure(Figure *figure)
{
    if(figure != nullptr)
    {
        this->figure = figure;
        return true;
    }
    else
    {
        return false;
    }
}
