#include <iostream>
using namespace std;

template <class T>
class Set {
	T* elements;
	int size;
public:
	Set(int size);
	~Set();
	void readSet();				//Вводит элементы мн-ва
	void printSet();			//Выводит элементы множества
	void setEmpty();			//Удаляет все элементы множества
	void addEl(T el);			//Добавить элемент el в множество elements
	void removeEl(T el);		//Удалить элемент el из множества elements
	bool contains(T el);		//Предикат: содержит ли множество элемент el
	bool isEmpty();				//Предикат: пусто ли множество
	
	//объединение
	template <class T>
	Set <T> operator + (Set <T> t1) {
		T* res = new Set <T>(this->size);
		for (int i = 0; i < this->size; i++) {
			res.elements = this->elements[i];
		}
		for (int i = 0; i <  t1.size; i++) {
			if (!this->contains(t1.elements[i])) {
				res.addEl(t1.elements[i]);
			}
		}
		return res;
	};

	//разность
	template <class T>
	Set <T> operator - (Set <T> t1) {
		T* res = new Set <T>(0);
		res = this;
		for (int i = 0; i < this->size; i++) {
			if (!t1.contains(this->elements[i])) {
				res.addEl(this->elements[i]);
			}
		}
		return res;
	};

	//пересечение
	template <class T>
	Set <T> operator * (Set <T> t1) {
		T* res = new Set <T>(0);
		for (int i = 0; i < this->size; i++) {
			if (t1.contains(this->elements[i])) {
				res.addEl(this->elements[i]);
			}
		}
		return res;
	};
};

template <class T>
Set <T>::Set(int size):size(size) {
	elements = new T[size];
	for (int i = 0; i < size; i++) {
		elements[i] = NULL;
	}
}

template <class T>
Set<T>::~Set() {
	delete elements;
}

template <class T>
void Set<T>::readSet() {
	for (int i = 0; i < size; i++) {
		cin >> elements[i];
	}
}

template <class T>
void Set<T>::printSet() {
	for (int i = 0; i < size; i++) {
		cout << elements[i] << " ";
	}
	cout << endl;
}

template <class T>
void Set<T>::setEmpty() {
	for (int i = 0; i < size; i++) {
		delete[]elements[i];
	}
	size = 0;
}

template <class T>
void Set<T>::addEl(T el) {
	this->size ++;
	T *tmp = new T[size];
	tmp = elements;
	tmp[size] = el;
	elements = new T[size];
	elements = tmp;
}

template <class T>
void Set<T>::removeEl(T el) {
	for (int i = 0; i < size; i++) {
		if (el == elements[i]) {
			if (i != size) {
				swap(elements[i], elements[size]);
			}
			delete elements[i];
			size--;
			return;
		}
	}
}

template <class T>
bool Set<T>::contains(T el) {
	for (int i = 0; i < size; i++) {
		if (el == elements[i]) {
			return true;
		}
	}
	return false;
}

template <class T>
bool Set<T>::isEmpty() {
	if (size != 0 && elements[0] != NULL) {
		return false;
	}
	return true;
}

int main(){
	setlocale(0, "Rus");
	Set <int> t1 = Set <int> (3);
	t1.readSet();
	t1.printSet();
	t1.addEl(5);
	t1.printSet();
	 

}