/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QFrame *line_2;
    QLabel *label_8;
    QLineEdit *ipToDEdit;
    QLabel *label_9;
    QLineEdit *ipToDResult;
    QPushButton *ipToDGet;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QFrame *line;
    QLabel *label_2;
    QLineEdit *dToIpEdit;
    QLabel *label;
    QLineEdit *dToIpResult;
    QPushButton *dToIpGet;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLineEdit *adapter;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QPushButton *renewButton;
    QPushButton *releaseButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 592);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_3->addWidget(label_7);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_3->addWidget(label_8);

        ipToDEdit = new QLineEdit(centralwidget);
        ipToDEdit->setObjectName(QString::fromUtf8("ipToDEdit"));

        verticalLayout_3->addWidget(ipToDEdit);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_3->addWidget(label_9);

        ipToDResult = new QLineEdit(centralwidget);
        ipToDResult->setObjectName(QString::fromUtf8("ipToDResult"));

        verticalLayout_3->addWidget(ipToDResult);

        ipToDGet = new QPushButton(centralwidget);
        ipToDGet->setObjectName(QString::fromUtf8("ipToDGet"));

        verticalLayout_3->addWidget(ipToDGet);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        dToIpEdit = new QLineEdit(centralwidget);
        dToIpEdit->setObjectName(QString::fromUtf8("dToIpEdit"));

        verticalLayout->addWidget(dToIpEdit);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        dToIpResult = new QLineEdit(centralwidget);
        dToIpResult->setObjectName(QString::fromUtf8("dToIpResult"));

        verticalLayout->addWidget(dToIpResult);

        dToIpGet = new QPushButton(centralwidget);
        dToIpGet->setObjectName(QString::fromUtf8("dToIpGet"));

        verticalLayout->addWidget(dToIpGet);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_5->addLayout(verticalLayout);


        verticalLayout_6->addLayout(verticalLayout_5);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_6->addWidget(label_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_2->addWidget(textEdit);


        verticalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        adapter = new QLineEdit(centralwidget);
        adapter->setObjectName(QString::fromUtf8("adapter"));

        verticalLayout_4->addWidget(adapter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        renewButton = new QPushButton(centralwidget);
        renewButton->setObjectName(QString::fromUtf8("renewButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, renewButton);

        releaseButton = new QPushButton(centralwidget);
        releaseButton->setObjectName(QString::fromUtf8("releaseButton"));

        formLayout->setWidget(0, QFormLayout::FieldRole, releaseButton);


        horizontalLayout->addLayout(formLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\243\320\267\320\275\320\260\321\202\321\214 IP \320\277\320\276 \320\264\320\276\320\274\320\265\320\275\320\275\320\276\320\274\321\203 \320\270\320\274\320\265\320\275\320\270 \321\203\320\267\320\273\320\260", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\274\320\265\320\275\320\275\320\276\320\265 \320\270\320\274\321\217 \321\203\320\267\320\273\320\260", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        ipToDGet->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\243\320\267\320\275\320\260\321\202\321\214 \320\264\320\276\320\274\320\265\320\275\320\275\320\276\320\265 \320\270\320\274\321\217 \321\203\320\267\320\273\320\260 \320\277\320\276 IP", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\274\320\265\320\275\320\275\320\276\320\265 \320\270\320\274\321\217 \321\203\320\267\320\273\320\260", nullptr));
        dToIpGet->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 DHCP-\321\201\320\265\321\200\320\262\320\265\321\200\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\275\320\264\320\265\320\272\321\201 \320\260\320\264\320\260\320\277\321\202\320\265\321\200\320\260", nullptr));
        renewButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\275\320\260\321\207\320\270\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \320\260\320\264\321\200\320\265\321\201 \320\260\320\264\320\260\320\277\321\202\320\265\321\200\321\203", nullptr));
        releaseButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\262\320\276\320\261\320\276\320\264\320\270\321\202\321\214 \320\260\320\264\321\200\320\265\321\201 \320\260\320\264\320\260\320\277\321\202\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
