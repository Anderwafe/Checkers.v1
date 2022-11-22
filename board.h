#ifndef BOARD_H
#define BOARD_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include "cell.h"
#include "figure.h"
#include <QObject>

class Board : public QObject
{
    Q_OBJECT
protected:
    unsigned int h, w;
    unsigned int figuresCount;
    Cell **cells;
    Figure **figures;
    QVBoxLayout *layout;
    QHBoxLayout **columnLayouts;

public slots:
    void checkTurn(Figure *figure, QWidget *start_pos, QWidget *new_pos);

public:
    Board(QWidget *parent = nullptr, unsigned int h = 10, unsigned int w = 10, unsigned int countOfFigures = 20);
    void Show();
    ~Board();
    QLayout* getBoard();
};

#endif // BOARD_H
