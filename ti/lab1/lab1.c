//Создать подпрограмму для вычисления энтропии дискретного источника с алфавитом произвольного размера.
//Создать программу для демонстрации работы подпрограммы.
//Задачи на вычисление энтропии, решѐнные вручную, использовать как тестовые данные.
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define basetype double
void readArray (basetype *a, int N){
    for (int i=0; i<N; i++){
        scanf ("%lf", &a[i]);
    }
}
double entropy (basetype *a, int N){
    double result;
    for (int i=0; i<N; i++){
        result += a[i]*log2(a[i]);
    }
    return (-result);
    printf ("%lf", -result);
}


int main(){
    setlocale(LC_ALL, "RUS");
    printf("Введите количество СВ:");
    int N;
    scanf ("%i", &N);
    basetype a[N];
    readArray (a, N);
    printf ("Энтропия = %lf", entropy(a, N));
}
