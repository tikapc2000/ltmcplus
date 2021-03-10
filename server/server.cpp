#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class server{
    private:
        int iResult;
        WSADATA wsaData;
        SOCKET ListenSocket = INVALID_SOCKET;
        SOCKET ClientSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL;
        struct addrinfo hints;
        char recvbuff[512];
        string data;
    private:
        void intialize(){
            iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            ZeroMemory(&hints, sizeof(hints));
            this->hints.ai_family = AF_INET;
            this->hints.ai_socktype = SOCK_STREAM;
            this->hints.ai_protocol = IPPROTO_TCP;
            this->hints.ai_flags = AI_PASSIVE;
        }
    public:
        server(){
            intialize();
        }

        server resolve(){
            iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
            return *this;
        }

        server createSocket(){
            ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            return *this;
        }

        server setupTCPListening(){
            iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
            iResult = listen(ListenSocket, SOMAXCONN);
            if (iResult == SOCKET_ERROR) {
                printf("listen failed with error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
            }
            return *this;
        }

        server acceptClientSocket(){
            ClientSocket = accept(ListenSocket, NULL, NULL);
            return *this;
        }

        server get(string* data){
            *data = this->data;
            return *this;
        }

        server receive(){
            do{
                iResult = recv(ClientSocket,recvbuff,512,0);
            }while(iResult>0);
            data = string(recvbuff);
            return *this;
        }

        server sendData(string data){
            send(ClientSocket,data.c_str(),data.length(),0);
            return *this;
        }

        server shutdownConnection(){
            freeaddrinfo(result);
            closesocket(ListenSocket);
            shutdown(ClientSocket, SD_SEND);
            closesocket(ClientSocket);
            WSACleanup();
            return *this;
        }
};
