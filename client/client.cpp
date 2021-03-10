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
        string data="Hello World";
        int iResult;
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
            std::cout << "Connect Success";
            return *this;
        }

        client sendData(const char* data){
            iResult = send( ConnectSocket,data, sizeof(int), 0 );

            return *this;
        }

        void shutdownConnection(){
            iResult = shutdown(ConnectSocket, SD_SEND);
        }
};