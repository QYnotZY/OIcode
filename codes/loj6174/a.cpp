#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e5 + 10;
char s[N], t[N];
int n, m, a[N], b[N];
int prea[N][4], preb[N][4], suma[4], sumb[4];
int p[4][2];
int x[N];
namespace smt {
    struct node {
        int maxx, tag;
    } tr[N << 2];
    void pushup(int p) {
        tr[p].maxx = max(tr[p << 1].maxx, tr[p << 1 | 1].maxx);
    }
    void add1(int p, int v) {
        tr[p].maxx += v;
        tr[p].tag += v;
    }
    void pushdn(int p) {
        add1(p << 1, tr[p].tag);
        add1(p << 1 | 1, tr[p].tag);
        tr[p].tag = 0;
    }
    void build(int p = 1, int l = 0, int r = n) {
        if(l == r) return void(tr[p].maxx = x[l]);
        tr[p].tag = 0;
        int mid = l + r >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int v, int p = 1, int l = 0, int r = n) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) return add1(p, v);
        pushdn(p);
        int mid = l + r >> 1;
        if(ql <= mid) update(ql, qr, v, p << 1, l, mid);
        if(mid < qr) update(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query() {return tr[1].maxx;}
}
void Hutao() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    for(int i = 1; i <= n; i ++) {
        memcpy(prea[i], prea[i - 1], 16);
        switch(s[i]) {
            case 'A' : a[i] = 0; ++ prea[i][0]; break;
            case 'C' : a[i] = 1; ++ prea[i][1]; break;
            case 'G' : a[i] = 2; ++ prea[i][2]; break;
            case 'T' : a[i] = 3; ++ prea[i][3]; break;
        }
    } memcpy(suma, prea[n], 16);
    for(int i = 1; i <= m; i ++) {
        memcpy(preb[i], preb[i - 1], 16);
        switch(t[i]) {
            case 'A' : b[i] = 0; ++ preb[i][0]; break;
            case 'C' : b[i] = 1; ++ preb[i][1]; break;
            case 'G' : b[i] = 2; ++ preb[i][2]; break;
            case 'T' : b[i] = 3; ++ preb[i][3]; break;
        }
    } memcpy(sumb, preb[m], 16);
    #ifdef db
    for(int i = 0; i <= n; i ++) {for(int j = 0; j < 4; j ++) printf("%d ", prea[i][j]); printf("\n");}
    for(int i = 0; i <= m; i ++) {for(int j = 0; j < 4; j ++) printf("%d ", preb[i][j]); printf("\n");}
    #endif
    for(int i = 0; i <= n; i ++) {
        x[i] = min(prea[i][0], suma[0] + sumb[0] - prea[i][0]);
        x[i] += min(prea[i][1], suma[1] + sumb[1] - prea[i][1]);
        x[i] += min(prea[i][2], suma[2] + sumb[2] - prea[i][2]);
        x[i] += min(prea[i][3], suma[3] + sumb[3] - prea[i][3]);
        #ifdef db
        printf("%d ", x[i]);
        #endif
    }
    #ifdef db
    putchar('\n');
    #endif
    smt::build();
    p[0][0] = p[1][0] = p[2][0] = p[3][0] = p[0][1] = p[1][1] = p[2][1] = p[3][1] = n;
    int ans = smt::query();
    for(int i = 1; i <= m; i ++) {
        while(~p[b[i]][0] && prea[p[b[i]][0]][b[i]] > (suma[b[i]] + sumb[b[i]] >> 1) - preb[i][b[i]]) -- p[b[i]][0];
        while(~p[b[i]][1] && prea[p[b[i]][1]][b[i]] >= (suma[b[i]] + sumb[b[i]] + 1 >> 1) - preb[i - 1][b[i]]) -- p[b[i]][1];
        smt::update(0, p[b[i]][0], 1), smt::update(p[b[i]][1] + 1, n, -1);
        #ifdef db
        printf("%d %d %d\n", p[b[i]][0], p[b[i]][1], smt::query());
        #endif
        ans = max(ans, smt::query());
    }
    printf("%d\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}