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

    bool isWhite;
};

#endif // FIGURE_H
