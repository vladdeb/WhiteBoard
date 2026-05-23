/********************************************************************************
** Form generated from reading UI file 'savetype.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVETYPE_H
#define UI_SAVETYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saveType
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *saveType)
    {
        if (saveType->objectName().isEmpty())
            saveType->setObjectName("saveType");
        saveType->resize(400, 300);
        verticalLayout = new QVBoxLayout(saveType);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(saveType);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget = new QWidget(saveType);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName("radioButton");

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName("radioButton_2");

        horizontalLayout->addWidget(radioButton_2);


        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(saveType);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(saveType);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, saveType, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, saveType, qOverload<>(&QDialog::reject));
        QObject::connect(radioButton_2, SIGNAL(clicked()), saveType, SLOT(bmp()));
        QObject::connect(radioButton, SIGNAL(clicked()), saveType, SLOT(json()));

        QMetaObject::connectSlotsByName(saveType);
    } // setupUi

    void retranslateUi(QDialog *saveType)
    {
        saveType->setWindowTitle(QCoreApplication::translate("saveType", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("saveType", "Save as", nullptr));
        radioButton->setText(QCoreApplication::translate("saveType", "json", nullptr));
        radioButton_2->setText(QCoreApplication::translate("saveType", "picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class saveType: public Ui_saveType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVETYPE_H
