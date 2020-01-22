#include "functions.h"
#include <QDebug>
Functions::Functions(){}

//Или не
int Functions::nor (int a, int b){
    return !(a | b);
}
//И не
int Functions::nand (int a, int b){
    return !(a & b);
}

int Functions::l1f(QBitArray v){
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (v[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (v[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if (3 < res && res < 8) return 1; else return 0;
}

int Functions::l1f1(QBitArray x){
    int u1, u2, u3, u4, u5, u6, u7, u8, z1, z2, z3, z4, z5, z6, z7, z8, g1, g2, g3, g4, g5, g6;
    z6 = !x[0] & x[2];
    z1 = x[4]  & z6;
    z2 = x[0]  & !x[4];
    z3 = x[0]  & !x[3];
    z4 = !x[0] & x[1];
    z5 = !x[1] & x[2];
    z7 = x[1]  & !x[3];
    z8 = x[0]  & !x[1];

    u1 = !x[1] & z3;
    u2 = !x[2] & z3;
    u3 = !x[2] & z8;
    u4 = x[3]  & z4;//
    u5 = x[3]  & z1;
    u6 = x[1]  & z1;
    u7 = z2    & z5;
    u8 = z2    & z7;

    g1 = u1 | u2;
    g2 = u3 | u4;
    g3 = u5 | u6;
    g4 = u7 | u8;
    g5 = g1 | g2;
    g6 = g3 | g4;


    return g5 | g6;
}

int Functions::l1f2(QBitArray x){
    int u10, u2, u3, u4, u5, u6, u9, u8, z1, z2, z3, z4, z5, z6, z7, z8, g1, g2, g3, g4, g5, g6;

    z2 = !x[0] | !x[1];     // +
    z3 = !x[0] | !x[3];     // +
    z4 = !x[0] | !x[1];     // +
    z5 = x[0] | x[1];       // +
    z6 = x[2] | x[4];       // +

    z1 = x[0] | z6;         // +

    u2 = !x[3] | z2;        // +
    u3 = !x[4] | z2;
    u4 = !x[2] | z3;
    u5 = !x[4] | z3;
    u6 = !x[2] | z4;
    u8 = x[3] | z5;
    u9 = x[3] | z1;
    u10 = x[1] | z1;

    g1 = u2 & u3;
    g2 = u4 & u5;
    g3 = u6 & u8;
    g4 = u9 & u10;
    g5 = g1 & g2;
    g6 = g3 & g4;


    return g5 & g6;

}
//СДНФ и не
int Functions::l2f1(QBitArray x){
    int z1, z2, z3, z4, z5, z6, z7, z8, u1, u2, u3, u4, u5, u6, u7, u8, g1, g2, g3, g4, g5, g6;
    z3 = nand(nand(x[0], !x[3]), nand(x[0], !x[3]));
    u1 = nand(nand(!x[1], z3), nand(!x[1], z3));
    u2 = nand(nand(!x[2], z3), nand(!x[2], z3));
    g1 = nand(nand(u1, u1), nand(u2, u2));
    z8 = nand(nand(x[0], !x[1]), nand(x[0], !x[1]));
    u3 = nand(nand(!x[2], z8), nand(!x[2], z8));
    z4 = nand(nand(!x[0], !x[1]), nand(!x[0], !x[1]));
    u4 = nand(nand(x[3], z4), nand(x[3], z4));
    g2 = nand((nand(u3, u3)), nand(u4, u4));
    g5 = nand(nand(g1, g1), nand(g2, g2));
    z6 = nand(nand(!x[0], x[2]), nand(!x[0], x[2]));
    z1 = nand(nand(x[4], z6), nand(x[4], z6));
    u5 = nand(nand(z1, x[3]), nand(z1, x[3]));
    u6 = nand(nand(z1, x[1]), nand(z1, x[1]));
    g3 = nand(nand(u5, u5), nand(u6, u6));
    z2 = nand(nand(x[1], !x[3]), nand(x[1], !x[3]));
    z5 = nand(nand(!x[1], x[2]), nand(!x[1], x[2]));
    u7 = nand(nand(z2, z5), nand (z2, z5));
    z7 = nand(nand(x[1], !x[3]), nand(x[1], !x[3]));
    u8 = nand(nand(z2, z7), nand(z2, z7));
    g4 = nand(nand(u7, u7), nand(u8, u8));
    g6 = nand(nand(g3, g3), nand(g4, g4));

    return nand(nand(g5, g5), nand(g6, g6));
}
//СДНФ или не
int Functions::l2f2(QBitArray x){
    int z1, z2, z3, z4, z5, z6, z7, z8, u1, u2, u3, u4, u5, u6, u7, u8, g1, g2, g3, g4, g5, g6;
    z3 = nor(nor(x[0], x[0]), nor(!x[3], !x[3]));
    u1 = nor(nor(!x[1], !x[1]), nor(z3, z3));
    u2 = nor(nor(z3, z3), nor(!x[2], !x[2]));
    g1 = nor(nor(u1, u2), nor(u1, u2));

    z8 = nor(nor(x[0], x[0]), nor(!x[1], !x[1]));
    u3 = nor(nor(!x[2], !x[2]), nor(z8, z8));
    z4 = nor(nor(!x[0], !x[0]), nor(!x[1], !x[1]));
    u4 = nor(nor(x[3], x[3]), nor(z4, z4));
    g2 = nor(nor(u3, u4), nor(u3, u4));
    g5 = nor(nor(g1, g2), nor(g1, g2));

    z6 = nor(nor(!x[0], !x[0]), nor(x[2], x[2]));
    z1 = nor(nor(x[4], x[4]), nor(z6, z6));
    u5 = nor(nor(x[3], x[3]), nor(z1, z1));

    u6 = nor(nor(z1, z1), nor(x[1], x[1]));
    g3 = nor(nor(u5, u6), nor(u5, u6));


    z2 = nor(nor(x[1], x[1]), nor(!x[3], !x[3]));
    z5 = nor(nor(!x[1], !x[1]), nor(x[2], x[2]));
    u7 = nor(nor(z5, z5), nor(z2, z2));

    z7 = nor(nor(x[1], x[1]), nor(!x[3], !x[3]));
    u8 = nor(nor(z2, z2), nor(z7, z7));
    g4 = nor(nor(u7, u8), nor(u7, u8));
    g6 = nor(nor(g3, g4), nor(g3, g4));
    return nor(nor(g5, g6), nor(g5, g6));
}
//СКНФ и не
int Functions::l2f3(QBitArray x){
    int u10, u2, u3, u4, u5, u6, u9, u8, z1, z2, z3, z4, z5, z6, z7, z8, g1, g2, g3, g4, g5, g6;

    z2 = nand(nand(!x[0], !x[0]), nand(!x[1], !x[1]));
    u2 = nand(nand(!x[3], !x[3]), nand(z2, z2));

    u3 = nand(nand(z2, z2), nand(!x[4], !x[4]));
    g1 = nand(nand(u2, u3), nand(u2, u3));

    z3 = nand(nand(!x[0], !x[0]), nand(!x[3], !x[3]));
    u4 = nand(nand(!x[2], !x[2]), nand(z3, z3));

    u5 = nand(nand(!x[4], !x[4]), nand(z3, z3));
    g2 = nand(nand(u4, u5), nand(u4, u5));
    g5 = nand(nand(g1, g2), nand(g1, g2));

    z4 = nand(nand(!x[0], !x[0]), nand(!x[1], !x[1]));
    u6 = nand(nand(!x[2], !x[2]), nand(z4, z4));

    z5 = nand(nand(x[0], x[0]), nand(x[1], x[1]));
    u8 = nand(nand(x[3], x[3]), nand(z5, z5));
    g3 = nand(nand(u6, u8), nand(u6, u8));

    z6 = nand(nand(x[2], x[2]), nand(x[4], x[4]));
    z1 = nand(nand(x[0], x[0]), nand(z6, z6));
    u9 = nand(nand(x[3], x[3]), nand(z1, z1));

    u10 = nand(nand(x[1], x[1]), nand(z1, z1));
    g4 = nand(nand(u9, u10), nand(u9, u10));
    g6 = nand(nand(g3, g4), nand(g3, g4));
    return nand(nand(g5, g6), nand(g5, g6));
}
//СКНФ или не
int Functions::l2f4(QBitArray x){
    int u10, u2, u3, u4, u5, u6, u9, u8, z1, z2, z3, z4, z5, z6, z7, z8, g1, g2, g3, g4, g5, g6;

    z2 = nor(nor(!x[0], !x[1]), nor(!x[0], !x[1]));
    u3 = nor(nor(!x[4], z2), nor(!x[4], z2));
    u2 = nor(nor(!x[3], z2), nor(!x[3], z2));
    g1 = nor(nor(u2, u2), nor(u3, u3));

    z3 = nor(nor(!x[0], !x[3]), nor(!x[0], !x[3]));
    u4 = nor(nor(!x[2], z3), nor(!x[2], z3));

    u5 = nor(nor(!x[4], z3), nor(!x[4], z3));
    g2 = nor(nor(u4, u4), nor(u5, u5));
    g5 = nor(nor(g1, g1), nor(g2, g2));

    z4 = nor(nor(!x[0], !x[1]), nor(!x[0], !x[1]));
    u6 = nor(nor(z4, !x[2]), nor(z4, !x[2]));

    z5 = nor(nor(x[0], x[1]), nor(x[0], x[1]));
    u8 = nor(nor(x[3], z5), nor(x[3], z5));
    g3 = nor(nor(u6, u6), nor(u8, u8));

    z6 = nor(nor(x[2], x[4]), nor(x[2], x[4]));
    z1 = nor(nor(x[0], z6), nor(x[0], z6));
    u9 = nor(nor(x[3], z1), nor(x[3], z1));

    u10 = nor(nor(x[1], z1), nor(x[1], z1));
    g4 = nor(nor(u9, u9), nor(u10, u10));
    g6 = nor(nor(g3, g3), nor(g4, g4));

    return nor(nor(g5, g5), nor(g6, g6));
}

/*Если на наборе аргументов условие 2 истинно,
то значение функции на этом наборе не определено. Если же на наборе
аргументов условие 2 ложно, то значение функции на этом наборе
равно значению условия 1 на этом наборе аргументов.*/
int Functions::l3c(QBitArray x){
    if ((x[2] == 0) && (x[3] == 0)) return 0; else return 1;
}

int Functions::l3f(QBitArray x){
    if (Functions::l3c(x)) return Functions::l1f(x); else return -1;
}

int Functions::l3f1(QBitArray x){
    int u1, u2, u3, u4, u5, u6, u7, z1, z2, z3, z4, z5, g1, g2, g3, g4, g5;
    z1 =  x[0] & !x[1];
    z2 = !x[0] &  x[1];
    z3 = !x[3] & !x[4];
    z4 =  x[3] &  x[4];
    z5 = !x[0] &  x[2];

    u1 =  x[3] &  z2;
    u2 =  x[4] &  z2;
    u3 = !x[2] &  z1;
    u4 =  x[0] &  z3;
    u5 = !x[4] &  z1;
    u6 = !x[3] &  z1;
    u7 =  z4   &  z5;
    g1 = u1 | u2;
    g2 = u3 | u4;
    g3 = u5 | u6;
    g4 = u7 | g1;
    g5 = g2 | g3;
    return g4 | g5;
}

int Functions::l3f2(QBitArray x){
    int u1, u2, u3, u4, u5, u6, u7, z1, z2, z3, z4, z5, g1, g2, g3, g4, g5;
    z1 =  x[0] | x[1];
    z2 =  x[0] | x[3];
    z3 = !x[0] | !x[4];
    z4 = !x[0] | !x[1];
    z5 = !x[2] | !x[3];

    u1 =  x[4] | z1;
    u2 =  x[2] | z1;
    u3 =  x[4] | z2;
    u4 =  x[1] | z2;
    u5 = !x[3] | z4;
    u6 = !x[1] | z3;
    u7 =  z3   | z5;

    g1 = u1 & u2;
    g2 = u3 & u4;
    g3 = u5 & u6;
    g4 = u7 & g1;
    g5 = g2 & g3;
    return g4 & g5;
}

int Functions::l4p(QBitArray x){
    return (!x[0] & x[2] & x[3] & x[4]) |
            (!x[0] & x[1] & x[3]) |
            (!x[0] & x[1] & x[4]) |
            (x[0] & !x[1] & !x[2]) |
            (x[0] & !x[3] & !x[4]) |
            (x[0] & !x[1] & !x[4]) |
            (x[0] & !x[1] & !x[3]);
}

int Functions::l4test1(QBitArray x){
    x[4] = 1;
    int res = (!x[0] & x[2] & x[3] & x[4]) |
            (!x[0] & x[1] & x[3]) |
            (!x[0] & x[1] & x[4]) |
            (x[0] & !x[1] & !x[2]) |
            (x[0] & !x[3] & !x[4]) |
            (x[0] & !x[1] & !x[4]) |
            (x[0] & !x[1] & !x[3]);
    qDebug() << res;
    return (!x[0] & x[2] & x[3] & x[4]) |
            (!x[0] & x[1] & x[3]) |
            (!x[0] & x[1] & x[4]) |
            (x[0] & !x[1] & !x[2]) |
            (x[0] & !x[3] & !x[4]) |
            (x[0] & !x[1] & !x[4]) |
            (x[0] & !x[1] & !x[3]);
}

int Functions::l5f1(QBitArray x){
    //3<( x1x2x3+x4x5)<8 & 4≤( x1x2x3+x4x5)≤6
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if ((3 < res & res < 8) & (4 <= res & res <= 6)) return 1; else return 0;
}

int Functions::l5f2(QBitArray x){
    //2≤| x1x2-x3x4x5|≤4 & 4≤( x1x2x3+x4x5)≤6
    int t11 = 0, t12 = 0;
    for (unsigned i = 0; i < 2; i++){
        t11 = t11 + (x[i] << 1 - i);
    }
    for (unsigned i = 2; i < 5; i++){
        t12 = t12 + (x[i] << 4 - i);
    }
    unsigned res1 = abs(t11 - t12);
    unsigned t1 = 0, t2 = 0;

    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res2 = t1 + t2;
    if ((2 <= res1 & res1 <= 4) & (4 <= res2 & res2 <= 6))return 1; else return 0;
}

int Functions::l5f3(QBitArray x){

    return  ((!x[0] & x[1] & !x[2] & x[3] & x[4])|
             (!x[0] & x[1] & x[2] & !x[3] & x[4])|
             (x[0] & !x[2] & !x[3] & !x[4])|
             (x[0] & !x[1] & x[2] & !x[3]));
    //f2
    return (!x[0] & x[1] & !x[2] & x[3] & x[4] |
            !x[0] & x[1] & x[2] & !x[3] & x[4] |
            x[0] & !x[1] & !x[3] & !x[4] |
            x[0] & !x[2] & !x[3] & !x[4] |
            x[0] & !x[1] & x[2] & !x[3]);


    /*return (!x[0] & x[2] & x[3] & x[4] |
            !x[0] & x[1] & x[2] & x[4] |
            x[0] & !x[1] & !x[2] & !x[4] |
            x[0] & !x[2] & !x[3] & !x[4] |
            !x[0] & x[1] & x[3] |
            x[0] & !x[1] & !x[3]);
    */
    //return l5f1(x);
}

int Functions::l5f11(QBitArray x){
    int u1, u2, u3, u4, u5, u6,
            z1, z2, z3, z4, z5, z6, z7,
            g1, g2, g3, g4;
        /*
        u1 = !x[0] & x[2] & x[3] & x[4];
        u2 = !x[0] & x[1] & x[2] & x[4];
        u3 = x[0] & !x[1] & !x[2] & !x[4];
        u4 = x[0] & !x[2] & !x[3] & !x[4];
        u5 = !x[0] & x[1] & x[3];
        u6 = x[0] & !x[1] & !x[3];
        */
        z5 = !x[0] & x[2];
        z6 = x[0] & !x[2];
        z1 = x[4] & z5;
        z2 = !x[4] & z6;
        z3 = !x[0] & x[1];
        z4 = !x[1] & !x[3];

        u1 = x[3] & z1;
        u2 = x[1] & z1;
        u3 = !x[1] & z2;
        u4 = !x[3] & z2;
        u5 = x[3] & z3;
        u6 = x[0] & z4;

        g1 = u1 | u2;
        g2 = u3 | u4;
        g3 = u5 | u6;
        g4 = g1 | g2;

        return g3 | g4;
}

int Functions::l5f12(QBitArray x){
    int u1, u2, u3, u4, u5,
           z1, z2, z3, z4, z5, z6, z7,
           g1, g2, g3;

       z7 = !x[0] & x[1];
       z1 = x[0] & !x[3];
       z2 = x[4] & z7;
       z3 = !x[4] & z1;
       z4 = !x[1] & x[2];
       z5 = !x[2] & x[3];
       z6 = x[2] & !x[3];

       u1 = z2 & z5;
       u2 = z2 & z6;
       u3 = !x[1] & z3;
       u4 = !x[2] & z3;
       u5 = z1 & z4;

       g1 = u1 | u2;
       g2 = u3 | u4;
       g3 = u5 | g1;

       return g2 | g3;
}

int Functions::mf1(QBitArray x){
    int u1, u2, u3, u4, u5, u6, u7, u8,
        z1, z2, z3, z4, z5, z6, z7, z8, z9, z10,
        g1, g2, g3, g4, g5, g6;

        z1 = !x[0] & x[1];
        z2 = x[0] & !x[1];
        z3 = x[2] & x[4];
        z4 = !x[2] & !x[4];
        z5 = !x[3] & z2;
        z6 = !x[0] & x[3];
        z7 = x[3] & z1;
        z8 = !x[2] & x[4];
        z9 = !x[3] & z3;
        z10 = x[0] &  !x[3];

        u1 = z3 & z6;
        u2 = z7;
        u3 = z2 & z4;
        u4 = z5 & x[4];
        u5 = z8 & z7;
        u6 = z1 &  !x[3] & z3;
        u7 = z10 & z4;
        u8 = x[2] & z5;

        g2 = u5 | u6;
        g3 = u7 | u8;
        g1 = g2 | g3;
        g4 = u1 | u2;
        g5 = u3 | u4;
        g6 = g4 | g5;

        return g1 | g6;
    /*return  ((!x[0] & x[2] & x[3] & x[4]) |
             (!x[0] & x[1] & x[3]) |
             (x[0] & !x[1] & !x[2] & !x[4]) |
             (x[0] & !x[1] & !x[3] & x[4]) |

             (!x[0] & x[1] & !x[2] & x[3] & x[4])|
             (!x[0] & x[1] & x[2] & !x[3] & x[4])|
             (x[0] & !x[2] & !x[3] & !x[4])|
             (x[0] & !x[1] & x[2] & !x[3]));*/
}

int Functions::mf2(QBitArray x){
    int u1, u2, u3, u4, u5, u6, u7, u8,
        z1, z2, z3, z4, z5, z6, z7, z8, z9, z10,
        g1, g2, g3, g4, g5, g6;

        z1 = !x[0] & x[1];
        z2 = x[0] & !x[1];
        z3 = x[2] & x[4];
        z4 = !x[2] & !x[4];
        z5 = !x[3] & z2;
        z6 = !x[0] & x[3];
        z7 = x[3] & z1;
        z8 = !x[2] & x[4];
        z9 = !x[3] & z3;
        z10 = x[0] &  !x[3];

        u1 = z3 & z6;
        u2 = z7;
        u3 = z2 & z4;
        u4 = z5 & x[4];
        u5 = z8 & z7;
        u6 = z1 &  !x[3] & z3;
        u7 = z10 & z4;
        u8 = x[2] & z5;

        g2 = u5 | u6;
        g3 = u7 | u8;

        return g2 | g3;
    /*return  ((!x[0] & x[1] & !x[2] & x[3] & x[4])|
             (!x[0] & x[1] & x[2] & !x[3] & x[4])|
             (x[0] & !x[2] & !x[3] & !x[4])|
             (x[0] & !x[1] & x[2] & !x[3]));*/
}

int Functions::l6c(QBitArray x){
    //4≤(x1x2x3+x4x5)≤6
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if (4 <= res & res <= 6) return 1; else return 0;
}

int Functions::l6f1(QBitArray x){
    //3<(x1x2x3+x4x5)<8
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if (3 < res & res < 8)  return 1; else return  0;
}

int Functions::l6f2(QBitArray x){
    int t11 = 0, t12 = 0;
    for (unsigned i = 0; i < 2; i++){
        t11 = t11 + (x[i] << 1 - i);
    }
    for (unsigned i = 2; i < 5; i++){
        t12 = t12 + (x[i] << 4 - i);
    }
    unsigned res1 = abs(t11 - t12);
    if (2 <= res1 & res1 <= 4) return  1; else return 0;
}

int Functions::test1(QBitArray x){
    return (x[1] | x[2] | x[3] | x[4] | !x[1] | !x[2] | !x[3] | !x[4] |
            (x[1] & !x[2] & x[3] & x[4]) |
            (x[1] & x[2] & !x[3] & x[4]) |
            (!x[1] & !x[2] & !x[3] & !x[4]) |
            (!x[1] & x[2] & !x[3] & !x[4]) |
            (!x[1] & x[2] & !x[3] & x[4]) |
            (x[1] & !x[2] & !x[3] & !x[4]));
}

int Functions::test2(QBitArray x){
    int u1, u2, u3, u4, u5, u6, z1, z2, g1, g2, g3, g4;

    z1 = !x[2] & x[4];
    z2 = !x[1] & x[2];

    u1 = !x[3] & !x[4];
    u2 = x[2] & !x[3];
    u3 = x[1] & !x[3];
    u4 = x[3] & z1;
    u5 = x[1] & z1;
    u6 = z2 & !x[4];

    g1 =  u1 | u2;
    g2 = u3 | u4;
    g3 = u5 | u6;
    g4 = g1 | g2;
    return g3 | g4;

    return (/*(!x[2] & x[3] & x[4]) |
            (x[1] & !x[2] & x[4]) |
            (x[1] & x[2] & !x[3]) |
            (!x[1] & x[2] & !x[4]) |
            (x[1] & !x[2] & !x[3]) |
            (!x[3] & !x[4]) |
            (x[2] & !x[3]) |
            (x[1] & !x[3]) |*/
            (!x[2] & x[3] & x[4]) |
            (x[1] & !x[2] & x[4]) |
            (!x[1] & x[2] & !x[4]) |
            (!x[3] & !x[4]) |
            (x[2] & !x[3]) |
            (x[1] & !x[3]) |
            (!x[1] & !x[4]));
    //Первый этап
    return ((x[1] & !x[2] & x[3] & x[4]) |
            (x[1] & x[2] & !x[3] & x[4]) |
            (!x[1] & !x[2] & !x[3] & !x[4]) |
            (!x[1] & x[2] & !x[3] & !x[4]) |
            (!x[1] & x[2] & !x[3] & x[4]) |
            (x[1] & !x[2] & !x[3] & !x[4]));
}

int Functions::l7f1(QBitArray x){
    return 1;
    int t11 = 0, t12 = 0;
    for (unsigned i = 0; i < 2; i++){
        t11 = t11 + (x[i] << 1 - i);
    }
    for (unsigned i = 2; i < 5; i++){
        t12 = t12 + (x[i] << 4 - i);
    }
    unsigned res1 = abs(t11 - t12);
    if (2 <= res1 & res1 <= 4) return  1; else return 0;
}

int Functions::l7f2(QBitArray x){
    //3<(x1x2x3+x4x5)<8
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if (3 < res & res < 8)  return 1; else return  0;
}

int Functions::l7f3(QBitArray x){
    //4≤(x1x2x3+x4x5)≤6
    unsigned t1 = 0, t2 = 0;
    for (unsigned i = 0; i < 3; i++){
        t1 = t1 + (x[i] << 2 - i);
    }
    for (unsigned i = 3; i < 5; i++){
        t2 = t2 + (x[i] << 4 - i);
    }
    unsigned res = t1 + t2;
    if (4 <= res & res <= 8) return 1; else return 0;
}

int Functions::l7c(QBitArray x){
    //5≤(x2x3+x4x5x1)≤8
    unsigned t1 = 0, t2 = 0;
    t1 = x[1] << 1;
    t1 += x[2];

    t2 = x[3] << 2;
    t2 += x[4] << 1;
    t2 += x[0];
    int res = t1 + t2;
    return (5 <= res && res <= 8);

}

int Functions::test3(QBitArray x){
    return 1;
}

int Functions::test4(QBitArray x){
    x[3] = 1;
    return ( ! x[3] & !x[4]) |
            (x[2] & !x[3]) |
            (x[1] & !x[3]) |
            (!x[2] & x[3] & x[4]) |
            (x[1] & !x[2] & x[4]) |
            (!x[1] & x[2] & !x[4]);
}


