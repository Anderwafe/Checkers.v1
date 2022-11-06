#include <QFrame>
#include <QWidget>
#include <QGridLayout>
#include "Figure.cpp"

class Board
{
    QGridLayout *layout;
    QFrame **cells;
    //Figure *figures;

public:
    Board(int h, int w, int figuresCount)
    {
        layout = new QGridLayout();

        cells = new QFrame*[h*w];

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                cells[i*w + j] = new QFrame();
                layout->addWidget(cells[i*w + j]);
                cells[i*w + j]->setLineWidth(2);
                cells[i*w + j]->setPalette(QPalette((j % 2) + (i%2) ? Qt::GlobalColor::white : Qt::GlobalColor::gray));

            }
        }
    }

    ~Board()
    {
        delete layout;
        delete[] cells;
        //delete[] figures;
    }

    QGridLayout* getBoard()
    {

        return layout;
    }
};
