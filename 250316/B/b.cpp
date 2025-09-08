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
int n, m;
int curidx, rt[N];
struct segnode{
    int lc, rc;
    int minlst;
}tr[N * 20];
void pushup(segnode &pa, segnode lc, segnode rc){
    pa.minlst = min(lc.minlst, rc.minlst);
}
void Insert(int x, int v, int p1, int p, int l = 0, int r = N){
    tr[p1] = tr[p];
    if(l == r){
        tr[p1].minlst = v;
        #ifdef db
        printf("%d %d %d\n",l,r,tr[p1].minlst);
        #endif
        return;
    }
    int mid = l + (r - l >> 1);
    if(x <= mid){
        tr[p1].lc = ++ curidx;
        Insert(x, v, tr[p1].lc, tr[p].lc, l, mid);
    }else{
        tr[p1].rc = ++ curidx;
        Insert(x, v, tr[p1].rc, tr[p].rc, mid + 1, r);
    }
    pushup(tr[p1], tr[tr[p1].lc], tr[tr[p1].rc]);
    #ifdef db
    printf("%d %d %d\n",l,r,tr[p1].minlst);
    #endif
}
int Query(int l0, int p, int l = 0, int r = N){
    #ifdef db
    printf("%d %d %d %d\n",l0,l,r,tr[p].minlst);
    #endif
    if(l == r) return l;
    int mid = l + (r - l >> 1);
    int tmp = tr[tr[p].lc].minlst;
    if(tmp < l0) return Query(l0, tr[p].lc, l, mid);
    else return Query(l0, tr[p].rc, mid + 1, r);
}
int main(){
    tr[0].minlst = 0;
    n = read(), m = read();
    for(int i = 1; i <= n; i ++){
        rt[i] = ++ curidx;
        Insert(read(), i, rt[i], rt[i - 1]);
    }
    for(int i = 1; i <= m; i ++){
        int l = read(), r = read();
        printf("%d\n", Query(l, rt[r]));
    }
    return 0;
}