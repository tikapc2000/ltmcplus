#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define DEFAULT_PORT "27015"

using namespace std;

class client{
    private:
        WSADATA wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL,
                        *ptr = NULL,
                        hints;
        int iResult;
        char recvbuff[512];
        string data;
    private:
        void intialize(){
            iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            ZeroMemory( &hints, sizeof(hints) );
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;
        }
    public:
        client(){
            intialize();
        }

        client resolve(){
            iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
            return *this;
        }

        client attemp(){
            for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

                // Create a SOCKET for connecting to server
                ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
                    ptr->ai_protocol);

                // Connect to server.
                iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                    continue;
                }
                break;
            }
            freeaddrinfo(result);
            return *this;
        }

        client sendData(string data){
            iResult = send( ConnectSocket,data.c_str(), data.length(), 0 );
            return *this;
        }

        client recive(){
            do{
                iResult = recv(ConnectSocket,recvbuff,512,0);
            }while(iResult>0);
            data = string(recvbuff);
            return *this;
        }

        client get(string* data){
            *data = this->data;
            return *this;
        }

        client shutdownConnection(){
            iResult = shutdown(ConnectSocket, SD_SEND);
            return* this;
        }
};