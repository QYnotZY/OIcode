#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
template<typename T=int> 
T readnum(){
    T res=0; bool f=0;
    char ch=getchar();
    while(!('0'<=ch&&ch<='9')){
        if(ch=='-') f=!f;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    return f?~res+1:res;
}
template<typename T=int>
T read() {return readnum<T>();}

const int N = 4e6 + 10;
const ll mod = 998244353, G = 3, invG = 332748118;
int n, m, len, lim, loglim;
ll a[N], b[N], c[N];
inline ll Add(ll a, ll b) {return (a + b) % mod;}
inline ll Minus(ll a, ll b) {return (a - b + mod) % mod;}
inline ll Mult(ll a, ll b) {return (a * b) % mod;}
inline ll Mod(ll a, ll b) {return (a % b + b) % b;}
ll power(ll a, int b){
    b = Mod(b, mod - 1);
    ll res = 1;
    for(; b; a = Mult(a, a), b >>= 1)
        if(b & 1) res = Mult(res, a);
    return res;
}
int tax[N];
void getTax(int loglim){
    int cur = 0;
    tax[cur ++] = 0;
    for(int d = 1 << loglim - 1, len = cur; d; d >>= 1, len = cur){
        for(int i = 0; i < len; i ++)
            tax[cur ++] = tax[i] ^ d;
    }
}
void Rev(ll* A, int loglim){
    int lim = 1 << loglim;
    getTax(loglim);
    for(int i = 0; i < lim; i ++)
        if(i < tax[i]) swap(A[i], A[tax[i]]);
}
void NTT(ll* A, int loglim, int typ){
    int lim = 1 << loglim;
    Rev(A, loglim);
    for(int mid = 1; mid < lim; mid <<= 1){
        ll wn = power(~typ ? G : invG, (mod - 1) / (mid << 1));
        for(int j = 0; j < lim; j += mid << 1){
            ll w = 1ll;
            for(int k = 0; k < mid; k ++, w = Mult(w, wn)){
                ll x = A[j + k], y = Mult(w, A[j + k + mid]);
                A[j + k] = Add(x, y);
                A[j + k + mid] = Minus(x, y);
            }
        }
    }
    if(!~typ){
        ll invlim = power(lim, -1);
        for(int i = 0; i < lim; i ++)
            A[i] = Mult(A[i], invlim);
    }
}
void polymult(ll *C, ll *A, ll *B, int loglim){
    int lim = 1 << loglim;
    NTT(A, loglim, 1); NTT(B, loglim, 1);
    for(int i = 0; i < lim; i ++) C[i] = Mult(A[i], B[i]);
    NTT(C, loglim, -1);
}
int main(){
    n = read(), m = read(), len = n + m + 1;
    for(loglim = 1; (1 << loglim) < len; ++ loglim) ;
    for(int i = 0; i <= n; i ++) a[i] = read<ll>();
    for(int i = 0; i <= m; i ++) b[i] = read<ll>();
    polymult(c, a, b, loglim);
    for(int i = 0; i < len; i ++)
        printf("%lld ", c[i]);
    return 0;
}