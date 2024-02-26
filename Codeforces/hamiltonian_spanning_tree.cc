// https://codeforces.com/problemset/problem/618/D
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
vector<int> adj[N];
ll dp[N][2], n, X, Y;
void DP(int x, int p) {
    if ((adj[x].size() == 1) && (p != 0)) {
        dp[x][0] = 0;
        dp[x][1] = 1;
    } else {
        ll total = 0;
        vector<ll> difs;
        for (int y : adj[x]) {
            if (y == p) continue;
            DP(y, x);
            total += dp[y][1];
            difs.push_back(dp[y][0] - dp[y][1]);
        }
        sort(difs.begin(), difs.end());
        dp[x][0] = total + difs[0];
        dp[x][1] = 1 + total + difs[0] + (difs.size() > 1) * difs[1];
    }
}
int main() {
    cin >> n >> X >> Y;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (Y <= X) {
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() == n - 1) {
                cout << (n - 2) * Y + X << endl;
                return 0;
            }
        }
        cout << (n - 1) * Y;
    } else {
        DP(1, 0);
        int cuts = dp[1][1] - 1;
        cout << (n - 1 - cuts) * X + cuts * Y << endl;
    }
}