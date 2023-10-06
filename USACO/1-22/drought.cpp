#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 101;
const int H = 1001;
const int M = 1e9 + 7;
int n, a[N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    int m = inf;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) m = min(m, a[i]);
    if (n % 2 == 0) m = 0;
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        int p[H]{};
        for (int j = i; j < H; j++) p[j] = 1;
        for (int j = 0; j < n; j++) {
            int v[H]{};
            for (int k = i; k <= a[j]; k++) {
                v[k] = ((p[i + a[j] - k] - (i ? p[i - 1] : 0)) % M + M) % M;
            }
            for (int k = 0; k < H; k++) p[k] = (v[k] + (k ? p[k - 1] : 0)) % M;
        }
        ans = ((ans + p[i] - (i ? p[i - 1] : 0)) % M + M) % M;
    }
    cout << ans << endl;
    return 0;
}