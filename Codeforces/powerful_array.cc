#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 2e5;
const int B = 500;
const int M = 1e6;
int n, t, a[N], freq[M + 1];
ll ans[N];
struct Q {
    int l, r, i;
} q[N];
int main() {
    cin >> n >> t;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < t; i++) {
        int l, r;
        cin >> l >> r;
        q[i] = {l - 1, r - 1, i};
    }
    sort(q, q + t, [](const Q& a, const Q& b) {
        if (a.l / B != b.l / B) return a.l / B < b.l / B;
        else return a.r < b.r;
    });
    int x = 0, y = 0;
    ll cur = 0;
    freq[a[0]]++;
    cur += a[0];
    auto add = [&](int i) {
        cur += (2LL * ++freq[a[i]] - 1) * a[i];
    };
    auto rem = [&](int i) {
        cur -= (2LL * --freq[a[i]] + 1) * a[i];
    };
    for (int i = 0; i < t; i++) {
        auto [l, r, qi] = q[i];
        while (x < l) rem(x++);
        while (x > l) add(--x);
        while (y < r) add(++y);
        while (y > r) rem(y--);
        ans[qi] = cur;
    }
    for (int i = 0; i < t; i++) cout << ans[i] << endl;
}
