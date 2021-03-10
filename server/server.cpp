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
        char recvbuff[255];
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
            freeaddrinfo(result);
            iResult = listen(ListenSocket, SOMAXCONN);
            return *this;
        }

        server acceptClientSocket(){
            ClientSocket = accept(ListenSocket, NULL, NULL);
            closesocket(ListenSocket);
            std::cout << "Accept client successs" << std::endl;
            return *this;
        }

        char* receive(){
            do{
                iResult = recv(ClientSocket,(char*)recvbuff,255,0);
                if(iResult<0){
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
            }while(iResult>0);
            return recvbuff;
        }

        void shutdownConnection(){
            iResult = shutdown(ClientSocket, SD_SEND);
            closesocket(ClientSocket);
            WSACleanup();
        }
};
