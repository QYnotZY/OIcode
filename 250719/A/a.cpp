#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T = int>
inline T read(){
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
}
using FastIO::read;
using FastIO::readch;
typedef long long ll;
namespace work {
const int N = 1e5 + 10, aN = 2e6 + 10, Sgm = 4;
int mp[128];
int n, m;
char s[N];
int mp1[N], mp2[N];
namespace trie {
    struct node {
        int trans[Sgm];
        vector<int> end;
        int ql, qr;
    } tr[aN];
    int rt, tot, stot;
    void init() {
        rt = tot = 1; stot = 0;
    }
    void insert(char *s, int id) {
        int cur = rt, len = strlen(s);
        for(int i = 1, j; i <= len; i ++) {
            j = mp[s[i - 1]];
            if(!tr[cur].trans[j]) tr[cur].trans[j] = ++ tot;
            cur = tr[cur].trans[j];
        }
        tr[cur].end.push_back(id);
    }
    void build(int u = rt) {
        tr[u].ql = stot;
        for(auto ele : tr[u].end) {
            mp1[ele] = ++ stot;
        }
        for(int i = 0; i < Sgm; i ++)
            if(tr[u].trans[i]) build(tr[u].trans[i]);
        tr[u].qr = stot;
    }
    int query(char *s) {
        int cur = rt, len = strlen(s);
        for(int i = 1, j; i <= len; i ++) {
            j = mp[s[i - 1]];
            if(!tr[cur].trans[j]) return 0;
            cur = tr[cur].trans[j];
        }
        return cur;
    }
}
namespace trier {
    struct node {
        int trans[Sgm];
        vector<int> end;
        int ql, qr;
    } tr[aN];
    int rt, tot, stot;
    void init() {
        rt = tot = 1; stot = 0;
    }
    void insert(char *s, int id) {
        int cur = rt, len = strlen(s);
        for(int i = len, j; i; i --) {
            j = mp[s[i - 1]];
            if(!tr[cur].trans[j]) tr[cur].trans[j] = ++ tot;
            cur = tr[cur].trans[j];
        }
        tr[cur].end.push_back(id);
    }
    void build(int u = rt) {
        tr[u].ql = stot;
        for(auto ele : tr[u].end) {
            mp2[ele] = ++ stot;
        }
        for(int i = 0; i < Sgm; i ++)
            if(tr[u].trans[i]) build(tr[u].trans[i]);
        tr[u].qr = stot;
    }
    int query(char *s) {
        int cur = rt, len = strlen(s);
        for(int i = len, j; i; i --) {
            j = mp[s[i - 1]];
            if(!tr[cur].trans[j]) return 0;
            cur = tr[cur].trans[j];
        }
        return cur;
    }
}
struct UPD {
    int x, y;
    bool operator < (UPD obj) {
        return x < obj.x;
    }
} u[N];
struct QRY {
    int id, sym, x, y1, y2;
    bool operator < (QRY obj) {
        return x < obj.x;
    }
} q[N << 1];
int ans[N];
namespace bit {
    int tr[N];
    inline int lowbit(int x) {return x & -x;}
    void add(int x) {
        while(x <= n) {
            tr[x] ++;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int res = 0;
        while(x) {
            res += tr[x];
            x -= lowbit(x);
        }
        return res;
    }
}
void Hutao() {
    mp['A'] = 0, mp['C'] = 1, mp['G'] = 2, mp['U'] = 3;
    trie::init(), trier::init();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++) {
        scanf("%s", s);
        trie::insert(s, i);
        trier::insert(s, i);
    }
    trie::build(), trier::build();
    for(int i = 1; i <= n; i ++)
        u[i] = {mp1[i], mp2[i]};
    for(int i = 1, p1, p2; i <= m; i ++) {
        scanf("%s", s);
        p1 = trie::query(s);
        scanf("%s", s);
        p2 = trier::query(s);
        q[(i << 1) - 1] = {i, -1, trie::tr[p1].ql, trier::tr[p2].ql, trier::tr[p2].qr};
        q[i << 1] = {i, 1, trie::tr[p1].qr, trier::tr[p2].ql, trier::tr[p2].qr};
    }
    sort(u + 1, u + n + 1);
    sort(q + 1, q + 2 * m + 1);
    for(int x = 0, i = 1, j = 1; x <= n; x ++) {
        for(; i <= n && u[i].x == x; i ++)
            bit::add(u[i].y);
        for(; j <= m << 1 && q[j].x == x; j ++) 
            ans[q[j].id] += q[j].sym * (bit::query(q[j].y2) - bit::query(q[j].y1));
    }
    for(int i = 1; i <= m; i ++)
        printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}