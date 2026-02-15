#include <bits/stdc++.h>
using namespace std;

// #define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, K; cin >> n >> K;
    int N = 1 << n;
    vector<int> w(N);
    for (int i = 1; i < N; i++) cin >> w[i];
    vector<int> ord(N);
    vector<vector<int>> vals(2 * N);
    for (int i = 0; i < N; i++) {
        cin >> ord[i];
        vals[N + i] = {i};
    }
    for (int i = N; i --> 1; ) {
        merge(
            vals[i << 1].begin(), vals[i << 1].end(),
            vals[i << 1 | 1].begin(), vals[i << 1 | 1].end(),
            back_inserter(vals[i]),
            [&](int i, int j) { return ord[i] > ord[j]; }
        );
        DBG(i);
        DBG(vals[i]);
    }
    vector<int> cost(2 * N, K + 1), val(2 * N);
    auto attempt = [&](int idx) {
        int cur = ord[idx];
        cost[idx += N] = 0;
        DBG(idx);
        // DBG(val);
        // DBG(cost);
        for ( ; idx > 1; idx >>= 1) {
            if (val[idx]) cur = val[idx];
            if (val[idx ^ 1]) { // first value already fixed
                if (cur > val[idx ^ 1]) cost[idx >> 1] = cost[idx] + cost[idx ^ 1];
                else if (idx & 1) cost[idx >> 1] = cost[idx] + cost[idx ^ 1] + w[idx >> 1];
                else cost[idx >> 1] = K + 1;
            }
            else {
                // DBG(cost[idx >> 1]);
                // DBG(val[idx >> 1]);
                cost[idx >> 1] = cost[idx] + cost[idx ^ 1];
                // if we are left child, we can activate parent
                if (!(idx & 1)) cost[idx >> 1] = min(cost[idx >> 1], cost[idx] + w[idx >> 1]);
                else if (!val[idx >> 1]) cost[idx >> 1] = min(cost[idx >> 1], cost[idx ^ 1] + w[idx >> 1]);
                // DBG(cost[idx >> 1]);
            }
        }
        DBG(cost);
        return cost[1] <= K;
    };
    auto reset = [&](this auto reset, int rt) -> void {
        cost[rt] = K + 1;
        if ((rt << 1) < 2 * N) for (int t : {0, 1}) reset(rt << 1 | t);
    };
    vector<int> res;
    int cur = 1;
    while (res.size() < N) {
        // DBG(cur);
        reset(cur);
        for (auto &idx : vals[cur]) if (attempt(idx)) {
            cur = idx + N;
            res.push_back(ord[idx]);
            for (idx += N; idx && !val[idx]; idx >>= 1) val[idx] = res.back();
            break;
        }
        // DBG(res);
        while (val[cur ^ 1]) cur >>= 1;
        cur ^= 1;
    }
    for (int x : res) cout << x << " ";
    cout << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
