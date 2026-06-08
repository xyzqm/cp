#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n; cin >> n;    
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); 
        g[v].push_back(u);
    }
    string s; cin >> s;
    s.insert(s.begin(), 0);
    int non = 0, zs = 0, os = 0, uk = 0;
    [&](this auto dfs, int x, int p) -> void {
        if (g[x].size() == 1 && p) {
            if (s[x] == '1') ++os; 
            else if (s[x] == '0') ++zs;
            else ++uk;
        }
        else if (s[x] == '?' && p) ++non;
        for (int y : g[x]) if (y != p) dfs(y, x);
    }(1, 0);
    // DBG(non);
    // DBG(zs);
    // DBG(os);
    // DBG(uk);
    if (s[1] == '0') cout << os + (uk + 1) / 2 << "\n";
    else if (s[1] == '1') cout << zs + (uk + 1) / 2 << "\n";
    else cout << max(
        min(os, zs) + (non & 1 ? (uk + 1) / 2 : uk / 2),
        max(os, zs) + uk / 2
     ) << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}