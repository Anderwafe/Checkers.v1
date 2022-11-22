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
    for(unsigned int i = 0, j = 0, k = h * w - 1; i < countOfFigures; i++)
    {
        while(cells[j]->isWhite) j++;
        figures[i] = new Figure(cells[j], false, parent);
        connect(figures[i], SIGNAL(turnAttempt(Figure*,QWidget*,QWidget*)), this, SLOT(checkTurn(Figure*,QWidget*,QWidget*)));
        //figures[i] = new Figure(parent, false, cells[j]->pos());
        //cells[j]->setLayout(new QHBoxLayout(parent));
        //cells[j]->layout()->addWidget(figures[i]);
        j++;

        while(cells[k]->isWhite) k--;
        figures[countOfFigures * 2 - 1 - i] = new Figure(cells[k], true, parent);
        connect(figures[countOfFigures * 2 - 1 - i], SIGNAL(turnAttempt(Figure*,QWidget*,QWidget*)), this, SLOT(checkTurn(Figure*,QWidget*,QWidget*)));
        //figures[countOfFigures * 2 - 1 - i] = new Figure(parent, true, cells[k]->pos());
        //cells[k]->setLayout(new QHBoxLayout(parent));
        //cells[k]->layout()->addWidget(figures[countOfFigures * 2 - 1 - i]);
        k--;

    }
}

void Board::checkTurn(Figure *figure, QWidget *start_pos, QWidget *new_pos)
{

}

void Board::Show()
{
    for(unsigned int i = 0; i < w*h; i++)
    {
        cells[i]->show();
    }
    for(unsigned int i = 0; i < figuresCount; i++)
    {
        figures[i]->show();
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
