#include "systeminfo.h"

SystemInfo::SystemInfo(){}

const QString SystemInfo::getUserName(){
    char str[4096];
    DWORD size = 4096;
    QString res;
    if(GetUserNameA(str, &size)) res = str; else res = "Ошибка!";
    return res;

}

const QString SystemInfo::getPcName(){
    char str[4096];
    DWORD size = 4096;
    QString res;
    if(GetComputerNameA(str, &size)) res = str; else res = "Ошибка!";
    return res;
}

const QString SystemInfo::getWinDir(){
    char str[4096];
    UINT size = 4096;
    QString res;
    if (GetSystemWindowsDirectoryA(str, size)) res = str; else res = "Ошибка!";
    return res;
}

const QString SystemInfo::getTempDir(){
    char str[4096];
    UINT size = 4096;
    QString res;
    if (GetTempPathA(size, str)) res = str; else res = "Ошибка!";
    return res;
}

const QString SystemInfo::getSysDir(){
    char str[4096];
    UINT size = 4096;
    QString res;
    if (GetSystemDirectoryA(str, size)) res = str; else res = "Ошибка!";
    return res;
}

const QString SystemInfo::getWinVersion(){
    QString res;
    if (IsWindows8Point1OrGreater()) res = "v 10.0"; else {
        OSVERSIONINFOA osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
        GetVersionExA(&osvi);
        res ="v " + QString::number(osvi.dwMajorVersion) +"." +
            QString::number(osvi.dwMinorVersion) + " build " +
            QString::number(osvi.dwBuildNumber);
    }
    return res;
}

const QString SystemInfo::getMouseParams(){
    int mouseParams[3];
    if (!SystemParametersInfoA(SPI_GETMOUSE, 0, &mouseParams, 0)) return "Ошибка!";
    return ("Чувствительность по оси х: " + QString::number(mouseParams[0]) +
            ", по оси у: " + QString::number(mouseParams[1]) +
            ", скорость мыши: " + QString::number(mouseParams[2]));
}

const QString SystemInfo::getFastSwitch(){
    long switchAvaliable;
    if (!SystemParametersInfoA(SPI_GETFASTTASKSWITCH, 0, &switchAvaliable ,0)) return "Ошибка!";
    if (switchAvaliable) return "Доступно"; else return "Не доступно";
}

const QString SystemInfo::getSoundSentry(){
    BOOL f;
    //if (!SystemParametersInfo(SPI_GETSOUNDSENTRY, 0, &f, 0)) return "Ошибка!";
    SystemParametersInfo(SPI_GETSOUNDSENTRY, 0, &f, 0);
    if (f) return "Предупреждающий сигнал проигрывается";
        else return "Предупреждающий сигнал не проигрывается";
}

/* SPI_SETICONTITLELOGFONT
 * Sets the font that is used for icon titles. The uiParam parameter specifies
 * the size of a LOGFONT structure, and the pvParam parameter must point to a
 * LOGFONT structure.*/

const LOGFONT SystemInfo::getCurrentLogFont(){
    LOGFONT l;
    SystemParametersInfoA(SPI_GETICONTITLELOGFONT, sizeof(l), &l, 0);
    return l;
}

void SystemInfo::setLogFont(LOGFONT l){
    SystemParametersInfoA(SPI_SETICONTITLELOGFONT, sizeof(l), &l, SPIF_UPDATEINIFILE);
}

/* 34 SPI_SETMOUSEKEYS 55
 * Sets the parameters of the MouseKeys accessibility feature.
 * The pvParam parameter must point to a MOUSEKEYS structure that contains the new parameters.
 * Set the cbSize member of this structure and the uiParam parameter to sizeof(MOUSEKEYS).*/

const MOUSEKEYS SystemInfo::getMouseKeys(){
    MOUSEKEYS k;
    k.cbSize = sizeof(MOUSEKEYS);
    SystemParametersInfoA(SPI_GETMOUSEKEYS, sizeof(MOUSEKEYS), &k, 0);
    //qDebug() << k.dwFlags;
    return k;
}

void SystemInfo::setMouseKeys(MOUSEKEYS k){
    k.cbSize = sizeof(MOUSEKEYS);
    SystemParametersInfoA(SPI_SETMOUSEKEYS, sizeof(MOUSEKEYS), &k, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

void SystemInfo::addMouseKeysFlag(DWORD f, MOUSEKEYS &k){
    //if ((k.dwFlags | f) != k.dwFlags) k.dwFlags += f;
    qDebug() << k.dwFlags; qDebug() << " - before";
    k.dwFlags = k.dwFlags + f;
    qDebug() << k.dwFlags; qDebug() << " - after";
}

void SystemInfo::removeMouseKeysFlag(DWORD f, MOUSEKEYS &k){
    //if ((k.dwFlags | f) == k.dwFlags) k.dwFlags -= f;
    qDebug() << k.dwFlags; qDebug() << " - before";
    k.dwFlags = k.dwFlags -  f;
    qDebug() << k.dwFlags; qDebug() << " - after";
}

bool SystemInfo::isMouseKeyFlagOn(DWORD f, MOUSEKEYS k){
    if ((k.dwFlags | f) == k.dwFlags) return true; else return false;
}
