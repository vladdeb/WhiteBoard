#include "line.h"
#include "canvas.h"

#include <QPainter>

void Line::init(QPointF p) {
    start = p;
    end = p;
}

void Line::draw(QPainter *painter) {
    painter->setPen(pen);
    painter->drawLine(static_cast<Canvas*>(_parent)->toScreen(start), static_cast<Canvas*>(_parent)->toScreen(end));
}

void Line::drag(QPointF p) {
    end = p;
}
