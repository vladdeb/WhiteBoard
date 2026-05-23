#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include "myfigure.h"
#include "factory.h"

#include <QWidget>
#include <QVector>
#include <QMouseEvent>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QVector<MyFigure*> figures = {};
    double _xMin, _xMax;
    double _yMin, _yMax;
    double scaleX, scaleY;
    Factory factory;
    MyFigure *tool = nullptr;
    Types toolType = Types::tpDrag;
    QPoint prevPos;
    bool redoAvailable = false;
    bool undoAvailable = false;
    std::uint32_t currentstate = 0;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void setBorders(double xMin, double xMax, double yMin, double yMax);
public:
    QColor _color = Qt::white;
    std::uint32_t _width = 2;
    explicit Canvas(QWidget *parent = nullptr) : QWidget(parent) {
        factory = Factory();
        scaleX = 1.0;
        scaleY = 1.0;
    }
    ~Canvas() {
        for(auto figure: figures) {
            delete figure;
        }
    }
    void setTool(Types type);
    void setColor(QColor c) { _color = c; }
    void setWidth(std::uint32_t w) { _width = w; }
    QPoint toScreen(QPointF);
    QPointF  toWorld(QPoint);
    double getScaleX() { return scaleX; }
    double getScaleY() { return scaleY; }
    double getXMin() { return _xMin; }
    double getXMax() { return _xMax; }
    double getYMin() { return _yMin; }
    double getYMax() { return _yMax; }
    int getCurrentState() { return currentstate; }
    void setCurrentState(int value) { currentstate = value; update();}

    void redo(bool send = 1);
    void undo(bool send = 1);
    bool isRedoAvailable() { return redoAvailable; }
    bool isUndoAvailable() { return undoAvailable; }
    QJsonDocument serialize();
    void deserialize(QJsonDocument);
    void addFigure(MyFigure*, bool send = 1);
    void clear(bool send = 1);

signals:
signals:
    void sigDraw(MyFigure* figure);
    void sigRedo();
    void sigUndo();
    void sigClear();
};

#endif // CANVAS_H
