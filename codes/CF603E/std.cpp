#include<bits/stdc++.h>
#define re register
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=1e5+5,maxm=3e5+5;
struct Edge{int u,v,t,w;}e[maxm],E[maxm];
int n,m,ans[maxm],id[maxm];
inline int cmp(const Edge &A,const Edge &B) {return A.w<B.w;}
struct dsu{
	int fa[maxn],sz[maxn],tot,top,st[maxn];
	inline void bud() {
		tot=n;for(re int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	}
	inline int find(int x) {
		while(x!=fa[x])x=fa[x];return x;
	}
	inline void lnk(int x,int y) {
		x=find(x),y=find(y);if(x==y) return;
		if(sz[x]<sz[y]) x^=y,y^=x,x^=y;
		fa[y]=x;tot-=(sz[x]&1),tot-=(sz[y]&1);
		sz[x]+=sz[y];tot+=(sz[x]&1);st[++top]=y;
	}
	inline void back() {
		int y=st[top--],x=fa[y];
		tot-=(sz[x]&1);sz[x]-=sz[y];fa[y]=y;
		tot+=(sz[x]&1);tot+=(sz[y]&1);
	}
}S;
void cdq(int l,int r,int x,int y) {
	if(l>r) return;
	int mid=l+r>>1,pre=S.top;
	for(re int i=l;i<=mid;++i)
		if(id[i]<x) S.lnk(E[i].u,E[i].v);
	for(re int i=x;i<=y;++i) {
		if(e[i].t<=mid) S.lnk(e[i].u,e[i].v); 
		if(!S.tot) {ans[mid]=i;break;}
	}
	while(S.top>pre) S.back();
	if(!ans[mid]) {
		for(re int i=l;i<=mid;++i) 
			if(id[i]<x) S.lnk(E[i].u,E[i].v);
		cdq(mid+1,r,x,y);
		while(S.top>pre) S.back();
		return;	
	}
	for(re int i=l;i<=mid;++i) 
		if(id[i]<x) S.lnk(E[i].u,E[i].v);
	cdq(mid+1,r,x,ans[mid]);
	while(S.top>pre) S.back();
	for(re int i=x;i<ans[mid];++i) 
		if(e[i].t<l) S.lnk(e[i].u,e[i].v);
	cdq(l,mid-1,ans[mid],y);
	while(S.top>pre) S.back();
	
}
int main() {
	n=read(),m=read();S.bud();
	for(re int i=1;i<=m;i++)
		e[i].t=i,e[i].u=read(),e[i].v=read(),e[i].w=read(); 
	for(re int i=1;i<=m;i++)E[i]=e[i];
	std::sort(e+1,e+m+1,cmp);
	for(re int i=1;i<=m;i++)id[e[i].t]=i;cdq(1,m,1,m);
	for(re int i=1;i<=m;++i)if(!ans[i]) puts("-1");else printf("%d\n",e[ans[i]].w);
	return 0;
}
