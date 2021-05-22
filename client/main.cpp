#include <iostream>
#include <string>
#include "client.cpp"
void input(string* data){
    cout << "Nhap so n" << endl;
    int n;
    cin >> n;
    cout << "Nhap mang du lieu:" << endl;
    for(int i=0;i<n;i++){
        int m;
        cin >> m;
        *data+=to_string(m);
        if(i!=n-1) *data+=" ";
    }
}

int main(){
    string data="";
    string recv;
    input(&data);

    (new client())->resolve()
            ->attemp()
            ->sendData(data)
            ->shutdownConnection()
            ->recive()
            ->get(&recv);
            
    cout << recv << endl;
    return 0;
}