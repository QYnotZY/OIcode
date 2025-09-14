#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
void Hutao() {
    int t = 0;
    printf("Compiling...\n");
    system("g++ -std=c++11 a.cpp -o a");
    system("g++ -std=c++11 std.cpp -o std");
    system("g++ -std=c++11 data.cpp -o data");
    printf("Done.\n");
    while(true) {
        printf("Test %d:\n", ++ t);
        system(".\\data.exe > data.in");
        system(".\\std.exe < data.in > std.out");
        system(".\\a.exe < data.in > a.out");
        if(system("fc std.out a.out > diff.log")) {
            printf("WA\n");
            break;
        }
        printf("AC\n");
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}