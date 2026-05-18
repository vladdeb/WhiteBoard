#include "myfigure.h"

MyFigure::MyFigure(QWidget *parent, QColor color, std::uint32_t width) : _color(color), _width(width), _parent(parent) {
    pen = QPen();
    pen.setColor(_color);
    pen.setWidth(_width);
}

QJsonObject MyFigure::toJson() {
    QJsonObject json;
    json["type"] = static_cast<int>(type());
    json["color"] = _color.name();
    json["width"] = static_cast<int>(_width);
    return json;
}

void MyFigure::fromJson(const QJsonObject &json) {
    if (json.contains("color")) _color = QColor(json["color"].toString());
    if (json.contains("width")) _width = json["width"].toInt();
    pen = QPen(_color, _width);
}
