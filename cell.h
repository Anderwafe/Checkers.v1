

#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
    Q_OBJECT
protected:

public:
    Cell(QWidget *parent = nullptr, bool isWhite = false);

    bool isWhite;
};

#endif // CELL_H
