#include <bits/stdc++.h>
#include "poly2.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    F f(n);
    for (int i = 0; i < n; i++) cin >> f[i];
    F g = f.inv();
    for (int i = 0; i < n; i++) cout << g[i] << " ";
    cout << endl;
}
