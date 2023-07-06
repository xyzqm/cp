#include <bits/stdc++.h>
#define int long long
using namespace std;
using pii = pair<int, int>;
vector<int> p, s;
int get(int x) {
    return p[x] = (x == p[x] ? x : get(p[x]));
}
void merge(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return;
    if (s[x] < s[y]) swap(x, y);
    p[y] = x;
    s[x] += s[y];
}
signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    set<pii> degs;
    for (int i = 1; i <= n; i++) degs.insert({deg[i], i});
    vector<int> ord;
    while (degs.size()) {
        int i = degs.begin()->second;
        degs.erase(degs.begin());
        ord.push_back(i);
        for (int j : adj[i]) {
            if (!deg[j]) continue; // already removed
            degs.erase({deg[j], j});
            --deg[j];
            --deg[i];
            degs.insert({deg[j], j});
        }
    }
    // DSU prep
    reverse(ord.begin(), ord.end());
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i;
    s.assign(n + 1, 1);
    vector<bool> seen(n + 1);
    int ans = 0;
    for (int i : ord) {
        seen[i] = true;
        for (int j : adj[i]) if (seen[j]) {
            merge(i, j);
            deg[i]++;
            deg[j]++;
        }
        // cout << i << " " << deg[i] << " " << s[get(i)] << endl;
        ans = max(ans, deg[i] * s[get(i)]);
    }
    cout << ans << endl;
}