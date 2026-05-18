#include "ellipse.h"
#include "canvas.h"

#include <QPainter>

void Ellipse::init(QPointF p) {
    start = p;
    end = p;
}

void Ellipse::draw(QPainter *painter) {
    painter->setPen(pen);
    QRect rect(static_cast<Canvas*>(_parent)->toScreen(start), static_cast<Canvas*>(_parent)->toScreen(end));
    painter->drawEllipse(rect.normalized());
}

void Ellipse::drag(QPointF p) {
    end = p;
}
