/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "C:\Users\Lenovo\Desktop\BSUIR\!sem4\OnlineBoard\WhiteBoard\canvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHost;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConnectServ;
    QAction *actionDisconnectServ;
    QAction *setDragAction;
    QAction *setLineAction;
    QAction *setRectAction;
    QAction *setEllipseAction;
    QAction *setPenAction;
    QAction *setTextAction;
    QAction *actionOpen;
    QAction *actionBmp;
    QAction *actionJson;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    Canvas *canvas;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *ledCode;
    QMenuBar *menubar;
    QMenu *menuRoom;
    QMenu *menuServer;
    QMenu *menuTools;
    QMenu *menuFile;
    QMenu *menuSave;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(933, 576);
        actionHost = new QAction(MainWindow);
        actionHost->setObjectName("actionHost");
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName("actionConnect");
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName("actionDisconnect");
        actionConnectServ = new QAction(MainWindow);
        actionConnectServ->setObjectName("actionConnectServ");
        actionDisconnectServ = new QAction(MainWindow);
        actionDisconnectServ->setObjectName("actionDisconnectServ");
        setDragAction = new QAction(MainWindow);
        setDragAction->setObjectName("setDragAction");
        setLineAction = new QAction(MainWindow);
        setLineAction->setObjectName("setLineAction");
        setRectAction = new QAction(MainWindow);
        setRectAction->setObjectName("setRectAction");
        setEllipseAction = new QAction(MainWindow);
        setEllipseAction->setObjectName("setEllipseAction");
        setPenAction = new QAction(MainWindow);
        setPenAction->setObjectName("setPenAction");
        setTextAction = new QAction(MainWindow);
        setTextAction->setObjectName("setTextAction");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionBmp = new QAction(MainWindow);
        actionBmp->setObjectName("actionBmp");
        actionJson = new QAction(MainWindow);
        actionJson->setObjectName("actionJson");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        canvas = new Canvas(centralwidget);
        canvas->setObjectName("canvas");

        verticalLayout->addWidget(canvas);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnClear = new QPushButton(widget);
        btnClear->setObjectName("btnClear");

        horizontalLayout->addWidget(btnClear);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        ledCode = new QLineEdit(widget);
        ledCode->setObjectName("ledCode");
        ledCode->setReadOnly(true);

        horizontalLayout->addWidget(ledCode);


        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 933, 25));
        menuRoom = new QMenu(menubar);
        menuRoom->setObjectName("menuRoom");
        menuServer = new QMenu(menubar);
        menuServer->setObjectName("menuServer");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuSave = new QMenu(menuFile);
        menuSave->setObjectName("menuSave");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuRoom->menuAction());
        menubar->addAction(menuServer->menuAction());
        menuRoom->addAction(actionHost);
        menuRoom->addAction(actionConnect);
        menuRoom->addAction(actionDisconnect);
        menuServer->addAction(actionConnectServ);
        menuServer->addAction(actionDisconnectServ);
        menuTools->addAction(setDragAction);
        menuTools->addAction(setLineAction);
        menuTools->addAction(setRectAction);
        menuTools->addAction(setEllipseAction);
        menuTools->addAction(setPenAction);
        menuTools->addAction(setTextAction);
        menuFile->addAction(menuSave->menuAction());
        menuFile->addAction(actionOpen);
        menuSave->addAction(actionBmp);
        menuSave->addAction(actionJson);
        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(btnClear, SIGNAL(clicked()), MainWindow, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionHost->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionConnectServ->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnectServ->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        setDragAction->setText(QCoreApplication::translate("MainWindow", "Pan", nullptr));
        setLineAction->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        setRectAction->setText(QCoreApplication::translate("MainWindow", "Rectangle", nullptr));
        setEllipseAction->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        setPenAction->setText(QCoreApplication::translate("MainWindow", "Pencil", nullptr));
        setTextAction->setText(QCoreApplication::translate("MainWindow", "Text", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionBmp->setText(QCoreApplication::translate("MainWindow", "Image", nullptr));
        actionJson->setText(QCoreApplication::translate("MainWindow", "Json", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "room Code", nullptr));
        menuRoom->setTitle(QCoreApplication::translate("MainWindow", "Room", nullptr));
        menuServer->setTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSave->setTitle(QCoreApplication::translate("MainWindow", "Save", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
