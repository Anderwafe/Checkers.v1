#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include "figure.h"

class Cell : public QLabel
{
    Q_OBJECT
protected:
    bool isWhite;
    Figure *figure;

public:
    Cell(QWidget *parent = nullptr, bool isWhite = false, Figure *figureOnCell = nullptr);
};

#endif // CELL_H
