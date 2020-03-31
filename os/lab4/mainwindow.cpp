#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "Системная информация");
    showSystemInfo();
    getProcesses();

    ui->tabWidget->setTabText(1, "Карта виртуальной памяти");
    ui->virtualMemoryMap->clear();
    ui->virtualMemoryMap->clearContents();
    ui->virtualMemoryMap->setRowCount(0);
    ui->virtualMemoryMap->reset();
    ui->virtualMemoryMap->setColumnCount(7);
    ui->virtualMemoryMap->setHorizontalHeaderLabels({"Базовый адрес", "Конечный адрес","Количество страниц",
                                                     "Размер области","Состояние памяти", "Тип защиты", "Тип области"});
    ui->virtualMemoryMap->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    updateProcesses();

    time = new QTime;           time->start();
    updateTimer = new QTimer;   updateTimer->start();

    ui->tabWidget->setTabText(2, "Физическая память");
    ui->tabWidget->setTabText(3, "Виртуальная память");
    ui->charts->setLayout(new QVBoxLayout);
    ui->vcharts->setLayout(new QVBoxLayout);
    showMemoryStatus();

    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateCharts);
    updateTimer->setInterval(1000);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showSystemInfo(){
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    switch (info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        ui->processorArch->setText("AMD x64");
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        ui->processorArch->setText("ARM");
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        ui->processorArch->setText("IA-64");
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        ui->processorArch->setText("Intel x86");
        break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
        ui->processorArch->setText("Не удалось получить информацию об архитектуре процессора");
        break;
    }
    switch (info.dwProcessorType) {
    case PROCESSOR_INTEL_386:
        ui->processorType->setText("i386");
        break;
    case PROCESSOR_INTEL_486:
        ui->processorType->setText("i486");
        break;
    case PROCESSOR_INTEL_PENTIUM:
        ui->processorType->setText("Pentium (i586)");
        break;
    case PROCESSOR_INTEL_IA64:
        ui->processorType->setText("Itanium");
        break;
    case PROCESSOR_AMD_X8664:
        ui->processorType->setText("x86-64");
        break;
    }
    ui->processorCores->setText(QString::number(info.dwNumberOfProcessors));
    ui->processorMask->setText(QString::number(info.dwActiveProcessorMask, 2));
    ui->processorLevel->setText(QString::number(info.wProcessorLevel));
    ui->processorRevision->setText("Family: " + QString::number(HIBYTE(info.wProcessorRevision)) + ", Stepping: " + QString::number(LOBYTE(info.wProcessorRevision)));
    ui->pageSize->setText(QString::number(info.dwPageSize / 1024) + " кб");
    ui->lowerBorder->setText("0x" + QString::number((long long)info.lpMinimumApplicationAddress, 16).toUpper().rightJustified(16, '0'));
    ui->upperBorder->setText("0x" +  QString::number((long long)info.lpMaximumApplicationAddress, 16).toUpper().rightJustified(16, '0'));
    ui->gr->setText(QString::number(info.dwAllocationGranularity / 1024) + " кб");
}

void MainWindow::updateProcesses(){
    getProcesses();
    ui->chooseProcess->clear();
    for (auto name : processes.keys())
        ui->chooseProcess->addItem(name);
}

void MainWindow::getProcesses(){
    HANDLE h;
    for (auto name : processes.keys()){
        HANDLE h = processes.take(name);
        CloseHandle(h);
    }
    DWORD cbNeeded, p[2048];
    WCHAR name[256];
    QString qname;
    WINBOOL f = false;
    if (!EnumProcesses(p, 2048 * sizeof(DWORD), &cbNeeded)) return;
    for (DWORD i = 0; i < cbNeeded; i++){
        h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, f, p[i]);

        if(GetModuleBaseNameW(h, NULL, name, 256)){
            processes.insert(QString::fromWCharArray(name), h);
            qDebug() << QString::fromWCharArray(name);
        }
    }
}

