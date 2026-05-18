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

Types Ellipse::type() {
    return Types::tpEllipse;
}

QJsonObject Ellipse::toJson() {
    QJsonObject json = MyFigure::toJson();
    json["startX"] = start.x();
    json["startY"] = start.y();
    json["endX"] = end.x();
    json["endY"] = end.y();
    return json;
}

void Ellipse::fromJson(const QJsonObject &json) {
    MyFigure::fromJson(json);
    start = QPointF(json["startX"].toDouble(), json["startY"].toDouble());
    end = QPointF(json["endX"].toDouble(), json["endY"].toDouble());
}

