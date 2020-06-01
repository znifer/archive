// udpclient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctime>

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
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR) {
		perror("Ошибка создания сокета!\n");
		return 1;
	};
	printf("Сокет успешно создан!\n");
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	unsigned short port = 0x4444;
	address.sin_port = htons(port);
	char addressStr[] = "127.0.0.1";
	address.sin_addr.s_addr = inet_addr(addressStr);

	printf("\nТип сокета: UDP; Порт сокета: %hu; Адрес сокета: %s\n", port, addressStr);
	printf("Нажмите любую кнопку...\n");
	getchar();
	getchar();
	printf("Отправляем идентификационный пакет серверу\n");
	printf("Отправляем число: %d\n", data);
	int result = sendto(sock, (char*)(&data), sizeof(int), 0, (SOCKADDR*)&addressStr, sizeof(addressStr)); 
	if (result == SOCKET_ERROR) {
		printf("\nПроизошла ошибка при отправке. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	printf("Ожидаем ответ от сервера\n");
	int echo;
	struct sockaddr_in senderAdress;
	int senderAdress_size = sizeof(senderAdress);

	result = recvfrom(sock, (char*)(&echo), sizeof(int), 0, (SOCKADDR*)&senderAdress, &senderAdress_size);
	if (result == SOCKET_ERROR) {
		printf("Ошибка при получении ответа. Код ошибки: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	};
	printf("Получен ответ: %d\n", echo);
	return 0;
}