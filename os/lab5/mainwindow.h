#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <reg.h>
#include <QTreeWidget>
#include <QMessageBox>
/*
Реализовать программу, считывающую из системного реестра данные о системных
службах Windows NT (ветка HKLM\SYSTEM\ \CurrentControlSet\Services). Обеспечить возможность
изменения описания службы и способа запуска. Информацию о службах выводить в файл.

•	настройки приложения должны храниться в реестре, в ветке HKCU\Software,
•	приложение должно определять свободное место на диске и проверять корректность всех файловых операций,

*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVector <QString> serviceNames;
    QVector <LONG> keys;
    HKEY hKey;
    Key k;
    QVector <Key> subkeys;
    int pos;
    int startValuesArray[5] = {0, 1, 2, 3, 4};
    QVector <QString> startDescriptions = {
        "0 - BOOT - драйвер загружается загрузчиком системы.",
        "1 - SYSTEM - драйвер загружается в процессе инициализации ядра.",
        "2 - AUTO - служба запускается автоматически при загрузке системы.",
        "3 - MANUAL - служба запускается вручную.",
        "4 - DISABLE - драйвер или сервис отключен.",
    };
    int errorControlValues[4] = {0, 1, 2, 3};
    QVector <QString> errorControlDescriptions = {
        "0 - игнорировать (Ignore)",
        "1 - нормальный (Normal)",
        "2 - особый (Severe)",
        "3 - критическая (Critical) ошибка."
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getServices();
    void loadSettings();
    void createKeys();
    void readKeySettings();
    void showKeyInfo(int);
private slots:
    void on_tree_itemClicked(QTreeWidgetItem *item, int column);
    void on_apply_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
