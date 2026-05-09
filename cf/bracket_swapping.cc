#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

string ac() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    int bal = 0, st = 0;
    array<int, 2> vals = {-1, 1};
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            bal += vals[a[i] == '('];
            if (bal < st) return "NO";
        }
        else {
            if (bal < (st ^= 1)) return "NO";
        }
    }
    return !bal && !st ? "YES" : "NO";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) cout << ac() << "\n";
}
