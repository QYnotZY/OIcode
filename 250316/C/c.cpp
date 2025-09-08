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
char readch(){
    char ch = getchar();
    while(33 > ch || ch > 126) ch = getchar();
    return ch;
}

const int N = 6e5 + 10, lgA = 25;
int curidx, rt[N];
struct trienode{
    int cnt;
    int next[2];
}tr[N << 5];
void Insert(int p, int p1, int x){
    for(int i = lgA - 1; i >= 0; i --){
        tr[p1] = tr[p];
        tr[p1].cnt ++;
        if(x & (1 << i)){
            tr[p1].next[1] = ++ curidx;
            p = tr[p].next[1];
            p1 = tr[p1].next[1];
        } else{
            tr[p1].next[0] = ++ curidx;
            p = tr[p].next[0];
            p1 = tr[p1].next[0];
        }
    }
    tr[p1] = tr[p];
    tr[p1].cnt ++;
}
int Query(int pl, int pr, int x){
    int res = 0;
    for(int i = lgA - 1; i >= 0; i --){
        int tmp = (x & (1 << i)) >> i;
        if(tr[tr[pr].next[1-tmp]].cnt - tr[tr[pl].next[1-tmp]].cnt){
            res += (1 << i);
            pl = tr[pl].next[1-tmp];
            pr = tr[pr].next[1-tmp];
        } else{
            pl = tr[pl].next[tmp];
            pr = tr[pr].next[tmp];
        }
    }
    return res;
}
int n, m, sn;
int main(){
    n = read(), m = read();
    Insert(0, rt[1] = ++ curidx, 0);
    for(int i = 1; i <= n; i ++){
        int x = read(); sn ^= x;
        rt[i + 1] = ++ curidx;
        Insert(rt[i], rt[i + 1], sn);
    }
    char op;
    for(int i = 1; i <= m; i ++){
        op = readch();
        if(op == 'A'){
            int x = read(); sn ^= x;
            rt[(++ n) + 1] = ++ curidx;
            Insert(rt[n], rt[n + 1], sn);
        }
        if(op == 'Q'){
            int l = read(), r = read(), x = read();
            printf("%d\n", Query(rt[l - 1], rt[r], x ^ sn));
        }
    }
    return 0;
}