void MainWindow::showMemoryMap(QString processName){
    HANDLE processHandle;
    auto h = processes.find(processName);
    if (h != processes.end()){
         processHandle = *h;
        prevName = processName;
    }else{
        return;
    }

    HMODULE modules[1024];
    DWORD sz;
    EnumProcessModules(processHandle, modules, 1024, &sz);

    QVector <LPVOID> addresses;
    QVector <QString> names;
    for (DWORD i = 0; i < sz; i++){
        MODULEINFO moduleInfo;
        GetModuleInformation(processHandle, modules[i], &moduleInfo, sizeof(moduleInfo));
        addresses.append(moduleInfo.lpBaseOfDll);
        WCHAR buffer[MAX_PATH];
        GetModuleFileNameExW(processHandle, modules[i], buffer, MAX_PATH);
        names.append(QString::fromWCharArray(buffer));
    }

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    long long address = 0;
    int row = 0;
    MEMORY_BASIC_INFORMATION memoryInfo;
    while (VirtualQueryEx(processHandle, (LPVOID)address, &memoryInfo, sizeof(memoryInfo)) != 0) {
        ui->virtualMemoryMap->insertRow(row);
        // Если участок памяти принадлежит модулю, надо добавить в таблицу строку с именем
        if (memoryInfo.BaseAddress != NULL && addresses.contains(memoryInfo.BaseAddress)){
            int index = addresses.indexOf(memoryInfo.BaseAddress);
            ui->virtualMemoryMap->setItem(row, 0, new QTableWidgetItem(names[index]));
            ui->virtualMemoryMap->setSpan(row, 0, 1, 7);
            row++;
            ui->virtualMemoryMap->insertRow(row);
        }
        // Начальный адрес
        QTableWidgetItem* baseAddressItem = new QTableWidgetItem("0x" + QString("%1").arg((long long)memoryInfo.BaseAddress, 16, 16, QChar('0')).toUpper());
        ui->virtualMemoryMap->setItem(row, 0, baseAddressItem);
        // Конечный адрес
        address += memoryInfo.RegionSize;
        QTableWidgetItem* finalAddressItem = new QTableWidgetItem("0x" + QString("%1").arg(address - 1, 16, 16, QChar('0')).toUpper());
        ui->virtualMemoryMap->setItem(row, 1, finalAddressItem);
        // Количество страниц
        ui->virtualMemoryMap->setItem(row, 2, new QTableWidgetItem(QString::number(memoryInfo.RegionSize/systemInfo.dwPageSize)));
        // Размер области
        ui->virtualMemoryMap->setItem(row, 3, new QTableWidgetItem(QString::number(memoryInfo.RegionSize / 1024) + " Кб"));
        // Состояние памяти
        QString memoryState= "Не удалось прочитать значение memoryState";
        switch (memoryInfo.State){
        case MEM_COMMIT: memoryState = "MEM_COMMIT - зафиксировано"; break;
        case MEM_RESERVE: memoryState = "MEM_RESERVE - зарезервировано"; break;
        case MEM_FREE: memoryState = "MEM_FREE - Свободно"; break;
        }
        ui->virtualMemoryMap->setItem(row, 4, new QTableWidgetItem(memoryState));

        // Если не свободно, то режим и тип области
        if (memoryInfo.State != MEM_FREE) {
            QString protectMode = "0 - нет доступа";
            switch (memoryInfo.Protect) {
            case  PAGE_EXECUTE_READWRITE: protectMode = "PAGE_EXECUTE_READWRITE - Исполнение, чтение и запись"; break;
            case  PAGE_READONLY: protectMode = "PAGE_READONLY - Только чтение"; break;
            case  PAGE_READWRITE: protectMode = "PAGE_READWRITE - Чтение и запись"; break;
            case  PAGE_EXECUTE_WRITECOPY: protectMode = "PAGE_EXECUTE_WRITECOPY - Исполнение и запись с копированием"; break;
            case  PAGE_EXECUTE_READ: protectMode = "PAGE_EXECUTE_READ - Исполнение и чтение"; break;
            case  PAGE_EXECUTE: protectMode = "PAGE_EXECUTE - Исполнение"; break;
            case  PAGE_NOACCESS: protectMode = "PAGE_NOACCESS - Нет доступа"; break;
            case  PAGE_WRITECOPY: protectMode = "PAGE_WRITECOPY - Запись копированием"; break;
            case  PAGE_GUARD: protectMode = "PAGE_GUARD - Защищено"; break;
            case  PAGE_NOCACHE: protectMode = "PAGE_NOCACHE - Нельзя кэшировать"; break;
            }
            ui->virtualMemoryMap->setItem(row, 5, new QTableWidgetItem(protectMode));

            QString type = "Неизвестно";
            switch (memoryInfo.Type) {
            case MEM_IMAGE: type = "MEM_IMAGE - загрузочный";
            case MEM_MAPPED: type = "MEM_MAPPED - файл данных";
            case MEM_PRIVATE: type = "MEM_PRIVATE - приватный";
            }
            ui->virtualMemoryMap->setItem(row, 6, new QTableWidgetItem(type));
        }
        row++;
    }
}

