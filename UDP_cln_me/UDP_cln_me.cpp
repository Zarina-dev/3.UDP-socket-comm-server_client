//  include socket comm libs
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;
#define PORT 3333
#define BUF_SIZE 1024

int main()
{
	cout << "accessing socket" << endl;

	// wsa 초기화
	WSADATA wsaData;
	int wsaRtn = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// socket [ which is trying to connect on ]
	SOCKET listeningMeServer = socket(AF_INET, SOCK_DGRAM, 0);
	if (listeningMeServer == INVALID_SOCKET) { cerr << " socket () error!" << endl; WSACleanup(); return 0; }


	// socket info
	sockaddr_in listeningMeServerInfo;
	sockaddr_in* PlisteningMeServerInfo = &listeningMeServerInfo;
	PlisteningMeServerInfo->sin_family = AF_INET;
	PlisteningMeServerInfo->sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &PlisteningMeServerInfo->sin_addr);

	// sendto  (bufMsg)
	
	/*
	string inputData;
	cout << "input data > ";
	getline(cin, inputData);
	*/

	char sendBuf[BUF_SIZE] = "test test test";

	int sentByteSize = sendto(listeningMeServer, (char*)&sendBuf, BUF_SIZE, 0,
		(sockaddr*)&listeningMeServerInfo, sizeof(listeningMeServerInfo));
	if (sentByteSize == SOCKET_ERROR)
	{
		cerr << " sendto () error!" << endl;
	}
	else
	{
		cout << "sent data : " << sendBuf << "\n sent data size : " << sentByteSize << endl;
	}

	// recvfrom (get data into recvBuf, get Ip info of receving socket into recvIpBuf)

	// display

	cout << " QUIT " << endl;
	Sleep(4000);
	closesocket(listeningMeServer);
	WSACleanup();


	system("PAUSE");

}
