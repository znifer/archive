/*Один поток выполняет подсчет количества гласных букв в тексте, а
другой вставляет случайным образом гласную букву.
Произвести синхронный вывод при каждой итерации. Показать
выполнение работы программы в синхронном и асинхронном режимах..*/

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

class Thread {
private:
	CONST HANDLE hMutex;
	bool sync;
	string& text;
	int& count;
public:
	friend void startThread(Thread&);
	virtual void f() = 0;
	Thread(CONST HANDLE hMutex, bool sync, string& text, int& count) : hMutex(hMutex), sync(sync), text(text), count(count) {};
	void lockMutex() { 
		WaitForSingleObject(this->hMutex, INFINITE); 
	}
	void unlockMutex() { 
		ReleaseMutex(this->hMutex); 
	}
	bool getSync() { 
		return this->sync; 
	}
	string& getText() { 
		return this->text; 
	}
	int& getCount() {
		return this->count;
	}
};

class CountThread : public Thread {
	void f() {
		char a[6] = { 'a', 'o', 'i', 'e', 'y', 'u' };
		while (1) {
			this->getCount() = 0;
			if (this->getSync()) this->lockMutex();
			for (int i = 0; i < this->getText().length(); i++) {
				for (int j = 0; j < 6; j++) {
					if (this->getText()[i] == a[j]) this->getCount()++;
				}
			}
			if (this->getSync()) this->unlockMutex();
			Sleep(500);
		}
	};
public:
	CountThread(CONST HANDLE hMutex, bool sync, string& text, int& count) : Thread(hMutex, sync, text, count) {};
};


class AddThread : public Thread {
	void f() {
		char a[6] = { 'a', 'o', 'i', 'e', 'y', 'u' };
		while (1) {
			if (this->getSync()) this->lockMutex();
			if (rand() % 2 == 1) {
				//this->getText() += a[rand() % 6];
				int tmp = rand() % this->getText().length();
				char c = a[rand() % 6];
				this->getText().insert(tmp, c);
			}
			else {
				for (int i = 0; i < this->getText().length(); i++) {
					for (int j = 0; j < 6; j++) {
						if (this->getText()[i] == a[j]) {
							this->getText().erase(i, i);
						}
					}
				}
			}

			if (this->getSync()) this->unlockMutex();
			Sleep(500);
		}
	};
public:
	AddThread(CONST HANDLE hMutex, bool sync, string& text, int& count) : Thread(hMutex, sync, text, count) {};

};

class OutThread : public Thread {
	void f() {
		while (1) {
			this->lockMutex();
			cout << "Количество гласных в тексте:" << this->getCount() << endl;
			cout << this->getText() << endl;
			this->unlockMutex();
			Sleep(500);
		}
	};
public:
	OutThread(CONST HANDLE hMutex, bool sync, std::string& text, int& count) : Thread(hMutex, sync, text, count) {};
};

DWORD WINAPI start_thread(CONST LPVOID lpParam) {
	((Thread*)lpParam)->f();
	ExitThread(0);
};

int main(){
	setlocale(LC_ALL, "RUS");
	string text;
	int count = 0;
	bool sync = true;
	cout << "Введите текст" << endl;
	cin >> text;
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	CountThread ct(hMutex, sync, ref(text), ref(count));
	AddThread at(hMutex, sync, ref(text), ref(count));
	OutThread ot(hMutex, sync, ref(text), ref(count));
	HANDLE hThreads[3];
	hThreads[0] = CreateThread(NULL, 0, &start_thread, &ct, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, &start_thread, &at, 0, NULL);
	hThreads[2] = CreateThread(NULL, 0, &start_thread, &ot, 0, NULL);
	WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);
	CloseHandle(hThreads[2]);
	CloseHandle(hMutex);
	ExitProcess(0);
	return 0;
}