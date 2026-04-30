#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int u) { return at(u) < 0 ? u : at(u) = rep(at(u)); }
    bool join(int u, int v) {
        u = rep(u), v = rep(v);
        if (u == v) return false;
        if (at(u) > at(v)) ::swap(u, v);
        at(u) += at(v);
        at(v) = u;
        return true;
    }
};

long long minimum_walk(std::vector<int> p, int s) {
    #define int long long
    int n = p.size(), ans = 0;
    set<int> rem;
    for (int i = 0; i < n; i++) {
        ans += abs(p[i] - i);
        rem.insert(i);
    }
    auto dfs = [&](this auto &&self, int u) -> bool {
        int l = u, r = p[u];
        if (l > r) swap(l, r);
        rem.erase(u);
        auto it = rem.lower_bound(l);
        while (it != rem.end()) {
            self(*it);
            it = rem.lower_bound(l);
        }
    };
    return ans;
}

#ifndef ONLINE_JUDGE
int32_t main() {
    cout << (minimum_walk({0, 2, 3, 1}, 0)) << "\n";
    cout << (minimum_walk({0, 3, 2, 1}, 0)) << "\n";
    cout << (minimum_walk({1, 0, 3, 4, 2}, 2)) << "\n";
}
#endif
