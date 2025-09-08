#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T = int>
inline T read(){
    T res = 0; bool f = 0;
    char ch = gc();
    for(; !('0' <= ch && ch <= '9'); ch = gc())
        if(ch == '-') f = !f;
    for(; '0' <= ch && ch <= '9'; ch = gc())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return f ? ~res + 1 : res;
}
inline char readch(bool sp = 0){
    char ch = gc();
    for(; !(33 - sp <= ch && ch < 127); ch = gc()) ;
    return ch;
}
}
using FastIO::read;
using FastIO::readch;
typedef long long ll;
namespace work {
const int N = 5005;
const int mod = 1e9 + 7, inv2 = 5e8 + 4;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int n;
int a[N], p[N * 3], ip[N * 3];
int pre[N << 1][N];
void Hutao() {
    n = read();
    p[0] = 1, a[0] = 1;
    for(int i = 1; i < n; i ++) {
        a[i] = read();
        p[i] = Mult(p[i - 1], a[i]);
    }
    ip[n - 1] = Inv(p[n - 1]);
    for(int i = n - 2; ~i; i --)
        ip[i] = Mult(ip[i + 1], a[i + 1]);
    for(int i = 0; i < n; i ++) pre[2][i] = Mult(p[i], p[i]), pre[3][i] = Mult(2, Mult(p[i], p[i + 1]));
    for(int i = 4; i <= n - 1 << 1; i ++)
        for(int j = 1; j < n && i + j - 2 >= 0; j ++)
            pre[i][j] = Add(pre[i - 2][j + 1], Mult(2, Mult(p[j], p[i + j - 2])));
    for(int i = 1, f; i <= n - 1 << 1; i ++) {
        f = 0;
        for(int k = 1, tmp; k < n; k ++) {
            f = Add(f, p[i - 1 + k]);
            f = Add(f, Mult(Mult(Minus(ip[k - 1], ip[k]), inv2), pre[i][k]));
        }
        printf("%d ", f);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}