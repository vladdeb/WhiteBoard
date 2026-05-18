#pragma once
#ifndef LINE_H
#define LINE_H

#include "myfigure.h"

class Line : public MyFigure
{
private:
    QPointF start, end;
public:
    Line(QWidget *parent, QColor color, std::uint32_t width) : MyFigure(parent, color, width) {}
    void init(QPointF p) override;
    void draw(QPainter *painter) override;
    void drag(QPointF p) override;
    void finalize() override {}
};

#endif // LINE_H
