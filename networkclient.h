#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "canvas.h"

#include <QObject>
#include <QTcpSocket>

class NetworkClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    Canvas *_canvas;
    quint32 id;
    qint32 expected = -1;
    QByteArray buffer;
    Factory factory;
    bool connected = 0;

    QByteArray packJson(const QJsonObject &obj);
    void proceedRequest(const QByteArray &data);
public:
    NetworkClient(Canvas *canvas, QObject *parent = nullptr);
    void connectToServer(QString ip, quint16 port);
    void hostBoard();
    void connectToBoard(quint32 id);
    void disconnectFromBoard();
    void disconnectFromServer();
    quint32 getId() { return id; }

private slots:
    void sendFigure(MyFigure *figure);
    void sendUndo();
    void sendRedo();
    void onReadyRead();
    void sendClear();

signals:
    void connectionToBoardFailed();
    void connectionToBoardSuccess();
    void hostBoardFailed();
    void hostBoardSuccess();
    void disconnected();
    void connectedToServer();
};

#endif // NETWORKCLIENT_H
