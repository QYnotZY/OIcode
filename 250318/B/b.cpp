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

constexpr int N = 2e5 + 10;
int n, q, a[N];
int cnt[N];
int bs;
struct node{
    int l, r, id;
    bool operator < (node obj){
        if(l/bs == obj.l/bs) return r < obj.r;
        return l/bs < obj.l/bs;
    }
}qr[N];
int l, r;
ll ans, ansq[N];
void move(int pos1, int sign){
    if(sign == 1){
        ans += 1ll * cnt[a[pos1]] * (cnt[a[pos1]] - 1) / 2;
    }
    cnt[a[pos1]] += sign;
    if(sign == -1){
        ans -= 1ll * cnt[a[pos1]] * (cnt[a[pos1]] - 1) / 2;
    }
}
int main(){
    n = read(), q = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1; i <= q; i ++)
        qr[i].l = read(), qr[i].r = read(), qr[i].id = i;
    bs = (int)ceil(sqrt(n));
    sort(qr + 1, qr + q + 1);
    l = 1, r = 1, cnt[a[1]] = 1, ans = 0;
    for(int i = 1; i <= q; i ++){
        const node &qq = qr[i];
        while (l > qq.l) move(--l, 1);
        while (r < qq.r) move(++r, 1);
        while (l < qq.l) move(l++, -1);
        while (r > qq.r) move(r--, -1);
        ansq[qq.id] = ans;
    }
    for(int i = 1; i <= q; i ++)
        printf("%lld\n", ansq[i]);
    return 0;
}