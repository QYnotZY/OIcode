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
const int N = 1e5 + 10, M = 2e5 + 10;
int n, m;
struct edge {
    int u, v, w, col;
} ed[M];
int check(int mid) {
    sort(ed + 1, ed + m + 1, [&](const edge &a, const edge &b){return a.w - a.col * mid < b.w - b.col * mid;});
}
void Hutao() {
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}