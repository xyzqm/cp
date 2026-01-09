#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

void ad(int &a, int b) { a = (a + b) % M; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    // psum[i] = sum of elts [0, i) of same parity as i
    vector<int> dp(n + 1), psum(n + 1);
    vector<array<int, 2>> itvs;
    dp[0] = 1;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        if (i + 2 <= n) psum[i + 2] = (psum[i] + dp[i]) % M;
        if (s[i] == 'R') { // all intervals reset
            itvs.clear();
        }
        else { // try painting this node
            decltype(itvs) nx;
            for (auto &[l, r] : itvs) { // [l, r) where l and r are same parity
                --l, --r;
                if (l < 0 || s[l] == 'B') l += 2;
                if (l < r) nx.push_back({l, r});
            }
            itvs = nx;
            if (i && s[i - 1] != 'B') {
                if (itvs.size() && itvs.back()[1] == i - 1) itvs.back()[1] += 2;
                else itvs.push_back({i - 1, i + 1});
            }
            for (auto &[l, r] : itvs) ad(dp[i + 1], psum[r] - psum[l] + M);
        }
        if (s[i] == 'X')  ad(dp[i + 1], dp[i]);
    }
    cout << dp[n] << endl;
}
