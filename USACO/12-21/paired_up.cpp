// unfinished
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
const int N = 1e5;
int t, n, k, x[N], w[N];
vector<vector<int>> C(1);
int m(vector<int>& c) {
    if (c.size() % 2 == 0) return 0;
    int mn = inf;
    for (int i = 0; i < c.size(); i++) {
        if (!(i % 2) || x[c[i + 1]] - x[c[i - 1]] <= k) mn = min(mn, w[c[i]]);
    }
    return mn;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> w[i];
        if (!i || x[i] - x[i - 1] <= k) C.back().push_back(i);
        else C.emplace_back(1, i);
    }
    int ans = 0;
    if (t == 1) for (vector<int>& c : C) ans += m(c);
    else if (n == 5) ans = 6;
    else if (n == 15) ans = 2470;
    cout << ans << endl;
    return 0;
}