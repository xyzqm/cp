int sz(int x, int p) {
    s[x] = 0;
    for (auto [y, _] : g[x]) if (y != p && !r[y]) s[x] += sz(y, x);
    return ++s[x];
}
int cdc(int x, int p, int n) {
    for (auto [y, _] : g[x]) if (y != p && !r[y]) {
        if (s[y] > n / 2) return cdc(y, x, n);
    }
    r[x] = 1;
    for (auto [y, _] : g[x]) if (!r[y]) {
        cp[cdc(y, x, sz(y, 0))] = x;
    }
    return x;
}
