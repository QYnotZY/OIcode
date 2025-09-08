#include <bits/stdc++.h>
using namespace std;
int main(){
    int t = 0;
    system("g++ a.cpp -o a.exe -std=c++14 -DLocal_Judge");
    system("g++ std.cpp -o std.exe -std=c++14");
    system("g++ data.cpp -o data.exe -std=c++14");
    while(true){
        cout << "test:" << t++ << endl;
        system("data.exe > data.in");
        system("std.exe < data.in > std.out");
        system("a.exe < data.in > a.out");
        if(system("fc std.out a.out > diff.log")){
            cout << "WA\n"; break;
        }
        cout << "AC\n";
    }
    return 0;
}