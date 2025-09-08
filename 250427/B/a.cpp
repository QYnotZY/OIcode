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

typedef pair<int, int> pii;
const int N = 2e5 + 10;
namespace work{
int n, m;
namespace llfs{
    int tot, head[N];
    struct edge{
        int to;
        int nxt;
    } e[N];
    void init(int n){
        tot = 0;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    void add(int u, int v){
        e[++ tot] = {v, head[u]};
        head[u] = tot;
    }
} using namespace llfs;
int dfn[N], curdfn, low[N], scc[N], cntscc, sz[N];
int stk[N], top; bitset<N> instk;
void Tarjan(int u, int f){
    
}
int Main(){
    return 0;
}
}
int main(){
    return work::Main();
}