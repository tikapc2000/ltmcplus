#include "server.cpp"
int main(){
    server().resolve().createSocket().bindSocket().receive( [](string data)->string{
        int counter = 0;
        for(int i=0;i<data.size();i++){
            if(data[i]=='A') counter++;
        }
        return to_string(counter);
    });
    getchar();
    return 0;
}