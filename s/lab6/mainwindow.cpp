#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    text = "";
    viewIpInfo();
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

MainWindow::~MainWindow(){
    WSACleanup();
    delete ui;
}

void MainWindow::viewIpInfo(){
    PIP_ADAPTER_INFO AdapterInfo, Adapter;
    ULONG ValueAdapterInfo;
    int Error;
    ValueAdapterInfo = 0;
    Error = GetAdaptersInfo(NULL, &ValueAdapterInfo);
    if ((Error != 0) && (Error != ERROR_BUFFER_OVERFLOW)){
        return;
    }
    if ((AdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, ValueAdapterInfo)) == NULL){
        return;
    }
    if (GetAdaptersInfo(AdapterInfo, &ValueAdapterInfo) != 0){
        return;
    }
    Adapter = AdapterInfo;
    while (Adapter){
        text += "Адаптер: " + QString::fromStdString(Adapter->AdapterName) + "\n";
        text += "Индекс: " + QString::number(Adapter->Index) + "\n";
        if (Adapter->DhcpEnabled) text += "DHCP включен\n"; else text += "DHCP выключен\n";
        text += "DHCP адрес: " + QString::fromStdString(Adapter->DhcpServer.IpAddress.String) + "\n";
        PIP_ADDR_STRING Address = &(Adapter->IpAddressList);
        while (Address){
            text += "Контекст: " + QString::number(Address->Context) + "\n";
            text += "IP-адрес: " + QString::fromStdString(Address->IpAddress.String) + "\n";
            text += "Маска: " + QString::fromStdString(Address->IpMask.String) + "\n";
            Address = Address->Next;
        }
        Adapter = Adapter->Next;
    }
    ui->textEdit->setText(text);
}
void MainWindow::changeIp(int index, bool toRenew){
    DWORD InterfaceInfoSize = 0;
    PIP_INTERFACE_INFO InterfaceInfo;
    if (GetInterfaceInfo(NULL, &InterfaceInfoSize) != ERROR_INSUFFICIENT_BUFFER){
        return;
    }
    if ((InterfaceInfo = (PIP_INTERFACE_INFO)GlobalAlloc(GPTR, InterfaceInfoSize)) == NULL){
        return;
    }
    if (GetInterfaceInfo(InterfaceInfo, &InterfaceInfoSize) != 0){
        return;
    }
    for (int i = 0; i < InterfaceInfo->NumAdapters; ++i) {
        if (index == InterfaceInfo->Adapter[i].Index){
            if (toRenew) IpRenewAddress(&InterfaceInfo->Adapter[i]);
            else IpReleaseAddress(&InterfaceInfo->Adapter[i]);
        }
    }
}

QString MainWindow::getIp(QString name){
    QString res = "";
    getaddrinfo(name.toStdString().c_str(), 0, &hints, &result);
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            if (ptr->ai_family == AF_INET) {
                sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
                res += QString::fromStdString(inet_ntoa(sockaddr_ipv4->sin_addr)) + "; ";
            }
        }
    return res;
}

QString MainWindow::getName(QString ip){
    saGNI.sin_family = AF_INET;
    saGNI.sin_addr.s_addr = inet_addr(ip.toStdString().c_str());
    saGNI.sin_port = htons(27015);
    getnameinfo((struct sockaddr *) &saGNI, sizeof(struct sockaddr), hostname, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);
    return QString(hostname);
}

void MainWindow::on_dToIpGet_clicked(){
    ui->dToIpResult->setText(getIp(ui->dToIpEdit->text()));
}

void MainWindow::on_ipToDGet_clicked(){
    ui->ipToDResult->setText(getName(ui->ipToDEdit->text()));
}

void MainWindow::on_renewButton_clicked(){
    changeIp(ui->adapter->text().toInt(), true);
}

void MainWindow::on_releaseButton_clicked(){
    changeIp(ui->adapter->text().toInt(), false);
}
