// https://codeforces.com/contest/1856/problem/E2
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 1e6 + 1;

int n, sz[N], r = 0;
vector<int> g[N];

template <int N = 1>
int mx(vector<int> &v, int s) {
    if (s > N) return mx<min(2 * N, ::N)>(v, s);
    bitset<N> bs = 1;
    for (int x : v) bs |= bs << x;
    int r = 0;
    for (int i = 0; i <= s; i++) if (bs[i]) r = max(r, i * (s - i));
    return r;
}

int dfs(int x) {
    map<int, int> mp;
    for (int y : g[x]) ++mp[dfs(y)];
    vector<int> S;
    for (auto [v, c] : mp) {
        sz[x] += v * c;
        for (int i = 1; i <= c; i *= 2) S.push_back(i * v), c -= i;
        S.push_back(v * c);
    }
    sort(S.begin(), S.end());
    if (S.size()) {
        if (int y = mp.rbegin()->first; 2 * y >= sz[x]) r += y * (sz[x] - y);
        else r += mx(S, sz[x]);
    }
    return ++sz[x];
}

int32_t main() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        g[p].push_back(i);
    }
    dfs(1);
    cout << r << endl;
}
