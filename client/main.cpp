#include <iostream>
#include <string>
#include "client.cpp"
int main(){
    std::cout << "Nhap du lieu" << std::endl;
    string data;
    getline(std::cin,data);
    string recv;

    client().resolve()
            .attemp()
            .sendData(data)
            .sendData("Send Second")
            .shutdownConnection();
            // .recive()
            // .get(&recv);
            
    std::cout << recv << std::endl;
    return 0;
}