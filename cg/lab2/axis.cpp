#include "axis.h"
#include <QtDebug>
void Axis::step(double& k, double& h, int& m, int& n){
    double hm = h / k;
    qDebug() << hm;
    double n1 = log10(hm),
           n2 = log10(hm / 2),
           n5 = log10(hm / 5);
    QVector <int> pows(6);
    pows.push_front(floor(n1));
    pows.push_front(ceil(n1));
    pows.push_front(floor(n2));
    pows.push_front(ceil(n2));
    pows.push_front(floor(n5));
    pows.push_front(ceil(n5));
    QVector <double> diffs(6);
    for (int i = 0; i < 6; i++){
        if (i < 2) diffs[i] =       fabs(pow(10, pows[i]) - hm);
        else if (i > 3) diffs[i] =  fabs(5 * pow(10, pows[i]) - hm);
        else diffs[i] =             fabs(2 * pow(10, pows[i]) - hm);
    }
    int minPos = 0;
    double min = diffs[minPos];
    for (int i = 0; i < diffs.size(); i++){
        if (min > diffs[i]){
            min = diffs[i];
            minPos = i;
        }
    }
    n = pows[minPos];
    if (minPos < 2) m = 1;
    else if (minPos > 3) m = 5;
    else m = 2;
    double k1 = m * pow (10, n);
    h = k * k1;
    k = k1;
}

AbscissaAxis::AbscissaAxis(QPainter* painter, const QRect& scr, double firstCoord, double lastCoord)
    :Axis(painter, scr, firstCoord, lastCoord){}

void AbscissaAxis::draw(double h){
    QPen oldPen = painter->pen();       // Сохраняем текущее перо для восстановления.
    double k = (double)scr.width() / (lastCoord - firstCoord);
    int m = 0;
    int n = 0;
    Axis::step(k, h, m, n);
    qDebug() << h;
    double firstWrd = ceil(firstCoord / k) * k;
    double firstScr = (firstWrd - firstCoord) * h / k;
    double currentScr= firstScr + scr.bottomLeft().x();
    double currentWrd = firstWrd;
    painter->setPen(QPen(Qt::black));
    painter->drawLine(scr.bottomLeft(), scr.bottomRight());
    for (; currentScr < scr.bottomRight().x() - 10; currentScr += h, currentWrd += k)    {
        painter->setPen(QPen(Qt::black));
        QPointF p1(currentScr, scr.top());
        QPointF p2(currentScr, scr.bottom() + 5);
        painter->drawLine(p1, p2);
        painter->setPen(QPen(Qt::black));
        QString str;
        str.setNum(currentWrd, 'g', 4);
        painter->drawText(currentScr - h / 2 - 5, scr.bottom() + 10, h + 10, 20, Qt::AlignCenter, str);
    }
    QFont oldFont = painter->font();
    QFont newFont;
    newFont.setPixelSize(14);
    painter->setFont(newFont);
    painter->drawText(scr.right() - newFont.pixelSize() + 3, scr.bottom() + 2, newFont.pixelSize(), newFont.pixelSize(), Qt::AlignCenter, "X");
    painter->setFont(oldFont);
    painter->setPen(oldPen);
}

OrdinateAxis::OrdinateAxis(QPainter* painter, const QRect& scr, double firstCoord, double lastCoord)
    :Axis(painter, scr, firstCoord, lastCoord){}

void OrdinateAxis::draw(double h){

    QPen oldPen = painter->pen();
    double k = (double)scr.height() / (lastCoord - firstCoord);
    int m = 0;
    int n = 0;
    Axis::step(k, h, m, n);
    double firstWrd = ceil(firstCoord / k) * k;
    double firstScr = (firstWrd - firstCoord) * h / k;
    double currentScr = scr.bottomLeft().y() - firstScr;
    double currentWrd = firstWrd;
    painter->setPen(QPen(Qt::black));
    painter->drawLine(scr.topLeft(), scr.bottomLeft());
    for (; currentScr > scr.topLeft().y() + 20; currentScr -= h, currentWrd += k)    {
        painter->setPen(QPen(Qt::black));
        QPointF p1(scr.left() - 5, currentScr);
        QPointF p2(scr.right(), currentScr);
        painter->drawLine(p1, p2);
        QString str;
        str.setNum(currentWrd, 'g', 4);
        painter->drawText(scr.left() - 50, currentScr - h / 2, 40, h, Qt::AlignVCenter | Qt::AlignRight, str);
    }
    QFont oldFont = painter->font();
    QFont font;
    font.setPixelSize(14);
    painter->setFont(font);
    painter->drawText(scr.left() - font.pixelSize(), scr.top(), font.pixelSize(), font.pixelSize(), Qt::AlignCenter, "Y");
    painter->setFont(oldFont);
    painter->setPen(oldPen);
}
