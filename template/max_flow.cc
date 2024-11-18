#include <bits/stdc++.h>
#include "flow.cc"

const int N = 502;
Flow<N> f;

int main() {
    int n, m; cin >> n >> m;
    vector<FE> g(m);
    for (auto &[u, v, c] : g) cin >> u >> v >> c;
    cout << f.init(n, 1, n, g).flow() << endl;
}
