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
const int N = 1e6 + 10;
namespace sam {
    struct node {
        int trans[26], fa;
        int val, len;
    } tr[N << 1];
    int tot = 1, lst = 1;
    void extend(int ch) {
        int p = lst, np = ++ tot; lst = np;
        tr[np].val = 1; tr[np].len = tr[p].len + 1;
        for(; p && !tr[p].trans[ch]; p = tr[p].fa) tr[p].trans[ch] = np;
        if(!p) return void(tr[np].fa = 1);
        int q = tr[p].trans[ch];
        if(tr[q].len == tr[p].len + 1) return void(tr[np].fa = q);
        int nq = ++ tot;
        tr[nq].val = 0; tr[nq].len = tr[p].len + 1;
        tr[nq].fa = tr[q].fa; tr[q].fa = tr[np].fa = nq;
        for(; p && tr[p].trans[ch] == q; p = tr[p].fa) tr[p].trans[ch] = nq;
        memcpy(tr[nq].trans, tr[q].trans, sizeof(tr[q].trans));
    }
    vector<int> son[N << 1];
    int sz[N << 1];
    void build() {
        for(int i = 2; i <= tot; i ++)
            son[tr[i].fa].push_back(i);
    }
    ll ans;
    void dfs(int u = 1) {
        sz[u] = tr[u].val;
        for(auto v : son[u]) {
            dfs(v);
            sz[u] += sz[v];
        }
        if(sz[u] ^ 1) ans = max(ans, 1ll * sz[u] * tr[u].len);
    }
}
int n;
char s[N];
void Hutao() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 1; i <= n; i ++)
        sam::extend(s[i] - 'a');
    sam::build();
    sam::dfs();
    printf("%lld", sam::ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}