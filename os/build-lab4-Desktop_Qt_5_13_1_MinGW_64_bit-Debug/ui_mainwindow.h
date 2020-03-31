/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *sysInfo;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *processorArch;
    QLabel *processorType;
    QLabel *processorLevel;
    QLabel *processorRevision;
    QLabel *processorCores;
    QLabel *processorMask;
    QLabel *lowerBorder;
    QLabel *label_19;
    QLabel *pageSize;
    QLabel *upperBorder;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *gr;
    QWidget *tab_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sysInfo = new QWidget();
        sysInfo->setObjectName(QString::fromUtf8("sysInfo"));
        formLayout = new QFormLayout(sysInfo);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(sysInfo);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_7 = new QLabel(sysInfo);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        label_4 = new QLabel(sysInfo);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        label_3 = new QLabel(sysInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        label_6 = new QLabel(sysInfo);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        label_5 = new QLabel(sysInfo);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        label_8 = new QLabel(sysInfo);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        processorArch = new QLabel(sysInfo);
        processorArch->setObjectName(QString::fromUtf8("processorArch"));

        formLayout->setWidget(0, QFormLayout::FieldRole, processorArch);

        processorType = new QLabel(sysInfo);
        processorType->setObjectName(QString::fromUtf8("processorType"));

        formLayout->setWidget(1, QFormLayout::FieldRole, processorType);

        processorLevel = new QLabel(sysInfo);
        processorLevel->setObjectName(QString::fromUtf8("processorLevel"));

        formLayout->setWidget(2, QFormLayout::FieldRole, processorLevel);

        processorRevision = new QLabel(sysInfo);
        processorRevision->setObjectName(QString::fromUtf8("processorRevision"));

        formLayout->setWidget(3, QFormLayout::FieldRole, processorRevision);

        processorCores = new QLabel(sysInfo);
        processorCores->setObjectName(QString::fromUtf8("processorCores"));

        formLayout->setWidget(4, QFormLayout::FieldRole, processorCores);

        processorMask = new QLabel(sysInfo);
        processorMask->setObjectName(QString::fromUtf8("processorMask"));

        formLayout->setWidget(5, QFormLayout::FieldRole, processorMask);

        lowerBorder = new QLabel(sysInfo);
        lowerBorder->setObjectName(QString::fromUtf8("lowerBorder"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lowerBorder);

        label_19 = new QLabel(sysInfo);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_19);

        pageSize = new QLabel(sysInfo);
        pageSize->setObjectName(QString::fromUtf8("pageSize"));

        formLayout->setWidget(8, QFormLayout::FieldRole, pageSize);

        upperBorder = new QLabel(sysInfo);
        upperBorder->setObjectName(QString::fromUtf8("upperBorder"));

        formLayout->setWidget(7, QFormLayout::FieldRole, upperBorder);

        label_10 = new QLabel(sysInfo);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_10);

        label_9 = new QLabel(sysInfo);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_9);

        gr = new QLabel(sysInfo);
        gr->setObjectName(QString::fromUtf8("gr"));

        formLayout->setWidget(9, QFormLayout::FieldRole, gr);

        tabWidget->addTab(sysInfo, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\220\321\200\321\205\320\270\321\202\320\265\320\272\321\202\321\203\321\200\320\260 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\235\320\270\320\266\320\275\321\217\321\217 \320\263\321\200\320\260\320\275\320\270\321\206\320\260 \320\260\320\264\321\200\320\265\321\201\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\321\201\321\202\320\262\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\320\272\320\260 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\262\320\270\320\267\320\270\321\217 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\276\320\262", nullptr));
        processorArch->setText(QString());
        processorType->setText(QString());
        processorLevel->setText(QString());
        processorRevision->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        processorCores->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        processorMask->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lowerBorder->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\321\213", nullptr));
        pageSize->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        upperBorder->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\205\320\275\321\217\321\217 \320\263\321\200\320\260\320\275\320\270\321\206\320\260 \320\260\320\264\321\200\320\265\321\201\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\321\201\321\202\320\262\320\260", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\320\275\321\203\320\273\321\217\321\200\320\275\320\276\321\201\321\202\321\214", nullptr));
        gr->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(sysInfo), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
