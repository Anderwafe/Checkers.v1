#include "figure.h"
#include <QApplication>
#include <QSizePolicy>

void Figure::resizeEvent(QResizeEvent *size)
{
    this->setPixmap(this->pixmap().scaled(size->size()));
}

void Figure::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit figureSelected(this);
        /*_parentWidget = this->parentWidget();
        this->hide();
        this->setParent(_boardWidget);
        move(this->mapToParent(event->pos()));
        this->show();
        b_move = true;*/
    }
}

void Figure::mouseMoveEvent(QMouseEvent *event)
{
    /*if((event->buttons() & Qt::LeftButton) && b_move)
    {
        move(this->mapToParent(event->pos()));
    }*/
}

void Figure::mouseReleaseEvent(QMouseEvent *event)
{
    /*if (event->button() == Qt::LeftButton && b_move)
    {
        b_move = false;
        qDebug() << pos().x() << " " << pos().y();
        emit turnAttempt(this, _parentWidget, QApplication::widgetAt(QCursor::pos()));
        this->hide();
        this->setParent(_parentWidget);
        this->show();
        //move(QPoint(0, 0));
    }*/
}

void Figure::parentResized(QResizeEvent *size)
{
    this->resize(size->size());
}

bool Figure::makeKing()
{
    this->isKing = true;
    QPixmap pixmap = QPixmap(isWhite ? ":/new/prefix1/checker_white_king" : ":/new/prefix1/checker_black_king");
    pixmap = pixmap.scaled(25, 25);
    this->setPixmap(pixmap.scaled(this->pixmap().size()));
    return true;
}


Figure::Figure(QWidget* parent, bool isWhite, QWidget *board) : QLabel()
{
    setParent(parent);
    _parentWidget = parent;
    isKing = false;

    //b_move = false;
    this->isWhite = isWhite;
    this->setBaseSize(25, 25);
    this->setMinimumSize(25,25);
    this->setAlignment(Qt::AlignCenter);

    _boardWidget = board;
    //move(QPoint(0,0));

    QPixmap pixmap = QPixmap(isWhite ? ":/new/prefix1/checker_white" : ":/new/prefix1/checker_black");
    pixmap = pixmap.scaled(25, 25);
    this->setPixmap(pixmap);
}

Figure::~Figure()
{
    if(availableTurns != nullptr) delete availableTurns;
    qDebug() << "шашка удалена";
}



