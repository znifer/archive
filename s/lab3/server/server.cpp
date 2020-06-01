// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

typedef struct _threadArg {
	struct sockaddr_in adr;
	int data;
} threadArg;

DWORD WINAPI sendEcho(LPVOID arg) {
	printf("\nПолучен ответ от клиента\n");
	printf("Создаем поток для ответа\n");
	printf("Полученный номер: %d\n", ((threadArg*)arg)->data);
	printf("Отправляем ответ....\n");
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == SOCKET_ERROR) {
		perror("Ошибка создания сокета\n");
		return 1;
	};
	int ret_val = sendto(sock, (char*)(&((threadArg*)arg)->data), sizeof(int), 0, (SOCKADDR*)&((threadArg*)arg)->adr, sizeof(((threadArg*)arg)->adr));
	if (ret_val == SOCKET_ERROR) {
		printf("Произошла ошибка при отправке. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	printf("Закрываем поток...\n");
	closesocket(sock);
	return 0;
}

void intHandler(int dummy) {
	exit(0);
}

int main() {
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, intHandler);
	WSADATA wsaData = { 0 };
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == SOCKET_ERROR) {
		perror("Ошибка создания сокета\n");
		return 1;
	};
	printf("Сокет создан успешно!\n");
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	unsigned short port = 0x4444;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("\nТип сокета: IP; Адрес сокета: %s\n", inet_ntoa(address.sin_addr));
	if (bind(sock, (SOCKADDR*)&address, sizeof(address)) < 0) {
		return 2;
	};

	printf("Ожидаем пакет от клиента...\n");
	int receivedData;
	while (1) {
		struct sockaddr_in senderAddress;
		int senderAddressSize = sizeof(senderAddress);
		int ret_val = recvfrom(sock, (char*)(&receivedData), sizeof(int), 0, (SOCKADDR*)&senderAddress, &senderAddressSize);
		if (ret_val == SOCKET_ERROR) {
			wprintf(L"Ошибка при получении пакета! Код ошибки: %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return 1;
		}
		else {
			threadArg arg;
			arg.data = receivedData;
			arg.adr = senderAddress;
			HANDLE thread = CreateThread(NULL, 0, sendEcho, &arg, 0, NULL);
		};
	};
	return 0;
}