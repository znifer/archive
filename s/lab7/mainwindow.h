#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTcpSocket>
#include <QListWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getMessageInfo(int index);
private slots:
    void on_loginButton_clicked();
    void on_sendButton_clicked();
    void on_attachFileButton_clicked();
    void on_mailList_itemClicked(QListWidgetItem *item);
    void on_updateButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isUserLogged;
    int port;
    QString login, password, attachFile, server;
    QByteArray attachment;
    QTcpSocket socket, pop3socket;
    bool isConnected;
    int currentMessage;
    QStringList infos;
};
#endif // MAINWINDOW_H
