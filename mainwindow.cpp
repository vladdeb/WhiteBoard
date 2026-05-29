#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "savetype.h"

#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QColorDialog>
#include <QSettings>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString configPath = QCoreApplication::applicationDirPath() + "/config.ini";
    if (!QFile::exists(configPath)) {
        QSettings settings(configPath, QSettings::IniFormat);
        settings.setValue("Network/server_ip", "127.0.0.1");
        settings.setValue("Network/server_port", 5173);
        settings.sync();
    }

    settings = new QSettings(configPath, QSettings::IniFormat);
    //move
    QAction *setDragAction = ui->setDragAction;
    setDragAction->setIcon(QIcon(iconsPath + "drag.ico"));
    setDragAction->setShortcut(Qt::Key_M);
    setDragAction->setToolTip(tr("Move"));
    connect(setDragAction, &QAction::triggered, this, [this]() {setTool(Types::tpDrag);});
    ui->toolBar->addAction(setDragAction);

    //line
    QAction *setLineAction = ui->setLineAction;
    setLineAction->setIcon(QIcon(iconsPath + "line.ico"));
    setLineAction->setShortcut(Qt::Key_L);
    setLineAction->setToolTip(tr("Line"));
    connect(setLineAction, &QAction::triggered, this, [this]() {setTool(Types::tpLine);});
    ui->toolBar->addAction(setLineAction);

    //rectangle
    QAction *setRectangleAction = ui->setRectAction;
    setRectangleAction->setIcon(QIcon(iconsPath + "rect.ico"));
    setRectangleAction->setShortcut(Qt::Key_R);
    setRectangleAction->setToolTip(tr("Rectangle"));
    connect(setRectangleAction, &QAction::triggered, this, [this]() {setTool(Types::tpRect);});
    ui->toolBar->addAction(setRectangleAction);

    //ELLIPSE
    QAction *setEllipseAction = ui->setEllipseAction;
    setEllipseAction->setIcon(QIcon(iconsPath + "ellipse.ico"));
    setEllipseAction->setShortcut(Qt::Key_E);
    setEllipseAction->setToolTip(tr("Ellipse"));
    connect(setEllipseAction, &QAction::triggered, this, [this]() {setTool(Types::tpEllipse);});
    ui->toolBar->addAction(setEllipseAction);

    //PEN
    QAction *setCurveAction = ui->setPenAction;
    setCurveAction->setIcon(QIcon(iconsPath + "pen.ico"));
    setCurveAction->setShortcut(Qt::Key_P);
    setCurveAction->setToolTip(tr("Pen"));
    connect(setCurveAction, &QAction::triggered, this, [this]() {setTool(Types::tpCurve);});
    ui->toolBar->addAction(setCurveAction);

    //TEXT
    QAction *setTextAction = ui->setTextAction;
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
    QAction *saveActionImg = ui->actionBmp;
    saveActionImg->setShortcut(Qt::CTRL | Qt::Key_S);
    saveActionImg->setToolTip(tr("Text"));
    connect(saveActionImg, &QAction::triggered, this, &MainWindow::saveImg);

    QAction *saveActionJson = ui->actionJson;
    saveActionJson->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    saveActionJson->setToolTip(tr("Text"));
    connect(saveActionJson, &QAction::triggered, this, &MainWindow::saveJson);
    //LOAD
    QAction *loadAction = ui->actionOpen;
    loadAction->setShortcut(Qt::CTRL | Qt::Key_O);
    loadAction->setToolTip(tr("Text"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::open);

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

    //Network
    client = new NetworkClient(ui->canvas);
    connect(client, &NetworkClient::connectionToBoardFailed, this, &MainWindow::connectFail);
    connect(client, &NetworkClient::connectionToBoardSuccess, this, &MainWindow::connectSuccess);
    connect(client, &NetworkClient::hostBoardFailed, this, &MainWindow::hostFail);
    connect(client, &NetworkClient::hostBoardSuccess, this, &MainWindow::hostSuccess);

    //Connection actions
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::connectToBoard);
    connect(ui->actionConnectServ, &QAction::triggered, this, &MainWindow::connectToServer);
    connect(ui->actionHost, &QAction::triggered, this, &MainWindow::host);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::disconnect);
    connect(ui->actionDisconnectServ, &QAction::triggered, this, &MainWindow::disconnectServ);
    connect(client, &NetworkClient::disconnected, this, [this]() {
        ui->actionDisconnectServ->setEnabled(false);
        ui->actionConnectServ->setEnabled(true);

        ui->radioButton->setStyleSheet(
            "QRadioButton::indicator {"
            "   width: 12px;"
            "   height: 12px;"
            "   border-radius: 6px;"
            "   border: 1px solid gray;"
            "}"
            "QRadioButton::indicator:checked {"
            "   background-color: red;"
            "}"
            );
        ui->radioButton->setText("Not connected to server");
        ui->ledCode->clear();
    });
    connect(client, &NetworkClient::connectedToServer, this, [this]() {
        ui->actionDisconnectServ->setEnabled(true);
        ui->actionConnectServ->setEnabled(false);

        ui->radioButton->setStyleSheet(
            "QRadioButton::indicator {"
            "   width: 12px;"
            "   height: 12px;"
            "   border-radius: 6px;"
            "   border: 1px solid gray;"
            "}"
            "QRadioButton::indicator:checked {"
            "   background-color: green;"
            "}"
            );
        setConnectios(true, true, false);
    });


    ui->radioButton->setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 12px;"
        "   height: 12px;"
        "   border-radius: 6px;"
        "   border: 1px solid gray;"
        "}"
        "QRadioButton::indicator:checked {"
        "   background-color: red;"
        "}"
        );
    ui->radioButton->setText("Not connected to server");
    ui->radioButton->setChecked(true);
    setConnectios(false, false, false);
    setWindowIcon(QIcon(iconsPath + "mainWindow.ico"));


    ui->actionDisconnectServ->setEnabled(false);
    ui->actionConnectServ->setEnabled(true);
}


