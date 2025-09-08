#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned int uint;
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
const int N=1e5+10;
uint x,y,z;
uint rng61(){
    x=x^(x<<11);
    x=x^(x>>4);
    x=x^(x<<5);
    x=x^(x>>14);
    uint w=x^(y^z);
    x=y;
    y=z;
    z=w;
    return z;
}
//segment tree
inline int mid(int l, int r) {return l + (r - l >> 1);}
inline int lc(int p) {return p << 1;}
inline int rc(int p) {return p << 1 | 1;}
struct segnode{
    int l, r;
    int maxx;
    int ver;
}tr[N<<2];
void upd1(int p, int val){
    tr[p].maxx = max(tr[p].maxx, val);
}
void pushdown(int p){
    upd1(lc(p), tr[p].maxx);
    upd1(rc(p), tr[p].maxx);
}
void Modify(int l0, int r0, int val, int p = 1){
    if(tr[p].maxx > val) return;
    if(l0 <= tr[p].l && tr[p].r <= r0){
        upd1(p, val);
        return;
    }
    if(l0 <= tr[lc(p)].r) Modify(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) Modify(l0, r0, val, rc(p));
}
int t,n,m;
ll Query(){
    ll res = 0ll;
    for(int p = 1; p <= n << 2; p++){
        if(tr[p].ver != t) continue;
        if(tr[p].l == tr[p].r) res ^= 1ll * tr[p].l * tr[p].maxx;
        else pushdown(p);
    }
    return res;
}
void Create(int p = 1, int l = 1, int r = n){
    tr[p] = segnode{l, r, 0, t};
    if(l == r) return;
    Create(lc(p), l, mid(l, r));
    Create(rc(p), mid(l, r) + 1, r);
}
//segment tree
int main(){
    scanf("%d",&t);
    while(t--){
        n=read();m=read();
        x=read<uint>();y=read<uint>();z=read<uint>();
        Create();
        for(int i=1,l,r,v;i<=m;i++){
            l=rng61()%n+1;
            r=rng61()%n+1;
            if(l>r) swap(l,r);
            v=rng61()%1073741824;
            Modify(l,r,v);
        }
        printf("%lld\n",Query());
    }
    return 0;
}