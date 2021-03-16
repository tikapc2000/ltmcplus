#include "client.cpp"
int main(){
    string str;
    getline(cin,str);
    string counter;
    client().resolve().sendData(str).receive().get(&counter);
    cout<< "Co " << counter << " ky tu A";
    return 0;
}