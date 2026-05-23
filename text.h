#ifndef TEXT_H
#define TEXT_H

#include "myfigure.h"

#include <QString>

class Text : public MyFigure
{
private:
    QPointF start, end;
    QString text;
    bool finished;
public:
    Text(QWidget *parent, QColor color, std::uint32_t width) : MyFigure(parent, color, width), finished(false) {}
    void init(QPointF p) override;
    void draw(QPainter *painter) override;
    void drag(QPointF p) override;
    void finalize() override;

    Types type() override;
    QJsonObject toJson() override;
    void fromJson(const QJsonObject& json) override;
};

#endif // TEXT_H
