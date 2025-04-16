#include <bits/stdc++.h>
using namespace std;

const int W = 13;
const int K = 30;
bitset<1 << W> g[1 << W][K];

int w, h, k;

bitset<1 << W> dp[W + 1];

void dbg(bitset<1 << W> st) {
    // for (int i = 0; i < (1 << W); i++) if (st[i]) cout << bitset<W>(i) << " ";
    // cout << endl;
}

bitset<1 << W> tr(bitset<1 << W> st) {
    fill(dp, dp + w + 1, 0);
    dp[0] = st;
    dbg(st);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < (1 << w); j++) if (dp[i][j]) {
            if (j >> i & 1) dp[i + 1][j ^ (1 << i)] = 1;
            else {
                if (i && !(j >> (i - 1) & 1)) dp[i + 1][j ^ (3 << (i - 1))] = 1;
                if (i + 3 <= w && !(j >> i & 7)) dp[i + 3][j ^ (7 << i)] = 1;
                if (i + 1 < w) {
                    dp[i + 2][j ^ (1 << i)] = 1;
                    if (!(j >> (i + 1) & 1)) dp[i + 2][j ^ (2 << i)] = 1;
                }
            }
        }
        // cout << i << ": ";
        dbg(dp[i]);
    }
    return dp[w];
}

int main() {
    cin >> w >> h >> k;
    for (int i = 0; i < (1 << w); i++) {
        g[i][0] = tr(bitset<1 << W>(1) << i);
        // cout << bitset<W>(i) << ": ";
        dbg(g[i][0]);
    }
    for (int k = 0; k + 1 < K; k++) {
        for (int i = 0; i < (1 << w); i++) {
            for (int j = 0; j < (1 << w); j++) if (g[i][k][j]) {
                g[i][k + 1] |= g[j][k];
            }
        }
    }
    map<int, int> gaps;
    while (k--) {
        int c, r; cin >> c >> r;
        gaps[r] |= (1 << (c - 1));
    }
    gaps[h] |= 0; // make sure h is inserted into the map
    int cr = 1;
    bitset<1 << W> st = 1;
    for (auto [r, gp] : gaps) {
        for (int k = K; k --> 0; ) if ((r - cr) >> k & 1) {
            bitset<1 << W> nx = 0;
            for (int i = 0; i < (1 << W); i++) if (st[i]) nx |= g[i][k];
            dbg(nx);
            swap(st, nx);
        }
        dbg(st);
        for (int i = 0; i < (1 << W); i++) if (i & gp) st[i] = 0;
        st <<= gp; // add gaps to all states
        dbg(st);
        st = tr(st);
        cr = r + 1;
        dbg(st);
    }
    cout << (st[0] ? "YES" : "NO") << endl;
}
