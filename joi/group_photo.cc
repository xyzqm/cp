#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void inc(int i) {
        for (++i; i < size(); i += i & -i) ++at(i);
    }
    int query(int r) {
        int sm = 0;
        for (; r > 0; r -= r & -r) sm += at(r);
        return sm;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> pos(n + 1);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        pos[x] = i;
    }
    auto rev = vector(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        bit fen(n + 1);
        for (int j = i, inv = 0; j > 0; j--) {
            inv += fen.query(n - pos[j]);
            fen.inc(n - pos[j]);
            rev[i][j] = inv;
        }
    }
    vector<int> dp(n + 1, n * n);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        bit fen(n);
        for (int j = 1; j <= i; j++) fen.inc(n - pos[j]);
        for (int j = i + 1, iv = 0; j <= n; j++) {
            iv += fen.query(n - pos[j]);
            dp[j] = min(dp[j], dp[i] + rev[j][i + 1] + iv);
        }
    }
    DBG(dp);
    cout << dp[n] << "\n";
}
