

#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
    Q_OBJECT
protected:
    bool isWhite;
    //Figure *figure;

public:
    Cell(QWidget *parent = nullptr, bool isWhite = false);
    //bool setFigure(Figure *figure = nullptr);
};

#endif // CELL_H
