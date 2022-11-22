#include "figure.h"
#include <QApplication>
void Figure::resizeEvent(QResizeEvent *size)
{
    this->setPixmap(this->pixmap().scaled(size->size()));
}

void Figure::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _parentWidget = this->parentWidget();
        this->hide();
        this->setParent(_boardWidget);
        move(this->mapToParent(event->pos()));
        this->show();
        b_move = true;
    }
}

void Figure::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && b_move)
    {
        move(this->mapToParent(event->pos()));
    }
}

void Figure::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && b_move)
    {
        b_move = false;
        qDebug() << pos().x() << " " << pos().y();
        emit turnAttempt(this, _parentWidget, QApplication::widgetAt(QCursor::pos()));
        this->hide();
        this->setParent(_parentWidget);
        this->show();
        //move(QPoint(0, 0));
    }
}

bool Figure::changeDefaultPos(QPoint new_pos)
{
    if(new_pos.x() < 0 || new_pos.y() < 0) return false;
    return true;
}

Figure::Figure(QWidget* parent, bool isWhite, QWidget *board) : QLabel()
{
    setParent(parent);
    _parentWidget = parent;

    b_move = false;
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
    qDebug() << "шашка удалена";
}
