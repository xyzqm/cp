#include <iostream>
#include <queue>
#define int long long
#define sz(x) ((int)x.size())
using namespace std;
using pii = pair<int, int>;
const int N = 1e5 + 1;
int n, m, k, r[N], e[N];
vector<pii> g[N]; // {node, weight}
priority_queue<int> res[N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            res[i] = priority_queue<int>();
        }
        priority_queue<pii, vector<pii>, greater<pii>> dj;
        for (int i = 0; i < k; i++) {
            cin >> e[i];
            dj.emplace(0, e[i]);
        }
        for (int i = 1; i <= n; i++) cin >> r[i];
        for (int i = 0; i < k; i++) for (int j = 0; j <= r[e[i]]; j++) res[e[i]].push(0);
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            g[x].emplace_back(y, z);
            g[y].emplace_back(x, z);
        }
        while (dj.size()) {
            auto [d, x] = dj.top();
            dj.pop();
            if (d != res[x].top()) continue;
            for (auto [y, w] : g[x]) {
                if (sz(res[y]) > r[y]) {
                    if (d + w < res[y].top()) {
                        res[y].pop();
                        res[y].push(d + w);
                        dj.emplace(res[y].top(), y);
                    }
                } else {
                    res[y].push(d + w);
                    if (sz(res[y]) > r[y]) dj.emplace(res[y].top(), y);
                }
            }
        }
        if (res[1].size() <= r[1]) cout << -1 << endl;
        else cout << res[1].top() << endl;
    }
}