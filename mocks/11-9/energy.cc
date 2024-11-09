#include <bits/stdc++.h>
#include <cstring>
using namespace std;
#define int long long

const int K = 61;
// bit, </= n, </= m, >/= k
int w[K + 1][2][2][2], s[K + 1][2][2][2];

vector<int> pos(int n, int i, int a, bool geq = false) {
    if (a == 0) return {0, 1}; // < to <
    if (a == 1) return {}; // < to =; not possible
    if (a == 2) return ((n >> i & 1) != geq ? vector<int>{geq} : vector<int>{}); // = to <
    if (a == 3) return {n >> i & 1}; // = to =
    assert(false);
}

int p, e[K];
int ad(int &a, int b) { return a = (a + b) % p; }

void ac() {
    int n, m, k; cin >> n >> m >> k >> p;
    e[0] = 1;
    for (int i = 1; i < K; i++) e[i] = (e[i - 1] * 2) % p;
    memset(w, 0, sizeof w);
    memset(s, 0, sizeof s);
    w[K][1][1][1] = 1;
    for (int i = K; i --> 0; ) { // transition from i + 1 to i
        for (int a = 0; a < 4; a++) { // cur n and target
            auto pn = pos(n, i, a);
            if (pn.size()) for (int b = 0; b < 4; b++) { // cur m and target
                auto pm = pos(m, i, b);
                if (pm.size()) for (int c = 0; c < 4; c++) {
                    auto pk = pos(k, i, c, 1);
                    int cw = w[i + 1][a >> 1][b >> 1][c >> 1];
                    int cs = s[i + 1][a >> 1][b >> 1][c >> 1];
                    for (int x : pn) for (int y : pm) for (int z : pk) if ((x ^ y) == z && cw) {
                        ad(w[i][a & 1][b & 1][c & 1], cw);
                        ad(s[i][a & 1][b & 1][c & 1], (cs + cw * (x ^ y) * e[i]) % p);
                    }
                }
            }
        }
    }
    int r = ((s[0][0][0][0] - w[0][0][0][0] * (k % p)) % p + p) % p;
    assert(r >= 0);
    cout << r << endl;
}

signed main() {
    int t; cin >> t;
    while (t--) ac();
}
