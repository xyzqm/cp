#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5 + 1;
const ll inf = 1e18;
vector<pii> g[N];
vector<ll> d[N];
bool vis[N];
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    auto cmp = [&](int i, int j) { return d[i] > d[j]; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    d[1] = {0};
    pq.push(1);
    while (pq.size()) {
        int x = pq.top();
        pq.pop();
        if (vis[x]) continue;
        vis[x] = true;
        vector<ll> v = d[x];
        // cout << x << endl;
        // for (ll& z : v) cout << z << " ";
        // cout << endl;
        int pw = 0;
        for (auto [y, w] : g[x]) {
            // cout << y << endl;
            for (ll& z : v) z += w - pw;
            // cout << "done" << endl;
            pw = w;
            int s = d[y].size();
            d[y].insert(d[y].end(), v.begin(), v.end());
            inplace_merge(d[y].begin(), d[y].begin() + s, d[y].end());
            if (d[y].size() > k) d[y].erase(d[y].begin(), d[y].begin() + d[y].size() - k);
            pq.push(y);
        }
    }
    for (int w : d[n]) cout << w << " ";
    cout << endl;
}