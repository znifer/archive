#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <windows.h>
#include <synchapi.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createMutex_clicked();
    void on_beginCount_clicked();
    void on_endCount_clicked();
    void on_exit_clicked();
private:
    Ui::MainWindow *ui;
    HANDLE h;
    QTimer timer;
    unsigned timerCounter;
    bool mutexOwned;
private slots:
    void updateTimer();
};
#endif // MAINWINDOW_H
