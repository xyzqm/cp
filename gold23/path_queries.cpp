#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#define int long long
using namespace std;
const int N = 2e5 + 1;
const int inf = 1e18;
int p[N], s[N], ans[N];
int find(int x) {
    if (p[x] == x) return x;
    else return p[x] = find(p[x]);
}
void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (s[x] < s[y]) swap(x, y);
    s[x] += s[y];
    p[y] = x;
}
signed main() {
    iota(p, p + N, 0);
    fill(s, s + N, 1);
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, int>> v;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        v.emplace_back(z, x, y);
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        v.emplace_back(x, inf, i);
    }
    sort(v.begin(), v.end());
    int cur = 0;
    for (auto [x, y, z] : v) {
        if (y == inf) ans[z] = cur;
        else {
            cur += s[find(y)] * s[find(z)];
            unite(y, z);
        }
    }
    for (int i = 0; i < q; i++) cout << ans[i] << " ";
    cout << endl;
}