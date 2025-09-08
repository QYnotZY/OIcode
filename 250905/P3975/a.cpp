#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 5e5 + 10;
namespace sam {
    struct node {
        int trans[26], fa;
        int val, len;
    } tr[N << 1];
    int tot = 1, lst = 1;
    void extend(int ch) {
        int p = lst, np = ++ tot; lst = np;
        tr[np].val = 1, tr[np].len = tr[p].len + 1;
        for(; p && !tr[p].trans[ch]; p = tr[p].fa) tr[p].trans[ch] = np;
        if(!p) return void(tr[np].fa = 1);
        int q = tr[p].trans[ch];
        if(tr[q].len == tr[p].len + 1) return void(tr[np].fa = q);
        int nq = ++ tot;
        tr[nq].val = 0, tr[nq].len = tr[p].len + 1;
        tr[nq].fa = tr[q].fa; tr[q].fa = tr[np].fa = nq;
        for(; p && tr[p].trans[ch] == q; p = tr[p].fa) tr[p].trans[ch] = nq;
        memcpy(tr[nq].trans, tr[q].trans, sizeof(tr[q].trans));
    }
    int tmp[N << 1], topo[N << 1];
    void build() {
        for(int i = 1; i <= tot; i ++) ++ tmp[tr[i].len];
        for(int i = 1; i <= tot; i ++) tmp[i] += tmp[i - 1];
        for(int i = 1; i <= tot; i ++) topo[tmp[tr[i].len] --] = i;
    }
    ll sz[N << 1], dp[N << 1];
    void dfs(int typ) {
        for(int i = 1; i <= tot; i ++) sz[i] = tr[i].val;
        for(int i = tot; i; -- i) sz[tr[topo[i]].fa] += sz[topo[i]];
        dp[1] = 0; for(int i = 2; i <= tot; i ++) dp[i] = typ ? sz[i] : 1;
        for(int i = tot; i; -- i) for(int j = 0; j < 26; j ++) dp[topo[i]] += dp[tr[topo[i]].trans[j]];
    }
    void query(int p, int typ, ll k) {
        if(p == 1 && dp[p] < k) return void(printf("-1\n"));
        if(p ^ 1 && k <= (typ ? sz[p] : 1)) return;
        if(p ^ 1) k -= typ ? sz[p] : 1;
        for(int i = 0; i < 26; i ++) {
            if(k > dp[tr[p].trans[i]]) k -= dp[tr[p].trans[i]];
            else return printf("%c", 'a' + i), query(tr[p].trans[i], typ, k);
        }
    }
}
char s[N];
int n, t; ll k;
void Hutao() {
    scanf("%s", s + 1); n = strlen(s + 1);
    t = read(), k = read<ll>();
    for(int i = 1; i <= n; i ++) sam::extend(s[i] - 'a');
    sam::build();
    sam::dfs(t);
    sam::query(1, t, k);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}