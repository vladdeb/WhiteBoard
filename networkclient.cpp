#include "networkclient.h"
#include "canvas.h"
#include "factory.h"

#include <QJsonArray>

NetworkClient::NetworkClient(Canvas *canvas, QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    _canvas = canvas;
    factory = Factory();

    connect(_canvas, &Canvas::sigDraw, this, &NetworkClient::sendFigure);
    connect(_canvas, &Canvas::sigRedo, this, &NetworkClient::sendRedo);
    connect(_canvas, &Canvas::sigUndo, this, &NetworkClient::sendUndo);
    connect(_canvas, &Canvas::sigClear, this, &NetworkClient::sendClear);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError socketError) {
        qDebug() << "❌ Socket Error occurred! Code:" << socketError;
    });
    connect(socket, &QTcpSocket::stateChanged, this, [](QAbstractSocket::SocketState socketState) {
        qDebug() << "🔄 Socket State Changed to:" << socketState;
    });
}

void NetworkClient::connectToServer(QString ip, quint16 port) {
    qDebug() << "Trying connection to " << ip << ":" << port;
    socket->connectToHost(ip, port);
    if (socket->error() != QAbstractSocket::UnknownSocketError) {
        qDebug() << "⚠️ Immediate error:" << socket->errorString();
    }
}

QByteArray NetworkClient::packJson(const QJsonObject &obj) {
    QJsonDocument doc(obj);
    QByteArray body = doc.toJson(QJsonDocument::Compact);

    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    out << static_cast<quint32>(body.size());
    packet.append(body);

    return packet;
}


void NetworkClient::hostBoard() {
    auto doc = _canvas->serialize();
    QJsonObject obj;
    obj["type"] = "host";
    obj["current"] = _canvas->getCurrentState();
    obj["figures"] = doc.object()["figures"];
    auto data = packJson(obj);
    socket->write(data);
    QJsonDocument doc1(obj);
}

void NetworkClient::connectToBoard(quint32 id) {
    QJsonObject obj;
    obj["type"] = "connect";
    obj["id"] = static_cast<int>(id);
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::sendFigure(MyFigure *figure) {
    if(connected) {
        QJsonObject obj;
        obj["figure"] = figure->toJson();
        obj["type"] = "draw";
        obj["id"] = static_cast<int>(id);
        auto data = packJson(obj);
        socket->write(data);
    }
}

void NetworkClient::sendRedo() {
    if(connected) {
        QJsonObject obj;
        obj["type"] = "redo";
        obj["id"] = static_cast<int>(id);
        auto data = packJson(obj);
        socket->write(data);
    }
}

void NetworkClient::sendUndo() {
    if(connected) {
        QJsonObject obj;
        obj["type"] = "undo";
        obj["id"] = static_cast<int>(id);
        auto data = packJson(obj);
        socket->write(data);
    }
}

void NetworkClient::sendClear() {
    if(connected) {
        QJsonObject obj;
        obj["type"] = "clear";
        obj["id"] = static_cast<int>(id);
        auto data = packJson(obj);
        socket->write(data);
    }
}

void NetworkClient::proceedRequest(const QByteArray &data) {
    auto doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    qDebug().noquote() << doc.toJson().toStdString();
    QString type = obj["type"].toString();

    qDebug() << "Type " << type;
    if(type == "host_failed") {
        emit hostBoardFailed();
    }
    if(type == "host_success") {
        id = obj["id"].toInt();
        connected = true;
        emit hostBoardSuccess();
    }
    if(type == "connection_success") {
        _canvas->deserialize(doc);
        _canvas->setCurrentState(obj["current"].toInt());
        id = obj["id"].toInt();
        connected = true;
        emit connectionToBoardSuccess();
    }
    if(type == "connection_failed") {
        emit connectionToBoardFailed();
    }
    if(type == "clear") {
        _canvas->clear(false);
    }

    if(type == "draw") {
        auto figure = obj["figure"].toObject();
        MyFigure *fig = factory.create((Types)figure["type"].toInt(), _canvas, Qt::white, 1);
        if (fig) {
            fig->fromJson(figure);
            _canvas->addFigure(fig, false);
        }
    }

    if(type == "redo") {
        _canvas->redo(false);
    }
    if(type == "undo") {
        _canvas->undo(false);
    }
}

void NetworkClient::onReadyRead() {
    buffer.append(socket->readAll());
    while(true) {
        if(expected == -1) {
            if(buffer.size() < sizeof(qint32)) {
                break;
            }
            QDataStream ds(buffer);
            ds >> expected;
            buffer.remove(0, sizeof(qint32));
        }
        if(buffer.size() < expected) {
            break;
        }

        QByteArray data = buffer.left(expected);
        proceedRequest(data);
        buffer.remove(0, expected);
        expected = -1;
    }
}
