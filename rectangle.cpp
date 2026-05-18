#include "rectangle.h"
#include "canvas.h"

#include <QPainter>

void Rectangle::init(QPointF p) {
    start = p;
    end = p;
}

void Rectangle::draw(QPainter *painter) {
    painter->setPen(pen);
    QRect rect(static_cast<Canvas*>(_parent)->toScreen(start), static_cast<Canvas*>(_parent)->toScreen(end));
    painter->drawRect(rect.normalized());
}

void Rectangle::drag(QPointF p) {
    end = p;
}
