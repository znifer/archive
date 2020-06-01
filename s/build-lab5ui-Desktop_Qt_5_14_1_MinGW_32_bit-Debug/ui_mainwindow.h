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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *_arpTable;
    QVBoxLayout *verticalLayout;
    QTableWidget *arpTable;
    QPushButton *refreshArpTable;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLineEdit *ipDrop;
    QLineEdit *ipEdit;
    QLabel *label_8;
    QFrame *line;
    QLabel *label_5;
    QLabel *label_3;
    QLineEdit *ipAdress;
    QLineEdit *macEdit;
    QLabel *label_4;
    QLineEdit *ifaceEdit;
    QPushButton *addEntry;
    QLabel *label_6;
    QLabel *label;
    QPushButton *getMacFromIp;
    QSpacerItem *verticalSpacer;
    QPushButton *deleteEntry;
    QLabel *label_9;
    QLineEdit *ifaceDrop;
    QLabel *label_2;
    QLabel *macAddress;
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
        _arpTable = new QWidget();
        _arpTable->setObjectName(QString::fromUtf8("_arpTable"));
        verticalLayout = new QVBoxLayout(_arpTable);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        arpTable = new QTableWidget(_arpTable);
        arpTable->setObjectName(QString::fromUtf8("arpTable"));

        verticalLayout->addWidget(arpTable);

        refreshArpTable = new QPushButton(_arpTable);
        refreshArpTable->setObjectName(QString::fromUtf8("refreshArpTable"));

        verticalLayout->addWidget(refreshArpTable);

        tabWidget->addTab(_arpTable, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        ipDrop = new QLineEdit(tab_2);
        ipDrop->setObjectName(QString::fromUtf8("ipDrop"));

        gridLayout->addWidget(ipDrop, 7, 1, 1, 1);

        ipEdit = new QLineEdit(tab_2);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));

        gridLayout->addWidget(ipEdit, 2, 1, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 8, 0, 1, 1);

        line = new QFrame(tab_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 11, 0, 1, 4);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 13, 0, 1, 1);

        ipAdress = new QLineEdit(tab_2);
        ipAdress->setObjectName(QString::fromUtf8("ipAdress"));

        gridLayout->addWidget(ipAdress, 13, 1, 1, 1);

        macEdit = new QLineEdit(tab_2);
        macEdit->setObjectName(QString::fromUtf8("macEdit"));

        gridLayout->addWidget(macEdit, 3, 1, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 15, 0, 1, 1);

        ifaceEdit = new QLineEdit(tab_2);
        ifaceEdit->setObjectName(QString::fromUtf8("ifaceEdit"));

        gridLayout->addWidget(ifaceEdit, 4, 1, 1, 1);

        addEntry = new QPushButton(tab_2);
        addEntry->setObjectName(QString::fromUtf8("addEntry"));

        gridLayout->addWidget(addEntry, 4, 2, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        getMacFromIp = new QPushButton(tab_2);
        getMacFromIp->setObjectName(QString::fromUtf8("getMacFromIp"));

        gridLayout->addWidget(getMacFromIp, 13, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 16, 2, 1, 1);

        deleteEntry = new QPushButton(tab_2);
        deleteEntry->setObjectName(QString::fromUtf8("deleteEntry"));

        gridLayout->addWidget(deleteEntry, 8, 2, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        ifaceDrop = new QLineEdit(tab_2);
        ifaceDrop->setObjectName(QString::fromUtf8("ifaceDrop"));

        gridLayout->addWidget(ifaceDrop, 8, 1, 1, 1);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        macAddress = new QLabel(tab_2);
        macAddress->setObjectName(QString::fromUtf8("macAddress"));

        gridLayout->addWidget(macAddress, 15, 1, 1, 1);

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

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        refreshArpTable->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(_arpTable), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "IP-\320\260\320\264\321\200\320\265\321\201", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 IP-\320\260\320\264\321\200\320\265\321\201", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\267\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\260\320\264\321\200\320\265\321\201", nullptr));
        addEntry->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\267\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\260\320\264\321\200\320\265\321\201", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        getMacFromIp->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214", nullptr));
        deleteEntry->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "IP-\320\260\320\264\321\200\320\265\321\201", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        macAddress->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
