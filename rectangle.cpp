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

Types Rectangle::type() {
    return Types::tpRect;
}

QJsonObject Rectangle::toJson() {
    QJsonObject json = MyFigure::toJson();
    json["startX"] = start.x();
    json["startY"] = start.y();
    json["endX"] = end.x();
    json["endY"] = end.y();
    return json;
}

void Rectangle::fromJson(const QJsonObject &json) {
    MyFigure::fromJson(json);
    start = QPointF(json["startX"].toDouble(), json["startY"].toDouble());
    end = QPointF(json["endX"].toDouble(), json["endY"].toDouble());
}

