#include <bits/stdc++.h>
using namespace std;

#ifdef EVAL
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void smin(int &a, int b) { a = min(a, b); }

// return {num, cost}
array<int, 2> run_dp(int pen, vector<array<int, 3>> &vals) { // {coord, type, cost}
    ranges::sort(vals);
    DBG(vals); // type 0 = (, 1 = )
    using T = array<int, 2>;
    priority_queue<T, vector<T>, greater<T>> opts;
    int num = 0, tot_cost = 0;
    for (auto &[_, type, cost] : vals) {
        if (!type) opts.push({cost - pen, 0});
        else if (opts.size() && opts.top()[0] + cost < 0) {
            tot_cost += opts.top()[0] + cost;
            if (!opts.top()[1]) ++num;
            opts.pop();
            opts.push({-cost, 1});
        }
    }
    return {num, tot_cost};
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<array<int, 3>> coords[2];
    while (n--) {
        int t, x, y, c; cin >> t >> x >> y >> c;
        if (t > 2) swap(x, y);
        coords[t > 2].push_back({x, t & 1, c});
    }
    auto ck = [&](int pen) {
        auto [num_x, x_cost] = run_dp(pen, coords[0]);
        auto [num_y, y_cost] = run_dp(pen, coords[1]);
        return array{num_x + num_y, x_cost + y_cost};
    };
    DBG(ck(1e10));
    if (ck(1e10)[0] < k) {
        cout << "-1\n";
        return 0;
    }
    int pen = 0;
    for (int d = (int)1 << 35; d > 0; d >>= 1) if (ck(pen + d)[0] <= k) pen += d;
    DBG(pen);
    cout << ck(pen)[1] + k * pen << "\n";
}
