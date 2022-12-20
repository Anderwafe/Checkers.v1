#include "board.h"

#include <QMessageBox>

Board::Board(QWidget *parent, unsigned int h, unsigned int w, unsigned int countOfFigures)
{
    _selectedFigure = nullptr;

    this->h = h;
    this->w = w;
    figuresCount = countOfFigures;

    layout = new QVBoxLayout(parent);
    columnLayouts = new QHBoxLayout*[h];
    for(unsigned int i = 0; i < h; i++)
    {
        columnLayouts[i] = new QHBoxLayout();
        layout->addLayout(columnLayouts[i]);
        for(unsigned int j = 0; j < w; j++)
        {
            cells.push_back(new Cell(parent, !((j % 2 + i % 2) % 2)));
            cells[i*w + j]->setObjectName(QString::number(i) + "_" + QString::number(j));
            columnLayouts[i]->addWidget(cells[i*w + j]);
            connect(cells[i*w + j], SIGNAL(cellSelected(Cell*)), this, SLOT(tryMakeTurn(Cell*)));
        }
    }

    figures.resize(countOfFigures * 2);
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



    startTurn(true);
}

Figure* Board::findFigureOnCell(Cell *cell)
{
    for(unsigned int i = 0; i < figuresCount * 2; i++)
    {
        if((figures[i] == nullptr) || (figures[i]->isHidden())) continue;
        if(figures[i]->parentWidget()->objectName() == cell->objectName())
            return figures[i];
    }
    return nullptr;
}

void Board::startTurn(bool isWhiteTurn)
{
    _selectedFigure = nullptr;
    this->isWhiteTurn = isWhiteTurn;

    for(unsigned int i = 0; i < figuresCount * 2; i++)
    {
        if(figures[i]->isHidden())
        {
            figures[i]->setParent(nullptr);
        }
        else
        {
            if(((figures[i]->parentWidget()->objectName()[0] == '0') && (figures[i]->isWhite)) || ((figures[i]->parentWidget()->objectName()[0] == '9') && (!figures[i]->isWhite)))
            {
                figures[i]->makeKing();
            }
        }
    }

    std::vector<std::vector<unsigned long long>> buf;
    for(unsigned int j = 0; j < h; j++)
    {
        buf.push_back(std::vector<unsigned long long>());
        for(unsigned int k = 0; k < w; k++)
        {
            buf[j].push_back((unsigned long long)(findFigureOnCell(cells[j*w + k]) == nullptr ? 0 : findFigureOnCell(cells[j*w + k])));
        }
    }

    turns.clear();
    for(unsigned int i = 0; i < figuresCount; i++)
    {
        if(figures[i + (isWhiteTurn ? 0 : figuresCount)]->parentWidget() != nullptr)
        {
            if(figures[i + (isWhiteTurn ? 0 : figuresCount)]->availableTurns != nullptr)
            {
                delete figures[i + (isWhiteTurn ? 0 : figuresCount)]->availableTurns;
                figures[i + (isWhiteTurn ? 0 : figuresCount)]->availableTurns = nullptr;
            }
        }
        if(figures[i + (isWhiteTurn ? figuresCount : 0)]->parentWidget() != nullptr)
        {
            QPoint pos = QPoint(figures[i + (isWhiteTurn ? figuresCount : 0)]->parentWidget()->objectName()[2].digitValue(), figures[i + (isWhiteTurn ? figuresCount : 0)]->parentWidget()->objectName()[0].digitValue());
            figures[i + (isWhiteTurn ? figuresCount : 0)]->availableTurns = new tree(pos, 0, figures[i + (isWhiteTurn ? figuresCount : 0)]->isKing, buf, figures[i + (isWhiteTurn ? figuresCount : 0)]->isWhite);
            auto bufturns = figures[i + (isWhiteTurn ? figuresCount : 0)]->availableTurns->getTurns();
            for(unsigned long j = 0; j < bufturns.size(); j++)
            {
                turns.push_back(bufturns[j]);
            }
        }
    }
    if(turns.empty())
    {
        QMessageBox::information(nullptr, "Winner!", this->isWhiteTurn ? "Black wins!" : "White wins!");
    }

    emit messageCreated(this->isWhiteTurn ? "White turn" : "Black turn");
}

void Board::moveFigure(Figure *figure, Cell *cell)
{
    figure->hide();
    figure->setParent(nullptr);
    figure->setParent(cell);
    figure->show();
}

void Board::tryMakeTurn(Cell *cell)
{
    qDebug() << cell->objectName();
    if(_selectedFigure == nullptr) return;

    auto figureturns = _selectedFigure->availableTurns->getTurns();
    for(unsigned long i = 0; i < figureturns.size(); i++)
    {
        QString name = QString::number(figureturns[i].stop.y()) + "_" + QString::number(figureturns[i].stop.x());
        if(name == cell->objectName())
        {
            bool trueTurn = true;
            for(unsigned long j = 0; j < turns.size(); j++)
            {
                if(figureturns[i].weight < turns[j].weight)
                {
                    trueTurn = false;
                    break;
                }
            }
            if(!trueTurn) continue;
            for(unsigned int j = 0; j < figuresCount * 2; j++)
            {
                if(figures[j] == nullptr) continue;
                figures[j]->hide();
            }

            for(unsigned int j = 0; j < h; j++)
            {
                for(unsigned int k = 0; k < w; k++)
                {
                    if(figureturns[i].playground[j][k] != 0)
                    {
                        moveFigure((Figure*)figureturns[i].playground[j][k], cells[j * w + k]);
                    }
                }
            }
            startTurn(!isWhiteTurn);
            return;
        }
    }
    emit messageCreated("Wrong turn!");
}

void Board::figureSelecting(Figure *figure)
{
    qDebug() << "Touched: " << figure->objectName() << "Is white? " << figure->isWhite << " " << figure->parentWidget()->objectName();

    if((figure->isWhite && isWhiteTurn) || (!figure->isWhite && !isWhiteTurn))
    {

        auto figureturns = figure->availableTurns->getTurns();
        if(figure == _selectedFigure)
        {
            for(unsigned int i = 0; i < figureturns.size(); i++)
            {
                if(figureturns[i].start == figureturns[i].stop)
                {
                    tryMakeTurn(cells[figureturns[i].stop.y() * w + figureturns[i].stop.x()]);
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < figureturns.size(); i++)
            {
                qDebug() << "Point: " << figureturns[i].stop << "; Weight: " << figureturns[i].weight;
            }
        }

        qDebug() << "selected";

        _selectedFigure = figure;
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
    figures.clear();
    cells.clear();
}

QLayout* Board::getBoard()
{
    return layout;
}
