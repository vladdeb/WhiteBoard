#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "myfigure.h"

class Ellipse : public MyFigure
{
private:
    QPointF start, end;
public:
    Ellipse(QWidget *parent, QColor color, std::uint32_t width) : MyFigure(parent, color, width) {}
    void init(QPointF p) override;
    void draw(QPainter *painter) override;
    void drag(QPointF p) override;
    void finalize() override {}

    Types type() override;
    QJsonObject toJson() override;
    void fromJson(const QJsonObject& json) override;
};

#endif // ELLIPSE_H
