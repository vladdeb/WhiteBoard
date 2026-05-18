#include "myfigure.h"

MyFigure::MyFigure(QWidget *parent, QColor color, std::uint32_t width) : _color(color), _width(width), _parent(parent) {
    pen = QPen();
    pen.setColor(_color);
    pen.setWidth(_width);
}
