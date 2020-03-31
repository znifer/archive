#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "NT");
    ui->tabWidget->setTabText(1, "Драйверы");
    ui->tabWidget->setTabText(2, "win9x");

    ui->moduleTable->setColumnCount(4);
    ui->moduleTable->setHorizontalHeaderLabels({"Название модуля", "Дескриптор модуля", "Размер", "Путь к модулю"});
    ui->moduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->threadsTable->setColumnCount(3);
    ui->threadsTable->setHorizontalHeaderLabels({"Id потока", "Id  процесса", "Приоритет"});
    ui->threadsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->driversTable->setColumnCount(3);
    ui->driversTable->setHorizontalHeaderLabels({"Название драйвера","Путь", "Адрес загрузки"});
    ui->driversTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->win9xTable->setColumnCount(5);
    ui->win9xTable->setRowCount(0);
    ui->win9xTable->setHorizontalHeaderLabels({"Имя процесса", "id", "Кол-во потоков", "Р. процесс", "Приоритет"});
    ui->win9xTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->ntTable->setColumnCount(2);
    ui->ntTable->setHorizontalHeaderLabels({"Id процесса", "Имя процесса"});
    ui->ntTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->ntModuleTable->setColumnCount(5);
    ui->ntModuleTable->setRowCount(0);
    ui->ntModuleTable->setHorizontalHeaderLabels({"Имя модуля", "Путь к модулю", "Адрес загрузки", "Размер", "Точка входа"});
    ui->ntModuleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    showDrivers();
    showNT();
    showWin9x();
}

MainWindow::~MainWindow(){
    delete ui;
}

/*
выдает списка перечисления всех процессов, потоков, модулей и их свойства в системе:
для Windows NT (и список загруженных драйверов устройств).
для Windows 9x.
*/


void MainWindow::showDrivers(){
    LPVOID drivers[256];
    DWORD count;
    if (EnumDeviceDrivers(drivers, sizeof(drivers), &count) && count < sizeof(drivers)){
        ui->driversTable->setRowCount(count / sizeof(DWORD));
        for (int i = 0; i < count / sizeof(DWORD); i++){
            WCHAR name[256], path[256];
            GetDeviceDriverFileName(drivers[i], path, sizeof(path));
            GetDeviceDriverBaseName(drivers[i], name, sizeof(path));
            ui->driversTable->setItem(i, 0, new QTableWidgetItem(QString::fromWCharArray(name)));
            ui->driversTable->setItem(i, 1, new QTableWidgetItem(QString::fromWCharArray(path)));
            ui->driversTable->setItem(i, 2, new QTableWidgetItem("0x"+QString::number((int)drivers[i],16)));
        }
    }
}

void MainWindow::showNT(){
    DWORD processIds[256];
    DWORD size = sizeof(processIds), count;
    HANDLE h;
    WCHAR name[256];
    int writePos = 0, descInc = 0;

    if (EnumProcesses(processIds, size, &count)){
        ui->ntTable->setRowCount(count / sizeof(DWORD));

        for (int i = 0; i < count / sizeof(DWORD); i++){
            h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processIds[i]);
            int t = GetModuleFileNameEx(h, NULL, name, sizeof(name));
            if (t){
                if (descInc == 0) descInc = (int)h;
                name[t + 1] = 0;
                ui->ntTable->setItem(writePos, 0, new QTableWidgetItem(QString::number(processIds[i])));
                ui->ntTable->setItem(writePos, 1, new QTableWidgetItem(QString::fromWCharArray(name)));
                //ui->ntTable->setItem(writePos, 2, new QTableWidgetItem(QString("%1").arg((int)h - descInc)));
                writePos++;
            }
            CloseHandle(h);
        }
    }
    ui->ntTable->setRowCount(writePos);
}

void MainWindow::showProcessModulesNT(DWORD processId){
    ui->ntModuleTable->setRowCount(0);
    ui->ntModuleTable->setColumnCount(5);
    ui->ntModuleTable->setHorizontalHeaderLabels({"Имя модуля", "Путь к модулю", "Адрес загрузки", "Размер", "Точка входа"});

    HMODULE modules[256];
    HANDLE h;
    DWORD cb = sizeof(HMODULE) * 256;
    DWORD cb_needed;
    WCHAR moduleName[255];
    int writePos = 0;
    h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processId);
    if (EnumProcessModules(h, modules, cb, &cb_needed)){
        for (int i = 0; i < cb_needed / sizeof(HMODULE); i++){
            int pos = GetModuleBaseName(h, modules[i], moduleName, 256);
            moduleName[pos + 1] = 0;
            ui->ntModuleTable->insertRow(writePos);
            qDebug() <<QString::fromWCharArray(moduleName) << "!!!";
            ui->ntModuleTable->setItem(writePos, 0, new QTableWidgetItem(QString::fromWCharArray(moduleName)));

            GetModuleFileNameEx(h, modules[i], moduleName, 256);
            MODULEINFO info;
            if (GetModuleInformation(h, modules[i], &info, sizeof(info))){
                ui->ntModuleTable->setItem(writePos, 1, new QTableWidgetItem(QString::fromWCharArray(moduleName)));
                ui->ntModuleTable->setItem(writePos, 2, new QTableWidgetItem(QString("0x%1").arg((int)info.lpBaseOfDll, 0, 16)));
                double size = (double)info.SizeOfImage / 1024 / 1024;
                ui->ntModuleTable->setItem(writePos, 3, new QTableWidgetItem(QString("%1").arg(size, 0, 'f', 2) + " Мбайт"));
                ui->ntModuleTable->setItem(writePos, 4, new QTableWidgetItem(QString("0x%1").arg((int)info.EntryPoint, 0, 16)));
            }


            writePos++;
        }
    }
    CloseHandle(h);

}

