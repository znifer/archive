#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    getCurrentInfo();
}

MainWindow::~MainWindow(){
    delete ui;
}

/*
Используя функцию GetCurrentProcessId определит идентификатор текущего процесса.
Используя функцию GetCurrentProcess определит псевдодескриптор текущего процесса.
Используя функцию DuplicateHandl и значение псевдодескриптора определит дескриптора текущего процесса.
Используя функцию OpenProcess определит копию дескриптора текущего процесса.
Закроет дескриптор, полученный функцией DuplicateHandl.
Закроет дескриптор, полученный функцией OpenProcess.
*/

void MainWindow::getCurrentInfo(){
    DWORD currentId = GetCurrentProcessId();
    HANDLE currentProcess = GetCurrentProcess();
    HANDLE copyProcess;
    DuplicateHandle(currentProcess, currentProcess, currentProcess, &copyProcess, PROCESS_ALL_ACCESS, false, 0);

    HANDLE openProcess = OpenProcess(PROCESS_ALL_ACCESS, false, currentId);

    ui->currentId->setText(QString::number(currentId));
    ui->currentHandle->setText(QString("%1").arg((int)currentProcess));
    ui->copyHandle->setText(QString("%1").arg((int)openProcess));
    ui->copyProcess->setText(QString("%1").arg((int)copyProcess));

    if (CloseHandle(copyProcess))
        ui->cp->setText("Закрыто успешно!"); else ui->cp->setText("Произошла ошибка!");
    if (CloseHandle(openProcess))
        ui->op->setText("Закрыто успешно!"); else ui->op->setText("Произошла ошибка!");
}
