#include "reg.h"

#include <QDebug>

Key::Key(QString qpath){
    WCHAR path[255];
    regPath = qpath;
    valuesCount = 0;
    subkeysCount = 0;
    qpath.toWCharArray(path);
    long result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_READ| KEY_WOW64_32KEY, &k);
    if (result == ERROR_SUCCESS){
        load();
    }
}

Key::~Key(){
    RegCloseKey(k);
}
void Key::load(){
    WCHAR    achKey[255];                   // buffer for subkey name
    DWORD    cbName;                        // size of name string
    WCHAR    achClass[MAX_PATH] = TEXT(""); // buffer for class name
    DWORD    cchClassName = MAX_PATH;       // size of class string
    DWORD    cSubKeys = 0;                  // number of subkeys
    DWORD    cbMaxSubKey;                   // longest subkey size
    DWORD    cchMaxClass;                   // longest class string
    DWORD    cValues;                       // number of values for key
    DWORD    cchMaxValue;                   // longest value name
    DWORD    cbMaxValueData;                // longest value data
    DWORD    cbSecurityDescriptor;          // size of security descriptor
    FILETIME ftLastWriteTime;               // last write time
    DWORD i, retCode;
    WCHAR achValue[16383];
    DWORD cchValue = 16383;

    retCode = RegQueryInfoKeyW(k, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass,
                               &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
    if (cSubKeys){
        subkeysCount = cSubKeys;
        for (i=0; i < cSubKeys; i++){
            cbName = 255;
            RegEnumKeyExW(k, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);

            QString tmp = QString::fromWCharArray(achKey);
            subkeys.push_back(tmp);
        }
    }
    // Enumerate the key values.
    BYTE* buffer = new BYTE[cbMaxValueData];
    ZeroMemory(buffer, cbMaxValueData);
    if (cValues){
        valuesCount = cValues;
        for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++){
            cchValue = 16383;
            achValue[0] = '\0';
            retCode = RegEnumValueW(k, i, achValue, &cchValue, NULL, NULL, NULL, NULL);
            if (retCode == ERROR_SUCCESS){
                DWORD lpData = cbMaxValueData;
                //buffer[0] = '\0'; // Не нужно, неизвестно, зачем появилось
                LONG dwRes = RegQueryValueExW(k, achValue, 0, NULL, buffer, &lpData);
                //buffer[lpData + 1] = '\0';
                QString tmpstr = QString::fromWCharArray(achValue);

                DWORD value = 0;
                //Заносим только нужные значения
                if (tmpstr == "Start\0"){
                    memcpy(&value, buffer, sizeof(value));
                    start = value;
                }
                if (tmpstr == "Description\0"){
                    memcpy(&description, buffer, sizeof(description));
                    //qDebug() << QString::fromWCharArray(displayName);
                }
                if (tmpstr == "ErrorControl\0"){
                    memcpy(&value, buffer, sizeof(value));
                    errorControl = value;
                }
                if (tmpstr == "Type\0"){
                    memcpy(&value, buffer, sizeof(value));
                    type = value;
                }
            }
        }
    }
    delete [] buffer;
}

bool Key::isLast(){
    if (valuesCount != 0 && subkeysCount == 0) return true; else return  false;
}

QVector <QString> Key::getSubkeys(){
    return subkeys;
}

void Key::setName(QString newName){
    name = newName;
}

QString Key::getName(){
    return name;
}

DWORD Key::getStart(){
    return start;
}
WCHAR * Key::getDescription(){
    return description;
}
DWORD Key::getErrorControl(){
    return errorControl;
}

void Key::setStart(DWORD newValue){
    WCHAR path[255];
    regPath.toWCharArray(path);
    DWORD result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_READ| KEY_WOW64_32KEY, &k);
    result = RegSetValueExA(k, "Start", 0, REG_DWORD, (byte*)(&newValue), sizeof(newValue));
    if (result != ERROR_SUCCESS){
       qDebug() << "Start error, value: " << result;
    }
    RegCloseKey(k);
}

void Key::setDescription(WCHAR * newValue){
    WCHAR path[255];
    regPath.toWCharArray(path);
    DWORD result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_READ| KEY_WOW64_32KEY, &k);
    result = RegSetValueExA(k, "Description", 0, REG_SZ, (byte*)(&newValue), sizeof(newValue));
    if (result != ERROR_SUCCESS){
       qDebug() << "Description error, value: " << result;
    }
    RegCloseKey(k);
}

