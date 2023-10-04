#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>
#define int long long
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
const int M = 998244353;
const int K = 20;
const ll inf = 1e18;
vector<int> g[N], rg[N];
int n, m;
pair<int, int> d[N];
ll D[N][K];
int pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % M, --b;
        else a = a * a % M, b /= 2;
    }
    return res % M;
}
struct Node {
    ll w;
    int x, t;
    bool operator <(const Node& other) const {
        return w > other.w;
    }
};
signed main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    using T = pair<pair<int, int>, int>;
    priority_queue<T, vector<T>, greater<T>> pq1;
    fill(d, d + n + 1, make_pair(inf, inf));
    pq1.push({d[1] = {0, 0}, 1});
    while (pq1.size()) {
        auto [w, x] = pq1.top();
        pq1.pop();
        if (w != d[x]) continue;
        auto nw = w;
        ++nw.second;
        for (int y : (w.first % 2 == 0 ? g[x] : rg[x])) if (nw < d[y]) {
            pq1.push({d[y] = nw, y});
        }
        ++nw.first;
        for (int y : (w.first % 2 == 0 ? rg[x] : g[x])) if (nw < d[y]) {
            pq1.push({d[y] = nw, y});
        }
    }
    // cout << d[n].first << " " << d[n].second << endl;
    if (d[n].first >= K) {
        // assert(false);
        cout << (d[n].second + pw(2, d[n].first) - 1) % M << endl;
        return 0;
    }
    priority_queue<Node> pq2;
    fill(&D[0][0], &D[0][0] + N * K, inf);
    pq2.push({D[1][0] = 0, 1, 0});
    ll ans = inf;
    while (pq2.size()) {
        auto [w, x, t] = pq2.top();
        pq2.pop();
        if (w != D[x][t]) continue;
        if (x == n) ans = min(ans, w);
        for (int y : (t % 2 == 0 ? g[x] : rg[x])) {
            if (w + 1 < D[y][t]) pq2.push({D[y][t] = w + 1, y, t});
        }
        for (int y : (t % 2 == 0 ? rg[x] : g[x])) {
            if (t + 1 < K && w + (1 << t) + 1 < D[y][t + 1]) pq2.push({D[y][t + 1] = w + (1 << t) + 1, y, t + 1});
        }
    }
    cout << ans % M << endl;
}