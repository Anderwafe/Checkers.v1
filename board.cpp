#include "board.h"

Board::Board(QWidget *parent, unsigned int h, unsigned int w, unsigned int countOfFigures)
{
    this->h = h;
    this->w = w;
    figuresCount = countOfFigures;

    layout = new QVBoxLayout(parent);
    columnLayouts = new QHBoxLayout*[h];
    cells = new Cell*[h * w];
    for(unsigned int i = 0; i < h; i++)
    {
        columnLayouts[i] = new QHBoxLayout();
        layout->addLayout(columnLayouts[i]);
        for(unsigned int j = 0; j < w; j++)
        {
            cells[i * w + j] = new Cell(parent, !((j % 2 + i % 2) % 2));
            columnLayouts[i]->addWidget(cells[i*w+j]);
        }
    }

    figures = new Figure*[countOfFigures * 2];
    for(unsigned int i = 0; i < countOfFigures; i++)
    {
        figures[i] = new Figure(parent, true);
        figures[countOfFigures * 2 - 1 - i] = new Figure(parent, false);

    }
}

void Board::Show()
{
    for(unsigned int i = 0; i < w*h; i++)
    {
        cells[i]->show();
    }
}

Board::~Board()
{
    delete layout;
    delete[] columnLayouts;
    delete[] figures;
    delete[] cells;
}

QLayout* Board::getBoard()
{
    return layout;
}
