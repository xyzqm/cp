// https://codeforces.com/problemset/problem/398/D
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;
using Q = tuple<char, int, int>;
const int B = 900;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, qc, o;
    cin >> n >> m >> qc >> o;
    vector<bool> on(n + 1);
    for (int i = 0; i < o; i++) {
        int x;
        cin >> x;
        on[x] = true;
    }
    vector<vector<int>> g(n + 1);
    vector<int> ans(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<Q> q(qc);
    vector<int> d(n + 1), md(n + 1);
    for (int i = 0; i < qc; ++i) {
        char c;
        int x, y;
        cin >> c >> x;
        if (c == 'A' || c == 'D') {
            cin >> y;
            if (c == 'A') ++d[x], ++d[y];
            else --d[x], --d[y];
            md[x] = max(md[x], d[x]);
            md[y] = max(md[y], d[y]);
        }
        q[i] = {c, x, y};
    }
    vector<int> id(n + 1);
    int c = 0;
    for (int i = 1; i <= n; ++i) if (md[i] + g[i].size() >= B) id[i] = ++c;
    vector<int> rid(c + 1);
    for (int i = 1; i <= n; ++i) rid[id[i]] = i;
    vector<vector<bool>> e(c + 1, vector<bool>(c + 1));
    for (int i = 1; i <= n; ++i) {
        if (id[i]) {
            for (int j : g[i]) e[id[i]][id[j]] = e[id[j]][id[i]] = true;
        } else if (on[i]) {
            for (int j : g[i]) ++ans[j];
        }
    }
    for (auto [C, x, y] : q) {
        if (C == 'O') {
            if (!id[x]) for (int z : g[x]) ++ans[z];
            on[x] = true;
        } else if (C == 'F') {
            if (!id[x]) for (int z : g[x]) --ans[z];
            on[x] = false;
        } else if (C == 'A') {
            g[x].push_back(y);
            g[y].push_back(x);
            e[id[x]][id[y]] = e[id[y]][id[x]] = true;
            if (!id[x] && on[x]) ++ans[y];
            if (!id[y] && on[y]) ++ans[x];
        } else if (C == 'D') {
            g[x].erase(find(g[x].begin(), g[x].end(), y));
            g[y].erase(find(g[y].begin(), g[y].end(), x));
            e[id[x]][id[y]] = e[id[y]][id[x]] = false;
            if (!id[x] && on[x]) --ans[y];
            if (!id[y] && on[y]) --ans[x];
        } else {
            int res = ans[x];
            if (!id[x]) {
                for (int z : g[x]) if (id[z] && on[z]) ++res;
            } else {
                for (int z = 1; z <= c; ++z) {
                    if (e[id[x]][z] && on[rid[z]]) ++res;
                }
            }
            cout << res << endl;
        }
    }
}