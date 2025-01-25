#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 1e3 + 1;
int x[N], y[N], v[N];
string s[N];
vector<int> ord, g[2 * N], rg[2 * N]; // 0 is up/left, 1 is down/right

void add(int i, int j) {
    g[i].push_back(j);
    rg[j].push_back(i);
}

void process(int i, int j) {
    if (s[i] == s[j]) return;
    if (s[i] == "UD") swap(i, j);
    // find the case in which they intersect
    int a = x[i] < x[j], b = y[i] < y[j];
    add(i << 1 | a, j << 1 | (b ^ 1));
    add(j << 1 | b, i << 1 | (a ^ 1));
}

void dfs(int i, vector<int> *g, vector<int> &o) {
    if (v[i]) return;
    v[i] = 1;
    for (int j : g[i]) dfs(j, g, o);
    o.push_back(i);
}

int ac() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> s[i];
    for (int i = 0; i < 2 * n; i++) g[i].clear(), rg[i].clear();
    for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) process(i, j);
    fill(v, v + 2 * n, 0);
    vector<int> ord;
    for (int i = 0; i < 2 * n; i++) if (!v[i]) dfs(i, g, ord);
    reverse(ord.begin(), ord.end());
    fill(v, v + 2 * n, 0);
    for (int i : ord) if (!v[i]) {
        vector<int> c;
        dfs(i, rg, c);
        sort(c.begin(), c.end());
        for (auto it = c.begin(); next(it) != c.end(); it++) {
            if (*it >> 1 == *next(it) >> 1) return 0;
        }
    }
    return 1;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << (ac() ? "YES\n" : "NO\n") << "0\n";
}
