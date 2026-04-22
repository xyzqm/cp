#include <bits/stdc++.h>
using namespace std;

int max_score(int N, int X, int Y, long long K,
              std::vector<int> U, std::vector<int> V, std::vector<int> W)
#define int long long
{
    vector<vector<array<int, 2>>> g(N);
    for (auto [u, v, w] : views::zip(U, V, W)) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    auto dfs = [&](this auto &&self, int u, int p, vector<int> &dist) -> void {
        for (auto [v, w] : g[u]) if (v != p) {
            dist[v] = dist[u] + w;
            self(v, u, dist);
        }
    };
    vector<int> a(N), b(N);
    // calculate distances to X and Y
    dfs(X, X, a);
    dfs(Y, Y, b);
    for (int i = 0; i < N; i++) if (a[i] > b[i]) swap(a[i], b[i]); // a = c(i), b = C(i)
    auto c = a;
    // first, solve when no nodes are squares
    auto acc = [&]() {
        ranges::sort(c);
        partial_sum(c.begin(), c.end(), c.begin());
    };
    acc();
    auto singles = [&](int K) { return K < 0 ? -10 * N : ranges::upper_bound(c, K) - c.begin(); };
    int ans = singles(K);

    // now, consider case when some nodes are squares
    int cnt = 0;
    c.clear(); // new single boxes
    vector<array<int, 2>> twos; // boxes of the second type (2a_i >= b_i)
    for (int i = 0; i < N; i++) {
        if (a[i] + b[i] == b[X]) K -= a[i], ++cnt, c.push_back(b[i] - a[i]); // node on path from X to Y
        else if (a[i] < b[i] - a[i]) c.push_back(a[i]), c.push_back(b[i] - a[i]);
        else twos.push_back({b[i], a[i]});
    }
    if (K < 0) return ans; // impossible for any nodes to be squares
    ranges::sort(twos);
    acc();
    vector<int> suf(twos.size());
    for (int i = twos.size(); i --> 0; ) {
        suf[i] = twos[i][1];
        if (i + 1 < twos.size()) suf[i] = min(suf[i], suf[i + 1]);
    }
    suf.push_back(2 * K);
    for (int i = 0, mx_down = 0; i <= twos.size(); i++) { // enumerate (last index of fully-taken box) + 1
        ans = max({
            ans,
            cnt + 2 * i - 1 + singles(K + mx_down), // downgrade one
            cnt + 2 * i + 1 + singles(K - suf[i]), // upgrade one
            cnt + 2 * i + singles(K) // leave unchanged
        });
        if (i == twos.size()) break;
        auto [b, a] = twos[i];
        K -= b;
        mx_down = max(mx_down, b - a);
    }
    return ans;
}

#ifndef ONLINE_JUDGE
int32_t main() {
    cout << max_score(4, 0, 3, 20, {0, 1, 2}, {1, 2, 3}, {18, 1, 19}) << "\n";
    cout << max_score(7, 0, 2, 10,
     {0, 0, 1, 2, 2, 5}, {1, 3, 2, 4, 5, 6}, {2, 3, 4, 2, 5, 3}) << "\n";
}
#endif
