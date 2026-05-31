#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define all(v) v.begin(), v.end()

const int M = 1e9 + 7;
int sb(int a, int b) {
    if ((a -= b) < 0) a += M;
    return a;
}
void mul(int &a, int b) { a = a * b % M; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> prod(n + 1);
    prod[0] = 1;
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        prod[i] = prod[i - 1];
        mul(prod[i], 2);
    }
    for (int i = 0; i < n; i++) mul(ans, prod[n] - prod[i]);
    cout << ans << "\n";
}
