#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int MX = 1e5;

int32_t main() {
    int n, m; cin >> n >> m;
    bitset<2 * MX + 1> al;
    al[MX] = 1;
    // cout << al << endl;
    while (n--) {
        int a, b; cin >> a >> b;
        decltype(al) nx;
        for (int s : {a, b}) nx |= (s > 0 ? al << s : al >> -s);
        al = nx;
    }
    // cout << al << endl;
    int sm = 0, neg = 0, pos = 0;
    while (m--) {
        int a, b; cin >> a >> b;
        sm += a;
        if (a > b) neg += b - a;
        else pos += b - a;
    }
    int ans = 1e9;
    for (int i = -MX; i <= MX; i++) if (al[i + MX]) {
        // cout << i << endl;
        ans = min(ans, max(abs(i + sm + neg), abs(i + sm + pos)));
    }
    cout << ans << endl;
}
