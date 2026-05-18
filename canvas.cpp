#include "canvas.h"

#include <QPainter>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

void Canvas::setBorders(double xMin, double xMax, double yMin, double yMax) {
    if(xMin >= xMax || yMin >= yMax) {
        throw std::runtime_error("Invalid arguments");
    }
    _xMin = xMin;
    _xMax = xMax;
    _yMin = yMin;
    _yMax = yMax;
    scaleX = width() / (_xMax - _xMin);
    scaleY = height() / (_yMax - _yMin);
    update();
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < currentstate; ++i) {
        auto figure = figures[i];
        if (figure) {
            figure->draw(&painter);
        }
    }

    if (tool) {
        tool->draw(&painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(toolType == Types::tpDrag) {
            prevPos = event->pos();
        }
        else {
            tool = factory.create(toolType, this, _color, _width);
            tool->init(toWorld(event->pos()));
        }
    }

}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        if(toolType == Types::tpDrag) {
            QPoint pos = event->pos();
            std::int32_t dx = pos.x() - prevPos.x();
            std::int32_t dy = pos.y() - prevPos.y();
            setBorders(_xMin - dx / scaleX, _xMax - dx / scaleX, _yMin - dy / scaleY, _yMax - dy / scaleY);
            prevPos = event->pos();
        }
        else if(tool) {
            tool->drag(toWorld(event->pos()));
        }
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if(tool) {
        tool->finalize();
        figures.resize(currentstate++);
        redoAvailable = false;
        undoAvailable = true;
        figures.push_back(tool);
        tool = nullptr;
    }
    update();
}

QPoint Canvas::toScreen(QPointF worldPos) {
    int x = static_cast<int>((worldPos.x() - _xMin) * scaleX);
    int y = static_cast<int>((worldPos.y() - _yMin) * scaleY);
    return QPoint(x, y);
}

QPointF Canvas::toWorld(QPoint screenPos) {
    double x = _xMin + screenPos.x() / scaleX;
    double y = _yMin + screenPos.y() / scaleY;
    return QPointF(x, y);
}

void Canvas::wheelEvent(QWheelEvent *event) {
    QPointF mouseWorldBefore = toWorld(event->position().toPoint());

    double zoomFactor = 1.1;
    if (event->angleDelta().y() > 0) {
        zoomFactor = 1.0 / zoomFactor;
    }

    double newWidth = (_xMax - _xMin) * zoomFactor;
    double newHeight = (_yMax - _yMin) * zoomFactor;

    double newXMin = mouseWorldBefore.x() - (mouseWorldBefore.x() - _xMin) * zoomFactor;
    double newYMin = mouseWorldBefore.y() - (mouseWorldBefore.y() - _yMin) * zoomFactor;

    double newXMax = newXMin + newWidth;
    double newYMax = newYMin + newHeight;

    try {
        setBorders(newXMin, newXMax, newYMin, newYMax);
    } catch (const std::runtime_error &e) {

    }
    event->accept();
}

void Canvas::setTool(Types type) {
    toolType = type;
}

void Canvas::undo() {
    if(undoAvailable) {
        currentstate--;
        if(currentstate == 0) {
            undoAvailable = false;
        }
        redoAvailable = true;
    }
    update();
}

void Canvas::redo() {
    if(redoAvailable) {
        currentstate++;
        if(currentstate == figures.size()) {
            redoAvailable = false;
        }
        undoAvailable = true;
    }
    update();
}

void Canvas::saveToFile(const QString &filePath) {
    QFile file(filePath);
    QJsonArray figuresArray;
    for (MyFigure *fig : figures) {
        figuresArray.append(fig->toJson());
    }

    QJsonObject mainObj;
    mainObj["figures"] = figuresArray;

    QJsonDocument doc(mainObj);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void Canvas::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray figuresArray = doc.object()["figures"].toArray();

    for(auto figure: figures) delete figure;
    figures.clear();

    for (QJsonValue val : figuresArray) {
        QJsonObject obj = val.toObject();
        Types figType = static_cast<Types>(obj["type"].toInt());

        MyFigure *fig = factory.create(figType, this, Qt::white, 1);
        if (fig) {
            fig->fromJson(obj);
            figures.append(fig);
        }
    }
    currentstate = figures.size();
    undoAvailable = (currentstate > 0);
    redoAvailable = false;

    update();
}
