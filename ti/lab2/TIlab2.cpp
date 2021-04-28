#include "pch.h"
#include <iostream>
#include "TI.h"
#include <locale>
#include <malloc.h>
using namespace std;

int main(){
	setlocale(LC_ALL, "Rus");
	probArray pab, pba;
	double **ab, **ba, **un;
	int m, n, mode;
	cout << "Введите количество символов в алфавите источника и приемника" << endl;
	cin >> m >> n;
	ab = new double *[n];
	for (int i = 0; i < n; i++) {
		ab[i] = new double[m];
	}
	ba = new double *[n];
	for (int i = 0; i < n; i++) {
		ba[i] = new double[m];
	}
	un = new double *[n];
	for (int i = 0; i < n; i++) {
		un[i] = new double[m];
	}
	cout << "Какую канальную матрицу вы хотите ввести ? 1 - A/B, 2 - B/A, 3 - A;B" << endl;
	cin >> mode;
	switch (mode) {
	case 1:
		cout << "Введите канальную матрицу" << endl;
		readMatr(ab, n, m);
		pab = readProbArray(n);
		pba = new double[n];
		transToUn(ab, pab, n, mode, un);
		transFromUn(un, ab, ba, n, m, pab, pba);
		break;
	case 2:
		cout << "Введите канальную матрицу" << endl;
		readMatr(ba, n, m);
		pba = readProbArray(n);
		pab = new double[n];
		transToUn(ba, pba, n, mode, un);
		transFromUn(un, ab, ba, n, m, pab, pba);
		break;
	case 3:
		cout << "Введите канальную матрицу" << endl;

		readMatr(un, n, m);
		cout << endl;
		printMatr(un, n, m);
		cout << endl;
		pba = new double[n];
		pab = new double[n];
		transFromUn(un, ab, ba, n, m, pab, pba);
		break;
	}
	//double entrA = entropyShen(pab, n);
	//double entrB = entropyShen(pba, n);
	double entrAB = 0;
	double entrBA = 0;
	double entrUN = 0;

}
