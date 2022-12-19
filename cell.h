#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

class Cell : public QLabel
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *size);

signals:
    void cellSelected(Cell *cell);
    void resized(QResizeEvent *size);

public:
    Cell(QWidget *parent = nullptr, bool isWhite = false);

    bool isWhite;
};

#endif // CELL_H
