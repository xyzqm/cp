#define CENTROID
#define LCA
#define WEIGHTED
#include "graph.h"
#include "sparse2.h"

const int N = 1e5 + 1;
Tree<N, W> t;

ll r[N];
vector<pair<int, ll>> a[N];
ST2<ll> st[N];

int main() {
    int n; cin >> n;
    t.init(n).input().root(1).dfs().decompose();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j; j = t.cp[j]) {
           a[j].push_back({i, t.D(i, j)});
        }
    }
    for (int i = 1; i <= n; i++) st[i].build(a[i], [](ll x, ll y) { return min(x, y); });
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        ll y = 1e18;
        for (int z = x; z; z = t.cp[z]) {
            y = min(y, t.D(x, z) + st[z].F(l, r));
        }
        cout << y << endl;
    }
}
