#ifndef AXIS_H
#define AXIS_H

#include <QtMath>
#include <QVector>
#include <QPainter>

class Axis{
protected:
    QPainter * painter;
    QRect scr;
    double firstCoord, lastCoord;
    int h, width;
public:
    Axis(QPainter * painter, const QRect& scr, double firstCoord, double lastCoord):
        painter(painter), scr(scr), firstCoord(firstCoord), lastCoord(lastCoord){};
    static void step(double& k, double& h, int& m, int& n);
    void draw(double h) {};
};

class AbscissaAxis : public Axis{
public:
    AbscissaAxis(QPainter * painter, const QRect& scr, double firstPoint, double lastPoint);
    void draw(double h);
};

class OrdinateAxis : public Axis{
public:
    OrdinateAxis(QPainter * painter, const QRect& scr, double firstPoint, double lastPoint);
    void draw(double h);
};

#endif // AXIS_H
