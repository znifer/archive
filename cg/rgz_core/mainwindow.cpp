#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFileAction = new QAction("Открыть", this);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    ui->menu->addAction(openFileAction);
    //ui->view->loadObject("z.obj");
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::openFile(){
    filename = QFileDialog::getOpenFileName(this, "", "*.obj");
    qDebug() << filename;
    //ui->view->loadObject(filename);
}