void MainWindow::showProcessThreads(DWORD processId){
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    ui->threadsTable->setColumnCount(3);
    ui->threadsTable->setRowCount(0);
    ui->threadsTable->setHorizontalHeaderLabels({"Id потока", "Id  процесса", "Приоритет"});
    int writePos = 0;
    if ((int)h == -1){
        QMessageBox::warning(this, "", "Ошибка получения снимка потоков");
        qDebug() << "ОШИБКА ПОЛУЧЕНИЯ СНИМКА ПОТОКОВ";
    } else {
        THREADENTRY32 thread;
        thread.dwSize = sizeof(thread);
        if (bool f = Thread32First(h, &thread)){
            while (f){
                if (thread.th32OwnerProcessID == processId){
                    ui->threadsTable->insertRow(writePos);
                    ui->threadsTable->setItem(writePos, 0, new QTableWidgetItem(QString::number(thread.th32ThreadID)));
                    ui->threadsTable->setItem(writePos, 1, new QTableWidgetItem(QString::number(thread.th32OwnerProcessID)));
                    ui->threadsTable->setItem(writePos, 2, new QTableWidgetItem(QString::number((int)thread.tpBasePri)));
                    writePos++;
                }
                f = Thread32Next(h, &thread);
            }
        }
    }
    ui->threadsTable->setRowCount(writePos + 1);
    CloseHandle(h);
}

void  MainWindow::showProcessModules(DWORD processId){
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

    ui->moduleTable->setColumnCount(4);
    ui->moduleTable->setRowCount(0);
    ui->moduleTable->setHorizontalHeaderLabels({"Название модуля", "Дескриптор модуля", "Размер", "Путь к модулю"});

    if ((int)h == -1){
         QMessageBox::warning(this, "", "Не удалось получить доступ к модулям");
    } else {
        MODULEENTRY32W module;
        module.dwSize = sizeof(module);
        int writePos = 0;
        if (bool f = Module32FirstW(h, &module)){
            while (f){
                ui->moduleTable->insertRow(writePos);
                ui->moduleTable->setItem(writePos, 0, new QTableWidgetItem(QString::fromWCharArray(module.szModule)));
                ui->moduleTable->setItem(writePos, 1, new QTableWidgetItem(QString("%1").arg((int)module.hModule)));
                ui->moduleTable->setItem(writePos, 2, new QTableWidgetItem(QString::number(module.modBaseSize)));
                ui->moduleTable->setItem(writePos, 3, new QTableWidgetItem(QString::fromWCharArray(module.szExePath)));
                writePos++;
                f = Module32NextW(h, &module);
            }
        }
    }
    CloseHandle(h);
}

void MainWindow::showWin9x(){
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W process;
    process.dwSize = sizeof(PROCESSENTRY32W);
    int writePos = 0;
    if (bool f = Process32FirstW(h, &process)){
        while(f){
            ui->win9xTable->insertRow(writePos);
            ui->win9xTable->setItem(writePos, 0, new QTableWidgetItem(QString::fromWCharArray(process.szExeFile)));
            ui->win9xTable->setItem(writePos, 1, new QTableWidgetItem(QString::number(process.th32ProcessID)));
            ui->win9xTable->setItem(writePos, 2, new QTableWidgetItem(QString::number(process.cntThreads)));
            ui->win9xTable->setItem(writePos, 3, new QTableWidgetItem(QString::number(process.th32ParentProcessID)));
            ui->win9xTable->setItem(writePos, 4, new QTableWidgetItem(QString::number((int)process.pcPriClassBase)));
            writePos++;
            f = Process32NextW(h, &process);
        }
    }
    CloseHandle(h);
}

void MainWindow::on_refresh_clicked(){
    showWin9x();
}

void MainWindow::on_ntRefresh_clicked(){
    showNT();
}

void MainWindow::on_win9xTable_cellClicked(int row, int column){
    showProcessModules(ui->win9xTable->item(row, 1)->text().toInt());
    showProcessThreads(ui->win9xTable->item(row, 1)->text().toInt());
}

void MainWindow::on_ntTable_cellClicked(int row, int column){
    ui->ntModuleTable->clear();
    showProcessModulesNT(ui->ntTable->item(row, 0)->text().toInt());
}
