#include <QCursor>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

class Figure : public QLabel
{
protected:
    bool b_move;
    QPoint* start_point = nullptr;
    QPoint* prev_point = nullptr;
    bool isWhite;

    void resizeEvent(QResizeEvent *size)
    {
        this->setPixmap(this->pixmap().scaled(size->size()));
    }

    void mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
        {
            start_point = new QPoint(this->pos());
            if(prev_point == nullptr)
                prev_point = new QPoint(QCursor::pos());
            b_move = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if((event->buttons() & Qt::LeftButton) && b_move)
        {
            move(QCursor::pos() - *prev_point);
        }
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton && b_move)
        {
            qDebug() << this->pos().x() << " " << this->pos().y();
            this->move(*start_point);
            b_move = false;
        }
    }

public:
    Figure(QWidget* parent = nullptr, bool isWhite = true) : QLabel(parent)
    {
        b_move = false;
        //this->setText("Label)");
        this->isWhite = isWhite;
        this->setBaseSize(50, 50);
        this->setMinimumSize(50,50);
        this->setAlignment(Qt::AlignCenter);

        QPixmap pixmap = QPixmap(isWhite ? ":/new/prefix1/checker_white" : ":/new/prefix1/checker_black");
        pixmap = pixmap.scaled(50, 50);
        this->setPixmap(pixmap);
    }

    ~Figure()
    {
        delete start_point;
        delete prev_point;
    }
};
