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
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    Canvas *canvas;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *ledCode;
    QPushButton *btnHost;
    QPushButton *btnConnect;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(724, 395);
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
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        ledCode = new QLineEdit(widget);
        ledCode->setObjectName("ledCode");
        ledCode->setReadOnly(true);

        horizontalLayout->addWidget(ledCode);

        btnHost = new QPushButton(widget);
        btnHost->setObjectName("btnHost");

        horizontalLayout->addWidget(btnHost);

        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName("btnConnect");

        horizontalLayout->addWidget(btnConnect);


        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 724, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(btnHost, SIGNAL(clicked()), MainWindow, SLOT(host()));
        QObject::connect(btnConnect, SIGNAL(clicked()), MainWindow, SLOT(connectToBoard()));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "room Code", nullptr));
        btnHost->setText(QCoreApplication::translate("MainWindow", "host", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
