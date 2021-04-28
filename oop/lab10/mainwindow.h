#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore>
#include <QDir>
#include <QDirModel>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QInputDialog>
#include <QtGlobal>
#include <algorithm>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getContentList(QDir &dir, QFileInfoList &list);
private slots:
    void on_createButton_clicked();
    void on_copyButton_clicked();
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
private:
    Ui::MainWindow *ui;
    QDirModel *model;
    std::vector<QModelIndex> buffer;
};
#endif // MAINWINDOW_H
