#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;
#define int long long
const int inf = 1e18;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
const int N = 1e5 + 1, K = 2e5 + 1;
int n, k, m, R, x[N], X[N], Y[N], in[N], a[N], p[N], S[N], v[N], c[N], r[N], b[K];
set<int> s[N];
vector<int> g[N];
int P(int x) { return p[x] = p[x] == x ? x : P(p[x]); }
int U(int x, int y) {
    x = P(x), y = P(y);
    if (x == y) return 0;
    if (s[x] < s[y]) swap(x, y);
    p[y] = x, S[x] += S[y];
}
int floyd(int x) {
    int t = x, h = X[x];
    while (t != h) t = X[t], h = X[X[h]];
    return t;
}
void dfs(int x) {
    v[x] = true;
    for (int i : s[x]) if (!c[i]++) R++;
    r[x] = R;
    for (int i : g[x]) if (!v[i]) dfs(i);
    for (int i : s[x]) if (!--c[i]) R--;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> m;
    for (int i = 0; i < k; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) s[i].insert(i), S[i] = 1, p[i] = x[i] = Y[i] = i;
    for (int i = 0; i < k; i++) swap(Y[a[i]], Y[b[i]]);
    for (int i = 1; i <= n; i++) X[Y[i]] = i;
    // for (int i = 1; i <= n; i++) cout << X[i] << " ";
    // cout << endl;
    for (int i = 1; i <= n; i++) g[X[i]].push_back(i);
    if (n <= 100 && k <= 200 && m < n * k) {
        for (int _ = 0; _ < n; _++) {
            for (int __ = 0; __ < k; __++) if (m) {
                swap(x[a[__]], x[b[__]]);
                s[x[a[__]]].insert(a[__]);
                s[x[b[__]]].insert(b[__]);
                m--;
            }
        }
        for (int i = 1; i <= n; i++) cout << s[i].size() << endl;
    } else {
        for (int i = 0; i < k; i++) {
            swap(x[a[i]], x[b[i]]);
            s[x[a[i]]].insert(a[i]);
            s[x[b[i]]].insert(b[i]);
        }
        for (int i = 1; i <= n; i++) if (!v[i]) {
            int j = floyd(i);
            int cur = j;
            // print(i, j);
            for (int _ = 1; _ <= n; _++) c[_] = 0;
            R = 0;
            do {
                cur = X[cur], v[cur] = true;
                for (int _ : s[cur]) if (!c[_]++) R++;
            } while (cur != j);
            do {
                cur = X[cur];
                r[cur] = R;
                for (int _ : g[cur]) if (!v[_]) dfs(_);
            } while (cur != j);
        }
        for (int i = 1; i <= n; i++) cout << r[i] << endl;
    }
    return 0;
}