#include "systemtime.h"

SystemTime::SystemTime(){
    GetSystemTime(&sysTime);
    GetLocalTime(&localTime);

}

QDateTime SystemTime::getLocalTime(){
    QDateTime t;
    QDate d; QTime time;
    d.setDate(localTime.wYear, localTime.wMonth, localTime.wDay);
    time.setHMS(localTime.wHour, localTime.wMinute, localTime.wSecond);
    t.setDate(d);
    t.setTime(time);
    return t;
}

QDateTime SystemTime::getSystemTime(){
    QDateTime t;
    QDate d; QTime time;
    d.setDate(sysTime.wYear, sysTime.wMonth, sysTime.wDay);
    time.setHMS(sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    t.setDate(d);
    t.setTime(time);
    return t;
}

void SystemTime::setLocalTime(QDateTime t){
    QDate d = t.date();
    QTime time = t.time();
    SYSTEMTIME newLocalTime;
    newLocalTime.wYear = d.year();
    newLocalTime.wMonth = d.month();
    newLocalTime.wDay = d.day();
    newLocalTime.wHour = time.hour();
    newLocalTime.wMinute = time.minute();
    newLocalTime.wSecond = time.second();
    SetLocalTime(&newLocalTime);
}

QString SystemTime::getCurrentBias(){
    TIME_ZONE_INFORMATION timeZoneInfo;
    DWORD currentBias = GetTimeZoneInformation(&timeZoneInfo);
    switch(currentBias){
            case TIME_ZONE_ID_UNKNOWN:
                return "Перевод времени не используется";
            case TIME_ZONE_ID_STANDARD:
                return "Часы без перевода";
            case TIME_ZONE_ID_DAYLIGHT:
                return "Часы с переводом";
    }
    return "Ошибка";
}

QString SystemTime::getStandartBias(){
    TIME_ZONE_INFORMATION timeZoneInfo;
    GetTimeZoneInformation(&timeZoneInfo);
    return QString::number(timeZoneInfo.StandardBias) + " мин.";
}

QString SystemTime::getDaylightBias(){
    TIME_ZONE_INFORMATION timeZoneInfo;
    GetTimeZoneInformation(&timeZoneInfo);
    return QString::number(timeZoneInfo.DaylightBias) + " мин.";
}
