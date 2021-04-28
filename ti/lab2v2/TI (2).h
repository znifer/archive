#ifndef TI_H_INCLUDED
#define TI_H_INCLUDED
typedef double* probArray;
probArray readProbArray(int);
void printProbArray(probArray, int);
void readMatr(double**, int, int);
void printMatr(double**, int, int);
double entropyShen(double*, int);
void transToUn(double**, probArray, int, int, double**);
void transFromUn(double**, double**, double**, int n, int m, probArray, probArray);
#endif //TI_H_INCLUDED