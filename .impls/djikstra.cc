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
vector<pii> g[N];
ll d[N];
int main() {
    int n, m;
    cin >> n >> m;
    fill(d, d + n + 1, inf);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
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
}