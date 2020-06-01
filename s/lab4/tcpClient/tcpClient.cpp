// tcpClient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

void intHandler(int dummy) {
	exit(0);
}

int __cdecl main(int argc, char** argv){
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, intHandler);
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	time_t t;
	srand((unsigned)time(&t));
	int data = rand();
	char sendbuf[DEFAULT_BUFLEN];
	((int*)sendbuf)[0] = data;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Ошибка инициализации WSA! Код ошибки: %d\n", iResult);
		return 1;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	char address[] = "127.0.0.1";

	iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("Ошибка получении информации об адресе! Код ошибки: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("Ошибка создания сокета! Код ошибки: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		printf("Сокет создан успешно!\n");
		printf("Тип сокета: TCP; Порт сокета: %hu; Адрес сокета: %s\n", DEFAULT_PORT, address);
		printf("Нажмите любую кнопку...\n");
		getchar();
		printf("Отправляем идентификационный пакет серверу\n");
		printf("Отправляем пакет: %d\n", ((int*)sendbuf)[0]);
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Не удалось подключится к серверу!!\n");
		WSACleanup();
		return 1;
	}
	iResult = send(ConnectSocket, sendbuf, sizeof(int), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Ошибка при отправке! Код ошибки: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("От сервера получен пакет: %d\n", ((int*)recvbuf)[0]);
		else if (iResult == 0)
			printf("Подключение закрыто!\n");
		else
			printf("Ошибка при получении ответа! Код ошики: %d\n", WSAGetLastError());
	} while (iResult > 0);
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}