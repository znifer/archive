
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sstream>
#include <fstream>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "http"

DWORD WINAPI ServeClient(LPVOID arg) {
	SOCKET ClientSocket = (*(SOCKET*)arg);
	char request_buffer[DEFAULT_BUFLEN];
	int request_buffer_len = DEFAULT_BUFLEN;
	int iResult;
	int iSendResult;
	char method[DEFAULT_BUFLEN];
	char URI[DEFAULT_BUFLEN];
	char host[DEFAULT_BUFLEN];
	int ver_h = 0;
	int ver_l = 0;
	iResult = recv(ClientSocket, request_buffer, request_buffer_len, 0);
	if (iResult > 0) {
		request_buffer[iResult] = '\0';
		sscanf(request_buffer, "%s %s HTTP/%i.%i\nHost: %s", method, URI, &ver_h, &ver_l, host);
		printf("Клиент запросил метод %s для URI %s (HTTP ver %i.%i)\nХост: %s\n", method, URI, ver_h, ver_l, host);
	}
	else if (iResult == 0)
		printf("Закрываем подключение\n");
	else {
		printf("Ошибка!");
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	char file_name[DEFAULT_BUFLEN];
	if (strcmp(URI, "/") == 0) {
		strcpy(file_name, "index.html");
	}
	else {
		strcpy(file_name, URI + 1);
	}
	std::ifstream file;
	file.open(file_name, std::ifstream::in);
	std::stringstream response; 
	std::stringstream responseBody;
	int responseCode = 0;
	if (strcmp(method, "GET") && strcmp(method, "HEAD")) {
		responseCode = 501;
		responseBody
			<< "<!DOCTYPE HTML>"
			<< "<html>"
			<< "<head>"
			<< "<title>501 Not Implemented</title>"
			<< "</head>"
			<< "<body>"
			<< "<h1>Not Implemented</h1>"
			<< "<p>This request can not be processed by this server</p>"
			<< "</body>"
			<< "</html>";
		response << "HTTP/1.1 501 Not Implemented\r\n"
			<< "Version: HTTP/1.1\r\n"
			<< "Content-Type: text/html; charset=utf-8\r\n"
			<< "Content-Length: " << responseBody.str().length()
			<< "\r\n\r\n"
			<< responseBody.str();
	}
	else {
		if (file.is_open()) {
			responseCode = 200;
			char buffer[DEFAULT_BUFLEN];
			while (file.getline(buffer, DEFAULT_BUFLEN))
				responseBody << buffer;
			response << "HTTP/1.1 200 OK\r\n" << "Version: HTTP/1.1\r\n" << "Content-Type: text/html; charset=utf-8\r\n" << "Content-Length: " << responseBody.str().length() << "\r\n\r\n";
			if (strcmp(method, "GET") == 0) {
				response << responseBody.str();
			}

			file.close();
		}
		else {
			responseCode = 404;
			responseBody << "<!DOCTYPE HTML>" << "<html>" << "<head>" << "<title>404 Not Found</title>" << "</head>" << "<body>" << "<h1>NE MOGU PO PRICHINE 404 (NET TAKOGO!)</h1>" << "<p></p>" << "</body>" << "</html>";
			response << "HTTP/1.1 404 Not Found\r\n" << "Version: HTTP/1.1\r\n" << "Content-Type: text/html; charset=utf-8\r\n" << "Content-Length: " << responseBody.str().length() << "\r\n\r\n" << responseBody.str();
		}
	}
	printf("Отправляем ответ с кодом %i\n", responseCode);
	iSendResult = send(ClientSocket, response.str().c_str(), response.str().length(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Отправка не удалась :с");
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket);
	printf("Сокет закрыт\n");
	free(arg);
}
void intHandler(int dummy) {
	exit(0);
}

int main(void){
	setlocale(LC_ALL, "rus");
	signal(SIGINT, intHandler);
	WSADATA wsaData;
	int iResult;
	SOCKET ListenSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return 1;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		WSACleanup();
		return 1;
	}
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	printf("Сокет создан успешно!\n");
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Порт сокета: %hu\n",
		ntohs(((struct sockaddr_in*)(result->ai_addr))->sin_port)
	);
	char tmpbuf[DEFAULT_BUFLEN];
	inet_ntop(AF_INET, &(((struct sockaddr_in*)(result->ai_addr))->sin_addr), tmpbuf, DEFAULT_BUFLEN);
	printf("Адрес сокета: %s\n\n", tmpbuf);
	freeaddrinfo(result);
	while (1) {
		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		SOCKET* ClientSocket = new SOCKET;
		(*ClientSocket) = accept(ListenSocket, NULL, NULL);
		if (*ClientSocket == INVALID_SOCKET) {
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		HANDLE thread = CreateThread(NULL, 0, ServeClient, ClientSocket, 0, NULL);
	}
	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}