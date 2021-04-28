#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define basetype double

int readArray (basetype *a, int N){
    int zeroes = 0;
    printf ("Введите вероятности появления сообщений:");
    for (int i=0;i<N; i++){
        scanf ("%lf", &a[i]);
        if (a[i]==0){
            zeroes++;
        }
    }
    return zeroes;
}

void initArray (basetype *a, int N){
    for (int i=0; i<N; i++){
        a[i] = 1/N;
    }
}

double entropyShen (basetype *a, int N){
    double result;
    for (int i=0; i<N; i++){
        result += a[i]*log2(a[i]);
    }
    return (-result);
}

double entropyHart(int N){
    return (log2(N));
}

double redundencyRatio (double a, double b){
    double result = 1-(a/b);
    return(result);
}

int main(){
    setlocale(LC_ALL, "Rus");
    char wMode = 'y';
    char prob;
    double H1, H2;
    basetype a[256] = {0};
    while (wMode == 'y'|| wMode == 'Y'){
        printf("Введите количество СВ: ");
        int N;
        scanf ("%i", &N);
        getchar();
        printf("Сообщения равновероятны? y/n ");
        prob = getchar();
        if (prob == 'n' || prob == 'N'){
            int tmp1 = readArray (a, N);
            H1=entropyHart(N-tmp1);
            H2=entropyShen(a, N);
        } else {
            initArray(a, N);
            H1=entropyHart(N);
            H2=H1;
        }
        printf ("Н = %lf по Хартли\n", H1);
        printf ("Н = %lf по Шеннону\n", H2);
        printf ("Коэффициент избыточности k = %lf\n", redundencyRatio(H2, H1));
        getchar();
        printf ("Продолжить работу программы? y/n\n");
        wMode = getchar();
    }
}
