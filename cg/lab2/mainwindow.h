#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QWheelEvent>
#include <qlayout.h>
#include "chart.h"
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void wheelEvent(QWheelEvent* wheelEvent);
    Chart * chart;
    QSpinBox * b;
    QDoubleSpinBox * x1val;
    QDoubleSpinBox * x2val;
    QSpinBox * hval;
    QLabel * x1l, * x2l, * hl, bl;
    int h;
    double x1, x2;

public slots:
    void bValueChanged(int value);
    void x1Changed(double value);
    void x2Changed(double value);
    void hChanged(int value);


};
#endif // MAINWINDOW_H
