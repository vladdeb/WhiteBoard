#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "factory.h"
#include <QAction>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QAction *setDragAction = new QAction(this);
    setDragAction->setIcon(QIcon(iconsPath + "drag.ico"));
    setDragAction->setShortcut(Qt::Key_M);
    setDragAction->setToolTip(tr("Move"));
    connect(setDragAction, &QAction::triggered, this, [this]() {setTool(Types::tpDrag);});
    ui->toolBar->addAction(setDragAction);

    QAction *setLineAction = new QAction(this);
    setLineAction->setIcon(QIcon(iconsPath + "line.ico"));
    setLineAction->setShortcut(Qt::Key_L);
    setLineAction->setToolTip(tr("Line"));
    connect(setLineAction, &QAction::triggered, this, [this]() {setTool(Types::tpLine);});
    ui->toolBar->addAction(setLineAction);

    QAction *setRectangleAction = new QAction(this);
    setRectangleAction->setIcon(QIcon(iconsPath + "rect.ico"));
    setRectangleAction->setShortcut(Qt::Key_R);
    setRectangleAction->setToolTip(tr("Rectangle"));
    connect(setRectangleAction, &QAction::triggered, this, [this]() {setTool(Types::tpRect);});
    ui->toolBar->addAction(setRectangleAction);

    QAction *setEllipseAction = new QAction(this);
    setEllipseAction->setIcon(QIcon(iconsPath + "ellipse.ico"));
    setEllipseAction->setShortcut(Qt::Key_E);
    setEllipseAction->setToolTip(tr("Ellipse"));
    connect(setEllipseAction, &QAction::triggered, this, [this]() {setTool(Types::tpEllipse);});
    ui->toolBar->addAction(setEllipseAction);

    QAction *setCurveAction = new QAction(this);
    setCurveAction->setIcon(QIcon(iconsPath + "pen.ico"));
    setCurveAction->setShortcut(Qt::Key_P);
    setCurveAction->setToolTip(tr("Pen"));
    connect(setCurveAction, &QAction::triggered, this, [this]() {setTool(Types::tpCurve);});
    ui->toolBar->addAction(setCurveAction);

    QAction *setTextAction = new QAction(this);
    setTextAction->setIcon(QIcon(iconsPath + "T.ico"));
    setTextAction->setShortcut(Qt::Key_T);
    setTextAction->setToolTip(tr("Text"));
    connect(setTextAction, &QAction::triggered, this, [this]() {setTool(Types::tpText);});
    ui->toolBar->addAction(setTextAction);

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

    QAction *saveAction = new QAction(this);
    saveAction->setIcon(QIcon(iconsPath + "save.ico"));
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    saveAction->setToolTip(tr("Text"));
    connect(saveAction, &QAction::triggered, this, [this]() {});
    ui->toolBar->addAction(saveAction);

    QAction *undoAction = new QAction(this);
    undoAction->setIcon(QIcon(iconsPath + "undo.ico"));
    undoAction->setShortcut(Qt::CTRL | Qt::Key_Z);
    undoAction->setToolTip(tr("Text"));
    connect(undoAction, &QAction::triggered, this, [this]() {});
    ui->toolBar->addAction(undoAction);

    QAction *redoAction = new QAction(this);
    redoAction->setIcon(QIcon(iconsPath + "redo.ico"));
    redoAction->setShortcut(Qt::CTRL | Qt::Key_Y);
    redoAction->setToolTip(tr("Text"));
    connect(redoAction, &QAction::triggered, this, [this]() {});
    ui->toolBar->addAction(redoAction);
}

void MainWindow::setTool(Types tool) {
    ui->canvas->setTool(tool);
}

MainWindow::~MainWindow()
{
    delete ui;
}
