// https://codeforces.com/problemset/problem/2038/I
#include <bits/stdc++.h>
using namespace std;

struct bset {
    vector<uint64_t> v;
    bset() {}
    bset(int n) : v(n / 64 + 1, ULLONG_MAX) {}
    bool empty() {
        for (auto x : v) if (x) return false;
        return true;
    }
    void toggle(int i) { v[i / 64] ^= (1LL << (i & 63)); }
    void operator&=(bset o) { for (int i = 0; i < v.size(); i++) v[i] &= o.v[i]; }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<string> g(n);
    for (auto &s : g) cin >> s;
    vector<int> ans(m);
    if (n * 64 < m) { // run O(n^2 m) solution
        for (int i = 0; i < n; i++) {
            vector<bool> wk(m, 1);
            for (int j = 0; j < n; j++) if (i != j) {
                bool w = g[i] > g[j];
                for (int k = m; k --> 0; ) {
                    if (g[i][k] != g[j][k]) w = g[i][k] > g[j][k];
                    wk[k] = wk[k] && w;
                }
            }
            for (int j = 0; j < m; j++) if (wk[j]) ans[j] = i;
        }
    }
    else { // run O(n m^2) solution
        vector<bset> col(m);
        for (int i = 0; i < m; i++) {
            col[i] = bset(n);
            for (int j = 0; j < n; j++) if (g[j][i] == '0') col[i].toggle(j);
        }
        for (int i = 0; i < m; i++) {
            bset cand(n);
            for (int j = n; j < cand.v.size() * 64; j++) cand.toggle(j);
            for (int j = i; j < i + m; j++) {
                bset nx = cand;
                nx &= col[j % m];
                if (!nx.empty()) cand = nx;
            }
            for (int j = 0; j < cand.v.size(); j++) if (cand.v[j]) {
                ans[i] = j * 64 + __builtin_ctzll(cand.v[j]);
                break;
            }
        }
    }
    for (int x : ans) cout << x + 1 << " ";
    cout << endl;
}
