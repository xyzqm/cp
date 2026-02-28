#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int inf = 1e15;

void smin(int &a, const int b) { a = min(a, b); }

void ac() {
    int n, q, C; cin >> n >> q >> C;
    vector<array<int, 2>> buildings(n);
    vector<int> hs;
    for (auto &[l, h] : buildings) {
        cin >> l >> h;
        hs.push_back(h);
    }
    ranges::sort(buildings);
    ranges::sort(hs);
    auto cost = [&](int i, int j) {
        return abs(buildings[i][1] - buildings[j][1]);
    };
    auto arc = [&](int i, int j) { // length of cw arc from i to j
        int len = buildings[j][0] - buildings[i][0];
        if (len < 0) len += C;
        return len;
    };

    auto dp = vector(n + 1, vector(n + 1, inf));
    for (int dif = 1; dif <= n; dif++) {
        for (int l = 0, r = l + dif; l < n; l++, r++) {
            if (r >= n) r -= n;
            if (dif == 1) dp[l][r] = 0;
            else for (int m = l + 1, mm = l + 1; m < l + dif; m++, mm++) {
                if (mm >= n) mm -= n;
                int edge = inf;
                if (2 * arc(l, mm) < C) smin(edge, cost(l, mm));
                if (2 * arc(mm, r) < C) smin(edge, cost(mm, r));
                smin(
                    dp[l][r],
                    dp[l][mm] + dp[mm][r] + edge
                );
            }
        }
    }

    // enumerate possibilities for two connect to middle
    vector<array<int, 3>> opts;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (buildings[i][1] < buildings[j][1]) {
            opts.push_back({
                buildings[i][1],
                buildings[j][1],
                dp[i][j] + dp[j][i] + cost(i, j)
            });
        }
    }
    ranges::sort(opts);
    auto it = opts.begin();
    multiset<array<int, 2>> cur;
    map<int, int> opt;
    multiset<int> vals = {opt[0] = inf};
    for (int h : hs) {
        while (it != opts.end() && (*it)[0] <= h) {
            auto &[l, r, v] = *it;
            cur.insert({r, v});
            vals.insert(v);
            it++;
        }
        while (cur.size() && (*cur.begin())[0] <= h) {
            vals.erase(vals.find((*cur.begin())[1]));
            cur.erase(cur.begin());
        }
        opt[h] = *vals.begin();
    }
    DBG(opt);

    buildings.emplace_back(); // add space for middle building
    while (q--) {
        cin >> buildings.back()[1];
        int res = inf;
        // first try only one building
        for (int i = 0; i < n; i++) smin(res, dp[i][i] + cost(n, i));
        smin(res, prev(opt.upper_bound(buildings.back()[1]))->second);
        // for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        //     smin(res, dp[i][j] + dp[j][i] + cost(n, i) + cost(n, j));
        // }
        cout << res << endl;
    }
    // DBG(dp[2][1]);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
