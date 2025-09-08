#include<bits/stdc++.h>
using namespace std;
long long n,m,a[500005],x[500005],c[500005],dfn[500005],tot,bj[500005],k,head[500005];
struct line{
	int to,pre;
}b[1000005];
void add(int u,int v){
	k++;
	b[k].to=v;
	b[k].pre=head[u];
	head[u]=k;
}
struct tree{
	vector<int>v;
}ans[2000005];
vector<int>al[500005],ar[500005];
void dfs(int x,int fr){
	dfn[x]=++tot;
	if(bj[x]>0)al /*ar*/ [bj[x]].push_back(tot);
    if(bj[x]<0)ar /*al*/ [abs(bj[x])].push_back(tot-1);
    for(int i=head[x];i;i=b[i].pre){
    	if(b[i].to==fr)continue;
    	dfs(b[i].to,x);
	}
    if(bj[x]>0)ar[bj[x]].push_back(tot);
    if(bj[x]<0)al[abs(bj[x])].push_back(tot+1);
}
int ls(int p){return p<<1;}
int rs(int p){return p<<1|1;}
void update(int p,int l,int r,int nl,int nr,int k){
	if(nl<=l&&nr>=r){
		if(ans[p].v.size()<2)ans[p].v.push_back(k);
		else{
			int v1=ans[p].v[ans[p].v.size()-1],v2=ans[p].v[ans[p].v.size()-2],v3=k;
			while(((x[v1]*x[v1]+c[v1])-(x[v2]*x[v2]+c[v2]))*(2*x[v3]-2*x[v1 /*v2*/ ])>=((x[v3]*x[v3]+c[v3])-(x[v1]*x[v1]+c[v1]))*(2*x[v1]-2*x[v2])){
				ans[p].v.pop_back();
				if(ans[p].v.size()<2)break;
				v1=ans[p].v[ans[p].v.size()-1];
				v2=ans[p].v[ans[p].v.size()-2];
			}
			ans[p].v.push_back(k);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(nl<=mid)update(ls(p),l,mid,nl,nr,k);
	if(nr>mid)update(rs(p),mid+1,r,nl,nr,k);
	return;
}
long long query(int p,int l,int r,int nn,long long x0,long long res){
	int gl=0,gr=ans[p].v.size()-2,gmid=gr>>1;
	while(gl<gr){
		if(x[ans[p].v[gmid + 1]]*x[ans[p].v[gmid + 1]]+c[ans[p].v[gmid + 1]]-x[ans[p].v[gmid]]*x[ans[p].v[gmid]]-c[ans[p].v[gmid]]>x0*(2*x[ans[p].v[gmid+1]]-2*x[ans[p].v[gmid]]))gl=gmid+1;
		// ?
        else gr=gmid;
		gmid=(gl+gr)>>1;
	}
	if(gmid<0)gmid=0;
	if(ans[p].v.size() >= 2) res=min(res,x[ans[p].v[gmid]]*x[ans[p].v[gmid]]+c[ans[p].v[gmid]]-x0*2* /**/ x[ans[p].v[gmid]]);
    else if(ans[p].v.size() == 1) res=min(res, x[ans[p].v[0]]*x[ans[p].v[0]]+c[ans[p].v[0]]-x0*2* /**/ x[ans[p].v[0]]); //666
	else res = min(res, (long long)(1e15));
	if(l==r)return res;
	int mid=(l+r)>>1;
	if(nn<=mid)res=min(res,query(ls(p),l,mid,nn,x0,res));
	else res=min(res,query(rs(p),mid+1,r,nn,x0,res));
	return res;
}
bool cmp(int ax,int ay){
	return x[ax]<x[ay];
}
int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	cin>>n>>m>>c[0];
	for(int i=1;i<=n-1;i++){
		int fr,ty,id,y,z;
		cin>>ty;
		if(ty==0){
			cin>>fr>>id;
			cin>>x[id]>>y>>z>>c[id];
			bj[i]=id;
			add(i,fr),add(fr,i);
		}else{
			cin>>fr>>id;
			bj[i]=-id;
			add(i,fr),add(fr,i);
		}
	}
	dfs(0,0);
	update(1,1,n,1,n,0);
	for(int i=1;i<n;i++)a[i]=i;
	sort(a+1,a+n,cmp); 
	for(int i=1;i<=n-1;i++)for(int j=0;j<al[a[i]].size();j++){
        #ifdef db
        printf("%d %d %lld\n", al[a[i]][j], ar[a[i]][j], bj[a[i]]);
        #endif
        if(al[a[i]][j]<= /*<*/ ar[a[i]][j])
        update(1,1,n,al[a[i]][j],ar[a[i]][j],bj[a[i]]);
    }
	for(int i=1;i<=m;i++){
		int s,X;
		cin>>s>>X;
		cout<<query(1,1,n,dfn[s],X,1e15)+X*X /**/ <<"\n";
	}
	return 0;
}