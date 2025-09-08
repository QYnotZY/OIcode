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
const int N = 5e5 + 10;
namespace work {
bitset<N> isnp;
vector<int> pri;
void init() {
    for(int i = 2; i < N; i ++) {
        if(!isnp[i]) pri.emplace_back(i);
        for(auto ele : pri) {
            if(ele * i >= N) break;
            isnp[ele * i] = 1;
            if(i % ele == 0) break;
        }
    }
}
int n, sump;
ll ans;
int a[N];
int vis[N];
vector<pair<int, int> > hpri;
void solve() {
    n = read();
    ans = sump = 0;
    vector<pair<int, int> > ().swap(hpri);
    for(int i = 1; i <= n; i ++)
        a[i] = read(), vis[i] = 0;
    for(int i = 1; i <= n; i ++) {
        if(!isnp[a[i]]) {
            ans += sump - vis[a[i]];
            sump ++;
        } else {
            for(auto ele : pri)
                if(a[i] % ele == 0) {
                    if(!isnp[a[i] / ele]) {
                        ans += vis[a[i]] + 1;
                        hpri.emplace_back(a[i], ele);
                    }
                    break;
                }
        }
        vis[a[i]] ++;
    }
    for(auto ele : hpri) {
        ans += vis[ele.second];
        if(ele.first / ele.second != ele.second)
            ans += vis[ele.first / ele.second];
    }
    write(ans);
}
int Main() {
    init();
    int t = read();
    while(t --) solve();
    return 0;
}
}
int main() {
    return work::Main();
}