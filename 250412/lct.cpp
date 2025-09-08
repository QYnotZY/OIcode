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

const int N = 1e6 + 10;
namespace lct{
#define pa(x) tr[x].pa
#define lc(x) tr[x].c[0]
#define rc(x) tr[x].c[1]
#define jud(x) tr[pa(x)].c[1] == x
    int rt;
    struct node{
        int pa, c[2];
        int val, sum;
        int rev_tag;
    } tr[N];
    inline void pushup(int p){
        tr[p].sum = tr[lc(p)].sum ^ tr[rc(p)].sum ^ tr[p].val;
    }
    inline void pushdown(int p){
        if(tr[p].rev_tag){
            swap(lc(p), rc(p));
            tr[p].rev_tag ^= 1;
            tr[lc(p)].rev_tag ^= 1;
            tr[rc(p)].rev_tag ^= 1;
        }
    }
    int stk[N], top;
    inline bool notroot(int p){
        return tr[pa(p)].c[0] == p || tr[pa(p)].c[1] == p;
    }
    inline void pushall(int p){
        top = 0;
        while(notroot(p)) stk[++ top] = p, p = pa(p);
        pushdown(p);
        while(top) pushdown(stk[top --]);
    }
    inline void rotate(int x){
        int y = pa(x), z = pa(y);
        int zy = jud(y), yx = jud(x);
        tr[y].c[yx] = tr[x].c[yx ^ 1];
        pa(tr[y].c[yx]) = y;
        if(notroot(y)) tr[z].c[zy] = x;
        pa(x) = z;
        tr[x].c[yx ^ 1] = y;
        pa(y) = x;
        pushup(y), pushup(x);
    }
    inline void splay(int x){
        pushall(x);
        while(notroot(x)){
            int y = pa(x), z = pa(y);
            if(notroot(y))
                jud(x) ^ jud(y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }
    inline void access(int x){
        for(int lst = 0; x; lst = x, x = pa(x)){
            splay(x);
            rc(x) = lst;
            pushup(x);
        }
    }
    inline void makeroot(int x){
        access(x);
        splay(x);
        tr[x].rev_tag ^= 1;
    }
    inline void split(int x, int y){
        makeroot(x);
        access(y);
        splay(y);
    }
    inline int query(int x, int y){
        split(x, y);
        return tr[y].sum;
    }
    inline int findroot(int x){
        access(x);
        splay(x);
        while(lc(x))
            pushdown(x), x = lc(x);
        return splay(x), x;
    }
    inline void link(int x, int y){
        makeroot(x);
        if(findroot(y) != x) pa(x) = y;
    }
    inline void cut(int x, int y){
        makeroot(x);
        if(findroot(y) == x && pa(y) == x && !lc(y)){
            rc(x) = pa(y) = 0;
            pushup(x);
        }
    }
    inline void modify(int x, int v){
        tr[x].val = v;
        splay(x);
    }
#undef pa
#undef lc
#undef rc
#undef jud
}
int n, m;
int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        lct::tr[i].val = read();
    for(int i = 1; i <= m; i ++){
        int op = read(), x = read(), y = read();
        switch(op){
            case 0: printf("%d\n", lct::query(x, y)); break;
            case 1: lct::link(x, y); break;
            case 2: lct::cut(x, y); break;
            case 3: lct::modify(x, y); break;
        }
    }
    return 0;
}