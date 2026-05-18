#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "factory.h"

#include <QMainWindow>

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
    QString iconsPath = "C:\\Users\\Lenovo\\Desktop\\BSUIR\\!sem4\\Course\\WhiteBoard\\icons\\";
    Ui::MainWindow *ui;
    void setTool(Types tool);

};
#endif // MAINWINDOW_H
