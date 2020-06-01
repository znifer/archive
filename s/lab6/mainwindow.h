#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <ws2tcpip.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getIp(QString name);
    QString getName(QString ip);
    void viewIpInfo();
    void changeIp(int index, bool toRenew);
private slots:
    void on_dToIpGet_clicked();
    void on_ipToDGet_clicked();
    void on_renewButton_clicked();

    void on_releaseButton_clicked();

private:
    Ui::MainWindow *ui;
    QString text;
    WSADATA wsaData;
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    struct sockaddr_in  *sockaddr_ipv4;
    struct sockaddr_in saGNI;
    LPSOCKADDR sockaddr_ip;
    char hostname[NI_MAXHOST];
    char servInfo[NI_MAXSERV];
    char ip[NI_MAXHOST];
};
#endif // MAINWINDOW_H
