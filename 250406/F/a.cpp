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

const int N = 20;
const int mod = 1e9 + 7;
inline int Add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int Minus(int a, int b) {return a >= b ? a - b : a + mod - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, m[N], u[N][N * N], v[N][N * N];
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
int siz;
ll ans;
void solve(int dep){
    if(dep == n){
        Mat A = D - M;
        A.slice(A.n, A.n);
        if((n - 1 - siz) & 1) ans = Minus(ans, A.det());
        else ans = Add(ans, A.det());
        return;
    }
    solve(dep + 1);
    siz ++;
    for(int i = 1; i <= m[dep]; i ++){
        D.a[u[dep][i]][u[dep][i]] ++;
        D.a[v[dep][i]][v[dep][i]] ++;
        M.a[u[dep][i]][v[dep][i]] ++;
        M.a[v[dep][i]][u[dep][i]] ++;
    }
    solve(dep + 1);
    siz --;
    for(int i = 1; i <= m[dep]; i ++){
        D.a[u[dep][i]][u[dep][i]] --;
        D.a[v[dep][i]][v[dep][i]] --;
        M.a[u[dep][i]][v[dep][i]] --;
        M.a[v[dep][i]][u[dep][i]] --;
    }
    return;
}
int main(){
    n = read();
    M.init(n, n);
    D.init(n, n);
    for(int i = 1; i < n; i ++){
        m[i] = read();
        for(int j = 1; j <= m[i]; j ++)
            u[i][j] = read(), v[i][j] = read();
    }
    solve(1);
    printf("%lld", ans);
}