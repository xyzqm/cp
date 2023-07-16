#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e5;
int n, cnt[N];
ll ans = 0;
int main() {
    cin >> n;
    ll p = 0;
    ++cnt[0];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        p = (p + x) % n;
        if (p < 0) p += n;
        ans += cnt[p]++;
    }
    cout << ans << endl;
}