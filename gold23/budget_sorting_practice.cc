#include <iostream>
#include <set>
using namespace std;
using pii = pair<int, int>;
const int N = 2e3;
const int M = 1e6;
int n, m, q, a[N];
pii p[M];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) cin >> p[i].first >> p[i].second;
    while (q--) {
        set<int> inv;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i && a[i] < a[i - 1]) inv.insert(i);
        }
        for (int i = 0; i < m; i++) {
            auto [l, r] = p[i];
            --l, --r;
            auto it = inv.upper_bound(l);
            while (it != inv.end() && *it <= r) {
                swap(a[*it], a[*it - 1]);
                if (*it - 2 >= 0 && a[*it - 2] > a[*it - 1]) inv.insert(*it - 1);
                if (*it + 1 < n && a[*it] > a[*it + 1]) inv.insert(*it + 1);
                inv.erase(it);
                it = inv.upper_bound(l);
            }
        }
        if (inv.size() == 0) cout << "AC\n";
        else cout << "WA\n";
    }
}