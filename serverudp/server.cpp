#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_PORT "8888"
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
        struct addrinfo *result = NULL;
        struct addrinfo hints;
        char recvbuff[512];
        struct sockaddr_in clientaddr;
        int slen;
        string data;
    private:
        void intialize(){
            iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            slen = sizeof(clientaddr);
            ZeroMemory(&hints, sizeof(hints));
            this->hints.ai_family = AF_INET;
            this->hints.ai_socktype = SOCK_DGRAM;
            this->hints.ai_protocol = IPPROTO_UDP;
            this->hints.ai_flags = AI_PASSIVE;
        }
    public:
        server(){
            intialize();
        }

        // ~server(){
        //     freeaddrinfo(result);
        //     closesocket(ListenSocket);
        //     WSACleanup();
        // }

        server resolve(){
            iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
            return *this;
        }

        server createSocket(){
            ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            return *this;
        }

        server bindSocket(){
            iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
            return *this;
        }

        server receive(string (func)(string data)){
            while(1){
                memset(recvbuff,0,512);
                cout << "Dang doi nhan du lieu" << endl;
                fflush(stdout);
                iResult = recvfrom(ListenSocket,recvbuff,512,0,(struct sockaddr *)&clientaddr,&slen);
                if(iResult == SOCKET_ERROR) {
                    cout << WSAGetLastError();
                    break;
                }

                cout << "Nhan du lieu tu:" << inet_ntoa(clientaddr.sin_addr) << endl;
                cout << "Du lieu vua nhan duoc la:" << string(recvbuff) << endl;

                sendData(func(string(recvbuff)));
                if(iResult == SOCKET_ERROR) {
                    cout << WSAGetLastError();
                    break;
                }
            }
            return *this;
        }

        server sendData(string data){
            sendto(ListenSocket,data.c_str(),data.length(),0,(struct sockaddr *)&clientaddr,slen);
            return *this;
        }
};