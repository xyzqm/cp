#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
const int N = 1e5 + 1;
const int M = 1e9 + 7;
const ll inf = 1e18;
vector<pii> g[N];
ll d[N], ways[N], mn[N], mx[N];
int main() {
    int n, m;
    cin >> n >> m;
    fill(d, d + n + 1, inf);
    fill(mn, mn + n + 1, inf);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    priority_queue<pli> pq;
    pq.push({d[1] = mn[1] = 0, 1});
    ways[1] = 1;
    while (pq.size()) {
        auto [W, x] = pq.top();
        pq.pop();
        if (d[x] < (W = -W)) continue;
        d[x] = W;
        for (auto [y, w] : g[x]) {
            if (W + w < d[y]) {
                ways[y] = ways[x];
                mx[y] = mx[x] + 1;
                mn[y] = mn[x] + 1;
                pq.push({-(d[y] = W + w), y});
            } else if (W + w == d[y]) {
                ways[y] = (ways[y] + ways[x]) % M;
                mx[y] = max(mx[y], mx[x] + 1);
                mn[y] = min(mn[y], mn[x] + 1);
            }
        }
    }
    cout << d[n] << " " << ways[n] << " " << mn[n] << " " << mx[n] << endl;
}