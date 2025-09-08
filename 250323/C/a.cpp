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

const int N = 5e5 + 10;
int n, m, cnt;
int x[N * 5], y[N * 5], ans[N << 2];
namespace INIT{
int rdx[N], rdy[N];
void init_input(){
    n = read(), m = read();
    for(int i = 1; i <= n; i ++){
        rdx[i] = x[i] = read(), rdy[i] = y[i] = read();
    }
    for(int i = 1; i <= m; i ++){
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        rdx[n + i] = x[n + i] = x1 - 1; rdy[n + i] = y[n + i] = y1 - 1;
        rdx[n + m + i] = x[n + m + i] = x1 - 1; rdy[n + m + i] = y[n + m + i] = y2;
        rdx[n + m * 2 + i] = x[n + m * 2 + i] = x2; rdy[n + m * 2 + i] = y[n + m * 2 + i] = y1 - 1;
        rdx[n + m * 3 + i] = x[n + m * 3 + i] = x2; rdy[n + m * 3 + i] = y[n + m * 3 + i] = y2;
    }
    cnt = n + (m << 2);
    sort(rdx + 1, rdx + cnt + 1);
    rdx[0] = unique(rdx + 1, rdx + cnt + 1) - rdx - 1;
    for(int i = 1; i <= cnt; i ++)
        x[i] = lower_bound(rdx + 1, rdx + *rdx + 1, x[i]) - rdx;
    sort(rdy + 1, rdy + cnt + 1);
    rdy[0] = unique(rdy + 1, rdy + cnt + 1) - rdy - 1;
    for(int i = 1; i <= cnt; i ++)
        y[i] = lower_bound(rdy + 1, rdy + *rdy + 1, y[i]) - rdy;
}
}
using INIT::rdx;
using INIT::rdy;
namespace bitree{
inline int lowbit(int x) {return x & ~x + 1;}
int tr[N * 5];
void add(int x, int val){
    while(x <= *rdy){
        tr[x] += val;
        x += lowbit(x);
    }
}
int query(int x){
    if(x == 0) return 0;
    int res = 0;
    while(x > 0){
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}
}
namespace WORK{
int p[N * 5];
bool cmp(int a, int b){
    if(x[a] == x[b]){
        if(a <= n) return true;
        else return false;
    }
    return x[a] < x[b];
}
void solve(){
    for(int i = 1; i <= cnt; i ++)
        p[i] = i;
    sort(p + 1, p + cnt + 1, cmp);
    for(int i = 1; i <= cnt; i ++){
        if(p[i] <= n){
            bitree::add(y[p[i]], 1);
            #ifdef db
            for(int i = 1; i <= *rdy; i ++)
                printf("%d ", bitree::query(i));
            printf("\n");
            #endif
        } else{
            ans[p[i] - n] = bitree::query(y[p[i]]);
        }
    }
    for(int i = 1; i <= m; i ++){
        printf("%d\n", ans[i + 3 * m] - ans[i + 2 * m] - ans[i + m] + ans[i]);
    }
}
}
int main(){
    INIT::init_input();
    WORK::solve();
    return 0;
}