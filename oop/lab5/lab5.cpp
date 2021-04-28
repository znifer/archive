#include "pch.h"
#include <iostream>
#include <string>
#include <locale>
using namespace std;

class Time{
	int hour;
	int minute;
	int second;
public:
	Time(int h, int m, int s):hour(h), minute(m), second(s) {};

	void setTime(int h, int m, int s) {
		hour = h;
		minute = m;
		second = s;
	
	};
	~Time() {};
	void printTime() {
		cout << "H:M:S: " << hour << ":" << minute << ":" << second << endl;
	}
	int timeCmp(unsigned h, unsigned m, unsigned s) {
		int d1 = hour * 3600 + minute * 60 + second;
		int d2 = h * 3600 + m * 60 + s;
		return (d1 < d2);
	}
};

class Date: public Time {
	int year;
	int month;
	int day;
public:
	Date(int y, int mo, int d, int h, int m, int s):year(y), month (mo), day (d), Time(h, m, s) {};

	void setDate(int d, int y, int m){
		year = d;
		month = m;
		day = d;
	};

	~Date() {};

	void printDate() {
		cout << "D:M:Y: " << day << ":" << month << ":" << year << endl;
	}

	int dateComp(Date* a){
		int y = a->year, m = a->month, d = a->day;
		int d1 = year * 365 + month * 30 + day;
		int d2 = y * 365 + m * 30 + d;
		return (d1 < d2);
	}
};

class Software {
	string name;
	string devby;
	Date *dateOfInstall;
public:
	Software(string n, string db, int y, int mo, int d, int h, int m, int s) : 
		name(n), 
		devby(db) {
		dateOfInstall = new Date(y, mo, d, h, m, s);
	};

	~Software() {
		delete dateOfInstall;
	};

	virtual void printSoft() {
		cout << name << ", разработано усилиями " << devby;
		cout << ", установлено: ";
		dateOfInstall->printDate();
		cout << " ";
		dateOfInstall->printTime();
		cout << endl;
	};
	virtual int isSoftUsable(Date d) = 0;
};

class Free : public Software {
	string license;
public:
	Free(string n, string db, string lic, int y, int mo, int d, int h, int m, int s): 
		license(lic), 
		Software(n, db, y, mo, d, h, m, s) {};

	~Free() {};

	int isSoftUsable(Date* d) {
		cout << "Данное ПО бесплатно, пользуйтесь сколько угодно!" << endl;
		return 1;
	};

	void printSoft() {
		Software::printSoft();
		cout << "Распространяется по лицензии " << license << endl;
	};
};

class Shareware : public Software {
	Date *trialTo;
public:
	Shareware(string n, string db, int y, int mo, int d, int h, int m, int s, int y1, int mo1, int d1, int h1, int m1, int s1) : Software(n, db, y, mo, d, h, m, s){
		trialTo = new Date(y1, mo1, d1, h1, m1, s1);
	};

	~Shareware() {
		delete trialTo;
	};

	int isSoftUsable(Date* a) {
		if (trialTo->dateComp(a)) return 1; else return 0;
	};

	void printSoft() {
		Software::printSoft();
		cout << ", пробный период до:";
		trialTo->printDate();
		cout << " ";
		trialTo->printTime();
		cout << endl;
	};
};

class Commercial : public Software {
public:
	Date *avaliableTo;
	unsigned price;
	Commercial(string n, string db, int y, int mo, int d, int h, int m, int s, int y1, int mo1, int d1, int h1, int m1, int s1, int pr) : Software(n, db, y, mo, d, h, m, s), price(pr) {
		avaliableTo = new Date(y1, mo1, d1, h1, m1, s1);
	};

	~Commercial() {
		delete avaliableTo;
	};

	int isSoftUsable(Date* a) {
		if (avaliableTo->dateComp(a)) return 1; else return 0;
	};

	void printSoft() {
		Software::printSoft();
		cout << ", лицензия активна до:";
		avaliableTo->printDate();
		cout << " ";
		avaliableTo->printTime();
	};
};

int main() {
	setlocale(LC_ALL, "Rus");
	int n, mode;
	int a, b, c, d, e, f, a1, b1, c1, d1, e1, f1, pr;
	string nam, devb, license;
	cout << "n?" << endl;
	cin >> n;
	Software **database = new Software *[n];
	cout << "Текущая дата?" << endl;
	cin >> a >> b >> c >> d >> e >> f;
	Date *cur = new Date(a, b, c, d, e, f);
	for (int i = 0; i < n; i++) {
		cout << " 0 1 2 ?? " << endl;
		cin >> mode;
		switch (mode) {
		case (0):
			cout << "Введите название ПО и разработчика, а так же тип лицензии" << endl;
			cin >> nam >> devb >> license;
			cout << "Введите дату и время установки ПО" << endl;
			cin >> a >> b >> c >> d >> e >> f;
			database[i] = new Free(nam, devb, license, a, b, c, d, e, f);
			break;
		case (1):
			cout << "Введите название ПО и разработчика" << endl;
			cin >> nam >> devb;
			cout << "Введите дату и время установки ПО" << endl;
			cin >> a >> b >> c >> d >> e >> f;
			cout << "Пробный период до:";
			cin >> a1 >> b1 >> c1 >> d1 >> e1 >> f1;
			database[i] = new Shareware(nam, devb, a, b, c, d, e, f, a1, b1, c1, d1, e1, f1);
			//database[i].setSSoft();
			break;
		case (2):
			cout << "Введите название ПО и разработчика" << endl;
			cin >> nam >> devb;
			cout << "Введите дату и время установки ПО" << endl;
			cin >> a >> b >> c >> d >> e >> f;
			cout << "Лицензия активна до:";
			cin >> a1 >> b1 >> c1 >> d1 >> e1 >> f1;
			cout << "Стоимость ПО:" << endl;
			cin >> pr;
			database[i] = new Commercial(nam, devb, a, b, c, d, e, f, a1, b1, c1, d1, e1, f1, pr);
			//database[i].setCSoft();
			break;
		default:
			cout << "Таких программ не бывает! Попробуйте ввести нормально" << endl;
			i--;
			break;
		}

		for (int i = 0; i < n; i++) {
			if (database[i]->isSoftUsable(*cur)) {
				database[i]->printSoft();
			}
		}
		for (int i = 0; i < n; i++) {
			delete database[i];
		}
	}
}