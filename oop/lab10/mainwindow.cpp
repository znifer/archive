#include "mainwindow.h"
#include "ui_mainwindow.h"

/*Создать приложение файловый менеджер, с возможностью копировать
файлы из 1 директории в другую. Выделять для копирования можно сразу
несколько файлов.*/

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    model = new QDirModel (this);
    model->setReadOnly (false);
    model->setSorting((QDir::DirsFirst | QDir::IgnoreCase | QDir::Name));
    ui->treeView->setModel(model);
    QModelIndex index = model->index("C://");
    ui->treeView->setCurrentIndex((index));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_createButton_clicked(){
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) return;
    QString name = QInputDialog::getText(this,"ща спою","Введите название папки");
    if (name.isEmpty()) name = "Новая папка";
    model->mkdir(index, name);
}

void MainWindow::on_copyButton_clicked(){
    QMessageBox msg;
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) return;
    for (unsigned i = 0; i < buffer.size(); i++){
        if (index == buffer[i]){
            msg.setWindowTitle("Ой-ой!");
            msg.setText("Данный файл уже находится в буффере!");
            msg.exec();
            qWarning("Item already exists");
            return;
        }
    }
    msg.setWindowTitle("Получилось!");
    msg.setText("Файл добавлен в буффер");
    msg.exec();
    buffer.push_back(index);
    model->refresh();
}

void MainWindow::on_insertButton_clicked(){
    QModelIndex index = ui->treeView->currentIndex();
    QString insertDirIndex = model->filePath(index);
    QDir insertDir = QDir(insertDirIndex);
    if (!index.isValid()) return;
    qWarning("copying started");
    if(buffer.size() == 0){
        QMessageBox msg;
        msg.setWindowTitle("Ой-ой!");
        msg.setText("Буффер пуст!");
        msg.exec();
        return;
    } else {
        for (unsigned i = 0; i < buffer.size(); i++){
            qWarning("nachinau checkat`");
            if (model->fileInfo(buffer[i]).isDir()){
                //если директория - получить лист с приколами в папке и скопировать
                qWarning("dir!");
                QFileInfoList list;
                QDir dir = QDir(model->filePath(buffer[i]));
                getContentList(dir, list);

                foreach(QFileInfo copyInfo, list){
                    if (copyInfo.isFile()){
                        QFileInfo info;
                        info.setFile(model->filePath(buffer[i]));
                        QFile file(model->filePath(buffer[i]));
                        if (!file.copy(insertDirIndex + QDir::separator() + info.fileName())){
                            qWarning("item already exists");
                        }
                    }
                    if (copyInfo.isDir()){
                        dir.mkdir(insertDirIndex);
                        //dir.mkdir();
                    }

                }
            } else {
                qWarning("file!");
                QFileInfo info;
                info.setFile(model->filePath(buffer[i]));
                QFile file(model->filePath(buffer[i]));
                if (!file.copy(insertDirIndex + QDir::separator() + info.fileName())){
                    qWarning("item already exists");
                }
            }
        }
        buffer.clear();
        model->refresh();
        qWarning("buffer is done");
    }
}


void MainWindow::getContentList(QDir &dir, QFileInfoList &list){
    foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::Name|QDir::DirsFirst)){
        list.append(info);
        if(info.isDir() && dir.cd(info.fileName())){
            getContentList(dir, list);
            dir.cdUp();
        }
    }
}

void MainWindow::on_deleteButton_clicked(){
    QModelIndex index = ui->treeView->currentIndex();
    //Если удаляемый элемент в буффере - вечная ему память, удаляем из буффера
    for (unsigned i = 0; i < buffer.size(); i++){
        if (index == buffer[i]){
            buffer.erase(buffer.begin() + i - 1);
        }
    }
    if (!index.isValid()) return;
    if (model->fileInfo(index).isDir()){
        model->rmdir(index);
    }else{
        model->remove(index);
    }
    model->refresh();
}
