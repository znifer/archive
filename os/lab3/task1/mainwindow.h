#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <psapi.h>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DWORD getProcessID(QString name);


private slots:
    void on_ProcessNameButton_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
