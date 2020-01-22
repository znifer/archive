#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QtMath>
#include <QPainter>
#include <QMatrix4x4>
#include <QLine>
#include <QPoint>
#include <QMouseEvent>
#include <float.h>

#include "object.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

private:
    Cubes f;
    float globalScale, ctrlMouseWheelCount, altMouseWheel;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* e);
    void drawLines(QPainter & painter);
    void drawProjections(QPainter & painter, Object & obj);
    void draw3D(QPainter & painter, Object & obj, int view);

private slots:
    void on_zoomInc_clicked();
    void on_zoomDec_clicked();
    void on_central_clicked();
    void on_cabinet_clicked();
    void on_free_clicked();
    void on_ortogonal_clicked();
private:
    Ui::MainWindow *ui;
    QMatrix4x4 rotationMatrix;
    int view, range;
    QPointF pos;
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void mousePressEvent(QMouseEvent * event);
};
#endif // MAINWINDOW_H
