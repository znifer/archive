// tcpServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef struct _threadArg {
	struct sockaddr_in adr;
	int data;
} threadArg;

DWORD WINAPI sendEcho(LPVOID arg) {
	SOCKET ClientSocket = (*(SOCKET*)arg);
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	int iSendResult;
	printf("Установка соединения с клиентом\n");
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Получен пакет: %d\n", ((int*)recvbuf)[0]);
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("Ошибка отправки! Код ошибки: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Отправляем ответ клиенту...\n");
		}
		else if (iResult == 0)
			printf("Закрываем подключение...\n");
		else {
			printf("Ошибка отправки! Код ошибки: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	free(arg);
}

void intHandler(int dummy) {
	exit(0);
}


int __cdecl main(void){
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, intHandler);
	WSADATA wsaData;
	int iResult;
	SOCKET listenSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Ошибка инициализации WSA! Код ошибки: %d\n", iResult);
		return 1;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("Ошибка при получении адреса и порта! Код ошибки: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		printf("Ошибка создания сокета! Код ошибки: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	printf("Сокет создан успешно\n");
	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("Сокет создан успешно!\n");
	printf("Тип сокета: TCP; Порт сокета: %hu; Адрес сокета: 127.0.0.1\n", DEFAULT_PORT);
	freeaddrinfo(result);
	while (1) {
		iResult = listen(listenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}
		SOCKET* ClientSocket = new SOCKET;
		(*ClientSocket) = accept(listenSocket, NULL, NULL);
		if (*ClientSocket == INVALID_SOCKET) {
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}
		HANDLE thread = CreateThread(NULL, 0, sendEcho, ClientSocket, 0, NULL);
	}
	closesocket(listenSocket);
	WSACleanup();
	return 0;
}