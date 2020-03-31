#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class CustomChart : public QChart{
    Q_OBJECT
public:
    CustomChart(qreal maxY, qreal mult, QColor color, QString title, QString xTitle, QString yTitle,
                QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    void update(qreal x, qreal y);
private:
    QAreaSeries *series;
    QSplineSeries *seriesTop, *seriesBottom;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    qreal _x, xMax, _y, yMax;
    QColor color;
    QString title, xTitle, yTitle;
    qreal  mult;

};

#endif // CUSTOMCHART_H
