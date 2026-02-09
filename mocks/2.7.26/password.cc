#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 998244353;

int xp(int v, int pw) {
    int r = 1;
    for (; pw; v = v * v % M, pw >>= 1) if (pw & 1) r = r * v % M;
    return r;
}

int sub(int x) { return x < 0 ? x + M : x; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, q; cin >> n >> k >> q;
    vector<int> phi(k + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= k; i++) if (phi[i] == i) {
        for (int j = i; j <= k; j += i) phi[j] -= phi[j] / i;
    }
    DBG(phi);
    const int i25 = xp(25, M - 2);
    auto ws = [&](int k) { // ways to have a string of length <= k
       return sub(xp(26, k + 1) - 26) * i25 % M;
    };
    int res = 0;
    for (int i = 1; i <= k; i++) {
        res += (1 + (i > 1)) * phi[i] * ws(k / i);
        res %= M;
    }
    DBG(res);
    vector<int> pref(n + 1), hsh(n + 1);
    for (int i = 1, p2 = 1; i <= n; i++, p2 = (p2 << 1) % M) {
        char c; cin >> c;
        pref[i] = pref[i - 1] + (c == '1');
        hsh[i] = (hsh[i - 1] + (c == '1') * p2) % M;
    }
    auto hash = [&](int l, int r) {
        return sub(hsh[r] - hsh[l]) * xp(2, M - 1 - l) % M;
    };
    DBG(pref);
    while (q--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        int o = pref[b] - pref[--a] - (pref[d] - pref[--c]);
        int z = (d - c) - (b - a) + o;
        DBG(o);
        DBG(z);
        if (o < 0) o = -o, z = -z;
        if (!o && !z) { // check for string equality
            DBG(hash(a, b));
            DBG(hash(c, d));
            if (hash(a, b) == hash(c, d)) {
                cout << (ws(k) * ws(k) % M) << "\n";
            }
            else cout << res << "\n";
            continue;
        }
        if (!o || z <= 0) cout << "0\n";
        else {
            int rt = max(o, z) / gcd(o, z);
            int mx = k / rt;
            cout << ws(mx) << "\n";
        }
    }
}
