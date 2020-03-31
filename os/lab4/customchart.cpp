#include "customchart.h"

CustomChart::CustomChart(qreal maxY, qreal mult, QColor color, QString title, QString xTitle, QString yTitle,
                         QGraphicsItem *parent, Qt::WindowFlags wFlags):
        QChart(QChart::ChartTypeCartesian, parent, wFlags),
        xAxis(new QValueAxis()),
        yAxis(new QValueAxis()),
        color(color),
        title(title),
        xTitle(xTitle),
        yTitle(yTitle),
        mult(mult)
    {
        seriesTop = new QSplineSeries(this);
        seriesBottom = new QSplineSeries(this);
        series =  new QAreaSeries(seriesTop, seriesBottom);
        QPen pen(color);
        series->setPen(pen);
        series->setBrush(QBrush(pen.color().lighter()));
        legend()->setVisible(false);
        addSeries(series);

        addAxis(xAxis,Qt::AlignBottom);
        addAxis(yAxis,Qt::AlignLeft);
        series->attachAxis(xAxis);
        series->attachAxis(yAxis);
        xAxis->setTickCount(10);
        xAxis->setRange(0, 10);
        xMax = 10;
        yMax = maxY/mult;
        xAxis->setTickCount(10);
        yAxis->setRange(0, yMax);
        setTitle(title);
        xAxis->setTitleText(xTitle);
        yAxis->setTitleText(yTitle);
}

void CustomChart::update(qreal x, qreal y){
    y = y / mult;
    seriesTop->append(x, y);
    seriesBottom->append(x, 0);
    if (x > xMax){
        qreal step = plotArea().width() / xAxis->tickCount() * (x - _x);
        xMax += x - _x;
        scroll(step, 0);
    }
    _x = x;
    _y = y;
}

