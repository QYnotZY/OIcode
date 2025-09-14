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
const int N = 10;
char ch[5] = "ACGT";
int n, m;
mt19937 fate(time(0));
void Hutao() {
    printf("1\n");
    n = fate() % N + 1, m = fate() % N + 1;
    for(int i = 1; i <= n; i ++) putchar(ch[fate() % 4]);
    putchar('\n');
    for(int i = 1; i <= m; i ++) putchar(ch[fate() % 4]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}