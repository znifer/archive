/*Разработать программное обеспечение для решения следующей задачи:
загрузка формата *.obj в программу,
обработка объекта путем добавления цвета отображения различных элементов объекта.
Вывести полученные списки на экран.
Выполнить сложение *.obj объектов, путем удаления лишних точек, лежащих внутри новой поверхности.
Организовать сортировку точек, треугольников.
Класс для хранения *.obj представляет собой набор из двух list. Один точки, другой треугольники.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class Colour {
	int _r, _g, _b;
public:
	
	Colour() : _r(0), _g(0), _b(0) {};
	Colour(int r, int g, int b) : _r(r), _g(g), _b(b) {};
	void set(int r, int g, int b);
	void print();
};

class Point {
	double _x, _y, _z;
public:
	Point() : _x(0), _y(0), _z(0) {};
	Point(double x, double y, double z) : _x(x), _y(y), _z(z) {};
	void set(double x, double y, double z);
	double x() { return this->_x; }
	double y() { return this->_y; }
	double z() { return this->_z; }
	void print();
	bool operator < (Point t) {
		return (_x < t._x && _y < t._y && _z < t._z);
	}
	bool operator == (Point t) {
		return (_x == t._x && _y == t._y && _z == t._z);
	}
	Point operator - (Point t) {
		Point res(_x - t._x, _y - t._y, _z - t._z);
		return res;
	}
};

class Triangle {
	list <Point> triangle;
	Colour col;
	int a, b, c;
public:
	Triangle() : col() {};
	Triangle(Point a1, Point b1, Point c1): col(){
		triangle.push_back(a1);
		triangle.push_back(b1);
		triangle.push_back(c1);
	};
	~Triangle() {};
	void set();
	void set(Point a1, Point b1, Point c1);
	void set(int a1, int b1, int c1) {a = a1; b = b1; c = c1;}
	list <Point> get() { return triangle;}
	void print();
	double getTriangleSquare();
	bool operator < (Triangle t) {
		return (getTriangleSquare() < t.getTriangleSquare());
	}
};
 
class Vector {
	Point vector, _s, _f;
public:
	Vector():vector (0, 0, 0){};
	void set(double a, double b, double c) {
		vector.set(a, b, c);
	}
	void set(Point p1, Point p2) { vector.set(p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z());  _s = p1; _f = p2; }
	Point v() { return this->vector; }
	Point s() { return this->_s; }
	Point f() { return this->_f; }
	void normalize() {
		double m = sqrt(pow(vector.x(), 2) + pow(vector.y(), 2) + pow(vector.z(), 2));
		set(vector.x() / m, vector.y() / m, vector.z() / m);
	};
	//Векторное произведение
	Vector operator + (Vector v){
		Vector tmp;
		tmp.set(this->vector.y() * v.vector.z() - v.vector.y() * this->vector.z(), this->vector.z() * v.vector.x() - v.vector.z() * this->vector.x(), this->vector.x() * v.vector.y() - v.vector.x() * this->vector.y()
		);
		return tmp;
	}
	//скалярное произведение
	double operator * (Vector v) {
		return (this->vector.x() * v.vector.x() + this->vector.y() * v.vector.y() + this->vector.z() * v.vector.z());
	}
};

class Object {
	list <Point> points;
	list <Vector> vectors;
	list <Triangle> triangles;
public:
	Object() {};
	~Object() {};
	void setPoints(list <Point> newPoints) { points = newPoints; }
	void sortTriangles();
	void sortPoints();
	//Считывает данные о 3д-модели из файла filename. Будут считаны только данные о точках и полигонах
	bool read(char* filename);
	bool save(char* filename);
	void inputTriangleData(int a, int b, int c, Triangle t);
	bool triangleComparator(Triangle t1, Triangle t2);
	bool pointComparator(Point t1, Point t2);
	void merge();
	bool intersection(Triangle t, Vector v, Point &result);
	void deletePoint(Point p);
	void print();
};

void Colour::set(int r, int g, int b) {
	if (r >= 0 && r <= 255) {
		this->_r = r;
	}
	else {
		cout << "Wrong red colour! Setting default value." << endl;
		this->_r = 0;
	}
	if (g >= 0 && g <= 255) {
		this->_g = g;
	}
	else {
		cout << "Wrong green colour! Setting default value." << endl;
		this->_g = 0;
	}
	if (b >= 0 && b <= 255) {
		this->_b = b;
	}
	else {
		cout << "Wrong green colour! Setting default value." << endl;
		this->_b = 0;
	}

}

void Colour::print() {
	cout << this->_r << " ";
	cout << this->_g << " ";
	cout << this->_b << " ";
	cout << endl;
}

void Point::set(double x, double y, double z) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

void Point::print() {
	cout << x() << " ";
	cout << y() << " ";
	cout << z() << " ";
}

void Triangle::set() {
	Point tmp(0, 0, 0);
	triangle.push_back(tmp);
	triangle.push_back(tmp);
	triangle.push_back(tmp);
}

void Triangle::set(Point a1, Point b1, Point c1) {
	triangle.push_back(a1);
	triangle.push_back(b1);
	triangle.push_back(c1);
}

void Triangle::print() {
	Point tmp(0, 0, 0);
	list<Point>::iterator i;
	i = triangle.begin();
	tmp = *i;
	tmp.print();
	cout << endl;
}

double Triangle::getTriangleSquare() {
	list <Point>::iterator it = triangle.begin();
	Point a = *it;
	it++;
	Point b = *it;
	it++;
	Point c = *it;
	double A = sqrt(pow(a.x(), 2) + pow(a.y(), 2) + pow(a.z(), 2));
	double B = sqrt(pow(b.x(), 2) + pow(b.y(), 2) + pow(b.z(), 2));
	double C = sqrt(pow(c.x(), 2) + pow(c.y(), 2) + pow(c.z(), 2));
	double p = 0.5 * (A + B + C);
	return sqrt(p * (p - A) * (p - B) * (p - C));
}

void Object::print() {
	list <Point>::iterator pit = points.begin();
	Point tmp(0, 0, 0);
	while (pit != points.end()) {
		tmp = *pit;
		tmp.print();
		cout << endl;
		pit++;
	}
}

bool Object::triangleComparator (Triangle t1, Triangle t2) {
	return (t1 < t2);
}

bool Object::pointComparator(Point t1, Point t2) {
	return (t1 < t2);
}

void Object::sortTriangles() {
	//std::sort(triangles.begin(), triangles.end());
	triangles.sort(triangleComparator);
}

void Object::sortPoints() {
	//std::sort(points.begin(), points.end());
	points.sort(pointComparator);
}

void Object::inputTriangleData(int a, int b, int c, Triangle t) {
	list<Point>::iterator it = points.begin();
	Point a1, b1, c1;
	t.set(a, b, c);
	for (int i = 0; i < a; i++) {
		it++;
	}
	a1 = *it;
	it = points.begin();
	for (int i = 0; i < b; i++) {
		it++;
	}
	b1 = *it;
	it = points.begin();
	for (int i = 0; i < c; i++) {
		it++;
	}
	c1 = *it;
	t.set(a1, b1, c1);
	Vector tmpv;
	tmpv.set(a1, b1);
	vectors.push_back(tmpv);
	tmpv.set(a1, c1);
	vectors.push_back(tmpv);
	tmpv.set(b1, c1);
	vectors.push_back(tmpv);
}

bool Object::read(char* filename) {
	FILE* f = fopen(filename, "r");
	Triangle tmpt;
	Point tmpp;
	char ch, tr[100] = " ";
	double x, y, z;
	int a, b, c;
	if (!f) return false;
	while (!feof(f)) {
		ch = fgetc(f);
		switch (ch) {
		case 'v':
			x = 0; y = 0; z = 0;
			fscanf(f, "%lf %lf %lf\n", &x, &y, &z);
			//cout << x << " " << y << " " << z << endl;
			tmpp.set(x, y, z);
			points.push_back(tmpp);
			fgets(tr, 100, f);
		case 'f':
			fscanf(f, "%i %i %i\n", &a, &b, &c);
			fgets(tr, 100, f);
			inputTriangleData(a - 1, b - 1, c - 1, tmpt);
			triangles.push_back(tmpt);			
		default:
			fgets(tr, 100, f);
		}
	}
	return true;
}

bool Object::save(char* filename) {
	FILE* f;
	if (f = fopen(filename, "w")) return false;
	list <Point>::iterator it;
	Point tmp;
	it = points.begin();
	while (it != points.end()) {
		tmp = *it;
		fprintf(f, "v %lf %lf %lf", tmp.x(), tmp.y(), tmp.z());
	}
	return true;
}

void Object::deletePoint(Point p) {
	list <Point>::iterator it = points.begin();
	list <Point> res;
	int i = 0;
	while (it != points.end()) {
		if (!(p == *it)) {
			res.push_back(*it);
		}
		i++; it++;
	}
	setPoints(res);
}

bool Object::intersection(Triangle t, Vector v, Point &result) {
	Point a, b, c, res;
	res.set(0, 0, 0);
	Vector N, W;
	list <Point>::iterator it = t.get().begin();
	a = *it; it++;
	b = *it; it++;
	c = *it; it++;
	Vector tmp1, tmp2;
	tmp1.set(a, b);
	tmp2.set(a, c);
	N = tmp1 + tmp2;
	N.normalize();
	W.set(v.s(), a);
	double d = W * N;
	W.set(v.s(), v.f());
	double e = N * W;
	if (e != 0.0000) {
		res.set(v.s().x() + W.v().x() * d / e, v.s().y() + W.s().y() * d / e, v.s().y() + W.s().z() * d / e);
		cout << "Intersection!" << endl;
		return true;
	}
	return false;
}

void Object::merge() {
	list <Triangle>::iterator it = triangles.begin();
	list <Vector>::iterator vit = vectors.begin();
	Point res (0, 0, 0);
	while (it != triangles.end()) {
		vit = vectors.begin();
		while (vit != vectors.end()) {
			if (intersection(*it, *vit, res)) {
				deletePoint(res);
				vit++;
			}
		}
	}
}

int main(){
	setlocale(0, "RUS");
	Object t;
	char filename[256] = "test.txt";
	cout << "Reading..." << endl;
	if (!t.read(filename)) { exit(1); }
	cout << "Reading done!" << endl;
	cout << "Sorting points" << endl;
	cout << "Before:" << endl;
	t.print();
	t.sortPoints();
	cout << "After:" << endl;
	t.print();
	cout << "Checking for intersection" << endl;
	t.merge();
	cout << "Saving" << endl;
	t.save(filename);
}