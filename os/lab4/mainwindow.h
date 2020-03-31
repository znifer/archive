#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include <QTime>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAreaSeries>
#include <QtMath>

#include <windows.h>
#include <psapi.h>

#include "customchart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showSystemInfo();
    void showMemoryStatus();
    void showMemoryMap(QString processName);
    void getProcesses();
    void updateProcesses();
private slots:
    void on_chooseProcess_currentTextChanged(const QString &arg1);
    void updateCharts();
private:
    Ui::MainWindow *ui;
    QMap <QString, HANDLE> processes;
    QString prevName;
    QTimer * updateTimer;
    QTime * time;
    CustomChart * memoryUsedInPercents, * memoryUsed, * virtualUsed, * virtualAvaliable, * swapFileUsed;
};
#endif // MAINWINDOW_H
