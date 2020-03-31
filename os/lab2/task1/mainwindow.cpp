#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    DWORD currentId = GetCurrentProcessId();
    TCHAR path[MAX_PATH], modulename[MAX_PATH];
    HANDLE currentHandle = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, currentId);
    GetModuleFileNameExW(currentHandle, m, path, MAX_PATH);

    m = GetModuleHandleW(path);
    name = "Ошибка!";
    fullname = "Ошибка!";
    getInfoByHandle(m, name, fullname);
    ui->name->setText(name);
    ui->fullname->setText(fullname);
    ui->handle->setText("0x" + QString::number((int)m, 16));
    on_nameButton_clicked();
    CloseHandle(currentHandle);
}

MainWindow::~MainWindow(){
    delete ui;
}

/*1.принимая дескриптор, имя или полное имя модуля, возвращает другие два
элемента в своих выходных параметрах. Возможны четыре варианта работы этой
функции.*/

bool MainWindow::getInfoByHandle(HMODULE m, QString &name, QString &fullname){
    WCHAR processName[256];
    int size = GetModuleFileNameW(m, processName, sizeof(processName));
    if (size == 0) return false;

    processName[size + 1] = 0;
    fullname = QString::fromWCharArray(processName);
    name = fullname;
    name.remove(0, name.lastIndexOf("\\") + 1);

    return true;
}

bool MainWindow::getInfoByName(HMODULE &handle, QString name, QString &fullname){
    WCHAR processName[256];
    int size = name.toWCharArray(processName);
    processName[size] = 0;
    handle = GetModuleHandle(processName);

    if (handle != NULL){
        WCHAR wFullname[256];
        int wSize = GetModuleFileName(handle, wFullname, sizeof(wFullname));
        wFullname[wSize + 1] = 0;
        fullname = QString::fromWCharArray(wFullname);
        return true;
    }
    return false;
}

bool MainWindow::getInfoByFullname(HMODULE &handle, QString &name, QString fullname){
    name.remove(0, name.lastIndexOf("\\") + 1);
    getInfoByFullname(handle, name, fullname);
}

void MainWindow::on_handleButton_clicked(){
    handle = ui->handle->text();
    m = (HMODULE)handle.toInt(0, 0);
    if  (getInfoByHandle(m, name, fullname)){
        ui->name->setText(name);
        ui->fullname->setText(fullname);
    } else {
        ui->fullname->setText("Ошибка!");
        ui->name->setText("Ошибка!");
    }
}

void MainWindow::on_nameButton_clicked(){
    name = ui->name->text();
    m = nullptr;
    if  (getInfoByName(m, name, fullname)){
        ui->handle->setText("0x" + QString::number((int)m, 16));
        ui->fullname->setText(fullname);
    } else {
        ui->handle->setText("Ошибка!");
        ui->fullname->setText("Ошибка!");
    }
}

void MainWindow::on_fullnameButton_clicked(){
    m = nullptr;
    fullname = ui->fullname->text();
    if (getInfoByFullname(m, name, fullname)){
        ui->handle->setText("0x" + QString::number((int)m, 16));
        ui->name->setText(name);
    } else {
        ui->handle->setText("Ошибка!");
        ui->name->setText(name);
    }

}
