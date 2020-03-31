#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <psapi.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool getInfoByHandle(HMODULE handle, QString & name, QString & fullname);
    bool getInfoByName(HMODULE & handle, QString name, QString & fullname);
    bool getInfoByFullname(HMODULE & handle, QString & name, QString fullname);


private slots:
    void on_nameButton_clicked();
    void on_handleButton_clicked();
    void on_fullnameButton_clicked();

private:
    Ui::MainWindow *ui;
    QString name, fullname, handle;
    DWORD id;
    HANDLE h;
    HMODULE m;
};
#endif // MAINWINDOW_H
