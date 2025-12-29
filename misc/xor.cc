#include <bits/stdc++.h>
using namespace std;

#define int int64_t

using ll = __int128;

void read(__int128 &x){
	// read a __int128 variable
	char c; bool f = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-'){f = 1; c = getchar();}
	x = c - '0';
	while((c = getchar()) >= '0' && c <= '9')x = x * 10 + c - '0';
	if(f) x = -x;
}
void write(__int128 x){
	// print a __int128 variable
	if(x < 0){putchar('-'); x = -x;}
	if(x > 9)write(x / 10);
	putchar(x % 10 + '0');
}

void ac() {
    int n, m, k; cin >> n >> m >> k;

    ll inf = (ll)1 << k;

    vector<ll> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) read(a[i]);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<array<int, 2>> tri(1);
    vector<int> cost(1);
    vector<ll> mns(1, inf);
    auto insert = [&](ll a, int c) {
        for (int kk = k + 1, cur = 0; kk --> 0; ) {
            ll b = a >> kk & 1;
            if (!tri[cur][b]) {
                tri[cur][b] = tri.size();
                tri.emplace_back();
                cost.emplace_back();
                mns.push_back(inf);
            }
            cur = tri[cur][b];
            cost[cur] += c;
            mns[cur] = min(mns[cur], a);
        }
    };

    for (int i = 0; i < n; i++) insert(a[i], b[i]);

    auto slv = [&](this auto slv, int u, int rem, ll ans, ll x, ll mn, ll bit) -> ll {
        ll ones = bit - 1;
        if (!bit) return ans;
        if (cost[u] <= rem) return min(mn, mns[u]) + (x | bit | ones);

        ll bst = ans;
        // try setting next bit of ans to 1
        for (int t : {0, 1}) { // enhance all of subtree t and set bit of x to t
           ll nx_mn = min(mn, mns[tri[u][t]]);
           if (cost[tri[u][t]] <= rem && nx_mn + (x | (t * bit) | ones) >= (ans | bit)) {
               ans |= bit;
               bst = max(bst, slv(tri[u][t ^ 1], rem - cost[tri[u][t]], ans, x | (t * bit), nx_mn, bit >> 1));
           }
        }

        if (!(ans & bit)) for (int t : {0, 1}) {
            bst = max(bst, slv(tri[u][t], rem, ans, x | (t * bit), mn, bit >> 1));
        }

        return bst;
    };

    write(slv(1, m, 0, 0, inf, inf >> 1));
    cout << endl;
}

int32_t main() {
    int c, t; cin >> c >> t;
    while (t--) ac();
}
