#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 2e5 + 1;
int d[N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    set<P> S;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto u = S.upper_bound({x, 0});
        auto l = u == S.begin() ? S.end() : prev(u);
        if (u != S.end()) {
            if (l == S.end() || l->second < u->second) ++d[x], --d[u->first];
        }
        S.insert({x, i});
    }
    int c = 0;
    for (int i = 0; i <= n; i++) {
        c += d[i];
        cout << c << endl;
    }
    return 0;
}