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
T read(bool ch = 0, bool sp = 0) {return ch ? readch(sp) : readnum<T>();}
}
using FastIO::read;
using FastIO::readch;
typedef long long ll;

const int N = 510;
int mod;
inline int Add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int Minus(int a, int b) {return a >= b ? a - b : a + mod - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
struct DSU{
    int fa[10500];
    void init(int n){
        for(int i = 1; i <= n; i ++)
            fa[i] = i;
    }
    int find(int x){
        return fa[x] == x ? x : fa[x] = find(x);
    }
    void merge(int u, int v){
        fa[v] = u;
    }
}dsu;
struct Mat{
    int n, m, a[N][N];
    void init(int n, int m, int isI = 0){
        this->n = n, this->m = m;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                a[i][j] = 0;
        for(int i = 1; i <= min(n, m); i ++)
            a[i][i] = isI;
    }
    Mat operator - (Mat obj){
        assert(n == obj.n && m == obj.m);
        Mat res;
        res.init(n, m);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                res.a[i][j] = Minus(a[i][j], obj.a[i][j]);
        return res;
    }
    void slice(int x, int y){
        for(int i = x + 1; i <= n; i ++){
            swap(a[i - 1], a[i]);
        }
        n --;
        for(int j = y + 1; j <= m; j ++)
            for(int i = 1; i <= n; i ++)
                swap(a[i][j - 1], a[i][j]);
        m --;
    }
    int det(){
        assert(n == m);
        if(n <= 0) return 0;
        int res = 1;
        for(int j = 1; j <= n; j ++){
            for(int i = j; i <= n; i ++){
                if(a[i][j]){
                    swap(a[i], a[j]);
                    if(i != j) res = mod - res;
                    break;
                }
            }
            if(!a[j][j]) return 0;
            for(int i = j + 1; i <= n; i ++){
                if(a[j][j] < a[i][j]) swap(a[i], a[j]), res = mod - res;
                while(a[i][j]){
                    int div = a[j][j] / a[i][j];
                    for(int k = 1; k <= n; k ++)
                        a[j][k] = Minus(a[j][k], Mult(a[i][k], div));
                    swap(a[i], a[j]), res = mod - res;
                }
            }
        }
        for(int i = 1; i <= n; i ++)
            res = Mult(res, a[i][i]);
        return res;
    }
}M, D;
int n, m;
char a[N][N];
inline int id(int x, int y) {return (x - 1) * (m + 1) + y;}
inline int eo(int id) {return ((id - 1) / (m + 1) & 1) ^ ((id - 1) % (m + 1) & 1);}
int bid[10500], cur[2];
int ans;
int main(){
    n = read(), m = read(), mod = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++){
            a[i][j] = readch();
            if(a[i][j] == '\\'){
                dsu.merge(id(i, j), id(i + 1, j + 1));
            }
            if(a[i][j] == '/'){
                dsu.merge(id(i, j + 1), id(i + 1, j));
            }
        }
    for(int i = 1; i <= (n + 1) * (m + 1); i ++)
        if(!bid[dsu.find(i)]) bid[dsu.find(i)] = ++ cur[eo(i)];
    D.init(cur[0], cur[0]); M.init(cur[0], cur[0]);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++){
            if(cur[0] == '*'){
                if(!eo(id(i, j))){
                    D.a[bid[id(i, j)]][bid[id(i, j)]] ++;
                    D.a[bid[id(i + 1, j + 1)]][bid[id(i + 1, j + 1)]] ++;
                    M.a[bid[id(i, j)]][bid[id(i + 1, j + 1)]] ++;
                    M.a[bid[id(i + 1, j + 1)]][bid[id(i, j)]] ++;
                } else{
                    D.a[bid[id(i, j + 1)]][bid[id(i, j + 1)]] ++;
                    D.a[bid[id(i + 1, j)]][bid[id(i + 1, j)]] ++;
                    M.a[bid[id(i, j + 1)]][bid[id(i + 1, j)]] ++;
                    M.a[bid[id(i + 1, j)]][bid[id(i, j + 1)]] ++;
                }
            }
        }
    Mat A = D - M;
    A.slice(1, 1);
    ans = Add(ans, A.det());
    D.init(cur[1], cur[1]); M.init(cur[1], cur[1]);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++){
            if(eo(id(i, j))){
                D.a[bid[id(i, j)]][bid[id(i, j)]] ++;
                D.a[bid[id(i + 1, j + 1)]][bid[id(i + 1, j + 1)]] ++;
                M.a[bid[id(i, j)]][bid[id(i + 1, j + 1)]] ++;
                M.a[bid[id(i + 1, j + 1)]][bid[id(i, j)]] ++;
            } else{
                D.a[bid[id(i, j + 1)]][bid[id(i, j + 1)]] ++;
                D.a[bid[id(i + 1, j)]][bid[id(i + 1, j)]] ++;
                M.a[bid[id(i, j + 1)]][bid[id(i + 1, j)]] ++;
                M.a[bid[id(i + 1, j)]][bid[id(i, j + 1)]] ++;
            }
        }
    A = D - M;
    A.slice(1, 1);
    ans = Add(ans, A.det());
    printf("%d", ans);
    return 0;
}