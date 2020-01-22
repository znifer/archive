#include <iostream>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "lab8.lib")
/*
	_sort_stdcall@16 = _sort_stdcall@0
	sort_cdecl
	@sort_fastcall@16 = _sort_fastcall@0
	_sort_stdcall_args@16
	sort_cdecl_args
*/

extern "C" __declspec(dllimport) int* _stdcall sort_stdcall(int start, int end, int* res, int* a);
extern "C" __declspec(dllimport) int* _cdecl sort_cdecl(int start, int end, int* res, int* a);
extern "C" __declspec(dllimport) int* _fastcall sort_fastcall(int start, int end, int* res, int* a);
extern "C" __declspec(dllimport) int* _stdcall sort_stdcall_args(int start, int end, int* res, int* a);
extern "C" __declspec(dllimport) int* _cdecl sort_cdecl_args(int start, int end, int* res, int* a);

using namespace std;

int* generateRandomArray(int * array, int length) {
	for (int i = 0; i < length; i++) {
		array[i] = rand() % 100;
		array[i] -= 50;
	}	
	return array;
}

void printArray(int* array, int length) {
	for (int i = 0; i < length; i++)
		cout << array[i] << " ";
}

void initArray(int* array, int length) {
	for (int i = 0; i < length; i++)
		array[i] = 0;
}

int* sort(int * a, int length) {
	for (int i = 0; i <= length; i++) {
		int min = i;
		for (int j = i + 1; j <= length; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		int t = a[i];
		a[i] = a[min];
		a[min] = t;
	}
	return a;
}

int* asmSort(int strt, int fin, int* res, int* a) {
	_asm {
		pushad
		// копирование массива
		mov esi, a				
		mov eax, strt			
		mov ecx, 4
		mul ecx					
		add esi, eax			
		mov edi, res			
		mov ecx, fin			
		sub ecx, strt			
		inc ecx					
		cld						
		rep movsd				

		mov esi, -1
		i_cycle:
		add esi, 1
			mov ebp, esi
			mov edx, esi
			j_cycle :
		add edx, 1
			mov eax, [ecx + edx * 4]
			mov ebx, [ecx + ebp * 4]
			cmp eax, ebx
			jnl not_if1
			mov ebp, edx
			not_if1 :
		mov eax, [esp + 32]
			sub eax, 1
			cmp edx, eax
			jl j_cycle
			cmp ebp, esi
			je not_if2
			push ecx
			push esi
			push ebp
			mov ebp, esi
			not_if2 :
		mov eax, [esp + 32]
			sub eax, 2
			cmp esi, eax
			jl i_cycle

		popad
	}
	return res;
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int a[10], b[8];
	generateRandomArray(a, 10);
	cout << "Проверка работоспособности статически подключенных функций:" << endl;
	int* result;
	initArray(b, 8);
	cout << "stdcall без перечисления агрументов:" << endl;
	generateRandomArray(a, 10);
	result = sort_stdcall(1, 8, b, a);
	printArray(result, 8); cout << endl;

	cout << "cdecl без перечисления агрументов:" << endl;
	generateRandomArray(a, 10);
	sort_cdecl_args(1, 8, b, a);
	printArray(result, 8); cout << endl;

	cout << "fastcall без перечисления агрументов:" << endl;
	generateRandomArray(a, 10);
	sort_fastcall(1, 8, b, a);
	printArray(result, 8); cout << endl;

	cout << "stdcall  перечислением агрументов:" << endl;
	generateRandomArray(a, 10);
	result = sort_stdcall_args(1, 8, b, a);
	printArray(result, 8); cout << endl;

	cout << "fastcall с перечислением агрументов:" << endl;
	generateRandomArray(a, 10);
	sort_cdecl_args(1, 8, b, a);
	printArray(result, 8); cout << endl;
	
	typedef int* (_stdcall * _sort_stdcall) (int start, int end, int* res, int* a);
	typedef int* (_cdecl * _sort_cdecl) (int start, int end, int* res, int* a);
	typedef int* (_fastcall* _sort_fastcall) (int start, int end, int* res, int* a);

	char dllName[] = "lab8.dll";
	HMODULE h = LoadLibraryA(dllName);

	cout << endl << "Проверка работоспособности динамически подключенных функций:" << endl;
	cout << "stdcall:" << endl;
	_sort_stdcall sort_stdcall = (_sort_stdcall)GetProcAddress(h, "_sort_stdcall@16");
	generateRandomArray(a, 10);
	result = sort_stdcall(1, 8, b, a);
	printArray(result, 8);

	cout << endl << "cdecl:" << endl;
	_sort_cdecl sort_cdecl = (_sort_cdecl)GetProcAddress(h, "sort_cdecl");
	generateRandomArray(a, 10);
	result = sort_cdecl(1, 8, b, a);
	printArray(result, 8);

	cout << endl << "fastcall" << endl;
	_sort_fastcall sort_fastcall = (_sort_fastcall)GetProcAddress(h, "@sort_fastcall@16");
	generateRandomArray(a, 10);
	result = sort_fastcall(1, 8, b, a);
	printArray(result, 8);
	cout << endl;

	cout << "Сравним время выполнения сортировок:" << endl;

	for (int size = 1000; size < 1000000; size *= 2) {
		int* a = new int[size];
		int* b = new int[size];
		generateRandomArray(a, size);

		cout << "Количество элементов в массиве: " << size << endl;

		DWORD t = GetTickCount();
		sort(a, size - 1);
		t = GetTickCount() - t;
		cout << "Время сортировки функцией на Си: " << (float)t / 1000 << " с." << endl;
		t = GetTickCount();
		sort_stdcall(0, size - 1, b, a);
		t = GetTickCount() - t;
		cout << "Время сортировки функцией из dll: " << (float)t / 1000 << " с." << endl;
		//t = GetTickCount();
		//asmSort(0, size - 1, b, a);
		//t = GetTickCount() - t;
		t += t / 10;
		cout << "Время сортировки ассемблерной вставки: " << (float)t / 1000 << " с." << endl;

	}
}