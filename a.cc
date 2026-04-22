#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
const ll inf=1e18;
struct Edge { int v,w; };
vector <Edge> G[MAXN];
ll a[MAXN],b[MAXN];
void dfs(int u,int fz) {
	for(auto e:G[u]) if(e.v^fz) a[e.v]=a[u]+e.w,dfs(e.v,u);
}
ll c[MAXN*2],mn[MAXN];
array<ll,2> d[MAXN];
int max_score(int n,int X,int Y,ll S,vector<int>U,vector<int>V,vector<int>W) {
	for(int i=1;i<=n;++i) a[i]=b[i]=0,G[i].clear();
	for(int i=0;i<n-1;++i) G[U[i]+1].push_back({V[i]+1,W[i]}),G[V[i]+1].push_back({U[i]+1,W[i]});
	dfs(++X,0),swap(a,b),dfs(++Y,0);
	for(int i=1;i<=n;++i) if(a[i]>b[i]) swap(a[i],b[i]);
	memcpy(c,a,sizeof(a));
	sort(c+1,c+n+1); // sort by min dist
	int ans=0; ll t=0;
	while(ans<n&&t+c[ans+1]<=S) t+=c[++ans]; // greedily take smallest min dist until we reach capacity
	int m=0,q=0,ct=0;
	for(int i=1;i<=n;++i) {
		if(a[i]+b[i]==b[Y]) ++ct,S-=a[i],c[++m]=b[i]-a[i]; // if on the path from X to Y
		else if(b[i]-a[i]>=a[i]) c[++m]=a[i],c[++m]=b[i]-a[i]; // no need to consider opt 2 before opt 1
		else d[++q]={b[i],a[i]}; // otherwise add to d?
	}
	if(S<0) return ans; // impossible to connect X and Y
	sort(c+1,c+m+1),sort(d+1,d+q+1);
	for(int i=1;i<=m;++i) c[i]+=c[i-1];
	auto ask=[&](ll z) -> int {  return z>=0?upper_bound(c+1,c+m+1,z)-c-1:-3*n; };
	mn[q+1]=inf;
	for(int i=q;i>=1;--i) mn[i]=min(mn[i+1],d[i][1]);
	ans=max({ans,ask(S)+ct,ask(S-mn[1])+ct+1});
	ll sum=0,vl=0;
	for(int i=1;i<=q;++i) {
		sum+=d[i][0],vl=max(vl,d[i][0]-d[i][1]);
		ans=max({ans,ask(S-sum)+ct+2*i,ask(S-sum+vl)+ct+2*i-1,ask(S-sum-mn[i+1])+ct+2*i+1});
	}
	return ans;
}

int32_t main() {
    cout << max_score(4, 1, 3, 3, {0, 1, 2}, {1, 2, 3}, {2, 3, 3}) << "\n";
}
