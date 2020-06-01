// udpServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

typedef struct _thread_arg {
	struct sockaddr_in adr;
	int data;
} thread_arg;

DWORD WINAPI sendEcho(LPVOID arg) {
	printf("Получен пакет от клиента: %d, отправляем ответ...\n", ((thread_arg*)arg)->data);
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR) {
		perror("Ошибка открытия сокета\n");
		return 1;
	};
	int result = sendto(sock, (char*)(&((thread_arg*)arg)->data), sizeof(int), 0, (SOCKADDR*)&((thread_arg*)arg)->adr, sizeof(((thread_arg*)arg)->adr));
	if (result == SOCKET_ERROR) {
		printf("Ошибка при отправке ответа. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
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
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
	printf("\nТип сокета: UDP; Порт сокета: %hu; Адрес сокета: %s\n", port, inet_ntoa(address.sin_addr));
	if (bind(sock, (SOCKADDR*)&address, sizeof(address)) < 0) {
		printf("Ошибка при назначении сокету адрес! Код ошибки: %d\n", WSAGetLastError());
		return 2;
	};
	printf("Ожидаем пакет от клиента...\n");
	int data;
	while (1) {
		struct sockaddr_in senderAdress;
		int senderAdressSize = sizeof(senderAdress);
		int result = recvfrom(sock, (char*)(&data), sizeof(int), 0, (SOCKADDR*)&senderAdress, &senderAdressSize );
		if (result == SOCKET_ERROR) {
			closesocket(sock);
			WSACleanup();
			return 1;
		}
		else {
			thread_arg arg;
			arg.data = data;
			arg.adr = senderAdress;
			HANDLE thread = CreateThread(NULL, 0, sendEcho, &arg, 0, NULL);
		};
	};
	return 0;
}