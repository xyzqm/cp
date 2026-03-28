#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X);
#endif

#define int int64_t

vector<vector<int>> g(1);
vector<bool> removed;
vector<int> sz;
vector<vector<array<int, 2>>> ancs;

int get_sz(int x, int p) {
    sz[x] = 1;
    for (int y : g[x]) if (y != p && !removed[y]) sz[x] += get_sz(y, x);
    return sz[x];
}

void fill(int x, int p, int cen, int dist) {
    ancs[x].push_back({dist, cen});
    for (int y : g[x]) if (y != p && !removed[y]) fill(y, x, cen, dist + 1);
}

void decompose(int x, int p, int n) {
    for (int y : g[x]) if (y != p && !removed[y] && sz[y] > n / 2) return decompose(y, x, n);
    // this is the centroid
    fill(x, 0, x, 0);
    removed[x] = true;
    for (int y : g[x]) if (!removed[y]) decompose(y, 0, get_sz(y, 0));

}

int32_t main() {
    int q; cin >> q;
    vector<array<int, 2>> qs(q);
    for (char c; auto &[t, u] : qs) {
        cin >> c >> u;
        t = c == 'Q';
        if (!t) {
            if (u > 0) g[u].push_back(g.size());
            g.emplace_back();
            if (u > 0) g.back().push_back(u);
        }
    }
    removed.assign(g.size(), false);
    ancs.resize(g.size());
    sz.resize(g.size());
    for (int i = 1; i < g.size(); i++) if (!removed[i]) decompose(i, 0, get_sz(i, 0));
    for (int i = 1; i < g.size(); i++) reverse(ancs[i].begin(), ancs[i].end());
    vector<vector<array<int, 2>>> mx(g.size(), {{-(int)g.size(), 0}, {-(int)g.size(), 0}}); // two max dists to each centroid ancestor
    for (int cur = 0; auto &[t, u] : qs) {
        if (t) {
           int res = 0;
           for (int prv = 0; auto &[dist, anc] : ancs[u]) {
               res = max(res, dist + mx[anc][mx[anc][0][1] == prv][0]);
               prv = anc;
           }
           cout << res << "\n";
        }
        else {
            u = ++cur;
            for (int prv = 0; auto &[dist, anc] : ancs[u]) {
                bool placed = false;
                for (auto &[d, sb] : mx[anc]) if (sb == prv) d = max(d, dist), placed = true;
                if (!placed) mx[anc].push_back({dist, prv});
                sort(mx[anc].begin(), mx[anc].end(), greater());
                if (mx[anc].size() > 2) mx[anc].pop_back();
                prv = anc;
            }
        }
    }
}
