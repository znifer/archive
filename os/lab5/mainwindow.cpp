#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->tree->clear();
    pos = 0;
    QString tmpstr = "SYSTEM\\CurrentControlSet\\Services";     tmpstr.append('\0');
    k = Key(tmpstr);
    k.setName("Services");

    getServices();
    loadSettings();
    //showKeyInfo(0);

}

MainWindow::~MainWindow(){
    RegCloseKey(hKey);
    delete ui;
}

void MainWindow::getServices(){
    QVector <QString> tmpSubkeys = k.getSubkeys();
    QString tmpstr = QString("SYSTEM\\CurrentControlSet\\Services") + QString("\\");
    for (int i = 0; i < tmpSubkeys.size(); i++){
        QString subPath = "SYSTEM\\CurrentControlSet\\Services\\" + tmpSubkeys[i];
        subPath.append('\0');
        Key subkey = Key(subPath);
        subkey.setName(tmpSubkeys[i]);
        //ВЫЛЕТ ЗДЕСЬ!
        subkeys.push_back(subkey);

        if (subkey.isLast()){
            QTreeWidgetItem * item = new QTreeWidgetItem(ui->tree);
            item->setText(0, subkey.getName());
        }
    }
}

void MainWindow::loadSettings(){
    DWORD dispos;
    LONG codeError = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\lab5", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dispos);
    if (codeError != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть или создать ключ реестра");
        exit(codeError);
    }
    DWORD width, height, top, left;
    if (dispos == REG_CREATED_NEW_KEY) {
        width = 500;
        height = 500;
        top = 500;
        left = 500;
        this->setGeometry(left, top, width, height);
        createKeys();
    }
    else if (dispos == REG_OPENED_EXISTING_KEY){
        readKeySettings();
    }
}

void MainWindow::createKeys(){
    LONG codeError;
    DWORD width, height, top, left;
    width = this->width();
    QRect geom = this->geometry();
    codeError = RegSetValueExA(hKey, "FormWidth", 0, REG_DWORD, (byte*)(&width), sizeof(width));
    if (codeError != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось установить значение FormWidth ключа реестра");
        RegCloseKey(hKey);
    }
    height = this->height();
    codeError = RegSetValueExA(hKey, "FormHeight", 0, REG_DWORD, (byte*)(&height), sizeof(height));
    if (codeError != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось установить значение FormHeight ключа реестра");
        RegCloseKey(hKey);
    }
    top = geom.top();
    codeError = RegSetValueExA(hKey, "FormTop", 0, REG_DWORD, (byte*)(&top), sizeof(top));
    if (codeError != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось установить значение FormTop ключа реестра");
        RegCloseKey(hKey);
    }
    left = geom.left();
    codeError = RegSetValueExA(hKey, "FormLeft", 0, REG_DWORD, (byte*)(&left), sizeof(left));
    if (codeError != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось установить значение FormLeft ключа реестра");
        RegCloseKey(hKey);
    }
}

void MainWindow::readKeySettings(){
    LONG codeError;
    DWORD width, height, top, left;
    DWORD dwtype = REG_DWORD, bufSize = sizeof(DWORD);
    if ((codeError = RegQueryValueExA(hKey, "FormWidth", 0, &dwtype, (byte*)(&width), &bufSize)) != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать значение FormWidth ключа реестра");
        RegCloseKey(hKey);
        exit(codeError);
    }
    if ((codeError = RegQueryValueExA(hKey, "FormHeight", 0, &dwtype, (byte*)(&height), &bufSize)) != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать значение FormHeight ключа реестра");
        RegCloseKey(hKey);
        exit(codeError);
    }
    if ((codeError = RegQueryValueExA(hKey, "FormTop", 0, &dwtype, (byte*)(&top), &bufSize)) != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать значение FormTop ключа реестра");
        RegCloseKey(hKey);
        exit(codeError);
    }
    if ((codeError = RegQueryValueExA(hKey, "FormLeft", 0, &dwtype, (byte*)(&left), &bufSize)) != ERROR_SUCCESS) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать значение FormLeft ключа реестра");
        RegCloseKey(hKey);
        exit(codeError);
    }
    this->setGeometry(left, top, width, height);
}

void MainWindow::on_tree_itemClicked(QTreeWidgetItem *item, int column){
    pos = 0;
    for (int i = 0; i < subkeys.size() && !pos; i++){
        if (subkeys[i].getName() == item->text(0))
            pos = i;
    }
    showKeyInfo(pos);

}

void MainWindow::showKeyInfo(int pos){
    ui->startCurrent->setText(startDescriptions[subkeys[pos].getStart()]);
    ui->displayNameCurrent->setText(QString::fromWCharArray(subkeys[pos].getDescription()));
    ui->errorControlCurrent->setText(errorControlDescriptions[subkeys[pos].getErrorControl()]);
    ui->startEdit->setValue(subkeys[pos].getStart());
    ui->errorControlEdit->setValue(subkeys[pos].getErrorControl());
    ui->displayNameEdit->setText(QString::fromWCharArray(subkeys[pos].getDescription()));
}

void MainWindow::on_apply_clicked(){
    DWORD newStart = ui->startEdit->text().toLong();
    if (newStart > 4 || newStart < 0){
        QMessageBox::warning(this, "Ошибка", "Введено неправильное значение start. Допустимые значения в диапазоне 0 - 4");
    } else {
        subkeys[pos].setStart(newStart);
    }
    DWORD newErrorControl = ui->errorControlEdit->text().toLong();
    if (newErrorControl > 3 || newErrorControl < 0){
        QMessageBox::warning(this, "Ошибка", "Введено неправильное значение errorControl. Допустимые значения в диапазоне 0 - 3");
    } else {
        subkeys[pos].setErrorControl(newErrorControl);
    }
    WCHAR newDisplayName[255];
    if (ui->displayNameEdit->text() != ""){
        ui->displayNameEdit->text().toWCharArray(newDisplayName);
        subkeys[pos].setDescription(newDisplayName);
    }
}

void MainWindow::on_pushButton_clicked(){
    subkeys[pos].saveParameters("E://info" + subkeys[pos].getName() + ".txt");
}
