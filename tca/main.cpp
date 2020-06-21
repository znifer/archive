#include <QTextStream>
#include <QVector>
#include <QString>
#include "vectors.h"
#include "functions.h"

int test1(QBitArray x){
    return !x[0] & x[1] & !x[2];
}

int test2(QBitArray x){
    return !x[0] & x[1] & !x[2] & !x[3] | !x[0] & x[1] & !x[2] & x[3];
}

int test3(QBitArray x){
    return !x[0] & x[1] & !x[2] & x[3] |
           !x[0] & !x[1] & x[2] & !x[3] |
           x[0] & !x[1] & !x[2] & !x[3];
}
int test4(QBitArray x){
    return !x[0] & x[1] & !x[2]  |
           !x[0] & !x[1] & x[2] & !x[3] |
           x[0] & !x[1] & !x[2] & !x[3];
}

int main(){
    QTextStream out(stdout);
    Table t1(5), t2(5);
    t1.getTable(test3);
    t2.getTable(test4);

    if (t1 == t2) qDebug() << "+++";
    //t1.print();
    //t2.print();
}

