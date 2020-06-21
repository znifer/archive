
#include "vectors.h"

QTextStream out(stdout);

Table::Table(unsigned size){
    this->vsize = size + 1;
    vec.resize(vsize);
    dv(0);
    tsize = pow(2, size);
    isFull = true;
}

Table::Table(unsigned size, bool isfull){
    this->vsize = size + 1;
    vec.resize(vsize);
    dv(0);
    tsize = pow(2, size);
    t.resize(tsize);
    isFull = isfull;
}

Table::~Table(){

}

void Table::getTable(int func(QBitArray)){
    for (int i = 0; i < t.size(); i++){
        t[i][vsize - 1] = func(t[i]);
        indicies.push_back(i);
        //qDebug() << t[i];
    }
}


/*Если на наборе аргументов условие 2 истинно,
то значение функции на этом наборе не определено. Если же на набореAZ
аргументов условие 2 ложно, то значение функции на этом наборе
равно значению условия 1 на этом наборе аргументов.*/
void Table::getTableWithCondition(int func(QBitArray v), int cond(QBitArray x)){
    QVector <QBitArray> newTable;
    for (int i = 0; i < tsize; i++){
         t[i][vsize - 1] = func(t[i]);
         if (!cond(t[i])){
             undefinedIndicies.push_back(i);
         } else {
             definedIndicies.push_back(i);
         }
         newTable.push_back(t[i]);
         indicies.push_back(i);
    }
    tsize = newTable.size();
    t = newTable;
}

void Table::dv(unsigned pos){
    for (unsigned x = 0; x < 2; x++){
        vec[pos] = x;
        if (pos == (vsize - 2)){
            t.push_back(vec);
        } else {
            dv(pos + 1);
        }
    }
}

void Table::print(){
    out << "-----------------------"; endl(out);
    int count = 0;
    for (int i = 0; i < t.size(); i++){
        out << indicies[i] + 1 << "\t";
        for (int j = 0; j < t[i].size(); j++){
            if (count == t[i].size() - 1) {
                out << " " << "|" << " ";
                count = -1;
                if (undefinedIndicies.contains(i)){
                    out << "X ";
                } else {
                    out << t[i][j] << " ";
                }
            } else{
                out << t[i][j] << " ";
            }
            count++;
        }
        endl(out);
    }
    //out << "---------------";
}

bool operator == (Table &a, Table &b){
    if (a.t.size() != b.t.size()){
        out << "size of a != size of b";
        return false;
    }
    for (int i = 0; i < a.t.size(); i++){
        if (a.t[i] != b.t[i]) return false;
    }
    return true;
}

void Table::printNF(int isD){
    out << "---------------"; endl(out);
    int count = 0;
    for (int i = 0; i < t.size(); i++){
       if (t[i][5] == isD){
           for (int j = 0; j < t[i].size(); j++){
               if (count == t[i].size() - 1) {
                   out << " " << "|" << " ";
                   count = -1;
               }
               out << t[i][j] << " ";
               count++;
           }
           endl(out);
       }
    }
    out << "---------------";
}

bool Table::isfull(){
    return isFull;
}

void Table::printTables(QVector<Table> tables){
    for (int row = 0; row < tables[0].t.size(); row++){
        out << tables[0].indicies[row] + 1 << "\t";
        for (int els = 0; els < tables[0].t[0].size() - 1; els++){
            out << tables[0].t[row][els] << " ";
        }
        out << " | ";
        for (int i = 0; i < tables.size(); i++){
            if (tables[i].undefinedIndicies.contains(row)){
                out << "X ";
            } else
                out << tables[i].t[row][tables[i].t[row].size() - 1] << " ";
        }
        out << "\n";
    }
    out << "\n";
}

void Table::printOnlyDefinedRows(QVector<Table> tables){
    out << "\n";
    for (int row = 0; row < tables[0].t.size(); row++){
        if (!tables[0].undefinedIndicies.contains(row)){
            out << tables[0].indicies[row] + 1 << "\t";
            for (int els = 0; els < tables[0].t[0].size() - 1; els++){
                out << tables[0].t[row][els] << " ";
            }
            out << " | ";
            for (int i = 0; i < tables.size(); i++){
                if (tables[i].undefinedIndicies.contains(row)){
                    out << "X ";
                } else
                    out << tables[i].t[row][tables[i].t[row].size() - 1] << " ";
            }
            out << "\n";
        }
    }
}

MalfunctionTable::MalfunctionTable(unsigned size) : Table(size){
    /*malsize = tsize;
    vec.clear();
    vec.resize(tsize);
    for (int els = 0; els < t[0].size(); els++){
        for (int rows = 0; rows < t.size(); rows++){
            vec[rows] = t[rows][els];
        }
        mal.push_back(vec);
    }*/
};

