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

const int N = 2e5;
int n, k, a[N + 100], b[N + 100], c[N + 100], ans[N + 100];
namespace smt{
int tot, rt[N + 100];
struct segnode{
    int lc, rc;
    int sum;
}tr[N << 6];
void pushup(segnode &p, segnode lc, segnode rc){
    p.sum = lc.sum + rc.sum;
}
void modify(int x0, int val, int p, int l = 1, int r = k){
    if(l == r){
        tr[p].sum += val;
        return;
    }
    int mid = l + (r - l >> 1);
    if(x0 <= mid){
        if(tr[p].lc == 0) tr[p].lc = ++ tot;
        modify(x0, val, tr[p].lc, l, mid);
    } else{
        if(tr[p].rc == 0) tr[p].rc = ++ tot;
        modify(x0, val, tr[p].rc, mid + 1, r);
    }
    pushup(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
}
int query(int l0, int r0, int p, int l = 1, int r = k){
    if(l0 <= l && r <= r0) return tr[p].sum;
    int mid = l + (r - l >> 1), res = 0;
    if(tr[p].lc && l0 <= mid) res += query(l0, r0, tr[p].lc, l, mid);
    if(tr[p].rc && r0 > mid) res += query(l0, r0, tr[p].rc, mid + 1, r);
    return res;
}
void m(int ver, int val){
    if(!rt[ver]) rt[ver] = ++ tot;
    modify(val, 1, rt[ver]);
}
int q(int ver, int cmax){
    return query(1, cmax, rt[ver]);
}
}
namespace bismt{
inline int lowbit(int x) {return x & -x;}
void add(int b, int c){
    int x = b;
    while(x <= k){
        smt::m(x, c);
        x += lowbit(x);
    }
}
int query(int b, int c){
    int x = b, res = 0;
    while(x > 0){
        res += smt::q(x, c);
        x -= lowbit(x);
    }
    return res;
}
}
namespace WORK{
int p[N + 100];
bool cmpp(int x, int y){
    return a[x] < a[y];
}
void solve(){
    n = read(), k = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), b[i] = read(), c[i] = read(), p[i] = i;
    sort(p + 1, p + n + 1, cmpp);
    for(int i = 1, j = 1; i <= n; i = j){
        while(j <= n && a[p[j]] == a[p[i]]) bismt::add(b[p[j]], c[p[j]]), ++ j;
        for(int k = i; k < j; k ++) ans[bismt::query(b[p[k]], c[p[k]]) - 1] ++;
    }
    for(int i = 0; i < n; i ++)
        printf("%d\n", ans[i]);
}
}
int main(){
    WORK::solve();
    return 0;
}