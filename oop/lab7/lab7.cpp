#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <stack>
#include <exception>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class MyException : std::exception {
public:
	virtual const char* what() const throw() override = 0;
};

class MyEmptyStackException : public MyException {
public:
	MyEmptyStackException() : MyException() {};
	const char* what() const throw() {
		char* str = new char[80];
		sprintf(str, "Stack is empty!");
		return str;
	}
};

class MyFullStackException : public MyException {
public:
	MyFullStackException() : MyException() {};
	const char* what() const throw () {
		char* str = new char[80];
		sprintf(str, "Stack is full!");
		return str;
	}
};

class MyAbstractException : public MyException {
public:
	MyAbstractException() : MyException() {};
	const char* what() const throw () {
		char* str = new char[80];
		sprintf(str, "Abstract element!");
		return str;
	}
};

class Product_ {
	string name;
	int price;
public:
	Product_(string name, int price) :name(name), price(price) {};
	~Product_() {};
	virtual void setProduct(string n, int pr) {
		name = n;
		price = pr;
	}
	virtual void printProduct() {
		cout << name << ' ' << price << ' ';
	}
};

class Product : public Product_ {
	int weight;
public:
	Product(string name, int price, int weight) : weight(weight), Product_(name, price) {};
	~Product() {};
	void setProduct(string n, int pr, int w) {
		Product_::setProduct(n, pr);
		weight = w;
	}
	void printProduct() {
		Product_::printProduct();
		cout << weight << endl;
	}
};

struct node {
	Product_* el;
	node* p; 
};

class ProdStack {
	node* top;
public:
	ProdStack(): top(NULL) {};
	~ProdStack() {
		delete[] top;
	};
	bool isEmpty() {
		if (top) return false; else return true;
	}

	void put(Product_* e) {
		node* t;
		if (std::is_abstract<Product_>::value) {
			throw MyAbstractException();
		}
		try {
			node* t = new node;
		}
		catch (std::bad_alloc) {
			throw MyFullStackException();
		}
			t->el = e;
			t->p = top;
			top = t;
	};

	Product_ get() {
		if (!isEmpty()) {
			Product_* e = top->el;
			node* pv = top;
			top = top->p;
			delete pv;
			return *e;
		}
	};
	
	void printStack() {
		Product_* a = new Product("", 0, 0);
		while (top) {
			*a = get();
			a->printProduct();
		}
	}
};

int main() {}

/*Разработать абстрактный класс “продукт”, разработать конкретный класс продукт. Разработать класс, реализующий стек для хранения
указателей объектов. Предусмотреть обработку следующих исключительных ситуаций:
стек пуст, +
стек переполнен, +
невозможно добавить элемент из-за отсутствия экземпляра класса.*/


