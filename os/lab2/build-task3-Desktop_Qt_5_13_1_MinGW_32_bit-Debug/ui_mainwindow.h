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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTableWidget *ntTable;
    QTableWidget *ntModuleTable;
    QPushButton *ntRefresh;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QTableWidget *driversTable;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *win9xTable;
    QTableWidget *moduleTable;
    QTableWidget *threadsTable;
    QPushButton *refresh;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ntTable = new QTableWidget(tab);
        ntTable->setObjectName(QString::fromUtf8("ntTable"));

        verticalLayout->addWidget(ntTable);

        ntModuleTable = new QTableWidget(tab);
        ntModuleTable->setObjectName(QString::fromUtf8("ntModuleTable"));

        verticalLayout->addWidget(ntModuleTable);

        ntRefresh = new QPushButton(tab);
        ntRefresh->setObjectName(QString::fromUtf8("ntRefresh"));

        verticalLayout->addWidget(ntRefresh);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        driversTable = new QTableWidget(tab_2);
        driversTable->setObjectName(QString::fromUtf8("driversTable"));

        horizontalLayout->addWidget(driversTable);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        win9xTable = new QTableWidget(tab_3);
        win9xTable->setObjectName(QString::fromUtf8("win9xTable"));

        verticalLayout_2->addWidget(win9xTable);

        moduleTable = new QTableWidget(tab_3);
        moduleTable->setObjectName(QString::fromUtf8("moduleTable"));

        verticalLayout_2->addWidget(moduleTable);

        threadsTable = new QTableWidget(tab_3);
        threadsTable->setObjectName(QString::fromUtf8("threadsTable"));

        verticalLayout_2->addWidget(threadsTable);

        refresh = new QPushButton(tab_3);
        refresh->setObjectName(QString::fromUtf8("refresh"));

        verticalLayout_2->addWidget(refresh);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ntRefresh->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        refresh->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
