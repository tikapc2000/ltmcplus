#include <iostream>
#include <string>
#include "client.cpp"
int main(){
    string a;
    std::cin >> a;
    client cl;
    cl.resolve().attemp().sendData(a.c_str()).shutdownConnection();
    return 0;
}