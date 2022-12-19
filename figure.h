#ifndef FIGURE_H
#define FIGURE_H

#include <QCursor>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPoint>
#include <vector>
//#include "tree.h"
#include "turn.h"

class tree;

class Figure : public QLabel
{
    Q_OBJECT
protected:

    QWidget *_parentWidget;
    QWidget *_boardWidget;

    void resizeEvent(QResizeEvent *size);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void parentResized(QResizeEvent *size);

signals:
    void figureSelected(Figure *figure);

public:
    Figure(QWidget *parent = nullptr, bool isWhite = true, QWidget *board = nullptr);
    ~Figure();

    tree *availableTurns = nullptr;

    bool isKing;
    bool makeKing();

    bool isWhite;
};



class tree
{
    QPoint pos;//позиция хода
    int weight;//была ли убита фигура
    std::vector<std::vector<unsigned long long>> playground;

    bool isking;

    std::vector<tree*> ur;// деревья ходов
    std::vector<tree*> ul;
    std::vector<tree*> dl;
    std::vector<tree*> dr;
public:
    // iteration[0] = 1;
    tree(QPoint pos, int weight, bool isking, std::vector<std::vector<unsigned long long>> playground, bool isWhite, int iteration = 1)
    {
        this->isking = isking;
        this->pos = pos;
        this->weight = weight;
        this->playground = playground;
        if(weight == 0)
        {
            if(iteration != 1)
            {
                return;
            }
        }
        if(isking)
        {
            if((pos.y() != 0) && (pos.x() != 0))
            {
                int i = 1;
                while((pos.y() - i != -1) && (pos.x() - i != -1))
                {
                    if(playground[pos.y() - i][pos.x() - i] == 0)
                    {
                        if(iteration == 1)
                        {
                            std::vector<std::vector<unsigned long long>> buf = playground;
                            buf[pos.y() - i][pos.x() - i] = playground[pos.y()][pos.x()];
                            buf[pos.y()][pos.x()] = 0;
                            ul.push_back(new tree(QPoint(pos.x()-i, pos.y() - i), 0, true, buf, isWhite, iteration+1));
                        }
                    }
                    else
                    {
                        Figure *figure_on_cell = (Figure*)playground[pos.y() - i][pos.x() - i];
                        if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                        {
                            if((pos.y() - i - 1 != -1) && (pos.x() - i - 1 != -1))
                            {
                                int j = i + 1;
                                if(playground[pos.y()-j][pos.x()-j] == 0)
                                {
                                    for(unsigned int k = 0; k < ul.size(); k++)
                                    {
                                        delete ul[k];
                                    }
                                    ul.clear();

                                    while((pos.y() - j != -1) && (pos.x() - j != -1))
                                    {
                                        if(playground[pos.y() - j][pos.x() - j] == 0)
                                        {
                                            std::vector<std::vector<unsigned long long>> buf = playground;
                                            buf[pos.y() - j][pos.x() - j] = playground[pos.y()][pos.x()];
                                            buf[pos.y() - i][pos.x() - i] = 0;
                                            buf[pos.y()][pos.x()] = 0;
                                            ul.push_back(new tree(QPoint(pos.x()-j, pos.y() - j), 1, true, buf, isWhite, iteration+1));
                                        }
                                        else
                                        {
                                            break;
                                        }
                                        j++;
                                    }
                                }
                            }
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                    i++;
                }
            }

            if((pos.y() != 9) && (pos.x() != 0))
            {
                int i = 1;
                while((pos.y() + i != 10) && (pos.x() - i != -1))
                {
                    if(playground[pos.y() + i][pos.x() - i] == 0)
                    {
                        if(iteration == 1)
                        {
                            std::vector<std::vector<unsigned long long>> buf = playground;
                            buf[pos.y() + i][pos.x() - i] = playground[pos.y()][pos.x()];
                            buf[pos.y()][pos.x()] = 0;
                            dl.push_back(new tree(QPoint(pos.x()-i, pos.y() + i), 0, true, buf, isWhite, iteration+1));
                        }
                    }
                    else
                    {
                        Figure *figure_on_cell = (Figure*)playground[pos.y() + i][pos.x() - i];
                        if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                        {
                            if((pos.y() + i + 1 != 10) && (pos.x() - i - 1 != -1))
                            {
                                int j = i + 1;
                                if(playground[pos.y()+j][pos.x()-j] == 0)
                                {
                                    for(unsigned int k = 0; k < dl.size(); k++)
                                    {
                                        delete dl[k];
                                    }
                                    dl.clear();


                                    while((pos.y() + j != 10) && (pos.x() - j != -1))
                                    {
                                        if(playground[pos.y() + j][pos.x() - j] == 0)
                                        {
                                            std::vector<std::vector<unsigned long long>> buf = playground;
                                            buf[pos.y() + j][pos.x() - j] = playground[pos.y()][pos.x()];
                                            buf[pos.y() + i][pos.x() - i] = 0;
                                            buf[pos.y()][pos.x()] = 0;
                                            dl.push_back(new tree(QPoint(pos.x()-j, pos.y() + j), 1, true, buf, isWhite, iteration+1));
                                        }
                                        else
                                        {
                                            break;
                                        }
                                        j++;
                                    }
                                }
                            }
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                    i++;
                }
            }

            if((pos.y() != 9) && (pos.x() != 9))
            {
                int i = 1;
                while((pos.y() + i != 10) && (pos.x() + i != 10))
                {
                    if(playground[pos.y() + i][pos.x() + i] == 0)
                    {
                        if(iteration == 1)
                        {
                            std::vector<std::vector<unsigned long long>> buf = playground;
                            buf[pos.y() + i][pos.x() + i] = playground[pos.y()][pos.x()];
                            buf[pos.y()][pos.x()] = 0;
                            dr.push_back(new tree(QPoint(pos.x()+i, pos.y() + i), 0, true, buf, isWhite, iteration+1));
                        }
                    }
                    else
                    {
                        Figure *figure_on_cell = (Figure*)playground[pos.y() + i][pos.x() + i];
                        if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                        {
                            if((pos.y() + i + 1 != 10) && (pos.x() + i + 1 != 10))
                            {
                                int j = i + 1;
                                if(playground[pos.y()+j][pos.x()+j] == 0)
                                {
                                    for(unsigned int k = 0; k < dr.size(); k++)
                                    {
                                        delete dr[k];
                                    }
                                    dr.clear();

                                    while((pos.y() + j != 10) && (pos.x() + j != 10))
                                    {
                                        if(playground[pos.y() + j][pos.x() + j] == 0)
                                        {
                                            std::vector<std::vector<unsigned long long>> buf = playground;
                                            buf[pos.y() + j][pos.x() + j] = playground[pos.y()][pos.x()];
                                            buf[pos.y() + i][pos.x() + i] = 0;
                                            buf[pos.y()][pos.x()] = 0;
                                            dr.push_back(new tree(QPoint(pos.x()+j, pos.y() + j), 1, true, buf, isWhite, iteration+1));
                                        }
                                        else
                                        {
                                            break;
                                        }
                                        j++;
                                    }
                                }
                            }
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                    i++;
                }
            }

            if((pos.y() != 0) && (pos.x() != 9))
            {
                int i = 1;
                while((pos.y() - i != -1) && (pos.x() + i != 10))
                {
                    if(playground[pos.y() - i][pos.x() + i] == 0)
                    {
                        if(iteration == 1)
                        {
                            std::vector<std::vector<unsigned long long>> buf = playground;
                            buf[pos.y() - i][pos.x() + i] = playground[pos.y()][pos.x()];
                            buf[pos.y()][pos.x()] = 0;
                            ur.push_back(new tree(QPoint(pos.x()+i, pos.y() - i), 0, true, buf, isWhite, iteration+1));
                        }
                    }
                    else
                    {
                        Figure *figure_on_cell = (Figure*)playground[pos.y() - i][pos.x() + i];
                        if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                        {
                            if((pos.y() - i - 1 != -1) && (pos.x() + i + 1 != 10))
                            {
                                int j = i + 1;
                                if(playground[pos.y()-j][pos.x()+j] == 0)
                                {
                                    for(unsigned int k = 0; k < ur.size(); k++)
                                    {
                                        delete ur[k];
                                    }
                                    ur.clear();

                                    while((pos.y() - j != -1) && (pos.x() + j != 10))
                                    {
                                        if(playground[pos.y() - j][pos.x() + j] == 0)
                                        {
                                            std::vector<std::vector<unsigned long long>> buf = playground;
                                            buf[pos.y() - j][pos.x() + j] = playground[pos.y()][pos.x()];
                                            buf[pos.y() - i][pos.x() + i] = 0;
                                            buf[pos.y()][pos.x()] = 0;
                                            ur.push_back(new tree(QPoint(pos.x()+j, pos.y() - j), 1, true, buf, isWhite, iteration+1));
                                        }
                                        else
                                        {
                                            break;
                                        }
                                        j++;
                                    }
                                }
                            }
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                    i++;
                }
            }
        }
        else
        {
            if((isWhite ? pos.y() != 0 : pos.y() != 9) && (pos.x() != 0))
            {
                if(playground[pos.y() + (isWhite ? -1 : 1)][pos.x() - 1] == 0)
                {
                    if(iteration == 1)
                    {
                        std::vector<std::vector<unsigned long long>> buf = playground;
                        buf[pos.y() + (isWhite ? -1 : 1)][pos.x() - 1] = playground[pos.y()][pos.x()];
                        buf[pos.y()][pos.x()] = 0;
                        (isWhite ? ul : dl).push_back(new tree(QPoint(pos.x()-1, pos.y() + (isWhite ? -1 : 1)), 0, false, buf, isWhite, iteration+1));
                    }
                }
                else
                {
                    Figure *figure_on_cell = (Figure*)playground[pos.y() + (isWhite ? -1 : 1)][pos.x() - 1];
                    if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                    {
                        if((isWhite ? pos.y() != 1 : pos.y() != 8) && (pos.x() != 1))
                        {
                            if(playground[pos.y() + (isWhite ? -2 : 2)][pos.x() - 2] == 0)
                            {
                                std::vector<std::vector<unsigned long long>> buf = playground;
                                buf[pos.y() + (isWhite ? -2 : 2)][pos.x() - 2] = playground[pos.y()][pos.x()];
                                buf[pos.y()][pos.x()] = 0;
                                buf[pos.y() + (isWhite ? -1 : 1)][pos.x() - 1] = 0;
                                (isWhite ? ul : dl).push_back(new tree(QPoint(pos.x()-2, pos.y() + (isWhite ? -2 : 2)), 1, false, buf, isWhite, iteration+1));
                            }
                        }
                    }
                }
            }

            if((isWhite ? pos.y() != 0 : pos.y() != 9) && (pos.x() != 9))
            {
                if(playground[pos.y() + (isWhite ? -1 : 1)][pos.x() + 1] == 0)
                {
                    if(iteration == 1)
                    {
                        std::vector<std::vector<unsigned long long>> buf = playground;
                        buf[pos.y() + (isWhite ? -1 : 1)][pos.x() + 1] = playground[pos.y()][pos.x()];
                        buf[pos.y()][pos.x()] = 0;
                        (isWhite ? ur : dr).push_back(new tree(QPoint(pos.x()+1, pos.y() + (isWhite ? -1 : 1)), 0, false, buf, isWhite, iteration+1));
                    }
                }
                else
                {
                    Figure *figure_on_cell = (Figure*)playground[pos.y() + (isWhite ? -1 : 1)][pos.x() + 1];
                    if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                    {
                        if((isWhite ? pos.y() != 1 : pos.y() != 8) && (pos.x() != 8))
                        {
                            if(playground[pos.y() + (isWhite ? -2 : 2)][pos.x() + 2] == 0)
                            {
                                std::vector<std::vector<unsigned long long>> buf = playground;
                                buf[pos.y() + (isWhite ? -2 : 2)][pos.x() + 2] = playground[pos.y()][pos.x()];
                                buf[pos.y()][pos.x()] = 0;
                                buf[pos.y() + (isWhite ? -1 : 1)][pos.x() + 1] = 0;
                                (isWhite ? ur : dr).push_back(new tree(QPoint(pos.x()+2, pos.y() + (isWhite ? -2 : 2)), 1, false, buf, isWhite, iteration+1));
                            }
                        }
                    }
                }
            }

            if((isWhite ? pos.y() != 9 : pos.y() != 0) && (pos.x() != 0))
            {
                if(playground[pos.y() + (isWhite ? 1 : -1)][pos.x() - 1] != 0)
                {
                    Figure *figure_on_cell = (Figure*)playground[pos.y() + (isWhite ? 1 : -1)][pos.x() - 1];
                    if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                    {
                        if((isWhite ? pos.y() != 8 : pos.y() != 1) && (pos.x() != 1))
                        {
                            if(playground[pos.y() + (isWhite ? 2 : -2)][pos.x() - 2] == 0)
                            {
                                std::vector<std::vector<unsigned long long>> buf = playground;
                                buf[pos.y() + (isWhite ? 2 : -2)][pos.x() - 2] = playground[pos.y()][pos.x()];
                                buf[pos.y()][pos.x()] = 0;
                                buf[pos.y() + (isWhite ? 1 : -1)][pos.x() - 1] = 0;
                                (isWhite ? dl : ul).push_back(new tree(QPoint(pos.x()-2, pos.y() + (isWhite ? 2 : -2)), 1, false, buf, isWhite, iteration+1));
                            }
                        }
                    }
                }
            }

            if((isWhite ? pos.y() != 9 : pos.y() != 0) && (pos.x() != 9))
            {
                if(playground[pos.y() + (isWhite ? 1 : -1)][pos.x() + 1] != 0)
                {
                    Figure *figure_on_cell = (Figure*)playground[pos.y() + (isWhite ? 1 : -1)][pos.x() + 1];
                    if((figure_on_cell->isWhite && !isWhite) || (!figure_on_cell->isWhite && isWhite))
                    {
                        if((isWhite ? pos.y() != 8 : pos.y() != 1) && (pos.x() != 8))
                        {
                            if(playground[pos.y() + (isWhite ? 2 : -2)][pos.x() + 2] == 0)
                            {
                                std::vector<std::vector<unsigned long long>> buf = playground;
                                buf[pos.y() + (isWhite ? 2 : -2)][pos.x() + 2] = playground[pos.y()][pos.x()];
                                buf[pos.y()][pos.x()] = 0;
                                buf[pos.y() + (isWhite ? 1 : -1)][pos.x() + 1] = 0;
                                (isWhite ? dr : ur).push_back(new tree(QPoint(pos.x()+2, pos.y() + (isWhite ? 2 : -2)), 1, false, buf, isWhite, iteration+1));
                            }
                        }
                    }
                }
            }
        }
    }

    ~tree()
    {
        playground.clear();
        for(unsigned long i = 0; i < ur.size(); i++)
        {
            delete ur[i];
        }

        for(unsigned long i = 0; i < ul.size(); i++)
        {
            delete ul[i];
        }

        for(unsigned long i = 0; i < dl.size(); i++)
        {
            delete dl[i];
        }

        for(unsigned long i = 0; i < dr.size(); i++)
        {
            delete dr[i];
        }
        ur.clear();
        ul.clear();
        dr.clear();
        dl.clear();
    }

    std::vector<turn> getTurns()
    {
        if(ur.empty() && ul.empty() && dl.empty() && dr.empty())
        {
            std::vector<turn> a;
            a.push_back(turn(pos, pos, playground, weight));
            return a;
        }
        std::vector<turn> res;

        for(unsigned long i = 0; i < ur.size(); i++)
        {
            std::vector<turn> aa1 = ur[i]->getTurns();
            for(unsigned int j = 0; j < aa1.size(); j++)
            {
                aa1[j].start = pos;
                aa1[j].weight += this->weight;
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < ul.size(); i++)
        {
            auto aa1 = ul[i]->getTurns();
            for(unsigned long j = 0; j < aa1.size(); j++)
            {
                aa1[j].start = pos;
                aa1[j].weight += this->weight;
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < dl.size(); i++)
        {
            auto aa1 = dl[i]->getTurns();
            for(unsigned long j = 0; j < aa1.size(); j++)
            {
                aa1[j].start = pos;
                aa1[j].weight += this->weight;
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < dr.size(); i++)
        {
            auto aa1 = dr[i]->getTurns();
            for(unsigned long j = 0; j < aa1.size(); j++)
            {
                aa1[j].start = pos;
                aa1[j].weight += this->weight;
                res.push_back(aa1[j]);
            }
        }

        return res;
    }
};

#endif // FIGURE_H
