#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;

int dp[N][2], sz[N];
vector<int> g[N];

void dfs(int x) {
    int msz = 0;
    int mdel = 0;
    for (int y : g[x]) {
        dfs(y);
        msz = max(msz, sz[y]);
        mdel = max(mdel, sz[y] + dp[y][1] - dp[y][0]);
        dp[x][0] += dp[y][1];
        dp[x][1] += dp[y][1];
        sz[x] += sz[y];
    }
    ++sz[x];
    dp[x][0] += sz[x] - mdel;
    auto sv = [&](int i) { return sz[i] + dp[i][1] - dp[i][0]; };
    sort(g[x].begin(), g[x].end(), [&](int i, int j) { return sv(i) > sv(j); });
    dp[x][1] += 2 * sz[x] - max(2 * msz, g[x].size() > 1 ? sv(g[x][0]) + sv(g[x][1]) : 0);
}

int main() {
    int n; cin >> n;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        g[p].push_back(i);
    }
    dfs(1);
    cout << dp[1][1] << endl;
}
