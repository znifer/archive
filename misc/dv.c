#include <stdio.h>
#define N 3
void dv(int n, int i, int tmp[N], int res[N*N][N], int j){
    int x;
    for (x = 0; x < 2; x++){
        tmp[i] = x;
        if (!(i == n-1)){
            dv (n, i+1, tmp, res, j);
        } else {
            for (int k = 0; k < N; k++){
                printf ("%i ", tmp[k]);
                res[j][k] = tmp[k];
            }
            j++;
            printf ("\n");
        }
    }
}

void dvToMatr(int tmp[N][N], int res[N][N]){
    int k=0, l=0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (tmp[j][i]){
                res[k][j] = j;
                l++;
            }
        }
        while (l < N){
            res[k][l] = -1;
        }
        k++;
        l = 0;
    }
}

int main(){
    int dvArr[N*N][N], res[N][N];
    int tmp[N];
    int n = N;
    dv(n, 0, tmp, dvArr, 0);
    //dvToMatr(a, res);
    for (int i = 0; i < N*N; i++){
        for (int j = 0; j < N; j++){
            printf ("%i ", dvArr[i][j]);
        }
        printf ("\n");
    }
    return 0;
}
/*
    unsigned char n;
    scanf("%i", &n);
    unsigned char bits = 1;
    for (unsigned char k = 0; k<(1«n); k++){
        for (unsigned char i = 0; i<n; i++){
            if ((1«i) & bits){
                printf("%u", i+1);
            }
        }
        printf("\n");
        bits++;
    }
*/
