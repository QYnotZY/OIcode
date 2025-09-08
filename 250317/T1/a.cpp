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

const int N = 1005, K = 25;
const int mod = 20050806;
int n, k, q, a[N][N], b[N][N];
int ans;
struct MatNK{
    int n, m, a[N][K];
    void init(int nn, int mm){
        n = nn, m = mm;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                a[i][j] = 0;
    }
}B;
struct MatKN{
    int n, m, a[K][N];
    void init(int nn, int mm){
        n = nn, m = mm;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                a[i][j] = 0;
    }
}AT, res;
struct MatKK{
    int n, m, a[K][K];
    void init(int nn, int mm, int isI = 0){
        n = nn, m = mm;
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++)
                a[i][j] = 0;
            a[i][i] = isI;
        }
    }
}ATB;
MatKK operator * (MatKN a, MatNK b){
    MatKK res; res.init(a.n, b.m);
    for(int i = 1; i <= res.n; i ++)
        for(int j = 1; j <= res.m; j ++)
            for(int k = 1; k <= a.m; k ++)
                (res.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}
MatKK operator * (MatKK a, MatKK b){
    MatKK res; res.init(a.n, b.m);
    for(int i = 1; i <= res.n; i ++)
        for(int j = 1; j <= res.m; j ++)
            for(int k = 1; k <= a.m; k ++)
                (res.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}
MatKN operator * (MatKK a, MatKN b){
    MatKN res; res.init(a.n, b.m);
    for(int i = 1; i <= res.n; i ++)
        for(int j = 1; j <= res.m; j ++)
            for(int k = 1; k <= a.m; k ++)
                (res.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}
MatKK pow(MatKK a, int idx){
    MatKK res; res.init(a.n, a.n, 1);
    for(; idx; idx >>= 1, a = a * a)
        if(idx & 1) res = res * a;
    return res;
}
int main(){
    n = read(), k = read();
    B.init(n + 1, k + 1);
    AT.init(k + 1, n + 1);
    B.a[n + 1][k + 1] = AT.a[k + 1][n + 1] = 1;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= k; j ++)
            B.a[i][j] = read();
        for(int j = 1; j <= k; j ++)
            AT.a[j][i] = read();
    }
    q = read();
    for(; q --;){
        int x = read(), y = read(), z = read();
        if(z == 0){
            printf("%d\n", x == y);
            continue;
        }
        B.a[y][k + 1] = 1;
        res.init(1, n + 1);
        res.a[1][x] = 1;
        ATB = AT * B;
        res = res * B * pow(ATB, z) * AT;
        printf("%d\n", res.a[1][n + 1]);
        B.a[y][k + 1] = 0;
    }
    return 0;
}