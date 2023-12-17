#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
const int N = 2e5 + 1;
const int M = 4e5 + 1;
const int K = 20;
vector<P> g[N];
int n, m, v[N], d[N], r[N], X[N], E[N];
void dfs(int x) {
    // cout << x << endl;
    v[x] = true;
    int min_label = inf;
    d[x] = r[x] = 0;
    vector<int> candidates;
    for (auto [y, l] : g[x]) {
        // cout << y << endl;
        if (!v[y]) dfs(y);
        if (d[y] + 1 > d[x]) {
            d[x] = d[y] + 1;
            min_label = l;
        } else if (d[y] + 1 == d[x]) min_label = min(min_label, l);
    }
    for (auto [y, l] : g[x]) if (d[y] + 1 == d[x] && l == min_label) candidates.push_back(y);
    // cout << x << ": ";
    // for (int i : candidates) cout << i << " ";
    // cout << endl;
    if (!candidates.size()) {
        d[x] = r[x] = X[x] = 0;
    } else {
        vector<int> cp = candidates;
        while (cp.size() > 1 && X[cp[0]]) {
            // cout << cp[0] << endl;
            int mn = inf;
            vector<int> nxt, NXT;
            for (int i : cp) mn = min(mn, E[i]);
            for (int _ = 0; _ < cp.size(); _++) {
                int i = cp[_];
                if (E[i] == mn) nxt.push_back(X[i]), NXT.push_back(candidates[_]);
            }
            cp = nxt, candidates = NXT;
        }
        // print(x, min_label, candidates[0]);
        r[x] = min_label + r[candidates[0]];
        X[x] = candidates[0], E[x] = min_label;
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int _ = 0; _ < m; _++) {
        int a, b, l;
        cin >> a >> b >> l;
        g[a].push_back({b, l});
    }
    for (int i = 1; i <= n; i++) if (!v[i]) dfs(i);
    for (int i = 1; i <= n; i++) cout << d[i] << " " << r[i] << endl;
    return 0;
}