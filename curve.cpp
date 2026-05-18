#include "curve.h"
#include "canvas.h"

#include <QPainter>
#include <QPainterPath>

void Curve::init(QPointF p) {
    points = {static_cast<Canvas*>(_parent)->toScreen(p)};
}

void Curve::draw(QPainter *painter) {
    QPainterPath path;
    path.moveTo(static_cast<Canvas*>(_parent)->toScreen(points[0]));
    for(auto point: points) {
        path.lineTo(static_cast<Canvas*>(_parent)->toScreen(point));
    }
    painter->drawPath(path);
}

void Curve::drag(QPointF p) {
    points.push_back(static_cast<Canvas*>(_parent)->toScreen(p));
}
