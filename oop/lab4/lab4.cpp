#include "pch.h"
#include <iostream>
using namespace std;
class Money {
	int first; //номинал купюр
	int second; //количество купюр

public:
	
	Money(int f, int s) {
		if (f < 0 || s < 0) {
			cout << "Таких денег не бывает" << endl;
			exit(1);
		}
		else {
			first = f;
			second = s;
		}
	}

	void printMoney() {
		cout << "В наличии " << second << " купюр номиналом " << first << endl;
	}

	int enoughMoney(int price) {
		if (first*second < price) {
			return 0;
		}
		else {
			return 1;
		}
	}

	int howManyProd(int price) {
		return ((first * second) % price);
	}
	//сложение
	friend const Money operator+ (const Money &a1, const Money &a2) {
		Money res(0, 0);
		if (a1.first < a2.first) {
			res.second = a1.second + a2.second * (a2.first / a1.first);
			res.first = a1.first;
		}
		else {
			res.second = a2.second + a1.second * (a1.first / a2.first);
			res.first = a2.first;
		}
		return res;
	}
	//префиксный инкремент
	Money& operator++ () {
		int tmp = this->second;
		tmp++;
		this->second = tmp;
		return (*this);
	}
	//сложение с присваиванием
	Money& operator += (const Money &a) {
		Money res(this->first, this->second);
		res.first = res.first + a.first;
		res.second = res.second + a.second;
		this->first = res.first;
		this->second = res.second;
		return (*this);
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	Money a(100, 3);
	Money b(50, 1);
	Money c(5, 0);
	//++c;
	//c = ++c;
	//c += a;
	//c = a +b;
	c.printMoney();
}
