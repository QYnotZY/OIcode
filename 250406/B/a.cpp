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

const int N = 100;
const int mod = 1e9;
inline int Add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int Minus(int a, int b) {return a >= b ? a - b : a + mod - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, m, nm; char mp[N][N];
inline int id(int x, int y) {return (x - 1) * m + y;}
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
}A, D, M;
int main(){
    n = read(), m = read(), nm = n * m;
    D.init(nm, nm);
    M.init(nm, nm);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++){
            mp[i][j] = readch();
            if(mp[i][j] == '*') continue;
            if(i != 1 && mp[i - 1][j] == '.')
                D.a[id(i - 1, j)][id(i - 1, j)] ++,
                D.a[id(i, j)][id(i, j)] ++,
                M.a[id(i - 1, j)][id(i, j)] = 1,
                M.a[id(i, j)][id(i - 1, j)] = 1;
            if(j != 1 && mp[i][j - 1] == '.')
                D.a[id(i, j - 1)][id(i, j - 1)] ++,
                D.a[id(i, j)][id(i, j)] ++,
                M.a[id(i, j - 1)][id(i, j)] = 1,
                M.a[id(i, j)][id(i, j - 1)] = 1;
        }
    A = D - M;
    for(int i = n; i >= 1; i --)
        for(int j = m; j >= 1; j --)
            if(mp[i][j] == '*')
                A.slice(id(i, j), id(i, j));
    A.slice(1, 1);
    printf("%d", A.det());
    return 0;
}