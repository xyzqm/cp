#include <bits/stdc++.h>
#define int long long
#define SQUARE(x) ((x) * (x))
using namespace std;
struct grazing {
    int x, y, t;
    grazing(int x, int y, int t) : x(x), y(y), t(t) {}
};
signed main() {
    int g, n; cin >> g >> n;
    auto cmp = [](grazing a, grazing b) {return a.t < b.t;};
    set<grazing, decltype(cmp)> grazings(cmp);
    for (int i = 0; i < g; i++) {
        int x, y, t; cin >> x >> y >> t;
        grazings.insert(grazing(x, y, t));
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x, y, t; cin >> x >> y >> t;
        auto nxt = grazings.lower_bound(grazing(INT_MIN, INT_MIN, t));
        bool innocent = false;
        if (nxt != grazings.end()) {
            int gx = nxt->x, gy = nxt->y, gt = nxt->t;
            // printf("next: %d %d %d\n", gx, gy, gt);
            innocent = innocent || (SQUARE(gx - x) + SQUARE(gy - y) > SQUARE(gt - t));
        }
        if (nxt != grazings.begin()) {
            nxt = prev(nxt);
            int gx = nxt->x, gy = nxt->y, gt = nxt->t;
            // printf("prev: %d %d %d\n", gx, gy, gt);
            innocent = innocent || (SQUARE(gx - x) + SQUARE(gy - y) > SQUARE(gt - t));
        }
        // cout << boolalpha << innocent << endl;
        ans += innocent;
    }
    cout << ans << endl;
}