#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <fstream>
#include <string>
#include <QDebug>
#include <QString>
#include <QBitArray>
#include <Windows.h>
#include <VersionHelpers.h>

class SystemInfo{
public:
    SystemInfo();
    static const QString getUserName();
    static const QString getPcName();
    static const QString getWinDir();
    static const QString getTempDir();
    static const QString getSysDir();
    static const QString getWinVersion();
    static const QString getMouseParams();
    static const QString getFastSwitch();
    static const QString getSoundSentry();
    static const LOGFONT getCurrentLogFont();
    static const MOUSEKEYS getMouseKeys();
    static bool isMouseKeyFlagOn(DWORD f, MOUSEKEYS k);
    static void setLogFont(LOGFONT l);
    static void setMouseKeys(MOUSEKEYS k);
    static void addMouseKeysFlag(DWORD f, MOUSEKEYS &k);
    static void removeMouseKeysFlag(DWORD f, MOUSEKEYS &k);

};

#endif // SYSTEMINFO_H
