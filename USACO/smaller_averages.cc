// https://usaco.org/index.php?page=viewproblem2&cpid=1427
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;
void ad(int &a, int b) { a = (a + b) % M; }

using rat = array<int, 2>;
bool lt(rat a, rat b) { return a[0] * b[1] < b[0] * a[1]; };
bool le(rat a, rat b) { return a[0] * b[1] <= b[0] * a[1]; };

// dp[i][j] = # of ways to split a[0, i) and b[0, j)
// sort all subarrays [_, i) by average

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    auto v = array{vector<int>(n), vector<int>(n)};
    for (int t : {0, 1}) for (int &x : v[t]) cin >> x;
    array<vector<vector<pair<rat, int>>>, 2> opts;
    for (int t : {0, 1}) {
        opts[t].resize(n + 1);
        for (int i = 1; i <= n; i++) {
            int sm = 0;
            for (int j = i - 1; j >= 0; j--) {
                sm += v[t][j];
                opts[t][i].push_back({{sm, i - j}, j});
            }
            sort(opts[t][i].begin(), opts[t][i].end(), [](auto a, auto b) {
                auto [ra, ja] = a;
                auto [rb, jb] = b;
                if (lt(ra, rb) || lt(rb, ra)) return lt(ra, rb);
                else return ja < jb;
            });
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        auto sm = vector(n + 1, vector<int>());
        for (int j = 0; j < n; j++) {
            sm.reserve(i);
            sm[j].push_back(0);
            for (auto &[_, k] : opts[0][i]) {
                sm[j].push_back((sm[j].back() + dp[k][j]) % M);
            }
        }
        for (int j = 1; j <= n; j++) {
            auto it = opts[0][i].begin();
            for (auto &[avg, k] : opts[1][j]) {
                while (it != opts[0][i].end() && le((*it).first, avg)) it++;
                ad(dp[i][j], sm[k][it - opts[0][i].begin()]);
            }
        }
    }
    cout << dp[n][n] << endl;
}
