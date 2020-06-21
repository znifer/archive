#ifndef VECTORS_H
#define VECTORS_H
#include <QVector>
#include <QBitArray>
#include <QDataStream>
#include <QDebug>
#include <cmath>
#include <iostream>

#endif // VECTORS_H

class Table {
protected:
    QVector <QBitArray> t;
   QBitArray vec;
   int vsize; //Длина вектора
   int tsize;
   void dv(unsigned pos);
   bool isFull;
   QVector <int> indicies;
   QVector <int> undefinedIndicies;
   QVector <int> definedIndicies;
public:
    //Принимает размер вектора без значения функции
    Table(unsigned size);
    Table(unsigned size, bool isfull);
    ~Table();
    void getTable(int func(QBitArray v));
    void getTableWithCondition(int func(QBitArray v), int cond(QBitArray c));

    void print();
    //Если нужно вывести ДНФ - 1, иначе 0
    void printNF(int);
    void printF();

    //Если необходимо составить ТИ по неполностью определенной функции - 0
    void setFull(bool);
    bool isfull();

    static void printDifferences(QVector <Table>);
    static void printOnlyDefinedRows(QVector <Table>);
    static void printTables(QVector <Table>);
    friend bool operator == (Table &a, Table &b);
};

class MalfunctionTable : public Table{
    QVector <QBitArray> mal;
    int malSize; //размер таблицы неисправностей
    QVector <QString> prefixes;
public:
    MalfunctionTable(unsigned size);
    //void getTable(int func(QBitArray v));
    void printMalTable();
    void getMalTable(int func(QBitArray v), int cond(QBitArray c));
    void check(int func(QBitArray v));
};

class MultiTable : public Table{
public:
    MultiTable(unsigned size);
    void getMultiTable(int func1(QBitArray v),
                       int func2(QBitArray v),
                       int func3(QBitArray v));
    void print();
};

class MultiMalTable : public MultiTable{
    QVector <QBitArray> mal;
    int malSize; //размер таблицы неисправностей
public:
    MultiMalTable(unsigned size);
    void print();
    void getMultiMalTable(int func1(QBitArray v),
                          int func2(QBitArray v),
                          int func3(QBitArray v));
    void getMalTable(int func1(QBitArray v),
                     int func2(QBitArray v),
                     int func3(QBitArray v));

};
