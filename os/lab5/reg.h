#ifndef REG_H
#define REG_H
#include <windows.h>
#include <winreg.h>
#include <QVector>
#include <QMap>
#include <QMessageBox>
#include <QDir>
class Key{
    HKEY k;
    QString regPath;
    QString name;
    QVector <QString> subkeys;
    DWORD start, errorControl, type;
    WCHAR description[255];
    int subkeysCount;
    int valuesCount;
public:
    Key(){};
    Key(QString);
    Key(HKEY);
    ~Key();
    void load();
    void setName(QString);
    bool isLast();
    QString path() {return regPath;}
    QString getName();
    QVector <QString> getSubkeys();
    DWORD getStart();
    WCHAR * getDescription();
    DWORD getErrorControl();

   void setStart(DWORD);
   void setErrorControl(DWORD);
   void setDescription(WCHAR *);
   void saveParameters(QString path);
};
#endif // REG_H
