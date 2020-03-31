#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H
#include "windows.h"
#include <QDateTime>
//GetSystemTime, GetTimeZonelnformation, GetTimeFormat
class SystemTime{
    SYSTEMTIME sysTime, localTime;
public:
    SystemTime();
    QDateTime getSystemTime();
    QDateTime getLocalTime();
    static void setLocalTime(QDateTime t);
    static QString getCurrentBias();
    static QString getStandartBias();
    static QString getDaylightBias();
};

#endif // SYSTEMTIME_H
