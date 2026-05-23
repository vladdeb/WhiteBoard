#include "curve.h"
#include "canvas.h"

#include <QPainter>
#include <QPainterPath>
#include <QJsonArray>

void Curve::init(QPointF p) {
    points = {p};
}

void Curve::draw(QPainter *painter) {
    QPainterPath path;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    path.moveTo(static_cast<Canvas*>(_parent)->toScreen(points[0]));
    for(auto point: points) {
        path.lineTo(static_cast<Canvas*>(_parent)->toScreen(point));
    }
    painter->drawPath(path);
}

void Curve::drag(QPointF p) {
    points.push_back(p);
}

Types Curve::type() {
    return Types::tpCurve;
}

QJsonObject Curve::toJson() {
    QJsonObject json = MyFigure::toJson();
    QJsonArray pointsArray;
    for(auto point: points) {
        QJsonObject jsonPoint;
        jsonPoint["x"] = point.x();
        jsonPoint["y"] = point.y();
        pointsArray.append(jsonPoint);
    }
    json["points"] = pointsArray;
    return json;
}

void Curve::fromJson(const QJsonObject &json) {
    MyFigure::fromJson(json);

    points.clear();

    if (json.contains("points") && json["points"].isArray()) {
        QJsonArray pointsArray = json["points"].toArray();

        for (const QJsonValue &value : pointsArray) {
            if (value.isObject()) {
                QJsonObject pointObj = value.toObject();
                double x = pointObj["x"].toDouble();
                double y = pointObj["y"].toDouble();
                points.append(QPointF(x, y));
            }
        }
    }
}
