#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define basetype double
#define N 256
void readMatr (basetype a[N][N], int n){
    printf ("matr?:\n");
    //printf ("Введите матрицу:\n");
    for (int i=0;i<n; i++){
        for (int j = 0; j < n; j++){
            scanf ("%lf", &a[i][j]);
        }
    }
}

void readArray (basetype a[N], int n){
    //printf ("Введите вероятности появления сообщений:\n");
    printf ("prob?:\n");
    for (int i = 0; i < n; i++){
        scanf ("%lf", &a[i]);
    }
}

void printArray (basetype a[N], int n){
    for (int i = 0; i < n; i++){
            printf ("%lf ", a[i]);
    }
}

void printMatr (basetype a[N][N], int n){
    //printf ("\nres:\n");
    for (int i=0;i<n; i++){
        for (int j = 0; j < n; j++){
            printf ("%lf ", a[i][j]);

        }
        printf ("\n");
    }
}

basetype entropyShen (basetype a[N], int n){
    basetype result;
    for (int i=0; i<n; i++){
        result += a[i]*log2(a[i]);
    }
    return (-result);
}

void transToUn (basetype a[N][N], basetype prob[N], int n, int mode, basetype un[N][N]){
    if (mode == 2){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                un[i][j] = a[i][j]*prob[i];
            }
        }
    } else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                un[j][i] = a[j][i]/prob[i];
            }
        }
    }
}

void transFromUn (basetype un[N][N], basetype ab[N][N], basetype ba[N][N], int n, int mode){
    //basetype
    double sumsB[N] = {0} , sumsA[N]={0};
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            sumsA[i] += un[i][j];
            sumsB[i] += un[j][i];
        }
    }
    printf("\nP(A):\n");
    printArray(sumsA, n);
    printf("\nP(B):\n");
    printArray(sumsB, n);
    printf ("\n");
    printf ("entr a = %lf\n", entropyShen(sumsA, n));
    //printf ("Энтропия А = %lf\n", entropyShen(sumsA, n));
    printf ("entr b = %lf\n", entropyShen(sumsB, n));
    //printf ("Энтропия B = %lf\n", entropyShen(sumsB, n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            ba[i][j] = un[i][j]/sumsA[i];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            ab[i][j] = un[i][j]/sumsB[j];
        }
    }
    printf ("\nab\n");
    printMatr(ab, n);
    printf ("\nba\n");
    printMatr(ba, n);
    printf ("\nun\n");
    printMatr(un, n);

}


int main(){
    setlocale(LC_ALL, "Rus");
    char wMode = 'y';
    int n, pMode;
    while (wMode == 'y'|| wMode == 'Y'){
        printf("Какую канальную матрицу вы хотите ввести? 1 - A/B, 2 - B/A, 3 - A; B");
        scanf ("%i", &pMode);
        //printf("Сколько символов в алфавите?");
        printf("N?");
        scanf ("%i", &n);
        //getchar();
        basetype ab[N][N], ba[N][N], un[N][N], p[N];
        switch (pMode){
        case 1:
            readMatr(ab, n);
            readArray(p, n);
            transToUn(ab, p, n, pMode, un);
            break;
        case 2:
            readMatr(ba, n);
            readArray(p, n);
            transToUn(ba, p, n, pMode, un);
            break;
        case 3:
            readMatr(un, n);
            break;
        }
        transFromUn(un, ab, ba, n, pMode);








        //printMatr(c, n);
        getchar();
        printf ("Продолжить работу программы? y/n\n");
        wMode = getchar();
    }
}

