#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, m, dp[1 << N], s[1 << N], adj1[2 * N], adj2[2 * N];
void add_edge(int a, int b) {
    if (b < n / 2) adj1[a] |= (1 << b);
    else adj2[a] |= (1 << (b - n / 2));
}
int main () {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        add_edge(a, b); add_edge(b, a);
    }
    for (int x = 1; x < (1 << (n / 2)); x++) {
        dp[x] = dp[x - (x & -x)];
        s[x] = s[x - (x & -x)];
        int y = (x & ~adj1[__builtin_ctz(x)]) - (x & -x);
        if (dp[y] + 1 > dp[x]) {
            dp[x] = dp[y] + 1;
            s[x] = s[y] + (x & -x);
        }
    }
    int ans = 0, mask1, mask2;
    for (int x = 0; x < (1 << (n - n / 2)); x++) { // enumerate which ones we pick in second half
        int y = (1 << n / 2) - 1; // bitmask of nodes we're allowed to take in first half
        bool valid = true; // whether x is a non-colliding mask
        for (int i = n / 2; i < n; i++) {
            if (x & (1 << (i - n / 2))) {
                if (x & (adj2[i])) {
                    valid = false;
                    break;
                } else y &= ~adj1[i];
            }
        }
        if (!valid) continue;
        if (__builtin_popcount(x) + dp[y] > ans) {
            ans = __builtin_popcount(x) + dp[y];
            mask1 = y; 
            mask2 = x;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < n / 2; i++) {
        if (s[mask1] & (1 << i)) cout << i << " ";
    }
    for (int i = n / 2; i < n; i++) {
        if (mask2 & (1 << (i - n / 2))) cout << i << " ";
    }
    cout << endl;
}