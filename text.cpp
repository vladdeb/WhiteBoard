#include "text.h"
#include "canvas.h"

#include <QPainter>
#include <QInputDialog>

void Text::init(QPointF p) {
    start = p;
    end = p;
}

void Text::draw(QPainter *painter) {
    double x1 = std::min(start.x(), end.x());
    double y1 = std::min(start.y(), end.y());
    double x2 = std::max(start.x(), end.x());
    double y2 = std::max(start.y(), end.y());
    if(!finished) {
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        painter->setPen(pen);
        QRect rect = QRect(static_cast<Canvas*>(_parent)->toScreen({x1, y1}), static_cast<Canvas*>(_parent)->toScreen({x2, y2}));
        painter->drawRect(rect);
    }
    else {
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(_width);
        painter->setPen(pen);
        QRect rect = QRect(static_cast<Canvas*>(_parent)->toScreen({x1, y1}), static_cast<Canvas*>(_parent)->toScreen({x2, y2}));
        painter->drawText(rect, Qt::AlignLeft, text);
    }
}

void Text::drag(QPointF p) {
    end = p;
}

void Text::finalize() {
    text = QInputDialog::getText(_parent, "Set text", "Your text");
    finished = true;
}
