#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
const int inf = 1e18;
using T = tuple<int, int, int>;
const int N = 1e5;
const int M = 11;
int n, x[N], y[N], v[N], p[N], s[N];
queue<int> q[M];
int D(int a, int b) { return a * a + b * b; }
int P(int x) { return p[x] = x == p[x] ? x : P(p[x]); }
bool U(int x, int y) {
    x = P(x), y = P(y);
    if (x == y) return false;
    if (s[x] < s[y]) swap(x, y);
    p[y] = x;
    s[x] += s[y];
    return true;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        v[i] = p[i] = i, s[i] = 1;
    }
    sort(v, v + n, [](int i, int j) { return x[i] < x[j]; });
    // for (int i = 0; i < n; i++) cout << v[i] << " ";
    // cout << endl;
    for (int i = 0; i < n; i++) q[y[v[i]]].push(v[i]);
    vector<T> E;
    // for (int i = 0; i < n; i++) {
    //     for (int j = i; j < min(n, i + 20); j++) {
    //         E.emplace_back(D(x[v[j]] - x[v[i]], y[v[j]] - y[v[i]]), v[i], v[j]);
    //     }
    // }
    for (int _ = 0; _ < n; _++) {
        int i = v[_];
        for (int j = 0; j < M; j++) {
            while (q[j].size() && x[q[j].front()] <= x[i]) q[j].pop();
            if (q[j].size()) E.emplace_back(D(x[q[j].front()] - x[i], j - y[i]), i, q[j].front());
        }
    }
    int ans = 0;
    // cout << E.size() << endl;
    sort(E.begin(), E.end());
    for (auto [w, u, v] : E) {
        // cout << u << " " << v << endl;
        if (U(u, v)) ans += w;
    }
    cout << ans << endl;
    return 0;
}