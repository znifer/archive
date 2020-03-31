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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *currentId;
    QLabel *label_4;
    QLineEdit *currentHandle;
    QLabel *label_2;
    QLineEdit *copyHandle;
    QLabel *label_3;
    QLineEdit *copyProcess;
    QLabel *label_5;
    QLabel *op;
    QLabel *label_6;
    QLabel *cp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(359, 355);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, label);

        currentId = new QLineEdit(centralwidget);
        currentId->setObjectName(QString::fromUtf8("currentId"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, currentId);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, label_4);

        currentHandle = new QLineEdit(centralwidget);
        currentHandle->setObjectName(QString::fromUtf8("currentHandle"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, currentHandle);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, label_2);

        copyHandle = new QLineEdit(centralwidget);
        copyHandle->setObjectName(QString::fromUtf8("copyHandle"));

        formLayout->setWidget(5, QFormLayout::SpanningRole, copyHandle);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(6, QFormLayout::SpanningRole, label_3);

        copyProcess = new QLineEdit(centralwidget);
        copyProcess->setObjectName(QString::fromUtf8("copyProcess"));

        formLayout->setWidget(7, QFormLayout::SpanningRole, copyProcess);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_5);

        op = new QLabel(centralwidget);
        op->setObjectName(QString::fromUtf8("op"));

        formLayout->setWidget(8, QFormLayout::FieldRole, op);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_6);

        cp = new QLabel(centralwidget);
        cp->setObjectName(QString::fromUtf8("cp"));

        formLayout->setWidget(9, QFormLayout::FieldRole, cp);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\264\320\265\320\275\321\202\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200 \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\201\320\265\320\262\320\264\320\276\320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200 \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 DuplicateHandle:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 OpenProcess:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\320\270\320\265 \320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200\320\260, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\320\276\320\263\320\276 DuplicateHandle:", nullptr));
        op->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\320\270\320\265 \320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200\320\260, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\320\276\320\263\320\276 OpenProcess:", nullptr));
        cp->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
