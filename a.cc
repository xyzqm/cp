#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int MOD = 998244353;

int add(int a, int b){
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
    return a;
}

int mul(int a, int b){
    return a * 1ll * b % MOD;
}

int binpow(int a, int b){
    int res = 1;
    while (b){
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int n, k;
vector<vector<int>> g;

struct dpar{
    vector<int> dp;
    int ml, ad;
    dpar(){
        ml = 1, ad = 0;
        dp.clear();
    }
    int& operator [](int k){
        return dp[max(0, int(dp.size()) - k - 1)];
    }
    int get(int k){
        int x = dp[max(0, int(dp.size()) - k - 1)];
        return add(mul(x, ml), ad);
    }
};

vector<dpar> dp;
vector<int> fact;

void dfs(int v){
    int bst = -1;
    vector<int> val;
    for (int u : g[v]){
        dfs(u);
        dp[u].dp.push_back(add(0, mul(binpow(dp[u].ml, MOD - 2), -dp[u].ad)));
        if (bst == -1 || dp[u].dp.size() > dp[bst].dp.size())
            bst = u;
        val.push_back(dp[u].get(k - 1));
    }
    if (val.empty()){
        dp[v].dp.push_back(1);
        return;
    }

    vector<int> pr(val.size() + 1, 1), su(val.size() + 1, 1);
    forn(i, val.size()){
        pr[i + 1] = mul(pr[i], val[i]);
        su[val.size() - i - 1] = mul(su[val.size() - i], val[val.size() - i - 1]);
    }

    swap(dp[v], dp[bst]);
    {
        int i = find(g[v].begin(), g[v].end(), bst) - g[v].begin();
        int cur = mul(fact[g[v].size() - 1], mul(pr[i], su[i + 1]));
        if (cur == 0){
            int mx = 1;
            for (int u : g[v]) mx = max(mx, int(dp[u].dp.size()));
            dp[v].dp.assign(mx, 0);
            dp[v].ml = 1, dp[v].ad = 0;
        }
        else{
            dp[v].ml = mul(dp[v].ml, cur);
            dp[v].ad = mul(dp[v].ad, cur);
        }
    }

    int rev = binpow(dp[v].ml, MOD - 2);
    forn(i, g[v].size()){
        int u = g[v][i];
        if (u == bst) continue;
        int cur = mul(fact[g[v].size() - 1], mul(pr[i], su[i + 1]));
        int tot = mul(cur, dp[u].get(n));
        dp[v].ad = add(dp[v].ad, tot);
        forn(j, dp[u].dp.size()){
            dp[v][j] = add(dp[v][j], -mul(rev, tot));
            dp[v][j] = add(dp[v][j], mul(mul(cur, dp[u].get(j)), rev));
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--){
        cin >> n >> k;
        g.assign(n, {});
        for (int i = 1; i < n; ++i){
            int p;
            cin >> p;
            --p;
            g[p].push_back(i);
        }
        dp.assign(n, {});
        fact.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i)
            fact[i] = mul(fact[i - 1], i);
        dfs(0);
        cout << dp[0].get(n) << '\n';
    }
    return 0;
}
