#include "systemmetrics.h"

SystemMetrics::SystemMetrics(){ mcount = 0; }

void SystemMetrics::readMetrics(){
    std::ifstream f("metrics.txt");
    metric m;
    int index;
    std::string str;
    if (!f.is_open()){
        return;
    } else {
        for (int i = 0; i < 50; i++){
            f >> str;
            m.name = QString::fromStdString(str);
            f >> index;
            m.index = index;
            std::getline(f, str);
            m.what = QString::fromStdString(str);
            metrics.push_back(m);
        }
    }
    f.close();
}

void SystemMetrics::getMetrics(QTableWidget *sysMetrics){
    readMetrics();
    int val;
    for (int i = 0; i < SystemMetrics::metrics.size(); i++){
        val = GetSystemMetrics(SystemMetrics::metrics[i].index);
        sysMetrics->setItem(i, 0, new QTableWidgetItem(SystemMetrics::metrics[i].name));
        //sysMetrics->setItem(i, 1, new QTableWidgetItem(QString::number(metrics[i].index)));
        sysMetrics->setItem(i, 1, new QTableWidgetItem(QString::number(val)));
        sysMetrics->setItem(i, 2, new QTableWidgetItem(SystemMetrics::metrics[i].what));
    }
}

QString SystemMetrics::getError(){
    DWORD res = GetLastError();
    return QString::number(res);
}
