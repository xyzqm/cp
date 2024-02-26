#include <iostream>
#include <set>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int N = 2e5 + 1;
const ll inf = 1e18;
ll p[N];
int n;
int main() {
    cin >> n;
    set<pll> s;
    s.insert({0, 0});
    ll ans = 0, prv = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] += p[i - 1];
        auto it = s.upper_bound({p[i], inf});
        ll cur = prv;
        if (it != s.begin()) cur = max(prv, i + prev(it)->second);
        ans = max(ans, prv = cur);
        while ((it = s.lower_bound({p[i], cur - i})) != s.end()) {
            if (cur - i < it->second) break;
            s.erase(it);
        }
        if (it == s.begin() || prev(it)->second < cur - i) s.insert({p[i], cur - i});
    }
    cout << ans << endl;
}