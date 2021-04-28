#include "TI.h"
#include "pch.h"
#include <math.h>
#include <iostream>
using namespace std;
double entropyShen(double* a, int N) {
	double result = 0;
	for (int i = 0; i < N; i++) {
		if (a[i] != 0) {
			result += a[i] * log2(a[i]);
		}
	}
	return (-result);
};

void printProbArray(probArray a, int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int checkProbArray(probArray a, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	if (sum == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

probArray readProbArray(int n) {
	probArray a = new double[n];
	cout << "Введите вероятности" << endl;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (checkProbArray(a, n)) {
		return a;
	}
	else {
		cout << "Сумма введенных вероятностей не равна 1!" << endl;
		//exit(1);
	}
}

void readMatr(double** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
}

void printMatr(double** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void transToUn(double** a, probArray prob, int n, int mode, double** un) {
	if (mode == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				un[i][j] = a[i][j] * prob[i];
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				un[i][j] = a[i][j] * prob[j];
			}
		}
	}
}

void transFromUn(double** un, double** ab, double** ba, int n, int m, probArray sumsA, probArray sumsB) {
	for (int i = 0; i < n; i++) {
		sumsA[i] = 0;
		sumsB[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sumsA[i] += un[i][j];
			sumsB[i] += un[j][i];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ba[i][j] = un[i][j] / sumsA[i];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ab[i][j] = un[i][j] / sumsB[j];
		}
	}
	cout << "P(A/B):" << endl;
	printMatr(ab, n, n);
	cout << endl;
	cout << "P(B/A):" << endl;
	printMatr(ba, n, n);
	cout << endl;
	cout << "P(A;B):" << endl;
	printMatr(un, n, n);
	cout << endl;
	double hab = 0, hba = 0, hun = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (ab[i][j]) {
				hab += un[i][j] * log2(ab[i][j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (ba[i][j]) {
				hba += un[i][j] * log2(ba[i][j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (un[i][j]) {
				hun += un[i][j] * log2(un[i][j]);
			}
		}
	}
	double ha = entropyShen(sumsA, n);
	double hb = entropyShen(sumsB, n);
	cout << "p(A):" << endl;
	printProbArray(sumsA, n);
	cout << "p(B):" << endl;
	printProbArray(sumsB, n);
	hab = -hab;
	hba = -hba;
	hun = -hun;
	//cout << hab << "  = H(A/B), " << hba << " = H(B/A), " << hun << " = H(A; B);" << endl;
	//cout << ha << "= H(A), " << hb << "= H(B), " << ha + hb - hun << " = I;" << endl;
	cout << "Совместная энтропия = " << hun << endl;
	cout << "Условная энтропия СВ А при условии В = " << hab << endl;
	cout << "Условная энтропия СВ B при условии A = " << hba << endl;
	cout << "Энтропия СВ А = " << ha << endl;
	cout << "Энтропия СВ В = " << hb << endl;
	cout << "Кол-во взаимной информации I = " << ha + hb - hun << endl;
}
