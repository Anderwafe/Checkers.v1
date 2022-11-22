#ifndef FIGURE_H
#define FIGURE_H

#include <QCursor>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

class Figure : public QLabel
{
    Q_OBJECT
protected:
    bool b_move;
    bool isWhite;

    QWidget *_parentWidget;
    QWidget *_boardWidget;

    void resizeEvent(QResizeEvent *size);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void turnAttempt(Figure *figure, QWidget *start_pos, QWidget *new_pos);

public:
    Figure(QWidget *parent = nullptr, bool isWhite = true, QWidget *board = nullptr);
    ~Figure();
    bool changeDefaultPos(QPoint new_pos);
};

#endif // FIGURE_H
