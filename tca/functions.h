#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QBitArray>
#include <QDebug>

class Functions{
public:
    Functions();
    static int nor(int, int);
    static int nand(int, int);
    static int l1f(QBitArray);
    static int l1f1(QBitArray);
    static int l1f2(QBitArray);
    static int l2f1(QBitArray);
    static int l2f2(QBitArray);
    static int l2f3(QBitArray);
    static int l2f4(QBitArray);
    static int l3c(QBitArray);
    static int l3f(QBitArray);
    static int l3f1(QBitArray);
    static int l3f2(QBitArray);
    static int l4p(QBitArray);
    static int l4test1(QBitArray);
    static int l5f1(QBitArray);
    static int l5f2(QBitArray);
    static int l5f3(QBitArray);
    static int l5f11(QBitArray);
    static int l5f12(QBitArray);
    static int mf1(QBitArray);
    static int mf2(QBitArray);
    static int l6c(QBitArray);
    static int l6f1(QBitArray);
    static int l6f2(QBitArray);
    static int test1(QBitArray);
    static int test2(QBitArray);
    static int l7f1(QBitArray);
    static int l7f2(QBitArray);
    static int l7f3(QBitArray);
    static int l7c(QBitArray);
    static int test3(QBitArray);
    static int test4(QBitArray);
    static void l7t();
};

#endif // FUNCTIONS_H
