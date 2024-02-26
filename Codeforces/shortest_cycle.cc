// https://codeforces.com/problemset/problem/1205/B
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int D = 60;
vector<int> vals[D];
int n, dist[120][120], e[120][120];
int main() {
    fill(&dist[0][0], &dist[0][0] + 120 * 120, 1e6);
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        for (int j = 0; j < D; j++) {
            if (x & (1ll << j)) vals[j].push_back(i);
        }
    }
    vector<int> mp(n, -1);
    int cnt = 0;
    for (int i = 0; i < D; i++) {
        if (vals[i].size() > 2) {
            cout << 3 << endl;
            return 0;
        } else if (vals[i].size() == 2) {
            if (mp[vals[i][0]] < 0) mp[vals[i][0]] = cnt++;
            if (mp[vals[i][1]] < 0) mp[vals[i][1]] = cnt++;
            int a = mp[vals[i][0]], b = mp[vals[i][1]];
            dist[a][b] = dist[b][a] = 1;
        }
    }
    for (int i = 0; i < cnt; i++) dist[i][i] = 0;
    for (int i = 0; i < cnt; i++) for (int j = 0; j < cnt; j++) e[i][j] = (dist[i][j] == 1) || (i == j);
    int ans = 1e6;
    for (int k = 0; k < cnt; k++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (i != j && e[i][k] && e[j][k]) ans = min(ans, dist[i][j] + 2);
            }
        }
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[j][k]);
            }
        }
    }
    if (ans == 1e6) cout << -1 << endl;
    else cout << ans << endl;
}