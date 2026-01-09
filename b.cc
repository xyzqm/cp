#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define bll __int128
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define fi first
#define sec second
#define vii vector<int>
#define pll pair<ll,ll>
#define vll vector<ll>
#define pii pair<int,int>
#define pil pair<int,ll>
#define re register
#define puu pair<ull,ull>
#define clr clear
#define vpi vector<pii>
#define qii queue<int>
using namespace std;
namespace io{
	const int __SIZE=(1<<22)+1;
	char ibuf[__SIZE],*iS,*iT,obuf[__SIZE],*oS=obuf,*oT=oS+__SIZE-1,__c,qu[55];int __f,qr,_eof;
#define Gc()(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,__SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
	inline void gc(char&x){x=Gc();}
	inline void pc(char x){*oS++=x;if(oS==oT)flush();}
	inline void pstr(const char*s){int __len=strlen(s);for(__f=0;__f<__len;++__f)pc(s[__f]);}
	inline void gstr(char*s){for(__c=Gc();__c<32||__c>126||__c==' ';)__c=Gc();
		for(;__c>31&&__c<127&&__c!=' ';++s,__c=Gc())*s=__c;*s=0;}
	template<class I>inline bool read(I&x){_eof=0;
		for(__f=1,__c=Gc();(__c<'0'||__c>'9')&&!_eof;__c=Gc()){if(__c=='-')__f=-1;_eof|=__c==EOF;}
		for(x=0;__c<='9'&&__c>='0'&&!_eof;__c=Gc())x=x*10+(__c&15),_eof|=__c==EOF;x*=__f;return!_eof;}
	template<class I>inline void write(I x){if(!x)pc('0');if(x<0)pc('-'),x=-x;
		while(x)qu[++qr]=x%10+'0',x/=10;while(qr)pc(qu[qr--]);}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}using io::pc;using io::gc;using io::pstr;using io::gstr;using io::read;using io::write;
const int N=2e5+5,mod=1e9+7;
int head[N],nex[N],to[N],tot;
int deg[N],BZ[N];
ll f[N][2],inv[N],fac[N],ans,I[N];
int T,n,k,c;
map<pii,bool>M;
void add_edge(int x,int y){deg[x]++,tot++,nex[tot]=head[x],head[x]=tot,to[tot]=y;}
ll ksm(ll x,int y){ll z=1;while(y){if(y&1)z=z*x%mod;x=x*x%mod,y>>=1;}return z;}
void clear(){for(int i=1;i<=n;i++)head[i]=BZ[i]=deg[i]=0;tot=1;}
void add(ll&x,ll y){x+=y;if(x>=mod)x-=mod;}
void dfs(int x,int F)
{
	ll s0=0,s1=0,nowans=0;f[x][0]=f[x][1]=0;
	for(int i=head[x];i;i=nex[i])
	{
		int y=to[i];
		if(y!=F)
		{
			dfs(y,x);
			ll nows0=f[y][0],nows1=f[y][1];
			if(BZ[i/2])add(nows1,nows0),nows0=0;
			add(nowans,nows0*s1%mod),add(nowans,nows1*s0%mod),add(nowans,nows1*s1%mod),add(s1,nows1),add(s0,nows0),add(f[x][0],nows0),add(f[x][1],nows1);
		}
	}
	add(ans,nowans*I[deg[x]-1]%mod);
	if(deg[x]==1)f[x][0]=I[deg[x]-1],f[x][1]=0;
	else f[x][0]=f[x][0]*I[deg[x]-1]%mod,f[x][1]=f[x][1]*I[deg[x]-1]%mod;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	fac[0]=1;for(int i=1;i<=1e5;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=1e5;i++)inv[i]=ksm(fac[i],mod-2),I[i]=ksm(i,mod-2);
	I[0]=1;
	cin>>c>>T;
	while(T--)
	{
		cin>>n>>k,clear(),M.clr(),ans=0;
		ll s=1;
		for(int i=1,x,y;i<n;i++)cin>>x>>y,add_edge(x,y),add_edge(y,x);
		for(int i=1,x;i<=k;i++)cin>>x,BZ[x]=1;
		if(n==2){cout<<1<<endl;continue;}
		int rt=0;
		for(int i=1;i<=n;i++)if(deg[i]!=1)rt=i;
		for(int i=1;i<=n;i++)s=s*fac[deg[i]-1]%mod;
		dfs(rt,0),cout<<s*ans%mod<<endl;
	}
}
