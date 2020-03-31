#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include <QPalette>
#include <QColorDialog>
#include <Windows.h>
#include <VersionHelpers.h>
#include <tchar.h>
#include <wchar.h>

#include "systeminfo.h"
#include "systemmetrics.h"
#include "systemcolors.h"
#include "systemtime.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getMetrics(QTableWidget *sysMetrics);
    void readMetrics();
private slots:
    void on_strikeOut_stateChanged(int arg1);
    void on_underLine_stateChanged(int arg1);
    void on_italic_stateChanged(int arg1);
    void on_confirmation_clicked();
    void on_setDefault_clicked();
    void on_mouseSetDefault_clicked();
    void on_mouseConfirmation_clicked();
    void on_confirmBrighlight_clicked();
    void on_setDefaultColors_clicked();
    void on_confirmInactivecaptions_clicked();
    void on_confirmScrollbar_clicked();
    void on_mouseKeysOn_stateChanged(int arg1);
    void on_mouseAvailable_stateChanged(int arg1);
    void on_mouseConfirmHotkey_stateChanged(int arg1);
    void on_mouseHotkeyActive_stateChanged(int arg1);
    void on_mouseHotkeySound_stateChanged(int arg1);
    void on_maxSpeed_valueChanged(int arg1);
    void on_mouseCtrlSpeed_valueChanged(int arg1);
    void on_mouseModifiers_stateChanged(int arg1);
    void on_localTime_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::MainWindow *ui;
    LOGFONT defaultLogFont;
    LOGFONT newLogFont;
    MOUSEKEYS defaultMouseKeys;
    MOUSEKEYS newMouseKeys;
    QColor defaultBrl;
    QColor defaultIAC;
    QColor defaultSCR;
};

#endif // MAINWINDOW_H
