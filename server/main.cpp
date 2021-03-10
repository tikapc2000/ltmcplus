#include "server.cpp"
#include <iostream>
#include <string>

int main(){
    server ser;
    ser.resolve().createSocket().setupTCPListening().acceptClientSocket();
    char* a = ser.receive();
    puts(a);
    ser.shutdownConnection();
    getchar();
    return 0;
}