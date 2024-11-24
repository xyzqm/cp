#include <bits/stdc++.h>
#include "poly2.h"

int main() {
    int n; cin >> n;
    F f; f.resize(n);
    cout << f.size() << endl;
    for (int i = 0; i < n; i++) cin >> f[i];
    F g = f.inv();
    for (int i = 0; i < n; i++) cout << g[i] << " ";
    cout << endl;
}
