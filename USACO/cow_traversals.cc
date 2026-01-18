#include <bits/stdc++.h>
using namespace std;

vector<int> rt; // roots of each tree
struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    int sz(int x) { return -at(rep(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        int r = rt[y];
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        rt[x] = r;
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    rt.resize(n + 1);
    vector<int> nx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nx[i];
        rt[i] = i;
    }
    int q; cin >> q;
    vector<int> qs(q);
    // ts[i] stores the operations applied at node i, from earliest to latest
    vector<vector<int>> ts(n + 1);
    char c;
    for (int &idx : qs) {
        cin >> idx >> c;
        int t;
        if (c == 'C') t = 0;
        else if (c == 'O') t = 1;
        else t = 2;
        ts[idx].push_back(t);
    }
    reverse(qs.begin(), qs.end()); // process queries backward
    dsu uf(n + 1); // our union-find data structure

    // join all non-parties to their parents
    for (int i = 1; i <= n; i++) if (!ts[i].size()) uf.join(i, nx[i]);
    array<int, 3> ans = {0, 0, 0}; // ans[i] = # of cows attending a party of type i
    for (int i = 1; i <= n; i++) if (ts[i].size()) {
        ans[ts[i].back()] += uf.sz(i);
    }
    vector<array<int, 3>> res = {ans};
    for (int i : qs) {
        assert(ts[i].size());
        ans[ts[i].back()] -= uf.sz(i);
        ts[i].pop_back();
        if (ts[i].size()) { // switch the type of this party from one to another
            ans[ts[i].back()] += uf.sz(i);
        }
        else { // delete this party and merge i into nx[i]
            int sz = uf.sz(i);
            uf.join(i, nx[i]);
            int r = rt[uf.rep(i)];
            if (ts[r].size()) ans[ts[r].back()] += sz;
        }
        res.push_back(ans);
    }
    reverse(res.begin(), res.end());
    res.erase(res.begin());
    for (auto &[c, o, w] : res) cout << c << " " << o << " " << w << "\n";
}
