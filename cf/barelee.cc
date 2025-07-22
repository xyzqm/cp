#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    int n; cin >> n;
    vector<array<int, 2>> v(n);
    for (auto &[s, e] : v) cin >> s >> e;
    reverse(v.begin(), v.end());
    bool w = 0, l = 1; // whether the first player will win/lose
    for (auto [s, e] : v) {
        int st1 = 0b11, st2 = 0b10; // [0: parity/1: P1 wins?][parity/bool] for s in (e, 2e]
        for (; e >= s; e >>= 1) {
            for (int &st : {ref(st1), ref(st2)}) {
                if (st & 0b10) { // fixed player always wins
                    if (st & 1) st = 0b01 ^ (e & 1); // same parity as e loses
                    else st ^= 1; // P2' wins -> P1 wins
                }
                else { // fixed parity always wins
                    if (st & 1) st = 0b11; // odd wins -> P1 wins (by doubling)
                    else ; // even win -> still even win
                }
            }
        }
        bool w_ = 0, l_ = 0;
        if (st1 == 0b11 || st1 < 2 && !((s ^ st1) & 1)) w_ |= !w, l_ |= !l; // we can win this round -> go second next round
        if (st2 == 0b11 || st2 < 2 && !((s ^ st2) & 1)) w_ |= w, l_ |= l; // we can lose this round -> go first next round
        w = w_, l = l_;
    }
    cout << w << " " << l << endl;
}
