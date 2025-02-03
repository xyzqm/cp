#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 1e5 + 1;
ld c[N], p[N];
int n, f[N], fa[N], nx[N], t[N];
int rt(int x) { return x = x == fa[x] ? x : rt(fa[x]); }

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        t[i] = f[i] = i;
        cin >> c[i] >> p[i] >> f[i];
    }
    auto fn = [&](int i, int j) { return c[i] + p[i] * c[j] < c[j] + p[j] * c[i]; }; // [i before j]
    set<int, decltype(fn)> pq(fn);
    while (pq.size()) {
        int x = *pq.begin(); pq.erase(x);
        if (x != fa[x]) continue;
        if (f[x]) {
            f[x] = rt(f[x]);
            if (fn(f[x], x)) { // merge x with f[x]
                pq.erase(f[x]);
                c[f[x]] += p[f[x]] * c[x];
                p[f[x]] *= p[x];
                t[f[x]] = t[nx[t[f[x]]] = x];
                pq.insert(fa[x] = f[x]);
            }
        }
    }
    reverse(o.begin(), o.end());
    for (int x : o) for (int y = x; y; y = nx[y]) cout << y << endl;
}
