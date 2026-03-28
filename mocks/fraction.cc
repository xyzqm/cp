#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

bool is_valid(int n, int m) {
    while (true) {
        if (n < m) swap(n, m);
        if (n == 2 && m == 1) return true;
        else if (2 * m > n) return false;
        else n -= 2 * m;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int nn, m; cin >> nn >> m;
    int cnt = 0;
    queue<array<int, 2>> q;
    q.push({1, 2});
    q.push({2, 1});
    while (q.size()) {
        auto [n, d] = q.front();
        q.pop();
        if (n <= nn && d <= m) ++cnt; else continue;
        q.push({n + 2 * d, d});
        q.push({n, 2 * n + d});
    }
    cout << cnt << "\n";
}
