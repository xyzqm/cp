#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) (int)((x).size())
// #define int ll
//#define N
using namespace std;
const int N=10000005;
int fac[N],mul[N],inv[N],f[N];
int n,m;

inline ll quickPower(ll x,ll y)
{
	ll res=1;
	while (y)
	{
		if (y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline int C(int x,int y)
{
	if (x<y||y<0) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int way(int x,int y)
{
	return C(x+y,y);
}
int way_(int x,int y)
{
	return (way(x,y)-way(y-1,x+1)+mod)%mod;
}

int h[N],hh[N];
int re[N];
void build_re(int nn)
{
	int x,now=nn>>1,len=0;
	while(now)
	  len++,now>>=1;
	for(int i=0;i<nn;i++)
	{
		x=i;now=0;
		for(int j=0;j<len;j++)
		  now=(now<<1)|(x&1),x>>=1;
		re[i]=now;
	}
}
void NTT(int a[],int len,int opt)
{
	for(int i=0;i<len;i++)
	  if(i<re[i])
	    swap(a[i],a[re[i]]);
	int wn,w,x;
	for(int i=2;i<=len;i<<=1)
	  for(int j=(wn=quickPower(3,(mod-1)/i),(opt==-1?wn=quickPower(wn,mod-2):0),0);j<len;j+=i)
	    for(int k=(w=1,0);k<i>>1;k++,w=1ll*w*wn%mod)
	      x=1ll*a[j+k+(i>>1)]*w%mod,a[j+k+(i>>1)]=(a[j+k]-x+mod)%mod,a[j+k]=(a[j+k]+x)%mod;
	if(opt==-1)
	{
		long long inv=quickPower(len,mod-2);
		for(int i=0;i<len;i++)
		  a[i]=1ll*a[i]*inv%mod;
	}
}
void poly_inv(int *a,int *tar,int len)
{
	static int now[N];
	memset(now,0,sizeof(int)*len);
	tar[0]=quickPower(a[0],mod-2);
	for(int i=2;i<=len;i<<=1)
	{
		build_re(i<<1);
		memcpy(now,a,sizeof(int)*i);
		NTT(tar,i<<1,1);NTT(now,i<<1,1);
		for(int j=0;j<i<<1;j++)
		  tar[j]=1ll*tar[j]*(2LL-1ll*now[j]*tar[j]%mod+mod)%mod;
		NTT(tar,i<<1,-1);
		memset(tar+i,0,sizeof(int)*i);
	}
}
void BellaKira()
{
	cin>>n>>m;
	n*=2;
	poly g;
	for (int i=1;i<=n;i++)
		mul[gcd(i,n)]++;
	if (m==1)
	{
		cout<<1<<'\n';
		return;
	}
	hh[0]=1;
	for (int i=1;i<=n/2;i++)
		hh[i]=(mod-1ll*way_(i-1,i-1)*quickPower(m-1,i-1)%mod*m%mod)%mod;
	int Len=1;
	while(Len<=n/2+1)
	  Len<<=1;
	poly_inv(hh,h,Len);
	// for (int i=0;i<=n;i++) cout<<h[i]<<" ";
	// cout<<endl;
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		if (n%i==0)
		{
			if (i%2==0)
			{
				if (m==1) f[i]=1;
				else
					f[i]=h[i/2];
			} else
			{
				if (m==1) f[i]=1;
				else
				for (int j=0;j<=i/2;j++)
				{
					f[i]=(f[i]+1ll*way(j,i-j)*m%mod
					*quickPower(m-1,j)%mod)%mod;
				}
			}
			ans=(ans+1ll*f[i]*mul[i]%mod)%mod;
		}
	}
	cout<<1ll*ans*quickPower(n,mod-2)%mod<<'\n';
}
signed main()
{
    size_t n; cin >> n;
    for (int i = 0; i < n; i++) cin >> hh[i];
    poly_inv(hh, h, __bit_ceil(n));
    for (int i = 0; i < n; i++) cout << h[i] << " ";
    cout << endl;
    // fac[0]=1;
	// for (int i=1;i<N;i++)
	// 	fac[i]=1ll*fac[i-1]*i%mod;
	// inv[N-1]=quickPower(fac[N-1],mod-2);
	// for (int i=N-1;i>=1;i--)
	// 	inv[i-1]=1ll*inv[i]*i%mod;
	// IOS;
	// cin.tie(0);
	// int T=1;
	// while (T--)
	// {
	// 	BellaKira();
	// }
}