void MainWindow::setConnectios(bool conn, bool host, bool disconn) {
    ui->actionConnect->setEnabled(conn);
    ui->actionHost->setEnabled(host);
    ui->actionDisconnect->setEnabled(disconn);
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

void MainWindow::saveImg() {
    QString path = QFileDialog::getSaveFileName(this, "Save to");
    if(!path.isEmpty()) {
        QPixmap screenshot = ui->canvas->grab();

        bool success = screenshot.save(path);

        if (!success) {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось сохранить изображение"));
        }
    }
}

void MainWindow::saveJson() {
    QString path = QFileDialog::getSaveFileName(this, "Save to");
    if(!path.isEmpty()) {
            auto doc = ui->canvas->serialize();
            auto data = doc.toJson();
            QFile f(path);
            if(!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                return;
            }
            f.write(data);
    }
}

void MainWindow::open() {
    QString path = QFileDialog::getOpenFileName(this, "Load from");
    if(!path.isEmpty()) {
        QFile f(path);
        if(!f.open(QIODevice::ReadOnly)) {
            return;
        }
        QByteArray data;
        data = f.readAll();
        auto doc = QJsonDocument::fromJson(data);
        ui->canvas->deserialize(doc);
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

void MainWindow::host() {
    client->hostBoard();
}

void MainWindow::connectToBoard() {
    QString idStr = QInputDialog::getText(this, "Connect", "Enter room key");
    bool ok;
    quint32 id = idStr.toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Error", "Key must be a number");
    }
    client->connectToBoard(id);
}

void MainWindow::connectFail() {
    QMessageBox::warning(this, "Error", "Connection to board failed");
    setConnectios(true, true, false);
    ui->ledCode->clear();
}


void MainWindow::connectSuccess() {
    QMessageBox::information(this, "Error", "Connected to board successfully");
    ui->ledCode->setText(QString::number(client->getId()));
    setConnectios(false, false, true);
}

void MainWindow::hostFail() {
    QMessageBox::warning(this, "Error", "Hosting to board failed");
    setConnectios(true, true, false);
    ui->ledCode->clear();
}

void MainWindow::hostSuccess() {
    QMessageBox::information(this, "Error", "Hosted board successfully");
    ui->ledCode->setText(QString::number(client->getId()));
    setConnectios(false, false, true);
}

void MainWindow::clear() {
    ui->canvas->clear();
}

void MainWindow::disconnect() {
    client->disconnectFromBoard();
    setConnectios(true, true, false);
    ui->ledCode->clear();
}

void MainWindow::disconnectServ() {
    client->disconnectFromServer();
    setConnectios(false, false, false);
    ui->radioButton->setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 12px;"
        "   height: 12px;"
        "   border-radius: 6px;"
        "   border: 1px solid gray;"
        "}"
        "QRadioButton::indicator:checked {"
        "   background-color: red;"
        "}"
        );
    ui->radioButton->setText("Not connected to server");
    ui->ledCode->clear();
}

void MainWindow::connectToServer() {
    settings->sync();
    QString ip = settings->value("Network/server_ip", "127.0.0.1").toString();
    quint16 port = settings->value("Network/server_port", 5173).toUInt();
    client->connectToServer(ip, port);
}
