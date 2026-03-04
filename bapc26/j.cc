#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int N = 2001;
const int K = 30;
int g[N][N], pref[N][N];
set<int> good[N];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cin >> g[i][j];
        if (j) pref[i][j] = pref[i][j - 1];
        if (g[i][j]) good[i].insert(j), ++pref[i][j];
        // cout << pref[i][j] << " \n"[j == m - 1];
    }
    for (int i = 1; i < n; i++) for (int j = 0; j < m; j++) {
        pref[i][j] += pref[i - 1][j];
        // cout << pref[i][j] << " \n"[j == m - 1];
    }
    auto rect_sum = [&](int x1, int y1, int x2, int y2) {
        if (x1 > x2) return (int)0;
        int sm = pref[x2][y2];
        if (y1) sm -= pref[x2][y1 - 1];
        if (x1) sm -= pref[x1 - 1][y2];
        if (y1 && x1) sm += pref[x1 - 1][y1 - 1];
        return sm;
    };
    DBG(rect_sum(1, 0, 2, 1));
    int q; cin >> q;
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        --x1, --y1, --x2, --y2;
        if (int tot = rect_sum(x1, y1, x2, y2); tot > K) cout << "YES\n";
        else {
            int cur_row = x1 - 1, cur_sum = 0;
            vector<int> vals;
            while (vals.size() < tot) {
                for (int dif = n; dif > 0; dif /= 2) {
                    while (cur_row + dif < n && rect_sum(x1, y1, cur_row + dif, y2) == cur_sum) cur_row += dif;
                }
                // assert(cur_row + 1 < n);
                cur_sum = rect_sum(x1, y1, ++cur_row, y2);
                for (auto it = good[cur_row].lower_bound(y1); it != good[cur_row].end() && *it <= y2; it++) {
                    vals.push_back(g[cur_row][*it]);
                }
            }
            DBG(vals);
            sort(vals.begin(), vals.end());
            // ranges::sort(vals);
            bool found = false;
            for (int i = 0; i + 2 < vals.size(); i++) {
                int a = vals[i], b = vals[i + 1], c = vals[i + 2];
                if (a + b > c) found = true;
            }
            cout << array{"NO\n", "YES\n"}[found];
        }
    }
}
