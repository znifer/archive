#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    isUserLogged = false;
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    isConnected = false;
    server = "127.0.0.1";
    currentMessage = 0;
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_loginButton_clicked(){
    QString request;
    QString response;
    password = ui->passwordEdit->text();
    login = ui->loginEdit->text();
    socket.connectToHost(server, 25);
    if(socket.waitForConnected(5000)){
        socket.waitForReadyRead();
        response = socket.readAll();
        request = "HELO " + server + "\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = "AUTH LOGIN\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = login.toUtf8().toBase64() + "\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = password.toUtf8().toBase64() + "\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        this->isConnected = true;

        pop3socket.connectToHost(server, 110);
            if(pop3socket.waitForConnected(5000)){
            pop3socket.waitForReadyRead();
            response = pop3socket.readAll();
            request = "USER " + this->ui->loginEdit->text() + "\r\n";
            pop3socket.write(request.toLocal8Bit());
            pop3socket.waitForBytesWritten();
            pop3socket.waitForReadyRead();
            response = pop3socket.readAll();
            request = "PASS " + password + "\r\n";
            pop3socket.write(request.toLocal8Bit());
            pop3socket.waitForBytesWritten();
            pop3socket.waitForReadyRead();
            response = pop3socket.readAll();
        }
    }
    if (isConnected){
            QMessageBox::warning(this, "Получилось!", "Произошло подключение");
    }

}

void MainWindow::on_sendButton_clicked(){
    QString request;
    QString response;
    if (this->isConnected){
        request = "MAIL FROM: <" + login + ">\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = "RCPT TO: <" + ui->receiverAdress->text() + ">\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = "DATA\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
        request = "";
        QTextStream messageStream(&request);
        messageStream << "From: " << login << "\r\n";
        messageStream << "Subject: " << ui->theme->text() << "\r\n";
        messageStream << "MIME-Version: 1.0\r\n";
        messageStream << "Content-Type: multipart/mixed; boundary=\"**********\"\r\n";
        messageStream << "--**********\r\n";
        messageStream << "Content-Type: text/html; charset=\"koi8-r\"\r\n";
        messageStream << "\r\n";
        messageStream << ui->message->toPlainText() << "\r\n";
        messageStream << "--**********\r\n";
        messageStream << "Content-Type: application/octet-stream; name=\"" << this->attachFile << "\"\r\n";
        messageStream << "Content-Transfer-Encoding: base64\r\n\r\n";
        messageStream << this->attachment.toBase64() << "\r\n";
        messageStream << "--**********\r\n";
        messageStream << ".\r\n";
        socket.write(request.toLocal8Bit());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        response = socket.readAll();
    }
}

void MainWindow::on_attachFileButton_clicked(){
    this->attachFile = QFileDialog::getOpenFileName(this, "Выбрать вложение", nullptr, "Изображения (*.png *.jpg *.bmp)");
    QFile file(this->attachFile);
    file.open(QIODevice::ReadOnly);
    this->attachment = file.readAll();
    file.close();
}

void MainWindow::on_mailList_itemClicked(QListWidgetItem *item){

}

void MainWindow::on_updateButton_clicked(){
    ui->mailList->clear();
    if (!isConnected){
        return;
    }
    QString request;
    QString response;
    request = "LIST\r\n";
    pop3socket.write(request.toLocal8Bit());
    pop3socket.waitForBytesWritten();
    pop3socket.waitForReadyRead();
    response = pop3socket.readAll();
    int messages = response.split(" ")[1].toInt();
    QStringList items;
    while (items.length() < messages){
        pop3socket.waitForReadyRead();
        response = pop3socket.readAll();
        items.append(response.split("\r\n"));
    }
    int pos = 0;
    for (auto item: items){
        pos++;
        if (item != "." && item != ""){
            QString tmp = getMessageInfo(pos);
            infos.append(tmp);
            QStringList lines = tmp.split("\n");
            QString info = "";
            for (int i = 0; i < lines.size(); i++){
                if (lines[i].contains("Subject") || lines[i].contains("From")){
                    info += lines[i] + " ";
                }
            }
            ui->mailList->addItem(info);
            infos.append(tmp);
        }
    }
    response = pop3socket.readAll();
}

QString MainWindow::getMessageInfo(int index){
    QString request;
    QString response;
    currentMessage = index;
    request = "RETR " + QString::number(index) + "\r\n";
    pop3socket.write(request.toLocal8Bit());
    pop3socket.waitForBytesWritten();
    pop3socket.waitForReadyRead();
    response = pop3socket.readAll();
    QString message;
    QTextStream message_stream(&message);
    int read = 0;
    int all = response.split(" ")[1].toInt();
    while (pop3socket.waitForReadyRead(1000)){
        read += pop3socket.bytesAvailable();
        response = pop3socket.readAll();
        message_stream << response;
    }
    return message;
}
