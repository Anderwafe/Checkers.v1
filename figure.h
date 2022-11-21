#ifndef FIGURE_H
#define FIGURE_H

#include <QCursor>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

#include "cell.h"

class Figure : public QLabel
{
    Q_OBJECT
protected:
    bool b_move;
    QPoint* start_point = nullptr;
    QPoint* prev_point = nullptr;
    bool isWhite;
    Cell *cell;

    void resizeEvent(QResizeEvent *size);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    Figure(QWidget* parent = nullptr, bool isWhite = true);
    ~Figure();

};

#endif // FIGURE_H
