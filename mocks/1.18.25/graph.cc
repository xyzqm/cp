#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
int n, u[N], v[N], rem[N], t[N], d[N], x[N], r[N + 2];
vector<int> g[N];

int main() {
    int m, q; cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        g[u[i]].push_back(i);
        g[v[i]].push_back(i);
    }
    fill(rem, rem + N, N);
    for (int i = 0; i < q; i++) {
        int j; cin >> j;
        rem[j] = i;
    }
    queue<int> bfs; bfs.push(1);
    fill(d, d + N, N);
    d[1] = 0, t[1] = N;
    while (bfs.size()) {
        int x = bfs.front(); bfs.pop();
        if (::x[x]) continue;
        ::x[x] = 1;
        for (int i : g[x]) {
            int y = u[i] ^ v[i] ^ x;
            if (d[x] + 1 <= d[y]) {
                d[y] = d[x] + 1;
                t[y] = max(t[y], min(t[x], rem[i]));
                bfs.push(y);
            }
        }
    }
    for (int i = 1; i <= n; i++) ++r[t[i]];
    for (int i = 0; i < q; i++) cout << (r[i] += (i ? r[i - 1] : 0)) << endl;
}
