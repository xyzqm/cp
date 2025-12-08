#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int q(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int x; cin >> x;
    return x;
}

void ac() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) if (!a[i]) {
        if (i + 2 <= n) {
            int x = q(i, i + 1);
            int y = q(i + 1, i + 2);
            a[i] = x / gcd(x, y);
            a[i + 1] = gcd(x, y);
            a[i + 2] = y / gcd(x, y);
        }
        else a[i] = q(1, i) / a[1];
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
