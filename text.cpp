#include "text.h"
#include "canvas.h"

#include <QPainter>
#include <QInputDialog>
const int BASE_FONT_SIZE = 10;

void Text::init(QPointF p) {
    start = p;
    end = p;
}

void Text::draw(QPainter *painter) {
    double x1 = std::min(start.x(), end.x());
    double y1 = std::min(start.y(), end.y());
    double x2 = std::max(start.x(), end.x());
    double y2 = std::max(start.y(), end.y());
    QFont font("comic sans");
    font.setPointSize(BASE_FONT_SIZE*_width*((Canvas*)_parent)->getScaleX());
    painter->setFont(font);
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

Types Text::type() {
    return Types::tpText;
}

QJsonObject Text::toJson() {
    QJsonObject json = MyFigure::toJson();
    json["startX"] = start.x();
    json["startY"] = start.y();
    json["endX"] = end.x();
    json["endY"] = end.y();
    json["text"] = text;
    return json;
}

void Text::fromJson(const QJsonObject &json) {
    MyFigure::fromJson(json);
    start = QPointF(json["startX"].toDouble(), json["startY"].toDouble());
    end = QPointF(json["endX"].toDouble(), json["endY"].toDouble());
    text = json["text"].toString();
    finished = true;
}