void Key::setErrorControl(DWORD newValue){
    WCHAR path[255];
    regPath.toWCharArray(path);
    DWORD result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_READ| KEY_WOW64_32KEY, &k);
    result = RegSetValueExA(k, "ErrorControl", 0, REG_DWORD, (byte*)(&newValue), sizeof(newValue));
    if (result != ERROR_SUCCESS){
       qDebug() << "ErrorControl error, value: " << result;
    }
    RegCloseKey(k);
}

ULONGLONG getFreeSpace(QString path){
    QString winPath = QDir::toNativeSeparators(path);
    int first= winPath.indexOf(QDir::separator());
    int last= winPath.lastIndexOf(QDir::separator());
    // Удалить букву диска
    winPath.remove(0, first);
    // Удалить название файла
    winPath.chop(winPath.length() - last + 2);
    TCHAR *buffer = new TCHAR[MAX_PATH];
    FillMemory(buffer, MAX_PATH, 0);
    winPath.toWCharArray(buffer);
    ULARGE_INTEGER freeSize;

    bool result = GetDiskFreeSpaceEx(
                buffer,         // Путь
                &freeSize,     // Кол-во байт доступных пользователю
                NULL,
                NULL
                );
    if (!result){
        throw std::runtime_error("Не удалось получить свободное место");
    }
    ULONGLONG byte_size = freeSize.QuadPart;
    delete[] buffer;
    return byte_size;
}

DWORD aligned(DWORD size){
    DWORD bytes_per_sector;
    GetDiskFreeSpace(NULL, NULL, &bytes_per_sector, NULL, NULL);
    // Получает ближайшее большее или равное, кратное размеру сектора
    return ((bytes_per_sector + ((size + bytes_per_sector)-1)) & ~(bytes_per_sector -1));
}

void Key::saveParameters(QString path){
    QString text;
    text = "Start: " + QString::number(start) + "; ErrorControl: " + QString::number(errorControl) + "; Type: " + QString::number(type) + ";";
    QByteArray utf8_buffer = text.toUtf8();
    BYTE *big_buffer = (BYTE *) utf8_buffer.data();

    ULONGLONG buffer_size = utf8_buffer.size();

    ULONGLONG free_space = getFreeSpace(path);
    if (free_space < buffer_size){
        throw std::runtime_error("Недостаточно места на диске");
    }
    TCHAR *buffer = new TCHAR[MAX_PATH];
    FillMemory(buffer, MAX_PATH, 0);
    // Преобразовали путь к WCHAR
    int len = path.toWCharArray(buffer);
    buffer[len] = '\0';

    HANDLE file_h;
    ULONGLONG current_size = 0;

    // Открытие файла
    file_h = CreateFileW(
                    buffer,             // Имя
                    GENERIC_WRITE,       // На запись
                    0,                  // не разделять
                    NULL,               // Флаги безопасности не установлены, наследование не нужно
                    CREATE_ALWAYS,      // Только создавать новый
                    FILE_FLAG_OVERLAPPED,  // Асинхронные операции
                    NULL                    // Шаблона нет
                    );
    DWORD size_in_bytes = aligned(buffer_size);

    // Создание события для асинхронных операций
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, NULL);
    // Структура OVERLAPPED для асинхронных операций
    OVERLAPPED ovl;
    ovl.hEvent = event;
    ovl.Offset = 0;
    ovl.OffsetHigh = 0;

    // Запись файла
    WriteFile(file_h, big_buffer, size_in_bytes, NULL, &ovl);
    // Ожидаем завершения операции записи
    WaitForSingleObject(event, INFINITE);
    // Урезаем файл по реально хранимым данным
    LONG bytes_to_cut = buffer_size + current_size;
    SetFilePointer(file_h, bytes_to_cut, 0, FILE_BEGIN);
    SetEndOfFile(file_h);
    // Закрытие и очистка
    CloseHandle(file_h);
    CloseHandle(event);
    //delete[] big_buffer; // Вылетает из за удаления буффера. Почему - неизвестно
}

