#include "mainwindow.h"

double f1(double x){
    return 2 * x + 1;
}

double f2(double x){
    return x * x;
}

double f3(double x){
    return 3 * x * -1;
}

MainWindow::MainWindow(QWidget *parent) :QWidget(parent){
    h = 70; x1 = -4.666; x2 = -4.3;
    //QFormLayout * l = new QFormLayout;
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox * b = new QSpinBox;
    QDoubleSpinBox * x1val = new QDoubleSpinBox;
    QDoubleSpinBox * x2val = new QDoubleSpinBox;
    QSpinBox * hval = new QSpinBox;
    hval->setRange(0, 500);
    hval->setValue(h);
    x1val->setRange(-1000, 1000);
    x2val->setRange(-1000, 1000);
    x1val->setValue(x1);
    x2val->setValue(x2);

    b->setRange(1, 3);

    chart = new Chart(f1, x1, x2, h);
    l->addWidget(chart);
    l->addWidget(b);
    //QLabel * bl = new QLabel;
    //bl->setText("Функция:");
    //l->addWidget(bl);
    l->addWidget(x1val);
    //QLabel * x1l = new QLabel;
    //x1l->setText("x1:");
    l->addWidget(x1l);

    l->addWidget(x2val);
    l->addWidget(hval);

    this->setLayout(l);
    this->resize(1200, 600);
    connect(b, SIGNAL(valueChanged(int)), this, SLOT(bValueChanged(int)));
    connect(hval, SIGNAL(valueChanged(int)), this, SLOT(hChanged(int)));
    connect(x1val, SIGNAL(valueChanged(double)), this, SLOT(x1Changed(double)));
    connect(x2val, SIGNAL(valueChanged(double)), this, SLOT(x2Changed(double)));
}

MainWindow::~MainWindow(){
    delete chart;
}

void MainWindow::wheelEvent(QWheelEvent *wheelEvent){
    if (wheelEvent->delta() > 0){
        x1 = x1 + 0.5;
        x2 = x2 - 0.5;
        chart->setX1(x1);
        chart->setX2(x2);
        //chart->setH(int(x1 - x2 / 10));
    } else {
        x1 = x1 - 0.5;
        x2 = x2 + 0.5;
        chart->setX1(x1);
        chart->setX2(x2);
        //chart->setH(int(x1 - x2 / 10));
    }
}

void MainWindow::bValueChanged(int value){
    switch (value) {
    case 1:
        chart->setFunc(f1);
        chart->update();
        break;
    case 2:
        chart->setFunc(f2);
        chart->update();
        break;
    case 3:
        chart->setFunc(f3);
        chart->update();
        break;
    }
}

void MainWindow::x1Changed(double value){
    chart->setX1(value);
}
void MainWindow::x2Changed(double value){
    chart->setX2(value);
}
void MainWindow::hChanged(int value){
    chart->setH(value);
}
