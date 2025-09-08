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

const int N = 2e5 + 10;
int n, m, a[N];
int curseg, rt[N], currt;
int redc[N];
void disc(){
    for(int i = 1; i <= n; i ++)
        redc[i] = a[i];
    sort(redc + 1, redc + n + 1);
    redc[0] = unique(redc + 1, redc + n + 1) - redc - 1;
}
int dc(int x){
    return lower_bound(redc + 1, redc + redc[0] + 1, x) - redc;
}
struct segnode{
    int lc, rc;
    int sum;
}tr[N * 20];
void pushup(segnode &tgt, segnode &lc, segnode &rc){
    tgt.sum = lc.sum + rc.sum;
}
void Modify(int x, int p, int p1, int l = 1, int r = n){
    tr[p1] = tr[p];
    if(l == r){
        tr[p1].sum ++;
        return;
    }
    int mid = l + (r - l >> 1);
    if(x <= mid){
        tr[p1].lc = ++ curseg;
        Modify(x, tr[p].lc, tr[p1].lc, l, mid);
    }
    if(x > mid){
        tr[p1].rc = ++ curseg;
        Modify(x, tr[p].rc, tr[p1].rc, mid + 1, r);
    }
    pushup(tr[p1], tr[tr[p1].lc], tr[tr[p1].rc]);
}
int Query(int k, int pl, int pr, int l = 1, int r = n){
    if(l == r) return l;
    int mid = l + (r - l >> 1), tmp = tr[tr[pr].lc].sum - tr[tr[pl].lc].sum;
    #ifdef db
    printf("%d\n",tmp);
    #endif
    if(tmp >= k) return Query(k, tr[pl].lc, tr[pr].lc, l, mid);
    else return Query(k - tmp, tr[pl].rc, tr[pr].rc, mid + 1, r);
}
int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    disc();
    for(int i = 1; i <= n; i ++){
        rt[++ currt] = ++ curseg;
        Modify(dc(a[i]), rt[currt - 1], rt[currt]);
    }
    #ifdef db
    for(int i = 1; i <= n; i ++) 
        printf("%d ", tr[rt[i]].sum);
    #endif
    for(int i = 1, l, r, k; i <= m; i ++){
        l = read(), r = read(), k = read();
        printf("%d\n", redc[Query(k, rt[l - 1], rt[r])]);
    }
    return 0;
}