#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
inline T readnum(){
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
template<typename T = int>
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
namespace work {
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Sq(int a) {return Mult(a, a);}
inline int Pow(int a, int b) {
    return b ? Mult(Sq(Pow(a, b >> 1)), (b & 1 ? a : 1)) : 1;
}
int t, n;
vector<int> to[N];
int dep[N], x, y, z, err;
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    int cnt = 0;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs(v, u); cnt ++;
        if(err) return;
    }
    if(cnt == 2) z = u;
    if(cnt == 0) {
        if(!x) x = u;
        else if(!y) y = u;
        else return void(err = 1);
    }
    return;
}
void init() {
    x = y = z = err = 0;
    for(int i = 1; i <= n; i ++) {
        vector<int>().swap(to[i]);
    }
}
int Main() {
    t = read();
    while(t --) {
        n = read();
        init();
        for(int i = 1; i < n; i ++) {
            int u = read(), v = read();
            to[u].emplace_back(v);
            to[v].emplace_back(u);
        }
        dfs(1, 0);
        if(err) {
            write(0);
            continue;
        }
        if(!y) {
            write(Pow(2, n));
            continue;
        }
        if(dep[x] == dep[y]) {
            write(Pow(2, dep[z] + 1));
        } else {
            write(Mult(Pow(2, dep[z] + abs(dep[x] - dep[y]) - 1), 3));
        }
    }
    return 0;
}
}
int main() {
    return work::Main();
}