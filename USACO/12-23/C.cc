#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
const int N = 2e5 + 2;
int n, q, a, b, x[N], l[N], r[N];
int cost(int X) {
    int L = upper_bound(x, x + n + 1, X) - x - 1;
    return a * (L * X - l[L]) + b * (r[L + 1] - (n - L) * X);
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++) l[i] = l[i - 1] + x[i];
    for (int i = n; i > 0; i--) r[i] = r[i + 1] + x[i];
    cin >> q;
    while (q--) {
        cin >> a >> b;
        int l = 0, r = x[n];
        while (r - l >= 3) {
            int x = l + (r - l) / 3;
            int y = r - (r - l) / 3;
            if (cost(x) < cost(y)) r = y;
            else l = x;
        }
        cout << min(cost(l), min(cost(l + 1), cost(l + 2)));
        cout << endl;
    }
    return 0;
}