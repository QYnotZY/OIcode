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

const int N = 1e6 + 10;
int n, a[N], fa[N], dep[N];
vector<int> e[N];
int ql, qr, q[N], r[N];
double f[N];
double dis(int x, int depy){
    return f[x] + pow(double(depy - dep[x]), 1.5);
}
bool check(int x1, int x2, int mid){
    return dis(x1, mid) < dis(x2, mid);
}
int getr1(int x1, int x2){
    #ifdef db
    printf("bs %d %d ", x1, x2);
    #endif
    int left = dep[x2], right = n + 1;
    while(left + 1 < right){
        int mid = left + (right - left >> 1);
        if(check(x1, x2, mid)) left = mid;
        else right = mid;
    }
    #ifdef db
    printf("%d\n", left);
    #endif
    return right;
}
int getr2(int x1, int x2){
    #ifdef db
    printf("bs %d %d ", x1, x2);
    #endif
    int l=dep[x2]+1,r=n,ans=n+1;
    while(l<=r){
        int mid =(l+r)>>1;
        if(check(x1, x2, mid)) l=mid+1;
        else ans=mid,r=mid-1;
    }
    return ans;
}
void dfs(int u, int fat){
    #ifdef db
    printf("%d : %d %d\n", u, ql, qr);
    #endif
    dep[u] = dep[fat] + 1;
    int l0 = ql, r0 = qr; stack<pair<int, int> > st;
    while(ql < qr && r[ql] <= dep[u]) 
    #ifdef db
    printf("pop %d(%d)\n", ql, q[ql]),
    #endif
    ql ++;
    if(u != 1) f[u] = 1.0 * a[u] + dis(q[ql], dep[u]);
    #ifdef db
    printf("%d %.5lf %.5lf\n", q[ql], dis(q[ql], dep[u]), f[u]);
    #endif
    while(ql < qr&&r[qr-1]>=getr1(q[qr],u)){
        #ifdef db
        printf("pop %d(%d)\n", qr, q[qr]),
        #endif
        st.push(make_pair(q[qr], r[qr - 1])), qr --; //抽象
    }
     r[qr] = getr1(q[qr], u);
    q[++ qr] = u;
    for(auto v : e[u]) dfs(v, u);
    qr --;
    ql = l0;
    while(qr < r0) q[++ qr] = st.top().first, r[qr - 1] = st.top().second, st.pop();
}
int main(){
    // freopen("onepointfive.in", "r", stdin);
    // freopen("onepointfive.out", "w", stdout);
    n = read();
    for(int i = 1; i <= n ; i ++)
        a[i] = read();
    for(int i = 2; i <= n; i ++)
        fa[i] = read(), e[fa[i]].emplace_back(i);
    ql = 1;
    dfs(1, 0);
    for(int i = 1; i <= n; i ++)
        printf("%.4lf ", f[i]);
    return 0;
}