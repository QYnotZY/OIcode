#include <iostream>
#include <cassert>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <random>
#include <chrono>
#include <ctime>
#include <map>
#include <set>
using namespace std;
// #define int long long
#define pii pair<int, int>
#define eb emplace_back
#define F first
#define S second
#define test(x) cout << "Test: " << (x) << '\n'
#define lowbit(x) (x & -x)
#define debug puts("qwq")
#define open(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define close fclose(stdin);fclose(stdout);
namespace FastIO {
	template <typename T = int>
	inline T read() {
		T s = 0, w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		return s * w;
	}
	template <typename T>
	inline void read(T &s) {
		s = 0;
		int w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		s = s * w;
	}
	template <typename T, typename... Arp> inline void read(T &x, Arp &...arp) {
		read(x), read(arp...);
	}
	template <typename T>
	inline void write(T x, char ch = '\n') {
		if (x < 0) x = -x, putchar('-');
		static char stk[25];
		int top = 0;
		do {
			stk[top++] = x % 10 + '0', x /= 10;
		} while (x);
		while (top) putchar(stk[--top]);
		putchar(ch);
		return;
	}
	template <typename T>
	inline void smax(T &x, T y) {
		if (x < y) x = y;
	}
	template <typename T>
	inline void smin(T &x, T y) {
		if (x > y) x = y;
	}
	void quit() {
		exit(0);
	}
} using namespace FastIO;
const int N = 3e6 + 91;
int n, m, H=1,T=0, deg[N], inq[N];
char mp[20][20];
int hsh(int a, int b, int c, int d, int x, int y) {
	return a + b * 10 + c * 100 + d * 1000 + x * 10000 + y * 100000;
} struct node {
	int val, op;
} Q[N], ans[N];
struct Graph {
	struct Edge {
		int v, nxt;
	} e[N];
	int head[N], cnt;
	void add(int u, int v) {
		e[++cnt] = {v, head[u]}; head[u] = cnt;
	}
	int Q[N], in[N];
	void topo() {
		H=1,T=0;
		for (int i=0;i<N;++i) if (inq[i]&&deg[i]==0) {
			Q[++T]=i; ans[i]={0,0}; in[i]=1;
		} else ans[i]={0,0};
		while (H<=T) {
			int u=Q[H++];
			for (int i=head[u];i;i=e[i].nxt) {
				int v=e[i].v;
				if (ans[u].op==0) {
					if (!ans[v].op) ans[v]={ans[u].val+1,1};
					else smin(ans[v].val,ans[u].val+1);
					if (!in[v]) Q[++T]=v,in[v]=1;
				} else {
					if (!ans[v].op) smax(ans[v].val,ans[u].val+1);
					if (!--deg[v]) Q[++T]=v,in[v]=1;
				}
			}
		}
	}
} G;
const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};
void check(int A, int a, int b, int c, int d, int x, int y) {
	if (a < 0 || a >= n || b < 0 || b >= m || ((a == c) || (b == d)) || mp[a][b] == '#') return ;
	if (a > c || (a == c && b > d)) swap(a, c), swap(b, d);
	int B=hsh(a,b,c,d,x,y);
	++deg[A]; G.add(B,A);
	if (!inq[B]) Q[++T]={B,1};
	inq[B]=1;
} // 0: Red 1: Black
void bfs() {
	memset(G.head, 0, sizeof G.head);
	while (H<=T) {
		node u=Q[H++];
		int tmp=u.val,a,b,c,d,x,y,A=u.val;
		a=tmp%10; tmp%=10;
		b=tmp%10; tmp%=10;
		c=tmp%10; tmp%=10;
		d=tmp%10; tmp%=10;
		x=tmp%10; tmp%=10;
		y=tmp%10; tmp%=10;
		if (!x || (a==x&&b==y) || (c==x&&d==y)) continue;
		if (u.op) {
			for (int i=0;i<3;++i) {
				int nx=x+dx[i],ny=y+dy[i];
				if (nx<0||nx>=n||ny<0||ny>=m||mp[nx][ny]=='#') continue;
				int B=hsh(a,b,c,d,nx,ny);
				++deg[A]; G.add(B,A);
				if (!inq[B]) Q[++T]={B,0};
				inq[B]=1;
			}
		} else {
			for (int i=0;i<4;++i) {
				int na=a+dx[i],nb=dy[i];
				check(A,na,nb,c,d,x,y);
			}
			for (int i=0;i<4;++i) {
				int nc=c+dx[i],nd=d+dy[i];
				check(A,nc,nd,a,b,x,y);
			}
		}
	}
}
void solve() {
	read(n, m); int V=0;
	for (int i=0;i<n;++i) scanf("%s",mp[i]);
	int a=-1,b,c,d,x,y;
	for (int i=0;i<n;++i) for (int j=0;j<m;++j) {
		if (mp[i][j]=='O') {
			if (a==-1) a=i,b=j;
			else c=i,d=j;
		} else if (mp[i][j]=='X') x=i,y=j;
	} Q[++T]={V=hsh(a,b,c,d,x,y),1}; bfs();
	G.topo();
	if (ans[V].op) printf("Red %d\n", ans[V].val);
	else if (G.in[V]) printf("Black %d\n", ans[V].val);
	else puts("Tie");
}
signed main() {
	int tc=read(),t=read();
	while (t--) solve();
	return 0;
}