#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myfigure.h"
#include "networkclient.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QSettings>

#define MAX_WIDTH 10

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString iconsPath = ":/icons/";
    Ui::MainWindow *ui;
    QPushButton *btnColor = new QPushButton("", this);
    QSlider *sldWidth = new QSlider(Qt::Horizontal, this);
    NetworkClient *client;
    QSettings *settings;

    void setConnectios(bool, bool, bool);

private slots:
    void setTool(Types tool);
    void undo();
    void redo();
    void saveImg();
    void saveJson();
    void open();
    void setColor();
    void setWidth();
    void host();
    void connectToBoard();
    void connectToServer();
    void disconnect();
    void disconnectServ();
    void hostSuccess();
    void connectSuccess();
    void hostFail();
    void connectFail();
    void clear();
};
#endif // MAINWINDOW_H
