#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int r, c, x; cin >> r >> c >> x;
    bool swp = r < c;
    if (swp) swap(r, c);
    vector<tuple<char, int, int>> pts(x);
    for (auto &[c, x, y] : pts) {
        cin >> c >> x >> y;
        if (swp) swap(x, y);
        --x, --y;
    }
    int dgs = r + c - 1;
    auto win = [&](bool ad) -> int { // refactor so we can reverse pts later
        vector<int> cons(dgs, -1);
        for (auto &[c, x, y] : pts) {
            int typ = c == '+';
            if (cons[x + y] >= 0 && cons[x + y] != typ) return 0;
            else cons[x + y] = typ;
        }
        auto eq = [](int a, int b) { return a < 0 || a == b; };
        DBG(cons);
        vector<array<int, 2>> pref(dgs), suf(dgs, {dgs - 1, dgs - 1});
        for (int i = 0; i < dgs; i++) for (int t: {0, 1}) {
            if (i > 0) pref[i][t] = pref[i - 1][t ^ 1];
            if (!eq(cons[i], t)) pref[i][t] = i + 1;
            // pref[i][t] = pref[i][t] && eq(cons[i], t);
        }
        for (int i = dgs; i --> 0; ) for (int t: {0, 1}) {
            if (i + 1 < dgs) suf[i][t] = suf[i + 1][t ^ 1];
            if (!eq(cons[i], t)) suf[i][t] = i - 1;
        }
        DBG(pref);
        DBG(suf);
        // case 1: only one pair of adjacent +
        int ans = 0;
        if (dgs > 2) for (int i = 0; i + 1 < dgs; i++) {
            if (pref[i][1] == 0 && suf[i + 1][1] == dgs - 1) ans++;
        }
        // case 2: two pairs of adjacent +
        vector<int> valid(r);
        for (int i = 1; i < r; i++) {
            if (i > 1) valid[i] = valid[i - 2];
            valid[i] += pref[i - 1][1] == 0;
        }
        if (dgs > 3) for (int i = r - 1; i + 1 < dgs; i++) if (suf[i + 1][1] == dgs - 1) {
            int mx = i - (r - 2);
            if ((i - mx) % 2) --mx;
            int mn = pref[i][1];
            // println("{} {} {}", i, mx, mn);
            if (mn > mx || mx < 1) continue;
            if ((mx - mn) % 2) ++mn;
            ans += valid[mx];
            if (mn >= 2) ans -= valid[mn - 2];
        }
        // if (dgs > 3) for (int i = 1; i < r; i++) for (int j = i; j + 1 < dgs; j++)
        // if (j - i >= r - 2 && (j - i) % 2 == 0) {
        //     if (pref[j][1] <= i && pref[i - 1][1] == 0 && suf[j + 1][1] == dgs - 1) ans++;
        // }
        DBG(ans);
        // case 3: all same or alternating
        if (ad) {
            for (int &x : cons) if (x == -1) x = 1;
            if (r == 2 && c == 2 && accumulate(cons.begin(), cons.end(), 0) == dgs) ans++; // can be all same
            for (int t : {0, 1}) if (pref.back()[t] == 0) ans++;
        }
        return ans;
    };
    int res = win(true);
    for (auto &[_, x, y] : pts) {
        y = c - y - 1;
    }
    DBG(pts);
    if (c > 1) res += win(false);
    cout << res << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
