#include <iostream>
using namespace std;

int main(){
    //cout<<1024 + 1024/2;
    for(int i=1;i<=511;i++) cout<<"BBAA"; cout<<"BDFC";
    for(int i=1;i<=512;i++) cout<<"ABBA";
    cout<<"AC";
    return 0;
}

/*
#include <fstream>
using namespace std;

int main() {
    ofstream outfile("6.in");
    int m = 1 << 13; // 操作次数
    
    outfile << "ABCD";
    outfile <<endl<< 2*m<< endl;
    
    for(int i=1;i<=m;i++)
    {
        outfile << 2*i-1<<" A"<<endl;
        outfile << 2*i<<" B"<<endl;
    }
    
    outfile.close();
    return 0;
}*/