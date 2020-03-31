#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showNT();
    void showWin9x();
    void showDrivers();
    void showProcessThreads(DWORD processId);
    void showProcessModules(DWORD processId);
    void showProcessModulesNT(DWORD processId);
private slots:
    void on_ntRefresh_clicked();
    void on_refresh_clicked();
    void on_win9xTable_cellClicked(int row, int column);
    void on_ntTable_cellClicked(int row, int column);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
