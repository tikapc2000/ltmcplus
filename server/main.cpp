#include "server.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(string source,string seperator){
    vector<string> seperate;
    while (source.find(seperator)!=string::npos)
    {
        seperate.push_back(source.substr(0,source.find(seperator)));
        source = source.substr(source.find(seperator)+1,source.length());
    }
    seperate.push_back(source);

    return seperate;
}

vector<int> convert_vector(vector<string> vct){
    vector<int> arr;
    for(int i=0;i<vct.size();i++)
        arr.push_back(atoi(vct[i].c_str()));
    return arr;
}

string to_string(vector<int> vct){
    string str ="";
    for(int i=0;i<vct.size();i++)
        str+= to_string(vct[i])+" ";
    return str;
}

int main(){
    string recv_str;
    server* serv = new server();
    serv->resolve()
        ->createSocket()
        ->setupTCPListening()
        ->acceptClientSocket()
        ->receive()
        ->get(&recv_str);
    
    cout << recv_str << endl;

    vector<int> arr = convert_vector(split(recv_str," "));
    sort(arr.begin(),arr.end());


    serv->sendData("Day sau khi sap xep: "+to_string(arr))
        ->shutdownConnection();

    return 0;
}
