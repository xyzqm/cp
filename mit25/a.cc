#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    string s; cin >> s;
    int mc = 0, tc = 0, ans = 0;
    char prv = 'I';
    for (char c : s) {
        // cout << mc << " " << tc << endl;
        if ((prv == 'I') == (c == 'I')) ans += min(mc, tc / 2),  mc = tc = 0;
        if (c == 'M') ++mc;
        if (c == 'T') ++tc;
        prv = c;
    }
    cout << ans + min(mc, tc / 2) << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
