#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>
#include <QtMath>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow* ui;
    float angle;
    int n;
    float alpha;
    QColor green, blue;
    QColor color;
    bool flag;
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* wheelEvent);
    void mousePressEvent(QMouseEvent* mouseEvent);
    QColor getRandomColor();
    void changeColor();
private slots:
    void animate();
};

#endif // MAINWINDOW_H
