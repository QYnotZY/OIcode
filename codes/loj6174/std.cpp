#include<bits/stdc++.h>
using namespace std;
int T,n,m,cnt_s[4][100005],cnt_t[4][100005],sum[4],pos[4],pos2[4];
char s[100005],t[100005];
int calc(int x){
	return min(cnt_s[0][x],sum[0]-cnt_s[0][x])+min(cnt_s[1][x],sum[1]-cnt_s[1][x])+
		   min(cnt_s[2][x],sum[2]-cnt_s[2][x])+min(cnt_s[3][x],sum[3]-cnt_s[3][x]);
}
struct segment_tree{
	struct node{
		int l,r,mid,max,tag;
	}a[400005];
	void update(int x){
		a[x].max=max(a[x<<1].max,a[x<<1|1].max);
	}
	void build(int x,int l,int r){
		a[x].l=l,a[x].r=r,a[x].mid=(l+r)>>1,a[x].tag=0;
		if(l<r)build(x<<1,l,a[x].mid),build(x<<1|1,a[x].mid+1,r),update(x);
		else a[x].max=calc(l);
	}
	void push(int x,int v){
		a[x].max+=v,a[x].tag+=v;
	}
	void pushdown(int x){
		if(a[x].tag)push(x<<1,a[x].tag),push(x<<1|1,a[x].tag),a[x].tag=0;
	}
	void add(int x,int l,int r,int v){
		if(l>r)return;
		if(l<=a[x].l&&a[x].r<=r)return push(x,v),void();
		pushdown(x);
		if(l<=a[x].mid)add(x<<1,l,r,v);
		if(r>a[x].mid)add(x<<1|1,l,r,v);
		update(x);
	}
}sgt;
void solve(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	sum[0]=sum[1]=sum[2]=sum[3]=0;
	for(int i=1;i<=n;i++){
		cnt_s[0][i]=cnt_s[0][i-1]+(s[i]=='A');
		cnt_s[1][i]=cnt_s[1][i-1]+(s[i]=='T');
		cnt_s[2][i]=cnt_s[2][i-1]+(s[i]=='G');
		cnt_s[3][i]=cnt_s[3][i-1]+(s[i]=='C');
		sum[0]+=(s[i]=='A');
		sum[1]+=(s[i]=='T');
		sum[2]+=(s[i]=='G');
		sum[3]+=(s[i]=='C');
	}
	for(int i=1;i<=m;i++){
		cnt_t[0][i]=cnt_t[0][i-1]+(t[i]=='A');
		cnt_t[1][i]=cnt_t[1][i-1]+(t[i]=='T');
		cnt_t[2][i]=cnt_t[2][i-1]+(t[i]=='G');
		cnt_t[3][i]=cnt_t[3][i-1]+(t[i]=='C');
		sum[0]+=(t[i]=='A');
		sum[1]+=(t[i]=='T');
		sum[2]+=(t[i]=='G');
		sum[3]+=(t[i]=='C');
	}
	sgt.build(1,0,n);
	int ans=sgt.a[1].max;
	pos[0]=pos[1]=pos[2]=pos[3]=n+1;
	pos2[0]=pos2[1]=pos2[2]=pos2[3]=n;
	for(int i=1;i<=m;i++){
		int id=0;
		if(t[i]=='A')id=0;
		if(t[i]=='T')id=1;
		if(t[i]=='G')id=2;
		if(t[i]=='C')id=3;
		while(pos[id]&&(cnt_s[id][pos[id]-1]+cnt_t[id][i-1])*2>=sum[id])pos[id]--;
		while(pos2[id]>=0&&(cnt_s[id][pos2[id]]+cnt_t[id][i-1])>=sum[id]/2)pos2[id]--;
		sgt.add(1,pos[id],n,-1);
		sgt.add(1,0,pos2[id],1);
		ans=max(ans,sgt.a[1].max);
	}
	printf("%d\n",ans);
}
signed main(){
	scanf("%d",&T);
	while(T--)solve();
}