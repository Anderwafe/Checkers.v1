#ifndef TREE_H
#define TREE_H

#include <QPoint>
#include <vector>
////#include "figure.h"
#include "turn.h"

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
        /*if(!isking)
        {
            switch(thisbranch)
            {
            case 0:
                ur.push_back(this);
                break;
            case 1:
                ul.push_back(this);
                break;
            case 2:
                dl.push_back(this);
                break;
            case 3:
                dr.push_back(this);
                break;
            }
        }*/
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
                    if(playground[pos.y() + (isWhite ? -i : i)][pos.x() - i] == 0)
                    {
                        if(iteration == 1)
                        {

                        }
                    }
                    else
                    {

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
            auto aa1 = ur[i]->getTurns();
            for(int j = 0; j < aa1.size(); j++)
            {
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < ul.size(); i++)
        {
            auto aa1 = ul[i]->getTurns();
            for(int j = 0; j < aa1.size(); j++)
            {
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < dl.size(); i++)
        {
            auto aa1 = dl[i]->getTurns();
            for(int j = 0; j < aa1.size(); j++)
            {
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < dr.size(); i++)
        {
            auto aa1 = dr[i]->getTurns();
            for(int j = 0; j < aa1.size(); j++)
            {
                res.push_back(aa1[j]);
            }
        }

        for(unsigned long i = 0; i < res.size(); i++)
        {
            res[i].start = pos;
            res[i].weight += this->weight;
        }
        return res;
    }
};

#endif // TREE_H
