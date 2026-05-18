#ifndef CURVE_H
#define CURVE_H

#include "myfigure.h"

class Curve : public MyFigure
{
private:
    QVector<QPoint> points;
public:
    Curve(QWidget *parent, QColor color, std::uint32_t width) : MyFigure(parent, color, width) {}
    void init(QPointF p) override;
    void draw(QPainter *painter) override;
    void drag(QPointF p) override;
    void finalize() override {}
};

#endif // CURVE_H
