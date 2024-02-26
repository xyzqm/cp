#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <functional>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
const int N = 1e5 + 1, K = 2e5 + 1;
int n, k, m, unq, jumps, I, x[N], X[N], Y[N], a[K], v[N], c[N], r[N], prv[N], cyc[N], b[K];
vector<int> g[N];
vector<P> s[N];
int floyd(int x) {
    int t = x, h = X[x];
    while (t != h) t = X[t], h = X[X[h]];
    return t;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> m;
    for (int i = 1; i <= k; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        s[i].push_back({0, i});
        x[i] = Y[i] = i;
    }
    for (int i = 1; i <= k; i++) swap(Y[a[i]], Y[b[i]]);
    for (int i = 1; i <= n; i++) g[X[Y[i]] = i].push_back(Y[i]);
    for (int i = 1; i <= k; i++) {
        swap(x[a[i]], x[b[i]]);
        s[x[a[i]]].push_back({i, a[i]});
        s[x[b[i]]].push_back({i, b[i]});
    }
    for (int i = 1; i <= n; i++) if (!v[i]) {
        int max_jumps = m / k, max_steps = m % k;
        int root = floyd(i);
        int cur = root;
        for (int j = 1; j <= n; j++) c[j] = 0;
        unq = 0, jumps = 0, I = 0;
        if (max_jumps) do {
            for (auto [_, j] : s[cur]) if (!c[j]++) unq++;
            ++jumps;
            prv[X[cur]] = cur, cur = X[cur];
        } while (jumps < max_jumps && cur != root);
        // jumps now equals min(cycle length, max_jumps)
        // if we haven't already jumped the cycle, start stepping
        auto step = [&](int mx) { 
            while (I < s[cur].size() && s[cur][I].first <= mx) {
                if (!c[s[cur][I++].second]++) unq++;
            }
        };
        if (jumps == max_jumps) step(max_steps);
        v[root] = true, r[root] = unq;
        function<void(int)> dfs = [&](int x) {
            v[x] = true;
            if (--max_jumps < jumps) {
                while (I && I--) if (!--c[s[cur][I].second]) unq--;
                cur = prv[cur];
                I = s[cur].size();
                while (I-- && s[cur][I].first > max_steps) if (!--c[s[cur][I].second]) unq--;
                ++I;
            }
            for (auto [_, j] : s[x]) if (!c[j]++) unq++;
            r[x] = unq;
            for (int y : g[x]) if (!v[y]) {
                dfs(prv[x] = y);
            }
            for (auto [_, j] : s[x]) if (!--c[j]) unq--;
            if (++max_jumps <= jumps) {
                step(inf);
                cur = X[cur];
                step(max_steps);
            }
        };
        for (int j : g[root]) if (!v[j]) dfs(prv[root] = j);
    }
    for (int i = 1; i <= n; i++) cout << r[i] << endl;
    return 0;
}