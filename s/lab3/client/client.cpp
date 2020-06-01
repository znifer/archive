// client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock.h>
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

int main() {
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, intHandler);
	time_t t;
	srand((unsigned)time(&t));
	int data = rand();
	WSADATA wsaData = { 0 };
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == SOCKET_ERROR) {
		perror("Ошибка создания сокета\n");
		return 1;
	};
	printf("Сокет успешно создан\n");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	unsigned short port = 0x4444;
	addr.sin_port = htons(port);
	char address[] = "127.0.0.1";
	addr.sin_addr.s_addr = inet_addr(address);
	printf("\nТип сокета: IP; Адрес сокета: %s\n", address);
	printf("Нажмите любую кнопку для начала передачи\n");
	getchar();
	getchar();
	printf("Передача идентификационного пакета на сервер\nОтправляем число: %d\n", data);
	int result = sendto(sock, (char*)(&data), sizeof(int), 0, (SOCKADDR*)&addr, sizeof(addr));
	if (result == SOCKET_ERROR) {
		printf("\nОтправка не удалась. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	printf("Ожидаем ответ от сервера...\n");
	int echo;
	struct sockaddr_in senderAddress;
	int senderAddressSize = sizeof(senderAddress);
	result = recvfrom(sock, (char*)(&echo), sizeof(int), 0, (SOCKADDR*)&senderAddress, &senderAddressSize );
	if (result == SOCKET_ERROR) {
		printf("\nПроизошла ошибка при получении ответа с сервера. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	};
	printf("Полученный ответ: %d\n", echo);
	return 0;
}