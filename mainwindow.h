#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myfigure.h"
#include "networkclient.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

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

private slots:
    void setTool(Types tool);
    void undo();
    void redo();
    void save();
    void open();
    void setColor();
    void setWidth();
    void host();
    void connectToBoard();
    void hostSuccess();
    void connectSuccess();
    void hostFail();
    void connectFail();
    void clear();
};
#endif // MAINWINDOW_H