void MainWindow::on_chooseProcess_currentTextChanged(const QString &arg1){
    showMemoryMap(arg1);
}

void MainWindow::showMemoryStatus(){
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);

    QtCharts::QChartView * chart = new QtCharts::QChartView(this);
    memoryUsedInPercents = new CustomChart(100, 1, Qt::green, QString("Использование физ. памяти:"),
                                 QString("Время (сек)"), QString("Занято (%)"));
    chart->setChart(memoryUsedInPercents);
    ui->charts->layout()->addWidget(chart);

    memoryUsed = new CustomChart (memoryStatus.ullTotalPhys, pow(2, 30), Qt::green, QString("Доступно физической памяти:"),
                                       QString("Время (сек)"), QString("Доступно (Гб)"));
    chart = new QtCharts::QChartView(this);
    chart->setChart(memoryUsed);
    ui->charts->layout()->addWidget(chart);

    virtualUsed = new CustomChart(memoryStatus.ullTotalVirtual, pow(2, 30), Qt::green, QString("Использование вирт. памяти:"),
                                           QString("Время (сек)"), QString("Доступно (Гб)"));
    chart = new QtCharts::QChartView(this);
    chart->setChart(virtualUsed);
    ui->vcharts->layout()->addWidget(chart);

    virtualAvaliable = new CustomChart(memoryStatus.ullTotalVirtual, pow(2, 30), Qt::green, QString("Доступно виртуальной памяти"),
                                       QString("Время (сек)"), QString("Доступно (Гб)"));
    chart = new QtCharts::QChartView(this);
    chart->setChart(virtualAvaliable);
    ui->vcharts->layout()->addWidget(chart);

    swapFileUsed = new CustomChart(memoryStatus.ullTotalPageFile, pow(2, 30), Qt::green, QString("Доступный объём файла подкачки"),
                                   QString("Время (сек)"), QString("Доступно (Гб)"));
    chart = new QtCharts::QChartView(this);
    chart->setChart(swapFileUsed);
    ui->vcharts->layout()->addWidget(chart);
}

void MainWindow::updateCharts(){
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);

    qreal elapsed = time->elapsed() / 1000;
    memoryUsedInPercents->update(elapsed, memoryStatus.dwMemoryLoad);
    memoryUsed->update(elapsed, memoryStatus.ullAvailPhys);
    virtualUsed->update(elapsed, memoryStatus.ullAvailVirtual);
    virtualAvaliable->update(elapsed, memoryStatus.ullTotalVirtual - memoryStatus.ullAvailVirtual);
    swapFileUsed->update(elapsed, memoryStatus.ullAvailPageFile);
}
