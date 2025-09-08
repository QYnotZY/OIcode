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

const int N=5e5+10,inf=0x3fffffff;
//sgmtb
inline int mid(int l, int r) {return l + (r - l >> 1);}
inline int lc(int p) {return p << 1;}
inline int rc(int p) {return p << 1 | 1;}
struct segnode{
    int l, r;
    int maxx, max2, maxc, mintag, minn, min2, minc, maxtag, addtag;
    ll sum;
    int size() {return r - l + 1;}
}tr[N<<2];
bool updmin1(int p, int val){
    if(val >= tr[p].maxx) return 1;
    if(val > tr[p].max2){
        if(tr[p].minn == tr[p].maxx) tr[p].minn = val;
        if(tr[p].min2 == tr[p].maxx) tr[p].min2 = val;
        if(tr[p].maxtag > val) tr[p].maxtag = val;
        tr[p].sum -= 1ll * (tr[p].maxx - val) * tr[p].maxc;
        tr[p].maxx = val; tr[p].mintag = val;
        return 1;
    }
    return 0;
}
bool updmax1(int p, int val){
    if(val <= tr[p].minn) return 1;
    if(val < tr[p].min2){
        if(tr[p].maxx == tr[p].minn) tr[p].maxx = val;
        if(tr[p].max2 == tr[p].minn) tr[p].max2 = val;
        if(tr[p].mintag < val) tr[p].mintag = val;
        tr[p].sum += 1ll * (val - tr[p].minn) * tr[p].minc;
        tr[p].minn = val; tr[p].maxtag = val;
        return 1;
    }
    return 0;
}
void updadd1(int p, int val){
    tr[p].maxx += val; tr[p].max2 += val; tr[p].mintag += val;
    tr[p].minn += val; tr[p].min2 += val; tr[p].maxtag += val;
    tr[p].addtag += val; tr[p].sum += 1ll * val * tr[p].size();
}
void pushdown(int p){
    updadd1(lc(p), tr[p].addtag); updadd1(rc(p), tr[p].addtag); tr[p].addtag = 0;
    updmin1(lc(p), tr[p].mintag); updmin1(rc(p), tr[p].mintag); tr[p].mintag = inf;
    updmax1(lc(p), tr[p].maxtag); updmax1(rc(p), tr[p].maxtag); tr[p].maxtag = -inf;
}
void pushup(int p){
    if(tr[lc(p)].maxx > tr[rc(p)].maxx){
        tr[p].maxx = tr[lc(p)].maxx;
        tr[p].max2 = max(tr[rc(p)].maxx, tr[lc(p)].max2);
        tr[p].maxc = tr[lc(p)].maxc;
    }else if(tr[lc(p)].maxx == tr[rc(p)].maxx){
        tr[p].maxx = tr[lc(p)].maxx;
        tr[p].max2 = max(tr[lc(p)].max2, tr[rc(p)].max2);
        tr[p].maxc = tr[lc(p)].maxc + tr[rc(p)].maxc;
    }else{
        tr[p].maxx = tr[rc(p)].maxx;
        tr[p].max2 = max(tr[lc(p)].maxx, tr[rc(p)].max2);
        tr[p].maxc = tr[rc(p)].maxc;
    }
    if(tr[lc(p)].minn < tr[rc(p)].minn){
        tr[p].minn = tr[lc(p)].minn;
        tr[p].min2 = min(tr[rc(p)].minn, tr[lc(p)].min2);
        tr[p].minc = tr[lc(p)].minc;
    }else if(tr[lc(p)].minn == tr[rc(p)].minn){
        tr[p].minn = tr[lc(p)].minn;
        tr[p].min2 = min(tr[lc(p)].min2, tr[rc(p)].min2);
        tr[p].minc = tr[lc(p)].minc + tr[rc(p)].minc;
    }else{
        tr[p].minn = tr[rc(p)].minn;
        tr[p].min2 = min(tr[lc(p)].minn, tr[rc(p)].min2);
        tr[p].minc = tr[rc(p)].minc;
    }
    tr[p].sum = tr[lc(p)].sum + tr[rc(p)].sum;
}
void modifyAdd(int l0, int r0, int val, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return updadd1(p, val);
    pushdown(p);
    if(l0 <= tr[lc(p)].r) modifyAdd(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) modifyAdd(l0, r0, val, rc(p));
    pushup(p);
}
void modifyMin(int l0, int r0, int val, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        if(updmin1(p, val)) return;
    pushdown(p);
    if(l0 <= tr[lc(p)].r) modifyMin(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) modifyMin(l0, r0, val, rc(p));
    pushup(p);
}
void modifyMax(int l0, int r0, int val, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        if(updmax1(p, val)) return;
    pushdown(p);
    if(l0 <= tr[lc(p)].r) modifyMax(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) modifyMax(l0, r0, val, rc(p));
    pushup(p);
}
ll querySum(int l0, int r0, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return tr[p].sum;
    pushdown(p);
    ll res = 0;
    if(l0 <= tr[lc(p)].r) res += querySum(l0, r0, lc(p));
    if(r0 >= tr[rc(p)].l) res += querySum(l0, r0, rc(p));
    return res;
}
int queryMin(int l0, int r0, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return tr[p].minn;
    pushdown(p);
    int res = inf;
    if(l0 <= tr[lc(p)].r) res = min(res, queryMin(l0, r0, lc(p)));
    if(r0 >= tr[rc(p)].l) res = min(res, queryMin(l0, r0, rc(p)));
    return res;
}
int queryMax(int l0, int r0, int p = 1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return tr[p].maxx;
    pushdown(p);
    int res = -inf;
    if(l0 <= tr[lc(p)].r) res = max(res, queryMax(l0, r0, lc(p)));
    if(r0 >= tr[rc(p)].l) res = max(res, queryMax(l0, r0, rc(p)));
    return res;
}
int n, m, a[N];
void Create(int p = 1, int l = 1, int r = n){
    tr[p] = segnode{l, r, a[l], -inf, 1, inf, a[r], inf, 1, -inf, 0, a[l]};
    if(l == r) return;
    Create(lc(p), l, mid(l, r));
    Create(rc(p), mid(l, r) + 1, r);
    pushup(p);
}
//sgmtb
int main(){
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    Create();
    m = read();
    for(int i = 1, op, l, r, x; i <= m; i ++){
        op = read(), l = read(), r = read();
        switch(op){
            case 1:{
                x = read();
                modifyAdd(l, r, x);
                break;
            }
            case 2:{
                x = read();
                modifyMax(l, r, x);
                break;
            }
            case 3:{
                x = read();
                modifyMin(l, r, x);
                break;
            }
            case 4:{
                printf("%lld\n", querySum(l, r));
                break;
            }
            case 5:{
                printf("%d\n", queryMax(l, r));
                break;
            }
            case 6:{
                printf("%d\n", queryMin(l, r));
                break;
            }
        }
    }
    return 0;
}