#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

namespace work{
const int N = 1e6 + 10;
int n, m, t[N], b[N];
typedef pair<int, int> pii;
pii a[N];
int goal[N];
bool cmp(pii a, pii b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}
int V[N], cntv;
void disc(){
    for(int i = 1; i <= m; i ++)
        V[i] = a[i].second;
    sort(V + 1, V + m + 1);
    cntv = unique(V + 1, V + m + 1) - V - 1;
    for(int i = 1; i <= m; i ++)
        goal[i] = lower_bound(V + 1, V + cntv + 1, a[i].second) - V;
}
inline int lowbit(int x) {return x & - x;}
int tr[N];
void add(int x, int v){
    while(x <= cntv){
        tr[x] = max(tr[x], v);
        x += lowbit(x);
    }
}
int query(int x){
    int res = 0;
    while(x){
        res = max(res, tr[x]);
        x -= lowbit(x);
    }
    return res;
}
int Main(){
    n = read(), m = read();
    for(int i = 1; i <= m; i ++)
        t[i] = read();
    for(int i = 1; i <= m; i ++){
        b[i] = read();
        a[i] = make_pair(t[i] + b[i], t[i] - b[i]);
    }
    sort(a + 1, a + m + 1, cmp);
    disc();
    for(int i = 1; i <= m; i ++){
        add(cntv - goal[i] + 1, query(cntv - goal[i]) + 1);
    }
    printf("%d", query(cntv));
    return 0;
}
}
int main(){
    #ifndef db
    freopen("press.in", "r", stdin);
    freopen("press.out", "w", stdout);
    #endif
    return work::Main();
}