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
const ll mod = 998244353;
int n, m;
ll a[N];
namespace smt{
int cnttr;
struct segnode{
    int lc, rc;
    int tag;
    ll t[47];
    int tsz;
}tr[N << 2];
void upd1(segnode &p, int val){
    p.tag += val;
    if(p.tsz > 24){
        int tmp = min(p.tsz - 24, val);
        val -= tmp;
        p.tsz -= tmp;
        for(int i = 0; i < p.tsz; i ++)
            p.t[i] = p.t[i + tmp];
    }
    val %= 24;
    if(!val) return;
    int tmp[24];
    for(int i = 0; i < p.tsz; i ++)
        tmp[i] = p.t[(i + val) % 24];
    for(int i = 0; i < p.tsz; i ++)
        p.t[i] = tmp[i];
}
void pushup(segnode &p, segnode &lc, segnode &rc){
    p.tsz = max(lc.tsz, rc.tsz);
    for(int i = 0, j = 0, k = 0; i < p.tsz; i ++, ++ j, ++ k){
        if(j >= lc.tsz) j -= 24;
        if(k >= rc.tsz) k -= 24;
        p.t[i] = (lc.t[j] + rc.t[k]) % mod;
    }
}
void pushdown(segnode &p, segnode &lc, segnode &rc){
    upd1(lc, p.tag);
    upd1(rc, p.tag);
    p.tag = 0;
}
void modify(int l0, int r0, int p, int l = 1, int r = n){
    if(l0 <= l && r <= r0) return upd1(tr[p], 1);
    int mid = l + (r - l >> 1);
    pushdown(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
    if(l0 <= mid) modify(l0, r0, tr[p].lc, l, mid);
    if(r0 > mid) modify(l0, r0, tr[p].rc, mid + 1, r);
    pushup(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
}
ll query(int l0, int r0, int p, int l = 1, int r = n){
    if(l0 <= l && r <= r0) return tr[p].t[0];
    int mid = l + (r - l >> 1);
    ll res = 0ll;
    pushdown(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
    if(l0 <= mid) res += query(l0, r0, tr[p].lc, l, mid);
    if(r0 > mid) res += query(l0, r0, tr[p].rc, mid + 1, r);
    return res % mod;
}
void create(int p, int l = 1, int r = n){
    if(l == r){
        tr[p].tsz = 47;
        tr[p].tag = 0;
        tr[p].t[0] = a[l];
        for(int i = 1; i < tr[p].tsz; i ++)
            tr[p].t[i] = tr[p].t[i - 1] * tr[p].t[i - 1] % mod;
        return;
    }
    int mid = l + (r - l >> 1);
    tr[p].lc = ++ cnttr;
    create(tr[p].lc, l, mid);
    tr[p].rc = ++ cnttr;
    create(tr[p].rc, mid + 1, r);
    pushup(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
}
}
int main(){
    #ifdef db
    freopen("nagato2.in", "r", stdin);
    freopen("mine2.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read<ll>();
    smt::create(++ smt::cnttr);
    for(int i = 1, op, l, r; i <= m; i ++){
        op = read(), l = read(), r = read();
        if(op == 1) smt::modify(l, r, 1);
        if(op == 2) printf("%lld\n", smt::query(l, r, 1));
    }
    return 0;
}