#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
    T res = 0; bool f = 0;
    char ch = gc();
    for(; !('0' <= ch && ch <= '9'); ch = gc())
        if(ch == '-') f = !f;
    for(; '0' <= ch && ch <= '9'; ch = gc())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return f ? ~res + 1 : res;
}
inline char readch(bool sp = 0){
    char ch = gc();
    for(; !(33 - sp <= ch && ch < 127); ch = gc()) ;
    return ch;
}
template<typename T = int>
T read(bool ch = 0, bool sp = 0) {return ch ? readch(sp) : readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 1e6 + 10, inf = 1e7;
template<typename VT, int N>
class Splay{
    int rt, tot;
    struct node{
        int pa, c[2];
        VT val;
        int sz;
        int rev_tag;
    } tr[N];
    int newnode(VT v){
        ++ tot;
        tr[tot].pa = 0;
        tr[tot].c[0] = tr[tot].c[1] = 0;
        tr[tot].val = v;
        tr[tot].sz = 1;
        tr[tot].rev_tag = 0;
        return tot;
    }
    void pushup(int p){
        int &lc = tr[p].c[0], &rc = tr[p].c[1];
        tr[p].sz = tr[lc].sz + tr[rc].sz + 1;
    }
    void rev_upd(int p){
        swap(tr[p].c[0], tr[p].c[1]);
        tr[p].rev_tag ^= 1;
        tr[tr[p].c[0]].rev_tag ^= 1;
        tr[tr[p].c[1]].rev_tag ^= 1;
    }
    void pushdown(int p){
        if(tr[p].rev_tag) rev_upd(p);
    }
    void rotate(int x){
        int y = tr[x].pa, z = tr[y].pa;
        pushdown(y), pushdown(x);
        int yx = tr[y].c[1] == x, zy = tr[z].c[1] == y;
        tr[tr[x].c[yx ^ 1]].pa = y;
        tr[y].c[yx] = tr[x].c[yx ^ 1];
        tr[y].pa = x;
        tr[x].c[yx ^ 1] = y;
        tr[x].pa = z;
        tr[z].c[zy] = x;
        pushup(y), pushup(x);
    }
    void splay(int x, int goal){
        while(tr[x].pa != goal){
            int y = tr[x].pa, z = tr[y].pa;
            if(z != goal)
                (tr[z].c[1] == y) ^ (tr[y].c[1] == x) ? rotate(x) : rotate(y);
            rotate(x);
        }
        if(!goal) rt = x;
    }
    int create_pv(VT *a, int l, int r){
        if(l > r) return 0;
        int mid = l + (r - l >> 1);
        int p = newnode(a[mid]);
        int lc = create_pv(a, l, mid - 1), rc = create_pv(a, mid + 1, r);
        tr[p].c[0] = lc, tr[lc].pa = p;
        tr[p].c[1] = rc, tr[rc].pa = p;
        pushup(p);
        return p;
    }
    int get_rank_id(int k){
        int x = rt;
        while(true){
            pushdown(x);
            int &lc = tr[x].c[0];
            if(tr[lc].sz + 1 == k) return x;
            if(tr[lc].sz + 1 < k) k -= tr[lc].sz + 1, x = tr[x].c[1];
            else x = tr[x].c[0];
        }
    }
public:
    void create(VT *a, int l, int r){
        rt = create_pv(a, l, r);
    }
    void reverse(int l, int r){
        int x = get_rank_id(l), y = get_rank_id(r + 2);
        splay(x, 0), splay(y, x);
        int z = tr[y].c[0];
        tr[z].rev_tag ^= 1;
    }
    void print(int p = -1){
        if(!~p) p = rt;
        if(!p) return;
        pushdown(p);
        print(tr[p].c[0]);
        if(-inf < tr[p].val && tr[p].val < inf)
            printf("%d ", tr[p].val);
        print(tr[p].c[1]);
    }
} ;
int n, m;
int a[N];
Splay<int, N> sq;
int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = i;
    a[0] = -inf, a[n + 1] = inf;
    sq.create(a, 0, n + 1);
    for(int l, r; m --;){
        l = read(), r = read();
        sq.reverse(l, r);
    }
    sq.print();
    return 0;
}