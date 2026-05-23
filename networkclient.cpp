#include "networkclient.h"
#include "canvas.h"

#include <QJsonArray>

NetworkClient::NetworkClient(Canvas *canvas, QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    _canvas = canvas;

    connect(_canvas, &Canvas::sigDraw, this, &NetworkClient::sendFigure);
    connect(_canvas, &Canvas::sigRedo, this, &NetworkClient::sendRedo);
    connect(_canvas, &Canvas::sigUndo, this, &NetworkClient::sendUndo);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
}

void NetworkClient::connectToServer(QString ip, quint16 port) {
    socket->connectToHost(ip, port);
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
    QJsonObject obj = doc.object();
    obj["type"] = "host";
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::connectToBoard(quint32 id) {
    QJsonObject obj;
    obj["type"] = "connect";
    obj["id"] = static_cast<int>(id);
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::sendFigure(MyFigure *figure) {
    auto obj = figure->toJson();
    obj["type"] = "draw";
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::sendRedo() {
    QJsonObject obj;
    obj["type"] = "redo";
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::sendUndo() {
    QJsonObject obj;
    obj["type"] = "undo";
    auto data = packJson(obj);
    socket->write(data);
}

void NetworkClient::proceedRequest(const QByteArray &data) {
    auto doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();

    QString type = obj["type"].toString();
    if(type == "host_failed") {
        emit hostBoardFailed();
    }
    if(type == "host_success") {
        id = obj["id"].toInt();
        emit hostBoardSuccess();
    }
    if(type == "connection_success") {
        QJsonDocument figures(obj["figures"].toObject());
        _canvas->deserialize(figures);
        emit connectionToBoardSuccess();
    }
    if(type == "connection_failed") {
        emit connectionToBoardSuccess();
    }

    if(type == "draw") {

    }
}
