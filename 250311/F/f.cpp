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
template<typename T=int> T read() {return readnum<T>();}

const int N = 4010, mod = 1e9 + 7;
int n, k, st[N], dp[N][N][5][2], ans;
void add(int i, int a, int b, int typ, int i1, int a1, int b1, int typ1){
    if(typ1 == 0 && a1 > b1 + 2) a1 = b1 + 2;
    if(typ1 == 1 && b1 > a1 + 2) b1 = a1 + 2;
    (dp[i1][a1][b1-a1+2][typ1] += dp[i][a][b-a+2][typ]) %= mod;
}
int main(){
    n = read(); k = read();
    char ch = getchar();
    while(ch != 'A' && ch != 'B' && ch != '?') ch = getchar();
    for(int i = 1; i < n; i ++, ch = getchar()){
        if(ch == 'A') st[i] = 0;
        if(ch == 'B') st[i] = 1;
        if(ch == '?') st[i] = 2;
    }
    dp[0][0][2][0] = 500'000'004;
    dp[0][0][2][1] = 500'000'004;
    for(int i = 0; i < n - 1; i ++){
        for(int j = 0; j <= i; j ++){
            for(int k = -2; k <= 2; k ++){
                if(st[i + 1] != 1){
                    add(i, j, j + k, 0, i + 1, j + 1, j + k, 0);
                    add(i, j, j + k, 1, i + 1, min(j + 1, j + k + 1), min(j + 2, j + k), 0);
                }
                if(st[i + 1] != 0){
                    add(i, j, j + k, 1, i + 1, j, j + k + 1, 1);
                    add(i, j, j + k, 0, i + 1, min(j, j + k + 2), min(j + 1, j + k + 1), 1);
                }
            }
        }
    }
    for(int i = 0; i <= k + 2; i ++)
        for(int j = 0; j < 5; j ++)
            (ans += (i + 1 <= k || i + j - 1 <= k) ? (dp[n - 1][i][j][0] + dp[n - 1][i][j][1]) % mod : 0) %= mod;
    printf("%d", ans);
    return 0;
}