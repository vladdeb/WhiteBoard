#ifndef FACTORY_H
#define FACTORY_H

#include "myfigure.h"

#include <QMap>

enum Types {
    tpLine,
    tpRect,
    tpEllipse,
    tpText,
    tpCurve,
    tpDrag
};

class Factory
{
private:
    using CreatorFunc = std::function<MyFigure*(QWidget*, QColor, std::uint32_t)>;
    QMap<Types, CreatorFunc> creators;
public:
    Factory();
    MyFigure *create(Types type, QWidget*, QColor, std::uint32_t);
};

#endif // FACTORY_H
