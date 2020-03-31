#ifndef SYSTEMMETRICS_H
#define SYSTEMMETRICS_H

#include <QTableWidget>
#include <fstream>
#include <vector>
#include <QDebug>
#include <QString>
#include "windows.h"

class SystemMetrics{
    struct metric{
        int index;
        int value;
        QString name;
        QString what;
    };
    std::vector <metric> metrics;
    int mcount;
public:
    SystemMetrics();
    void getMetrics(QTableWidget *sysMetrics);
    void readMetrics();
    QString getError();
};

#endif // SYSTEMMETRICS_H
