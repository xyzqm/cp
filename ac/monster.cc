// https://atcoder.jp/contests/abc275/tasks/abc275_h
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct lz_set : set<array<int, 2>> {
    int off = 0;
    array<int, 2> least() {
        auto [frq, i] = *begin();
        return {frq - off, i};
    }
    void sb(int x) { off += x; }
    void insert(array<int, 2> v) { set::insert({v[0] + off, v[1]}); }
    void mg(lz_set &o) {
        if (size() < o.size()) ::swap(off, o.off), swap(o);
        for (auto &[x, y] : o) insert({x - o.off, y});
    }
};

int32_t main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    vector<array<int, 2>> c(n, {-1, -1});
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;
    vector<int> stk = {0};
    for (int i = 1; i < n; i++) {
        while (stk.size() && b[stk.back()] <= b[i]) c[i][0] = stk.back(), stk.pop_back();
        if (stk.size()) c[stk.back()][1] = i;
        stk.push_back(i);
    }

    vector<int> w(n);
    vector<lz_set> sons(n);
    int s = 0;
    auto dfs = [&](auto &&f, int x, int cur) -> int {
        s += (w[x] = max((int)0, a[x] - cur)) * b[x];
        int sm = 0;
        for (int y : c[x]) if (y >= 0) {
            sm += f(f, y, cur + w[x]);
            if (w[y]) sons[x].insert({w[y], y});
            else sons[x].mg(sons[y]);
        }
        while (b[x] <= sm) {
            auto [frq, y] = sons[x].least();
            sons[x].sb(frq);
            w[x] += frq;
            s += frq * (b[x] - sm);
            while (sons[x].size() && sons[x].least()[0] == 0) {
                int y = sons[x].least()[1];
                sons[x].erase(sons[x].begin());
                sm -= b[y];
                for (auto [_, z] : sons[y]) sm += b[z];
                sons[x].mg(sons[y]);
            }
        }
        return w[x] ? b[x] : sm;
    };
    dfs(dfs, stk[0], 0);
    cout << s << endl;
}
