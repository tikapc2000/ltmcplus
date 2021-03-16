#include "server.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countCharacter(string source,char search){
    int counter = 0;
    for(int i=0;i<source.size();i++)
        if(source[i]==search) counter++;
    return counter;
}

std::vector<string> split(string source,string seperator){
    std::vector<string> seperate;
    while (source.find(seperator)!=string::npos)
    {
        seperate.push_back(source.substr(0,source.find(seperator)));
        source = source.substr(source.find(seperator)+1,source.length());
    }
    seperate.push_back(source);

    return seperate;
};

int sumOfString(string source){
    std::vector<string> vct = split(source," ");
    int sum = 0;
    for(int i=0;i<vct.size();i++){
        sum+=atoi(vct[i].c_str());
    }
    return sum;
}

int main(){
    std::string s;
    server().resolve()
            .createSocket()
            .setupTCPListening()
            .acceptClientSocket()
            .receive()
            .receive()
            .get(&s)
            .sendData("Co "+to_string(countCharacter(s,'A'))+ " ky tu A")
            // .sendData("Tong: "+to_string(sumOfString(s)))
            .shutdownConnection();
    std::cout << s;
    getchar();
    return 0;
}
