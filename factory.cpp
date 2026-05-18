#include "factory.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "text.h"
#include "curve.h"

Factory::Factory() {
    creators[Types::tpCurve]   = [](QWidget* p, QColor c, std::uint32_t w) { return new Curve(p, c, w); };
    creators[Types::tpLine]    = [](QWidget* p, QColor c, std::uint32_t w) { return new Line(p, c, w); };
    creators[Types::tpRect]    = [](QWidget* p, QColor c, std::uint32_t w) { return new Rectangle(p, c, w); };
    creators[Types::tpEllipse] = [](QWidget* p, QColor c, std::uint32_t w) { return new Ellipse(p, c, w); };
    creators[Types::tpText]    = [](QWidget* p, QColor c, std::uint32_t w) { return new Text(p, c, w); };
}

MyFigure *Factory::create(Types type, QWidget* p, QColor c, std::uint32_t w) {
    if(creators.find(type) == creators.end()){
        return nullptr;
    }
    return creators[type](p, c, w);
}
