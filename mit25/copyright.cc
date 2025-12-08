#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int t;

void ac() {
    int x, y, z; cin >> x >> y >> z;
    string s = "";
    string m = "M", t = "T";
    if (x < z) swap(x, z), swap(m, t);
    // auto add = [&](string nx) {
    //     if (s.size()) {
    //         if (!y) return false;
    //         s += 'I', --y;
    //     }
    //     s += nx;
    //     return true;
    // };
    // while (x > z) {
    //     add(m), --x;
    // }
    // assert(x == z);
    // if (x) add(m + t), --x, --z;

    int g = x - z; // # of groups
    if (y < g - 1) {
        cout << "NO" << endl;
        return;
    }
    string l = m;
    --x;
    for (int i = 1; i < g; i++) {
        l += "I" + m;
        --y, --x;
    }
    while (y)
    if (y < g + 1) {
        for (int i = 1; i < g; i++) s += m + "I", y--;
        s += m;
        if (y) s = 'I' + s, --y;
        if (y) s += 'I', --y;
    }
    // while (x > z) {
    //     if (y) s += m + 'I', --x, --y;
    //     else if (x > z + 1) {
    //         // assert(::t <= 2 || false);
    //         cout << "NO" << endl;
    //         return;
    //     }
    //     else s += m, --x, swap(m, t);
    // }
    // assert(x == z);
    // int is = (y - 1) / 2;
    // y -= 2 * is;
    // // y %= 2;
    // if (is > x - 1) {
    //     cout << "NO" << endl;
    //     return;
    // }
    // for (string q : {m, t}) {
    //     for (int i = 0; i < is; i++) {
    //         s += q + "I";
    //     }
    //     s += q;
    // }
    // x -= is + 1, z -= is + 1;
    // if (y) s.insert(s.begin(), 'I'), --y;
    // if (y) s += 'I', --y, swap(m, t);
    // assert(!y);
    // while (x) {
    //     s += m + t, --x, --z;
    // }
    // assert(max({x, y, z}) == 0);
    // cout << "YES" << "\n";
    // cout << s << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) ac();
}
