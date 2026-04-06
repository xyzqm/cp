#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<int> pref(2 * n, 0); // parity of dividers before index i
    vector<int> lst(n + 1, -1), c;
    for (int i = 0, a; i < 2 * n; i++) {
        cin >> a;
        if (i) pref[i] = pref[i - 1];
        if (lst[a] < 0) lst[a] = i;
        else if ((pref[i] ^ pref[lst[a]]) == 0) {
            c.push_back(i);
            pref[i] ^= 1;
        }
    }
    cout << c.size() << "\n";
    for (int x : c) cout << x << " ";
    cout << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
