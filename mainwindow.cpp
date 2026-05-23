#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "savetype.h"

#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //move
    QAction *setDragAction = new QAction(this);
    setDragAction->setIcon(QIcon(iconsPath + "drag.ico"));
    setDragAction->setShortcut(Qt::Key_M);
    setDragAction->setToolTip(tr("Move"));
    connect(setDragAction, &QAction::triggered, this, [this]() {setTool(Types::tpDrag);});
    ui->toolBar->addAction(setDragAction);

    //line
    QAction *setLineAction = new QAction(this);
    setLineAction->setIcon(QIcon(iconsPath + "line.ico"));
    setLineAction->setShortcut(Qt::Key_L);
    setLineAction->setToolTip(tr("Line"));
    connect(setLineAction, &QAction::triggered, this, [this]() {setTool(Types::tpLine);});
    ui->toolBar->addAction(setLineAction);

    //rectangle
    QAction *setRectangleAction = new QAction(this);
    setRectangleAction->setIcon(QIcon(iconsPath + "rect.ico"));
    setRectangleAction->setShortcut(Qt::Key_R);
    setRectangleAction->setToolTip(tr("Rectangle"));
    connect(setRectangleAction, &QAction::triggered, this, [this]() {setTool(Types::tpRect);});
    ui->toolBar->addAction(setRectangleAction);

    //ELLIPSE
    QAction *setEllipseAction = new QAction(this);
    setEllipseAction->setIcon(QIcon(iconsPath + "ellipse.ico"));
    setEllipseAction->setShortcut(Qt::Key_E);
    setEllipseAction->setToolTip(tr("Ellipse"));
    connect(setEllipseAction, &QAction::triggered, this, [this]() {setTool(Types::tpEllipse);});
    ui->toolBar->addAction(setEllipseAction);

    //PEN
    QAction *setCurveAction = new QAction(this);
    setCurveAction->setIcon(QIcon(iconsPath + "pen.ico"));
    setCurveAction->setShortcut(Qt::Key_P);
    setCurveAction->setToolTip(tr("Pen"));
    connect(setCurveAction, &QAction::triggered, this, [this]() {setTool(Types::tpCurve);});
    ui->toolBar->addAction(setCurveAction);

    //TEXT
    QAction *setTextAction = new QAction(this);
    setTextAction->setIcon(QIcon(iconsPath + "T.ico"));
    setTextAction->setShortcut(Qt::Key_T);
    setTextAction->setToolTip(tr("Text"));
    connect(setTextAction, &QAction::triggered, this, [this]() {setTool(Types::tpText);});
    ui->toolBar->addAction(setTextAction);

    //GROUPING
    QActionGroup *toolGroup = new QActionGroup(this);
    setDragAction->setActionGroup(toolGroup);
    setLineAction->setActionGroup(toolGroup);
    setRectangleAction->setActionGroup(toolGroup);
    setEllipseAction->setActionGroup(toolGroup);
    setCurveAction->setActionGroup(toolGroup);
    setTextAction->setActionGroup(toolGroup);

    setDragAction->setCheckable(true);
    setLineAction->setCheckable(true);
    setRectangleAction->setCheckable(true);
    setEllipseAction->setCheckable(true);
    setCurveAction->setCheckable(true);
    setTextAction->setCheckable(true);

    //SAVE
    QAction *saveAction = new QAction(this);
    saveAction->setIcon(QIcon(iconsPath + "save.ico"));
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    saveAction->setToolTip(tr("Text"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    ui->toolBar->addAction(saveAction);

    //LOAD
    QAction *loadAction = new QAction(this);
    loadAction->setIcon(QIcon(iconsPath + "open.ico"));
    loadAction->setShortcut(Qt::CTRL | Qt::Key_O);
    loadAction->setToolTip(tr("Text"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::open);
    ui->toolBar->addAction(loadAction);

    //UNDO/REDO
    QAction *undoAction = new QAction(this);
    undoAction->setIcon(QIcon(iconsPath + "undo.ico"));
    undoAction->setShortcut(Qt::CTRL | Qt::Key_Z);
    undoAction->setToolTip(tr("Text"));
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
    ui->toolBar->addAction(undoAction);

    QAction *redoAction = new QAction(this);
    redoAction->setIcon(QIcon(iconsPath + "redo.ico"));
    redoAction->setShortcut(Qt::CTRL | Qt::Key_Y);
    redoAction->setToolTip(tr("Text"));
    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);
    ui->toolBar->addAction(redoAction);

    //CHOOSE COLOR

    connect(btnColor, &QPushButton::clicked, this, &MainWindow::setColor);
    ui->toolBar->addWidget(btnColor);

    //CHOOsE WHIDTH

    ui->toolBar->addWidget(sldWidth);

    sldWidth->setRange(0, MAX_WIDTH);
    sldWidth->setValue(3);
    sldWidth->setMaximumWidth(100);
    connect(sldWidth, &QSlider::valueChanged, this, &MainWindow::setWidth);

}

void MainWindow::setTool(Types tool) {
    ui->canvas->setTool(tool);
}

void MainWindow::undo() {
    ui->canvas->undo();
}

void MainWindow::redo() {
    ui->canvas->redo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save() {
    saveType diag(this);
    int result = diag.exec();
    if(result == QDialog::Accepted) {
        QString path = QFileDialog::getSaveFileName(this, "Save to");
        if(!path.isEmpty()) {
            if(diag.saveFormat == format::bmp) {
                QPixmap screenshot = ui->canvas->grab();

                bool success = screenshot.save(path);

                if (!success) {
                    QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось сохранить изображение"));
                }
            }
            else {
                ui->canvas->saveToFile(path);
            }
        }
    }
}

void MainWindow::open() {
    QString path = QFileDialog::getOpenFileName(this, "Load from");
    if(!path.isEmpty()) {
        ui->canvas->loadFromFile(path);
    }
}

void MainWindow::setColor() {
    QColor newColor = QColorDialog::getColor();
    QPalette pal = btnColor->palette();
    pal.setColor(QPalette::Button, newColor);
    btnColor->setAutoFillBackground(true);
    btnColor->setPalette(pal);
    btnColor->update();
    ui->canvas->setColor(newColor);
}

void MainWindow::setWidth() {
    ui->canvas->setWidth(sldWidth->value());
}
