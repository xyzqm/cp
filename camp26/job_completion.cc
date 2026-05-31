#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;

void mul(int &a, int b) { a = a * b % M; }
void ad(int &a, int b) { a = (a + b) % M; }
int inv(int x) {
    int r = 1;
    for (int y = M - 2; y; y >>= 1, mul(x, x)) if (y & 1) mul(r, x);
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    vector<int> s(n);
    for (int &x : s) cin >> x;
    ranges::sort(s, greater<int>());
    vector<array<int, 3>> evts;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) evts.push_back({s[i] + j * d, i, j - i});
    }
    ranges::sort(evts);
    int ans = 0;
    vector<int> m(n);
    for (int prv = 0; auto &[t, i, nw] : evts) {
        m[i] = nw;
        int prod = 1;
        for (int x : m) mul(prod, x);
        prod = (M + 1 - prod) % M;
        if (t != prv) {
            ad(ans, (t - prv) * prod);
            prv = t;
        }
    }
    cout << ans << "\n";
}
