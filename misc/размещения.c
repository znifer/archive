#include <stdio.h>
#include <stdlib.h>

#define N 4 //Мощность множества

//Генерация размещения по 2 с повторениями
int *Alloc(){
    static int x = 1;
    static int y = 1;
    int *result  = (int *)malloc(2*sizeof(int));
    if (y > N) y = 1, x++;
    if (x > N) x = 1;
    result[0] = x;
    result[1] = y;
    y++;
    return result;
}

//Генерация упорядоченного отношения, содержащего count упорядоченных пар
int **genR(int count){
    int **result = (int **)malloc(N*sizeof(int*));
    for (int i = 0; i<N; i++){
        result[i] = (int *)malloc(N*sizeof(int*));
        //Инициализация
        for (int j = 0; j<N; j++){
            result[i][j] = 0;
        }
    }
    int *A ;
    int x, y;
    for (int i = 0; i<count; i++){
        A = Alloc();
        x = A[0]-1;
        y = A[1]-1;
        result[x][y] = 1;
        free(A);
    }
    return result;
}

void freeR(int **R){
    for (int i = 0; i<N; i++){
        free(R[i]);
    }
    free(R);
}

//Печать размещения
void printAlloc(int *A){
    printf("{%i, %i}", A[0], A[1]);
}

//Печать отношения
void printRel(int **R){
    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            printf("%i ", R[i][j]);
        }
        putchar('\n');
    }
}

int main(){
    for (int i = 0; i<5; i++){
        int **R = genR(5);
        printRel(R);
        freeR(R);
        putchar('\n');
    }
    return 0;
}