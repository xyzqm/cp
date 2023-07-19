#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 1;
const int K = 17;
const ll inf = 1e18;
int n, m, k, x[N];
vector<pair<int, ll>> g[N];
ll D[N];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) cin >> x[i];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    ll ans = inf;
    for (int B = 0; B < K; B++) {
        fill(D, D + n + 1, inf);
        using T = pair<ll, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        vector<int> a, b;
        for (int i = 0; i < k; i++) {
            if (x[i] & (1 << B)) {
                a.push_back(x[i]);
                pq.push({D[x[i]] = 0, x[i]});
            }
            else b.push_back(x[i]);
        }
        if (!a.size() || !b.size()) continue;
        while (pq.size()) {
            auto [d, x] = pq.top();
            pq.pop();
            if (d != D[x]) continue;
            for (auto [y, w] : g[x]) if (d + w < D[y]) pq.push({D[y] = d + w, y});
        }
        for (int x : b) ans = min(ans, D[x]);
    }
    cout << (ans == inf ? -1 : ans) << endl;
}