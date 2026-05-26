#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
#define DBG(X)
#else
#define DBG(X) cout << #X << ": " << X << endl
#endif

#define int int64_t

using P = array<int, 2>;
#ifndef DEBUG
#define DBG_P(X)
#else
#define DBG_P(X) cout << #X << ": " << X[0] << " " << X[1] << "\n"
#endif

const int inf = 1e18;

void compute() {
    assert(false);
}

struct lz : vector<P> {
    int ad = 0;
    void swap(lz &b) {
        vector::swap(b);
        ::swap(ad, b.ad);
    }
    P back() {
        auto [x, t] = vector::back();
        return {x, t + ad};
    }
    void push_back(P v) { vector::push_back({v[0], v[1] - ad}); }
    void append(lz &b) {
        if (size() < b.size()) swap(b);
        while (b.size()) push_back(b.back()), b.pop_back();
    }
};

void construct() {
    int n, m; cin >> n >> m;
    vector<int> p(n + 1), c(n + 1), in(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        ++in[p[i]];
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        if (!in[i]) q.push(i);
    }
    assert(accumulate(c.begin(), c.end(), 0LL) <= inf);
    vector<lz> cows(n + 1);
    vector<P> ans;
    vector<bool> vis(n + 1);
    auto step = [&](int u, vector<P> &res, bool alr = false) {
        vis[u] = true;
        assert(!in[u]);
        if (alr) assert(cows[u].size() >= c[u]);
        while (cows[u].size() > c[u]) {
            res.push_back(cows[u].back());
            cows[u].pop_back();
        }
        while (cows[u].size() < c[u]) cows[u].push_back({u, 0});
        ++cows[u].ad;
        cows[p[u]].append(cows[u]);
        if (!--in[p[u]]) q.push(p[u]);
    };
    while (q.size()) {
        int x = q.front(); q.pop();
        step(x, ans);
    }
    // DBG_P(cows[3].back());
    // now we go through remaining cycle and add any necessary cows
    auto solve_cycle = [&](int u) {
        assert(in[u] == 1);
        int cycle_len = 0, zero_pos = 0, mn = 1e18;
        for (int i = u; ; i = p[i]) {
            assert(in[i] == 1);
            ++cycle_len;
            mn = min(mn, c[i]);
            while (c[p[i]] - c[i] > (int)cows[p[i]].size()) cows[p[i]].push_back({p[i], 0});
            if (p[i] == u) break;
        }
        for (int i = u; ; i = p[i]) {
            c[i] -= mn;
            if (!c[i]) zero_pos = i;
            if (p[i] == u) break;
        }
        vector<P> here;
        --in[zero_pos], q.push(zero_pos);
        while (q.size()) {
            int x = q.front(); q.pop();
            step(x, here, true);
        }
        while (cows[zero_pos].size()) here.push_back(cows[zero_pos].back()), cows[zero_pos].pop_back();
        if (mn) {
            if (!here.size()) here.push_back({u, mn * cycle_len});
            else here.back()[1] += mn * cycle_len;
        }
        for (auto &[x, t] : here) ans.push_back({x, t});
    };
    for (int i = 1; i <= n; i++) if (!vis[i]) solve_cycle(i);
    for (auto &[x, t] : ans) {
        cout << x << " " << t << "\n";
    }
    while (m --> ans.size()) cout << "1 0\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int x, t; cin >> x >> t;
    while (x--) if (t == 1) compute(); else construct();
}
