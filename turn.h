#ifndef TURN_H
#define TURN_H

#include <vector>
#include <QPoint>

class turn
{
public:
    QPoint start, stop;
    std::vector<std::vector<unsigned long long>> playground;
    int weight;

public:
    turn(QPoint start, QPoint stop, std::vector<std::vector<unsigned long long>> playground, int weight)
    {
        this->start = start;
        this->stop = stop;
        this->playground = playground;
        this->weight = weight;
    }
};

#endif // TURN_H
