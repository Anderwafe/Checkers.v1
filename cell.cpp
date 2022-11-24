#include "cell.h"

Cell::Cell(QWidget *parent, bool isWhite) : QLabel(parent)
{
    this->isWhite = isWhite;
    this->setMinimumSize(25, 25);
    this->setAutoFillBackground(true);
    if(isWhite) this->setPalette(QPalette(Qt::GlobalColor::white));
            else this->setPalette(QPalette(Qt::GlobalColor::darkGray));
}

void Cell::resizeEvent(QResizeEvent *size)
{
    emit resized(size);
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit cellSelected(this);
    }
}
