#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6;
int v[N];
vector<int> adj[N];
int tot, per, n;
int dif[N];
int p[N];
int cnt = 0;
int dfs1(int x, int par) {
    p[x] = par;
    dif[x] += v[x] - per;
    for (int y : adj[x]) {
        if (y != par) {
            dif[x] += dfs1(y, x);
        }
    }
    return dif[x];
}
void dfs2(int x) {
    for (int c : adj[x]) {
        if (c == p[x]) continue;
        if (dif[c] > 0) {
            dfs2(c);
            cnt++;
        } else if (dif[c] < 0) {
            cnt++;
            dfs2(c);
        } else dfs2(c);
    }
}
void dfs3(int x) {
    for (int c : adj[x]) {
        if (c == p[x]) continue;
        if (dif[c] > 0) {
            dfs3(c);
            cout << c << " " << x << " " << dif[c] << endl;
        } else if (dif[c] < 0) {
            cout << x << " " << c << " " << -dif[c] << endl;
            dfs3(c);
        } else dfs3(c);
    }
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        tot += v[i];
    }
    per = tot / n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 1);
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), [](int a, int b) {
            return dif[a] > dif[b];
        });
    }
    dfs2(1);
    cout << cnt << endl;
    dfs3(1);
}