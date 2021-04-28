#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <limits>
#include <windows.h>

/*Один поток удаляет случайное число из текста, а другой поток заносит в
текст символьное представление случайных чисел. Произвести
синхронный вывод при каждой итерации. Показать выполнение работы
программы в синхронном и асинхронном режимах.*/
using namespace std;
class Thread {
	mutex& m;
	bool sync;
	string& text;
	virtual void f() = 0;
public:
	Thread (mutex& m, bool sync, string& text) : m(m), sync(sync), text(text) {};
	void lockMutex() {
		this->m.lock();
	}
	void unlockMutex() {
		this->m.unlock();
	}
	bool getSync() {
		return this->sync;
	}
	string& getText() {
		return this->text;
	}
	void operator()() {
		this->f();
	}
};

class DelThread : public Thread {
	void f() {
		while (1) {
			if (this->getSync())
				this->lockMutex();
			unsigned tmp = rand() % this->getText().length();
			this->getText().erase(tmp, tmp);
			if (this->getSync())
				this->unlockMutex();
		}

	}
public:
	DelThread(std::mutex& m, bool sync, std::string& text) : Thread(m, sync, text) {};
};

class AddThread : public Thread {
	void f() {
		while (1) {
			if (this->getSync())
				this->lockMutex();
			char tmp = (rand() % 127) + 32; //символ от пробела до ~
			//this->getText()[rand() % this->getText().length()] = tmp;
			this->getText() += tmp;
			if (this->getSync())
				this->unlockMutex();
		}

	}
public:
	AddThread(std::mutex& m, bool sync, std::string& text) : Thread(m, sync, text) {};
};

class OutThread : public Thread {
	void f() {
		while (1) {
			this->lockMutex();
			cout << this->getText() << endl;
			this->unlockMutex();
			std::this_thread::sleep_for(2s);
		}
	}
public:
	OutThread(std::mutex& m, bool sync, std::string& text) : Thread(m, sync, text) {};
};

int main() {
	setlocale(LC_ALL, "RUS");
	mutex m;	
	string text = "test";
	bool sync = true;
	AddThread at(ref(m), sync, ref(text));
	DelThread dt(ref(m), sync, ref(text));
	OutThread ot(ref(m), sync, ref(text));
	thread th1(at);
	thread th2(dt);
	thread th3(ot);
	th1.detach();
	th2.detach();
	th3.join();
	return 0;
}