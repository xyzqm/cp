#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int p, q; cin >> p >> q;
    bool alice = false;
    if (p >= q) alice = true;
    else {
        int d = q - p;
        if (2 * d <= p && 3 * d <= q) alice = false;
        else alice = true;
    }
    cout << array{"Bob", "Alice"}[alice] << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
