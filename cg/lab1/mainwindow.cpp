#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QLineF>
#include <QPolygonF>
#include <QTimer>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::animate);
    timer->start(15);
    n = 1;
    alpha = 100;
    angle = 0;
    green.setHsv(120, 255, 255);
    blue.setHsv(240, 255, 255);
    flag = true;
}

MainWindow::~MainWindow() {
    delete ui;
}

QColor MainWindow::getRandomColor() {
    QColor color(rand() % 255, rand() % 255, rand() % 255);
    return color;
}

void MainWindow::changeColor() {
    if (blue.hsvHue() == 120 || blue.hsvHue() == 240) {
        flag = !flag;
    }
    if (!flag) {
        blue.setHsv(blue.hsvHue() - 1, 255, 255);
        green.setHsv(green.hsvHue() + 1, 255, 255);
    } else {
        blue.setHsv(blue.hsvHue() + 1, 255, 255);
        green.setHsv(green.hsvHue() - 1, 255, 255);
    }

}




void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    float radius;
    if (width() > height())
        radius = (height() - 20) / 2;
    else radius = (width() - 20) / 2;
    if (width() < 30 || height() < 30)	return;

    QPointF center = QPointF(width() / 2, height() / 2);
    QPolygonF pol;
    alpha = 0.45 * radius;

    //рисуем основание мельницы
    QLineF line1, line2, line3;
    line1.setP1(center); line1.setAngle(260); line1.setLength(alpha * 2.3);
    pol.push_back(line1.p1());
    pol.push_back(line1.p2());
    line1.setAngle(280);
    pol.push_back(line1.p2());
    ///
    painter.setBrush(green);
    painter.drawPolygon(pol);
    pol.clear();

    float innerRadius = alpha / 2; //Вычисляем радиус внутренней окружности
    QRectF rect = QRectF(center.x() - innerRadius, center.y() - innerRadius, innerRadius * 2, innerRadius * 2); //Задаем область отрисовки внутренней окружности
    ///painter.setBrush(getRandomColor());
    ///painter.setPen(getRandomColor());
    painter.setBrush(blue);
    painter.drawEllipse(rect);

    //Рисуем шестиугольник
    QLineF line; //Линия, с помощью которой будем вычислять координаты углов шестиугольника
    line.setP1(center);
    line.setAngle(-angle);
    line.setLength(innerRadius);
    float tmpAngle = 0;
    pol.push_back(line.p2());

    for (int i = 0; i < 6; i++) {
        line.setAngle(line.angle() + 60);
        pol.push_back(line.p2());
    }
    ///painter.setBrush(getRandomColor());
    painter.setBrush(green);
    painter.drawPolygon(pol); pol.clear();

    tmpAngle = 360;
    float step = 360 / n; //шаг в градусах,
    //рисуем n лопастей
    for (int i = 0; i < n; i++) {
        QLineF mainLine; //главная линия лопасти
        mainLine.setP1(center);
        mainLine.setAngle(tmpAngle - step - angle); //вычисляем угол наклона главной лопасти
        mainLine.setLength(alpha * 2);
        ///painter.setPen(getRandomColor());
        painter.drawLine(mainLine);

        //Вычисляем кусок лопасти
        QLineF line1, line2;
        line1.setP1(mainLine.p2());
        line1.setAngle(mainLine.angle() - 90);
        line1.setLength(alpha / 2);

        //Вычисляем второй кусок лопасти
        line2.setP1(line1.p2());
        line2.setAngle(line1.angle() - 135);
        line2.setLength(sqrt(pow(alpha / 2, 2) + pow(alpha / 2, 2)));

        //Создаем полигон с координатами лопастей
        pol.push_back(line1.p1());
        pol.push_back(line1.p2());
        pol.push_back(line2.p2());

        //Рисуем полигон
        ///painter.setBrush(getRandomColor());
        painter.setBrush(blue);
        painter.drawPolygon(pol);

        tmpAngle -= step;
        pol.clear();
    }
}


// Обработчик события прокрутки колеса мыши
void MainWindow::wheelEvent(QWheelEvent* wheelEvent) {
    if (wheelEvent->delta() > 0) {
        alpha++;
    }
    else {
        if (alpha < 1) return;
        else alpha--;
    }
}

void MainWindow::mousePressEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::RightButton) n++;
    if (mouseEvent->button() == Qt::LeftButton && n > 1) n--;
}

void MainWindow::animate() {
    angle += 0.5;
    changeColor();
    repaint();
}
