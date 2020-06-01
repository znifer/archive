#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wsipx.h>
#include <string>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int initializeWSA() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		cout << "WSAStartup failed with error: " << err << endl;
		cout << WSAGetLastError() << endl;
		return 1;
	}
	return 0;
}

int closeWSA() {
	int err;
	err = WSACleanup();
	if (err != 0) {
		cout << "WSACleanup failed with error: " << err << endl;
		cout << WSAGetLastError() << endl;
		return 1;
	}
	return 0;
}

long int getFileSize(FILE* f) {
	long int size;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
};

struct firstPacket {
	unsigned fileSize;
	int maxbufferferSize;
	int fullPacketsCount;
	int lastPacketSize;
};

void receiveFile(SOCKET s, struct sockaddr FAR* saddr, FILE* f) {
	unsigned fileSize, bufferferSize;
	int fullPacketsCount, lastPacketSize, packet_num;
	firstPacket fp;
    char tmp;
	int sz = sizeof(SOCKADDR_IPX);
	recvfrom(s, (char*) &fp, sizeof(fp), 0, saddr, &sz);
	fileSize= fp.fileSize;
	bufferferSize = fp.maxbufferferSize;
	fullPacketsCount = fp.fullPacketsCount;
	lastPacketSize = fp.lastPacketSize;
	packet_num = fullPacketsCount + (lastPacketSize != 0 ? 1 : 0);
	cout << "File size is " << fileSize << " bytes" << endl;
	cout << "Data size in one packet is " << bufferferSize << " bytes" << endl;
	cout << "Will be sent: " << fullPacketsCount << " full packets";
	if (lastPacketSize != 0)
		cout << " and 1 incomplete packet, that contains " << lastPacketSize << " bytes";
	cout << endl;
	char** buffer;
	buffer = new char*[packet_num];
	for (int i = 0; i < packet_num; i++)
        buffer[i] = new char[bufferferSize];
	for (int i = 0; i < fullPacketsCount; i++){
		recvfrom(s, buffer[i], bufferferSize, 0, saddr, &sz);
	}
	if (lastPacketSize != 0){
		recvfrom(s, buffer[fullPacketsCount], bufferferSize, 0, saddr, &sz);
	}
	for (int i = 0; i < fullPacketsCount; i++)
        for (int k = 0; k < bufferferSize; k++)
            fputc(buffer[i][k], f);
    for (int k = 0; k < lastPacketSize; k++)
            fputc(buffer[fullPacketsCount][k], f);
	for (int i = 0; i < packet_num; i++)
        delete buffer[i];
    delete buffer;
}


int main() {
	int errorCode;
	if (initializeWSA())
		return 1;

	SOCKET s;
	unsigned short socketID_svr = 0x4444, socketID_clt = 0x4445;
	s = socket(AF_IPX, SOCK_DGRAM, NSPROTO_IPX);
	if (s == INVALID_SOCKET) {
		cout << "Failed to create socket! Error code is " << WSAGetLastError() << endl;
		closeWSA();
		exit(10);
	}

	SOCKADDR_IPX serverAdress, clientAdress;
	clientAdress.sa_family = AF_IPX;
	clientAdress.sa_socket = htons(socketID_clt);
	bind(s, (sockaddr*)& clientAdress, sizeof(SOCKADDR_IPX));
	int sz = sizeof(SOCKADDR_IPX);
	getsockname(s, (sockaddr*)& clientAdress, &sz);
	serverAdress.sa_family = AF_IPX;
	serverAdress.sa_socket = htons(socketID_svr);
	memset(serverAdress.sa_netnum, 0, 4);
	memset(serverAdress.sa_nodenum, 0xFF, 6);
	char tmp[4];
	string fileName = itoa(htons(clientAdress.sa_socket), tmp, 16);
	fileName += "input.jpg";
	FILE* f_out = fopen(fileName.c_str(), "wb");
	if (f_out == NULL) {
		cout << "Failed to open file!";
		exit(20);
	}
	cout << "Waiting for start!" << endl;
	receiveFile(s, (sockaddr*)& serverAdress, f_out);
	fclose(f_out);

	errorCode = closesocket(s);
	if (errorCode == SOCKET_ERROR) {
		cout << "Failed to close socket! Error code is " << WSAGetLastError() << endl;
		closeWSA();
		exit(11);
	}

	if (closeWSA())
		return 1;
	cout << "Translation complete!" << endl;
	getchar();
	return 0;
}
