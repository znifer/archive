#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    h = NULL;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timerCounter = 1;
    ui->counter->setText(QString::number(timerCounter));
    timer.setInterval(1000);
    mutexOwned = false;
    ui->counter->setStyleSheet("color: green");
    setWindowTitle("Task2");
}

MainWindow::~MainWindow(){
    CloseHandle(h);
    delete ui;
}


void MainWindow::on_createMutex_clicked(){
    if (h != NULL) return;
    h = CreateMutexA(NULL, TRUE, "lab3Mutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS){
        ui->counter->setStyleSheet("color: red");
        ui->status->setText("Мьютекс уже создан другим процессом!");
    } else {
        mutexOwned = true;
        ui->status->setText("Мьютекс создан!");
    }
}

void MainWindow::on_beginCount_clicked(){
    if (h == NULL){
        ui->status->setText("Мьютекс не был создан или открыт!");
        return;
    }
    if (timer.isActive()) return;
    timer.start();
}

void MainWindow::on_endCount_clicked(){
    timer.stop();
}

void MainWindow::on_exit_clicked(){
    close();
}

void MainWindow::updateTimer(){
    if (mutexOwned){
        timerCounter++;
        ui->counter->setText(QString::number(timerCounter));
        if (timerCounter % 5 == 0){
            ReleaseMutex(h);
            mutexOwned = false;
            ui->counter->setStyleSheet("color: red");
            ui->status->setText("Мьютекс больше не принадлежит данному процессу");
        } else {
            ui->counter->setStyleSheet("color: green");
            ui->status->setText("Мьютекс принадлежит данному процессу");
        }
    } else {
        ui->counter->setStyleSheet("color: red");
        ui->status->setText("Ожидание освобождения мьютекса другим процессом");
        WaitForSingleObject(h, INFINITE);
        mutexOwned = true;
    }
}
