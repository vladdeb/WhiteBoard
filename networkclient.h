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
    qint32 expected;
    QByteArray buffer;

    QByteArray packJson(const QJsonObject &obj);
    void proceedRequest(const QByteArray &data);
public:
    NetworkClient(Canvas *canvas, QObject *parent = nullptr);
    void connectToServer(QString ip, quint16 port);
    void hostBoard();
    void connectToBoard(quint32 id);

private slots:
    void sendFigure(MyFigure *figure);
    void sendUndo();
    void sendRedo();
    void onReadyRead();

signals:
    void connectionToBoardFailed();
    void connectionToBoardSuccess();
    void hostBoardFailed();
    void hostBoardSuccess();
};

#endif // NETWORKCLIENT_H
