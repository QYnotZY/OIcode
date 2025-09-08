#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 1e5 + 5 ; 
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define lowbit(x) ( x & ( -x ) )
struct Qu {
	int x, y, z, id ; 
} di[N], q[N];
int n, m, Q, Maxn, u[N], d[N], sum[N], ans[N], tree[N], p[N], top, mod ; 
bool isp[N] ; 
bool cmp( Qu x, Qu y ) {
	return x.z < y.z ; 
}
void add( int x, int k ) {
	for( register int i = x; i <= Maxn; i += lowbit(i) ) tree[i] += k ;  
}
int query( int x ) {
	int num = 0; 
	for( register int i = x; i; i -= lowbit(i) ) num += tree[i];
	return num ; 
}
void init() {
	u[1] = 1;
	rep( i, 2, Maxn ) {
		if( !isp[i] ) u[i] = -1, p[++ top] = i ;
		rep( j, 1, top ) {
			if( p[j] * i > Maxn ) break ;
			isp[p[j] * i] = 1 ;
			if( i % p[j] == 0 ) break ;
			u[p[j] * i] = - u[i];
		}
	}
	rep( i, 1, Maxn ) for( register int j = i; j <= Maxn; j += i ) d[j] += i ; 
	rep( i, 1, Maxn ) di[i].id = i, di[i].z = d[i] ;
	sort( di + 1, di + Maxn + 1, cmp ) ; 
}
void u_add( int x ) {
	for( int i = 1; i * x <= Maxn; ++ i ) add( i * x, u[i] * d[x] ) ;
}
int solve( int x, int y ) {
	int num = 0; if( x > y ) swap( x, y ) ;
	for( int l = 1, r; l <= x; l = r + 1 ) {
		r = min( ( x / ( x / l ) ), ( y / ( y / l ) ) ) ;
		num += ( x / l ) * ( y / l ) * ( query(r) - query(l - 1) ) ;
	}
	return num % mod ;
} 
signed main()
{
	Q = read() ; mod = 1ll << 31 ;
	rep( i, 1, Q ) q[i].x = read(), q[i].y = read(), q[i].z = read(), q[i].id = i ;
	Maxn = N - 5 ; 
	sort( q + 1, q + Q + 1, cmp ), init() ; 
	int pr = 0 ; 
	rep( i, 1, Q ) {
		while( di[pr + 1].z <= q[i].z && pr < Maxn ) {++ pr, u_add( di[pr].id ) ;
        for(int i = 1; i <= 10; i ++) printf("%d ", query(i)); printf("\n");
        }
        printf("%d\n", pr);
		ans[q[i].id] = solve( q[i].x, q[i].y ) ;
	}
	rep( i, 1, Q ) printf("%lld\n", ans[i] % mod ) ; 
	return 0;
}
