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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *createTab;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *routersTable;
    QPushButton *addRouter;
    QPushButton *clearRouters;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *routesTable;
    QLabel *label;
    QGridLayout *gridLayout;
    QLineEdit *router2id;
    QLineEdit *router1id;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *addRoute;
    QPushButton *clearRoutes;
    QWidget *resultTab;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *routingTable;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabBarAutoHide(false);
        createTab = new QWidget();
        createTab->setObjectName(QString::fromUtf8("createTab"));
        horizontalLayout = new QHBoxLayout(createTab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        routersTable = new QTableWidget(createTab);
        routersTable->setObjectName(QString::fromUtf8("routersTable"));

        verticalLayout->addWidget(routersTable);

        addRouter = new QPushButton(createTab);
        addRouter->setObjectName(QString::fromUtf8("addRouter"));

        verticalLayout->addWidget(addRouter);

        clearRouters = new QPushButton(createTab);
        clearRouters->setObjectName(QString::fromUtf8("clearRouters"));

        verticalLayout->addWidget(clearRouters);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        routesTable = new QTableWidget(createTab);
        routesTable->setObjectName(QString::fromUtf8("routesTable"));

        verticalLayout_2->addWidget(routesTable);

        label = new QLabel(createTab);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        router2id = new QLineEdit(createTab);
        router2id->setObjectName(QString::fromUtf8("router2id"));

        gridLayout->addWidget(router2id, 0, 2, 1, 1);

        router1id = new QLineEdit(createTab);
        router1id->setObjectName(QString::fromUtf8("router1id"));

        gridLayout->addWidget(router1id, 0, 0, 1, 1);

        label_2 = new QLabel(createTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(createTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        addRoute = new QPushButton(createTab);
        addRoute->setObjectName(QString::fromUtf8("addRoute"));

        verticalLayout_2->addWidget(addRoute);

        clearRoutes = new QPushButton(createTab);
        clearRoutes->setObjectName(QString::fromUtf8("clearRoutes"));

        verticalLayout_2->addWidget(clearRoutes);


        horizontalLayout->addLayout(verticalLayout_2);

        tabWidget->addTab(createTab, QString());
        resultTab = new QWidget();
        resultTab->setObjectName(QString::fromUtf8("resultTab"));
        verticalLayout_4 = new QVBoxLayout(resultTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        routingTable = new QTextEdit(resultTab);
        routingTable->setObjectName(QString::fromUtf8("routingTable"));

        verticalLayout_4->addWidget(routingTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(resultTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        tabWidget->addTab(resultTab, QString());

        verticalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addRouter->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\270\320\267\320\260\321\202\320\276\321\200", nullptr));
        clearRouters->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\320\275\320\260\320\273 \321\201\320\262\321\217\320\267\320\270, \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \321\201\320\276\320\265\320\264\320\270\320\275\321\217\320\265\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\270\320\267\320\260\321\202\320\276\321\200\321\213", nullptr));
        addRoute->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        clearRoutes->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(createTab), QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\201\320\265\321\202\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(resultTab), QCoreApplication::translate("MainWindow", "\320\242\320\260\320\261\320\273\320\270\321\206\321\213 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
