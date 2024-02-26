#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
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
int n, m, v[N], l0 = 0, d[N], r[N], X[N], E[N];
bool all_same = true;
struct T {
    int e, x, o;
    bool operator<(T b) const {
        return make_tuple(e, x, o) < make_tuple(b.e, b.x, b.o);
    }
};
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
        E[x] = inf;
    } else if (!all_same) {
        set<T> s;
        for (int i : candidates) s.insert({min_label, i, i});
        while (s.size() > 1 && d[s.begin()->x]) {
            s.erase(s.upper_bound({s.begin()->e, inf, inf}), s.end());
            set<T> tmp;
            for (auto [e, x, o] : s) tmp.insert({E[x], X[x], o});
            s = tmp;
        }
        // print(x, min_label, candidates[0]);
        r[x] = min_label + r[s.begin()->o];
        X[x] = r[s.begin()->o], E[x] = min_label;
    } else r[x] = d[x] * l0;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int _ = 0; _ < m; _++) {
        int a, b, l;
        cin >> a >> b >> l;
        if (!l0) l0 = l;
        if (l0 != l) all_same = false;
        g[a].push_back({b, l});
    }
    for (int i = 1; i <= n; i++) if (!v[i]) dfs(i);
    for (int i = 1; i <= n; i++) cout << d[i] << " " << r[i] << endl;
    return 0;
}