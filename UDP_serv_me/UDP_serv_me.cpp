//  include socket comm libs
#include <iostream>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define PORT 3333
#define BUF_SIZE 1024

int main()
{
    cout << "listening server socket" << endl;

    // wsa 초기화
    WSADATA wsaData;
    int wsaRtn = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaRtn != 0) { cerr << " wsastartup error" << endl; }
    

    // socket
    SOCKET listeningServer = socket(AF_INET, SOCK_DGRAM, 0);
    if (listeningServer == INVALID_SOCKET) { cerr << " socket () error!" << endl; WSACleanup(); return 0; }
    else { cout << "listenign server descriptor : " << listeningServer << endl; }

    // socket info
    sockaddr_in listeningServInfo;
    sockaddr_in* PlisteningServerInfo = &listeningServInfo;
    PlisteningServerInfo->sin_family = AF_INET;
    PlisteningServerInfo->sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &PlisteningServerInfo->sin_addr);

    // bind socket inform to socket
    if (bind(listeningServer, (sockaddr*)&listeningServInfo, sizeof(listeningServInfo)) == SOCKET_ERROR)
    {
        cerr << "bind() error " << endl;
        WSACleanup(); return 0;
    }
    else
    {
        cout << "소켓이 bounded" << endl;
    }

    // recvfrom  (put recvd data info recvBuf, get IP data of socket which is connected)
    
    sockaddr_in receivingSocketAddr;
    int szreceivingSocketAddr = sizeof(receivingSocketAddr);

    char recvdBuf[BUF_SIZE];


    int recvdByteSize = recvfrom(listeningServer, (char*)&recvdBuf, BUF_SIZE, 0, 
        (sockaddr*)&receivingSocketAddr, &szreceivingSocketAddr);

    if (recvdByteSize == SOCKET_ERROR)
    {
        cerr << "recvfrom() error!" << endl; WSACleanup(); return 0;
    }
    else {
        // get source's IP address
        char recvdSocketIP[256];   
        ZeroMemory(recvdSocketIP, 256);
        inet_ntop(AF_INET, (void*)&receivingSocketAddr.sin_addr, recvdSocketIP, 256);

        // display recved data
        cout << "\n   received data : " << recvdBuf << 
            "\n received data size : " << recvdByteSize <<
            "\n received source IP : " << recvdSocketIP << endl;
    }


    // sendto 

    cout << "QUIT " << endl;
    closesocket(listeningServer);
    WSACleanup();

    system("PAUSE");

}
