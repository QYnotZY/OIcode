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
namespace work {
const int N = 1e5 + 10;
namespace dsu {
    int fa[N], r[N]; vector<int> ineq[N];
    void init(int n) {
        for(int i = 1; i <= n; i ++) {
            fa[i] = i; r[i] = 0;
            vector<int> ().swap(ineq[i]);
        }
    }
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    bool same(int u, int v) {return find(u) == find(v);}
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return true;
        if(r[u] < r[v]) swap(u, v);
        for(auto ele : ineq[v]) {
            ele = find(ele);
            if(same(u, ele)) return false;
            ineq[u].emplace_back(ele);
        }
        r[u] += r[v];
        fa[v] = u;
        return true;
    }
    bool add(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        r[u] ++; ineq[u].emplace_back(v);
        r[v] ++; ineq[v].emplace_back(u);
        return true;
    }
}
int n;
vector<int> ans;
vector<int> mov;
void Hutao() {
    n = read();
    dsu::init(1e5);
    for(int i = 1, t = 0; i <= n; i ++) {
        int x = read(), y = read(), e = read();
        mov.emplace_back(x), mov.emplace_back(y);
        if(e) {
            if(!dsu::merge(x, y)) {
                ans.emplace_back(i - t);
                t = i;
                for(auto ele : mov) {
                    dsu::fa[ele] = ele; dsu::r[ele] = 0;
                    vector<int> ().swap(dsu::ineq[ele]);
                }
                vector<int> ().swap(mov);
            }
        } else {
            if(!dsu::add(x, y)) {
                ans.emplace_back(i - t);
                t = i;
                for(auto ele : mov) {
                    dsu::fa[ele] = ele; dsu::r[ele] = 0;
                    vector<int> ().swap(dsu::ineq[ele]);
                }
                vector<int> ().swap(mov);
            }
        }
    }
    printf("%d\n", ans.size());
    for(auto ele : ans) {
        printf("%d\n", ele);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}