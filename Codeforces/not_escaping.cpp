#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const int K = 2e5;
const ll D = 1e6;
const ll inf = 1e18;
int n, m, k, I;
ll x[K], dist[2 * K];
vector<pair<int, ll>> l[K], g[2 * K];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            cin >> x[i];
            l[i].clear();
        }
        for (int i = 0; i <= 2 * (k + 1); i++) g[i].clear();
        l[1].push_back({1, 0});
        l[n].push_back({m, 1});
        map<pii, int> mp;
        mp[{1, 1}] = 0;
        mp[{n, m}] = I = 1;
        for (int i = 0; i < k; i++) {
            int a, b, c, d;
            ll h;
            cin >> a >> b >> c >> d >> h;
            int &i1 = mp[{a, b}], &i2 = mp[{c, d}];
            if (!i1) i1 = ++I;
            if (!i2) i2 = ++I;
            g[i1].push_back({i2, D * (c - a) - h});
            l[a].push_back({b, i1});
            l[c].push_back({d, i2});
        }
        // cout << "here" << endl;
        for (int i = 1; i <= n; i++) {
            // cout << i << " " << l[i].size() << endl;
            sort(l[i].begin(), l[i].end());
            l[i].erase(unique(l[i].begin(), l[i].end()), l[i].end());
            // for (auto  [x, y] : l[i]) cout << x << ":" << y << " ";
            // cout << l[i].size() << endl;
            if (l[i].size()) for (int j = 0; j < l[i].size() - 1; j++) {
                // cout << i << " " << j << endl;
                auto [p1, i1] = l[i][j];
                auto [p2, i2] = l[i][j + 1];
                g[i1].push_back({i2, x[i] * (p2 - p1)});
                g[i2].push_back({i1, x[i] * (p2 - p1)});
            }
        }
        // cout << "here" << endl;
        fill(dist, dist + I + 1, inf);
        using T = pair<ll, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({dist[0] = 0, 0});
        while (pq.size()) {
            auto [d, x] = pq.top();
            pq.pop();
            if (d != dist[x]) continue;
            // cout << d << " " << x << endl;
            for (auto [y, w] : g[x]) if (d + w < dist[y]) pq.push({dist[y] = d + w, y});
        }
        if (dist[1] == inf) cout << "NO ESCAPE" << endl;
        else cout << dist[1] - D * (n - 1) << endl;
    }
}