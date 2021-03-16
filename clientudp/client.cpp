#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define DEFAULT_PORT 8888
#define DEFAULT_HOST "127.0.0.1"

using namespace std;

class client{
    private:
        WSADATA wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        sockaddr_in to;
        int iResult,len;
        char recvbuff[512];
        string data;
    public:
        client(){
            WSAStartup(MAKEWORD(2,2), &wsaData);
            const char *IP="127.0.0.1";
            len = sizeof(to);
            to.sin_family = AF_INET;
            to.sin_port = htons(DEFAULT_PORT);
            to.sin_addr.S_un.S_addr = inet_addr(DEFAULT_HOST);
        }

        // ~client(){
        //     closesocket(ConnectSocket);
        //     WSACleanup();
        // }

        client resolve(){
            ConnectSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            if(iResult == SOCKET_ERROR){
                cout << WSAGetLastError();
            }
            return *this;
        }

        client sendData(string data){
            iResult = sendto( ConnectSocket,data.c_str(), data.size(), 0,(struct sockaddr *)&to,len);
            if(iResult == SOCKET_ERROR){
                cout << WSAGetLastError();
            }
            return *this;
        }

        client receive(){
            do{
                memset(recvbuff,0,512);
                iResult = recvfrom(ConnectSocket,recvbuff,512,0,(struct sockaddr *)&to,&len);
                if((string(recvbuff)).size()>0) {data = string(recvbuff);break;}
            }while(iResult>0);
            return *this;
        }

        client get(string* data){
            *data = this->data;
            return* this;
        }
};