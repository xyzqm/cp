#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 1;
const int K = 60;
int n, T[N];
// J[i][k][t] = {t', j} -> start at city i at time t, jump t' steps to reach j
// j is the first node reached s.t. t[j] > t[i] OR node after 2^k steps (whichever comes first)
struct ST { int t = 1, j; };
vector<ST> J[N][K];

int lg(int x) { return 63 - __builtin_clzll(x); }

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> T[i];
        for (int k = 0; k < K; k++) J[i][k].resize(T[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (auto &[t, x] : J[i][0]) cin >> x;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i <= n; i++) {
            for (int t = 0; t < T[i]; t++) {
                int del = 1LL << k;
                auto [t1, j1] = J[i][k - 1][t];
                del -= t1;
                while (T[j1] <= T[i] && del) {
                    auto [t2, j2] = J[j1][lg(del)][(t + t1) % T[j1]];
                    del -= t2, t1 += t2, j1 = j2;
                }
                J[i][k][t] = {t1, j1};
                assert(t1 == 1LL << k || T[j1] > T[i]);
            }
        }
    }
    while (q--) {
        int v, t, del; cin >> v >> t >> del;
        while (del) {
            auto [d, j] = J[v][lg(del)][t % T[v]]; // delta, next node
            del -= d, t += d;
            v = j;
        }
        cout << v << endl;
    }
}
