#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n, x; cin >> n >> x;
    string s; cin >> s;
    --x;
    int l_max = -1;
    for (int i = 0; i < x; i++) if (s[i] == '#') l_max = i;
    int r_min = n;
    for (int i = n - 1; i > x; i--) if (s[i] == '#') r_min = i;
    return max(
        min(x + 1, n - r_min + 1), // place on left
        min(n - x, l_max + 2)
    );
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
