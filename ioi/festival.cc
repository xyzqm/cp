#include <bits/stdc++.h>
using namespace std;

#define sz(V) (int)V.size()

const int K = 50;

vector<int> max_coupons(int X, vector<int> P, vector<int> T) {
    #define int int64_t
    vector<int> ord, ones;
    for (int i = 0; i < sz(P); i++)
        if (T[i] > 1) ord.push_back(i);
        else ones.push_back(i);
    int A = X;
    auto apply = [&](int A, int i) { return (A - P[i]) * T[i]; };
    ranges::sort(ord, [&](int i, int j) { return apply(apply(0, i), j) > apply(apply(0, j), i); });
    ranges::sort(ones, [&](int i, int j) { return P[i] < P[j]; });
    auto it = ord.begin();
    for (; it != ord.end() && apply(A, *it) >= A; it++) A = min(apply(A, *it), (int)2e14);
    vector<int32_t> R(ord.begin(), it);
    vector<int> dp(K, -1);
    array<vector<int>, K> cps;
    dp[0] = A;
    for (; it != ord.end(); it++) for (int k = K - 1; k --> 0; ) {
        if (int x = apply(dp[k], *it); x > dp[k + 1]) {
            cps[k + 1] = cps[k];
            cps[k + 1].push_back(*it);
            dp[k + 1] = x;
        }
    }
    int bst = -1;
    auto best_it = ones.begin();
    it = ones.begin();
    for (int k = K, sm = 0; k --> 0; ) if (dp[k] >= 0) {
        while (it != ones.end() && sm + P[*it] <= dp[k]) sm += P[*(it++)];
        if (k + (it - ones.begin()) > bst + (best_it - ones.begin())) bst = k, best_it = it;
    }
    assert(bst >= 0);
    R.insert(R.end(), cps[bst].begin(), cps[bst].end());
    R.insert(R.end(), ones.begin(), best_it);
    return R;
}

#ifndef ONLINE_JUDGE
#define int int32_t
int main() {
    int n, a; cin >> n >> a;
    vector<int> P(n), T(n);
    for (int i = 0; i < n; i++) cin >> P[i] >> T[i];
    println("{}", max_coupons(a, P, T));
}
#endif
