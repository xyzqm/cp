#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
const int N = 1e5 + 1;
const ll inf = 1e18;
vector<pii> g[N], rg[N];
ll d[N], d2[N];
int main() {
    int n, m;
    cin >> n >> m;
    fill(d, d + n + 1, inf);
    fill(d2, d2 + n + 1, inf);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        rg[b].push_back({a, c});
    }
    priority_queue<pli> pq;
    pq.push({d[1] = 0, 1});
    while (pq.size()) {
        auto [W, x] = pq.top();
        pq.pop();
        if (d[x] < (W = -W)) continue;
        d[x] = W;
        for (auto [y, w] : g[x]) {
            if (W + w < d[y]) pq.push({-(d[y] = W + w), y});
        }
    }
    pq.push({d2[n] = 0, n});
    while (pq.size()) {
        auto [W, x] = pq.top();
        pq.pop();
        if (d2[x] < (W = -W)) continue;
        d2[x] = W;
        for (auto [y, w] : rg[x]) {
            if (W + w < d2[y]) pq.push({-(d2[y] = W + w), y});
        }
    }
    ll ans = inf;
    for (int x = 1; x <= n; x++) {
        for (auto [y, w] : g[x]) {
            ans = min(ans, d[x] + w / 2 + d2[y]);
        }
    }
    cout << ans << endl;
}