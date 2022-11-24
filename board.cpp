#include "board.h"

Board::Board(QWidget *parent, unsigned int h, unsigned int w, unsigned int countOfFigures)
{
    isWhiteTurn = true;

    _selectedFigure = nullptr;

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
            cells[i * w + j]->setObjectName(QString::number(i) + "_" + QString::number(j));
            columnLayouts[i]->addWidget(cells[i*w+j]);
            connect(cells[i * w + j], SIGNAL(cellSelected(Cell*)), this, SLOT(tryMakeTurn(Cell*)));
        }
    }

    figures = new Figure*[countOfFigures * 2];
    for(unsigned int i = 0, j = 0, k = h * w - 1; i < countOfFigures; i++)
    {
        while(cells[j]->isWhite) j++;
        figures[i] = new Figure(cells[j], false, parent);
        connect(figures[i], SIGNAL(figureSelected(Figure*)), this, SLOT(figureSelecting(Figure*)));
        connect(cells[0], SIGNAL(resized(QResizeEvent*)), figures[i], SLOT(parentResized(QResizeEvent*)));
        figures[i]->setObjectName(QString::number(i));
        j++;

        while(cells[k]->isWhite) k--;
        figures[countOfFigures * 2 - 1 - i] = new Figure(cells[k], true, parent);
        connect(figures[countOfFigures * 2 - 1 - i], SIGNAL(figureSelected(Figure*)), this, SLOT(figureSelecting(Figure*)));
        connect(cells[0], SIGNAL(resized(QResizeEvent*)), figures[countOfFigures * 2 - 1 - i], SLOT(parentResized(QResizeEvent*)));
        figures[countOfFigures * 2 - 1 - i]->setObjectName(QString::number(countOfFigures * 2 - 1 - i));
        k--;

    }
}

void Board::tryMakeTurn(Cell *cell)
{
    qDebug() << cell->objectName();
    if(_selectedFigure != nullptr)
    {
        int current_h = QString(((Cell*)_selectedFigure->parentWidget())->objectName()[0]).toInt();
        int current_w = QString(((Cell*)_selectedFigure->parentWidget())->objectName()[2]).toInt();

        int new_h = QString(cell->objectName()[0]).toInt();
        int new_w = QString(cell->objectName()[2]).toInt();
        if((abs(current_h - new_h) == 1) && (abs(current_w - new_w) == 1))
        {
            if(((new_h - current_h) == 1 && !_selectedFigure->isWhite) || ((new_h - current_h) == -1 && _selectedFigure->isWhite))
            {
                qDebug() << _selectedFigure->objectName();
                _selectedFigure->hide();
                _selectedFigure->setParent(nullptr);
                _selectedFigure->setParent(cell);
                _selectedFigure->show();

                _selectedFigure = nullptr;

                isWhiteTurn = !isWhiteTurn;
            }
        }
        if((abs(current_h - new_h) == 2) && (abs(current_w - new_w) == 2))
        {
            qDebug() << "abs ok";
            for(unsigned int i = 0; i < figuresCount * 2; i++)
            {
                if(!figures[i]->isHidden() && (figures[i] != nullptr))
                {
                    qDebug() << figures[i]->parentWidget()->objectName() << " " <<(QString::number((new_h + current_h) / 2) + "_" + QString::number((new_w + current_w) / 2));
                    if(figures[i]->parentWidget()->objectName() == (QString::number((new_h + current_h) / 2) + "_" + QString::number((new_w + current_w) / 2)))
                    {
                        qDebug() << "objectName is ok";
                        if((figures[i]->isWhite && !_selectedFigure->isWhite) || (!figures[i]->isWhite && _selectedFigure->isWhite))
                        {
                            qDebug() << "turn is ok";
                            qDebug() << _selectedFigure->objectName();
                            _selectedFigure->hide();
                            _selectedFigure->setParent(nullptr);
                            _selectedFigure->setParent(cell);
                            _selectedFigure->show();

                            _selectedFigure = nullptr;

                            isWhiteTurn = !isWhiteTurn;

                            figures[i]->hide();
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Board::figureSelecting(Figure *figure)
{
    qDebug() << "Touched: " << figure->objectName() << "Is white? " << figure->isWhite << " " << figure->parentWidget()->objectName();
    if((figure->isWhite && isWhiteTurn) || (!figure->isWhite && !isWhiteTurn))
    {
        qDebug() << "Selected ";
        this->_selectedFigure = figure;
    }
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
