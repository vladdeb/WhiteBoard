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

Types Line::type() {
    return Types::tpLine;
}

QJsonObject Line::toJson() {
    QJsonObject json = MyFigure::toJson();
    json["startX"] = start.x();
    json["startY"] = start.y();
    json["endX"] = end.x();
    json["endY"] = end.y();
    return json;
}

void Line::fromJson(const QJsonObject &json) {
    MyFigure::fromJson(json);
    start = QPointF(json["startX"].toDouble(), json["startY"].toDouble());
    end = QPointF(json["endX"].toDouble(), json["endY"].toDouble());
}