void MalfunctionTable::printMalTable(){
   // qDebug() << "tsize = " << tsize << " vsize = " << vsize;
    for (int i = 0; i < mal.size(); i++){
        //qDebug() << mal[i];
        for (int j = 0; j < tsize; j++) out << mal[i][j] << " ";
        out << "\n";
        if (i == vsize - 1 || i == vsize - 2 || i == vsize - 1 + (vsize - 1) * 2)
            out << "===============================================================\n";


    }
}

void MalfunctionTable::getMalTable(int (*func)(QBitArray), int (*cond)(QBitArray)){
    getTableWithCondition(func, cond);
    malSize = tsize;
    vec.clear();
    vec.resize(tsize);
    for (int els = 0; els < t[0].size(); els++){
        for (int rows = 0; rows < t.size(); rows++){
            vec[rows] = t[rows][els];
        }
        mal.push_back(vec);
    }

    QVector <QBitArray> tmpTable;
    for (int funcSize = 0; funcSize < vsize - 1; funcSize++){
        //qDebug() << funcSize;
        for (int x = 0; x < 2; x++){
            bool f = false;
            if (funcSize == 2){
                f = true;

            }
            for (int i = 0; i < t.size(); i++){
                QBitArray tmpArray;
                tmpArray = t[i];
                tmpArray[funcSize] = x;
                vec[i] = func(tmpArray);

                if (f){
                    //qDebug() << "была внесена ошибка:" << x << "на" << funcSize << "позицию" << t[i] << ":" << tmpArray << "Получили" << vec[i];
                    //qDebug() << i << "-й набор:";
                    //qDebug() << tmpArray;
                    //qDebug() << vec;
                }
            }
            if (f) f = false;
            tmpTable.push_back(vec);
        }
    }

    //В таблицу неисправностей вносим все вектора без повторений
    int uniqVectorsCount = 0, malSize = mal.size();
    mal.push_back(tmpTable[0]);
    for (int i = 1; i < tmpTable.size(); i++){
        bool isUnique = true;
        for (int searchPos = 0; searchPos < i; searchPos++){
            if (tmpTable[i] == tmpTable[searchPos]) isUnique = false;
        }
        if (isUnique) {
            mal.push_back(tmpTable[i]);
            uniqVectorsCount++;
        }
    }
   // qDebug() << malSize;

    for (int i = 0; i <= 10; i++){
        for (int els = 0; els < mal[vsize - 1].size(); els++){
            vec[els] = mal[vsize - 1][els] ^ mal[i + 5][els];
        }
        mal.push_back(vec);
    }

    /*
    for (int rows = 0; rows < uniqVectorsCount + 1; rows++){
        for (int els = 0; els < mal[vsize - 1].size(); els++){
            vec[els] = mal[vsize - 1][els] ^ mal[rows + malSize][els];
        }
        mal.push_back(vec);
    }
    */
    //for (int i = 0; i < tmpTable.size(); i++)
        //mal.push_back(tmpTable[i]);
    //qDebug() << tmpTable;

}

void Table::printF(){
    for (int i = 0; i < t.size(); i++)
        out << t[i][vsize - 1] << " ";
}

void Table::printDifferences(QVector<Table> tables){
    out << "\nTable of differences:\n";
    out << "   ";
    for (int i = 0; i < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); i++){
        for (int j  = i + 1; j < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); j++){
            if (tables[0].definedIndicies[i] > 8)
                out << tables[0].definedIndicies[i] + 1 << "|";
            else
                out << tables[0].definedIndicies[i] + 1 << " |";
        }
    }
    out << "\n";
    out << "   ";
    for (int i = 0; i < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); i++){
        for (int j  = i + 1; j < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); j++){
            if (tables[0].definedIndicies[j] > 8)
                out << tables[0].definedIndicies[j] + 1 << "|";
            else
                out << tables[0].definedIndicies[j] + 1 << " |";
        }
    }
    out << "\n";
    for (int vars = 0; vars < tables[0].vsize - 1; vars++){
        out << "x" + QString::number(vars + 1) << " ";
        for (int i = 0; i < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); i++){
            for (int j  = i + 1; j < tables[0].indicies.size() - tables[0].undefinedIndicies.size(); j++){
                if (tables[0].t[tables[0].definedIndicies[i]][vars] ^
                        tables[1].t[tables[0].definedIndicies[j]][vars])
                    out << " x|";
                else
                    out << "  |";
            }
        }
        out << " \n";
    }
}

