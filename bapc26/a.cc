#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, a, b; cin >> n >> a >> b;
    vector<int> types(n), costs(n);
    for (int &x : types) cin >> x;
    for (int &x : costs) cin >> x;
    array<vector<int>, 2> cs;
    for (int i = 0; i < n; i++) {
        cs[--types[i]].push_back(costs[i]);
    }
    for (int t : {0, 1}) {
        sort(cs[t].begin(), cs[t].end());
        cs[t].insert(cs[t].begin(), 0);
        partial_sum(cs[t].begin(), cs[t].end(), cs[t].begin());
        DBG(cs[t]);
    }
    int best = 1e18;
    // enumerate number of operation 2
    for (int k = 0; a <= b && k < cs[1].size(); k++, a *= 2) {
        int dif = b - a;
        int ones = __builtin_popcount(dif) + (dif >> k) - __builtin_popcount(dif >> k);
        DBG(ones);
        if (ones < cs[0].size()) best = min(best, cs[1][k] + cs[0][ones]);
    }
    cout << (best == 1e18 ? -1 : best) << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
