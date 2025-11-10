// UNFINISHED
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;
const int N = 2001;

int n, binom[N + 1][N + 1];

void ad(int &x, const int y) { x = (x + y) % M; }

int ac() {
    int k; cin >> k;
    vector<int> pos(n, -1);
    auto ck = [&](int i, int x) { return i < 0 || pos[x] < 0 || pos[x] == i; };
    while (k--) {
        int i, j; cin >> i >> j;
        pos[j] = i;
    }
    auto rv = [&]() { for (int &x : pos) if (x >= 0) x = n - 1 - x; };
    int r = 0;

    auto ev = [&](int r, int l) { // ranges [0, r) and [l, n)
        int rr = r, ll = n, w = 1;
        for (int sm = 2, lg = 2 + n / 2, i = 2; lg < n - 1; ++sm, ++lg, i += 2) { // enumerate positions
            if (pos[sm] < 0 && pos[lg] < 0) continue;
            int idx = max(pos[lg], pos[sm] + 1);
            if (idx < 1 || !ck(idx, lg) || !ck(idx - 1, sm)) return 0LL; // S and L at idx - 1 and idx respectively
            int nr, nl;
            if (idx < r) {
                nr = idx - 1;
                nl = n - (idx - (r - nr));
            }
            else {
                nl = idx - 1;
                nr = r - (idx - (n - nl));
            }
            if (nr < 0 || nr > r || nl < l || nl > n) return 0LL;
            w *= binom[(rr - nr) / 2][(ll - nl) / 2];
            w %= M;
            rr = nr, ll = nl;
        }
        println("{} {}", rr, ll);
        return w * binom[rr / 2][(ll - l) / 2] % M;
    };

    println("{}", ev(0, 1));
    println("{}", ev(2, 5));

    for (int _ : {0, 1}) {

        if (n % 2 == 0) { // n even case---only two possibilities
                for (int i = 0; i < n; i += 2) if (!(ck(i, i / 2 + n / 2) && ck(i + 1, i / 2))) goto end;
                ++r;
        }


        end: rv();
    }

    return r % M;
}

int32_t main() {
    // precompute binomial coefficients
    binom[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ad(binom[i + 1][j], binom[i][j]);
            ad(binom[i][j + 1], binom[i][j]);
        }
    }

    int t; cin >> t >> n;
    while (t--) cout << ac() << endl;
}