void MalfunctionTable::check(int (*func)(QBitArray v)){
    if (func(t[1]) | func(t[6]) | func(t[9]) | func(t[14])) out << "OK\n"; else out << "Error!\n";

    if (func(t[6])){
        out << "f f1 f2 f5 f6 f7 f8\n";
        if (func(t[1])){
            out << "f5 f7 f8";
            if (func(t[16])){
                out << "f5 f8";
                if (func(t[2])){
                    out << "f5\n";
                } else {
                    out << "f8\n";
                }
            } else {
                out << "f7\n";
            }
        } else {
            if (func(t[1])){

            }
        }
    }


}

MultiTable::MultiTable(unsigned size) : Table(size){
    this->vsize += 2;
}

void MultiTable::getMultiTable(int (*func1)(QBitArray), int (*func2)(QBitArray), int (*func3)(QBitArray)){
    for (int i = 0; i < t.size(); i++){
        t[i].resize(vsize);
        t[i][vsize - 3] = func1(t[i]);
        t[i][vsize - 2] = func2(t[i]);
        t[i][vsize - 1] = func3(t[i]);
    }
}

void MultiTable::print(){
    out << "---------------"; endl(out);
    int count = 0;
    for (int i = 0; i < t.size(); i++){
        for (int j = 0; j < t[i].size(); j++){
            if (count == t[i].size() - 3) {
                out << " " << "|" << " ";
                count = -3;
            }
            out << t[i][j] << " ";
            count++;
        }
    endl(out);
    }
        //out << "---------------";
}

MultiMalTable::MultiMalTable(unsigned size) : MultiTable(size){
    //this->vsize += 2;
}

void MultiMalTable::getMultiMalTable(int (*func1)(QBitArray), int (*func2)(QBitArray), int (*func3)(QBitArray)){
    QVector <QBitArray> z;
    mal = z;
    mal.resize(48);
    for (int i = 8; i < mal.size(); i++){
        mal[i].resize(t.size());
    }
    for (int rows = 0; rows < t[0].size() - 1; rows++){
        mal[rows].resize(t.size());
        for (int els = 0; els < t.size(); els++){
            mal[rows][els] = t[els][rows];
            //mal[els][rows] = t[rows][els];
            out << mal[rows][els] << " ";
        }
        out << "\n";
    }
    out << "===============================================================\n";
    mal[5].resize(t.size());
    mal[6].resize(t.size());
    mal[7].resize(t.size());
    for (int i = 0; i < mal[0].size(); i++){
        mal[5][i] = func1(t[i]);
        mal[6][i] = func2(t[i]);
        mal[7][i] = func3(t[i]);
    }
    for (int i = 5; i < 8; i++){
        for (int j = 0; j < mal[0].size(); j++){
            out << mal[i][j] << " ";
        }
        out << "\n";
    }
    int c = 8, errorPos = 0;
    bool error = true;
    for (int errors = 0; errors < 10; errors++){
        error = !error;
        qDebug () << c << " " << error << " " << errorPos;
        for (int i = 0; i < mal[0].size(); i++){
            QBitArray vecWithError = t[i];
            vecWithError[errorPos] = error;
            mal[c][i] = func1(vecWithError);
            mal[c + 1][i] = func2(vecWithError);
            mal[c + 2][i] = func3(vecWithError);
        }
        c += 3;
        if (error) {
            errorPos++;
        }
    }
    for (int i = 8; i < 38; i++){
        if (!((i - 2) % 3)) out <<"---------------------------------------------------------------\n";
        for (int j = 0; j < mal[0].size(); j++){
            out << mal[i][j] << " ";
        }
        out << "\n";
    }
    out << "===============================================================\n";
    //5, 6, 7  - f
    int shift = 0;
    for (int r = 0; r < 10; r++){
        for (int els = 0; els < mal[0].size(); els++){
            mal[r + 38][els] = (mal[5][els] ^ mal[8 + shift][els]) |
                               (mal[6][els] ^ mal[9 + shift][els]) |
                               (mal[7][els] ^ mal[10 + shift][els]);
        }
        shift += 3;
    }
    for (int i = 38; i < 48; i++){
        for (int j = 0; j < mal[0].size(); j++){
            out << mal[i][j] << " ";
        }
        out << "\n";
    }

}

void MultiMalTable::getMalTable(int (*func1)(QBitArray), int (*func2)(QBitArray), int (*func3)(QBitArray)){

}

void MultiMalTable::print(){
    for (int i = 0; i < t.size(); i++){
        for (int j = 0; j < t[0].size(); j++){
            out << mal[i][j];
        }
        out << "\n";
    }
}




