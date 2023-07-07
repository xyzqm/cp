#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, h;
        cin >> n >> m >> h;
        vector<vector<int>> t(n, vector<int>(m));
        using pll = pair<ll, ll>;
        vector<pll> p;
        pll r;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cin >> t[i][j];
            sort(t[i].begin(), t[i].end());
            ll pen = 0, T = 0, P = 0;
            for (int& j : t[i]) {
                T += j;
                if (T > h) break;
                ++P, pen += T;
            }
            if (i) p.push_back({P, pen});
            else r = {P, pen};
        }
        // cout << r.first << " " << r.second << endl;
        auto cmp = [](pll a, pll b) {
            if (a.first != b.first) return a.first < b.first;
            else return a.second > b.second;
        };
        sort(p.begin(), p.end(), cmp);
        int i = 0;
        while (i < p.size() && !cmp(r, p[i])) ++i;
        cout << n - i << endl;
    }
}