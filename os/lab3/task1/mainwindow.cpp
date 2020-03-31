#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->statusLabel->setText("");
    ui->timeEdit->setValue(3.0);
    ui->timeEdit->setSuffix(" сек.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

DWORD MainWindow::getProcessID(QString name){
    DWORD length = 2048, cbNeeded, ids[2048];
    HANDLE h;
    WCHAR wName[256];
    QString tmpname;
    WINBOOL flag = false;
    if (!EnumProcesses(ids, length * sizeof(DWORD), &cbNeeded)) return -1;
    qDebug() << length << cbNeeded;
    for (long i = 0; i < cbNeeded / sizeof(DWORD); i++){
        h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, flag, ids[i]);

        if (!GetModuleBaseNameW(h, NULL, wName, 256)) tmpname = "";
        else {
            tmpname = QString::fromWCharArray(wName);
            qDebug() << tmpname << " = " << QString::fromWCharArray(wName);
        }

        if (tmpname.toLower() == name.toLower()){
            CloseHandle(h);
            qDebug() << ids[i];
            return ids[i];
        }
        CloseHandle(h);

    }
    return -1;
}

void MainWindow::on_ProcessNameButton_clicked(){
    ui->statusLabel->setText("Ждем, пока процесс завершится");
    //ui->statusLabel->setText("");
    DWORD id = getProcessID(ui->processName->text());
    if (id == -1){
        ui->statusLabel->setStyleSheet("color: rgb(255, 0, 0");
        ui->statusLabel->setText("Не удалось получить информацию о процессе");
        repaint();
        return;
    }
    ui->statusLabel->setText("Ждем, пока процесс " + ui->processName->text() + " завершится");
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | SYNCHRONIZE, false, id);
    QTime timer;
    DWORD timeout = ui->timeEdit->value();
    timer.start();
    DWORD waitingResult = WaitForSingleObject(h, timeout * 1000);
    double time = (timer.elapsed()/100)/10.0;
    CloseHandle(h);
    switch (waitingResult){
        case WAIT_OBJECT_0:
            ui->statusLabel->setStyleSheet("color: green");
            ui->statusLabel->setText("Процесс завершен! Прошло времени: " + QString::number(time) + " сек.");
        break;
        case WAIT_TIMEOUT:
            ui->statusLabel->setStyleSheet("color: red");
            ui->statusLabel->setText("Процесс не был завершен за " + QString::number(ui->timeEdit->value()) + " сек.");
        break;
        case WAIT_FAILED:
            ui->statusLabel->setStyleSheet("color: red");
            ui->statusLabel->setText("Произошла непредвиденная ошибка");
        break;
    }

}
