#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int N = 2e5;
int n;
pll a[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    sort(a, a + n);
    ll t = 0, ans = 0;
    for (int i = 0; i < n; i++) ans += a[i].second - (t += a[i].first);
    cout << ans << endl;
}