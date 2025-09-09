// https://codeforces.com/contest/2138/problem/C2
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

template <int N = 1>
bool can_sum(vector<int> &w, int n, int l, int r) {
    if (n>= N) return can_sum<min(::N, 2 * N)>(w, n, l, r);
    bitset<N> bs;
    bs[0] = 1;
    for (int &x : w) bs |= bs << x;
    for (int i = max(l, 0); i <= r; i++) if (bs[i] == 1) return true;
    return false;
}

void ac() {
    int n, k; cin >> n >> k;
    auto g = vector(n + 1, vector<int>());
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        g[x].push_back(i);
    }
    vector<int> sd(n + 1);
    int min_d = n;
    auto dfs = [&](this auto dfs, int x, int d) -> int {
        int mx = d;
        if (!g[x].size()) min_d = min(min_d, d);
        for (int y : g[x]) mx = max(mx, dfs(y, d + 1));
        ++sd[d];
        return mx;
    };
    dfs(1, 1);
    sd.resize(min_d + 1);
    int above = accumulate(sd.begin(), sd.end(), 0);
    cout << min_d - 1 + can_sum(sd, n, above - (n - k), k) << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
