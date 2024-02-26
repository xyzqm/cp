#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 5e4 + 1;
const int K = 51;
int n, k, b[N], d[N], l[K], L[K];
char s[K][K];
vector<P> g[N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        d[i] = inf;
        cin >> b[i];
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> s[i][j];
            if (s[i][j] == '0') s[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) if (s[b[i]][j]) {
            if (l[j]) g[i].push_back({l[j], i - l[j]});
        }
        l[b[i]] = i;
    }
    for (int i = n; i > 0; i--) {
        for (int j = 1; j <= k; j++) if (s[b[i]][j]) {
            if (L[j]) g[i].push_back({L[j], L[j] - i});
            if (j == b[n]) g[i].push_back({n, n - i});
        }
        L[b[i]] = i;
    }
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({d[1] = 0, 1});
    while (pq.size()) {
        auto [D, x] = pq.top(); 
        pq.pop();
        if (D != d[x]) continue;
        for (auto [y, w] : g[x]) if (D + w < d[y]) pq.push({d[y] = D + w, y});
    }
    cout << (d[n] < inf ? d[n] : -1) << endl;
    return 0;
}