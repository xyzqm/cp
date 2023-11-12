#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 201;
int n;
P c[N];
int solve() {
    sort(c + 1, c + n + 1);
    int r = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int d = c[j].first - c[i].first;
            int M = max(c[j].second, c[i].second);
            int m = min(c[j].second, c[i].second);
            if (d < M - m) continue;
            set<int> s;
            for (int k = i; k <= j; k++) {
                if (c[k].second > M && c[k].second <= m + d) s.insert(c[k].second - d - 1);
                else if (c[k].second < m && c[k].second >= M - d) s.insert(c[k].second);
            }
            r += s.size() + 1;
        }
    }
    return r;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i].first >> c[i].second;
    int r = solve();
    for (int i = 1; i <= n; i++) swap(c[i].first, c[i].second);
    r += solve();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            map<int, bool> v;
            int d = c[j].first - c[i].first;
            int M = max(c[j].second, c[i].second);
            int m = min(c[j].second, c[i].second);
            if (d < M - m) continue;
            for (int k = i; k <= j; k++) {
                v[c[k].second] = true;
                int t = r;
                if (c[k].second <= m && c[k].second >= M - d && v[c[k].second + d]) --r;
                else if (c[k].second >= M && c[k].second <= m + d && v[c[k].second - d]) --r;
            }
        }
    }
    cout << r + 1 << endl;
    return 0;
}