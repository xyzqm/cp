// The aim of this version is just short while fast enough
#include <bits/stdc++.h>
#include "mint.h"
#include "combo.h"
using namespace std;
typedef vector<int> poly;
const int N = 1e7 + 1, p = 998244353;
const int M = 998244353;
int inv[N];
inline int Qmi(int x, int y = p - 2) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % p) if (y & 1) ans = 1ll * ans * x % p;
    return ans;
}
namespace Core {
    int a[N], b[N], w[N], rev[N];
    inline void NTT(int *a, int len) {
        for (int i = 1; i < len; ++i) if (i > rev[i]) swap(a[i], a[rev[i]]);
        for (int d = 1; d < len; d <<= 1)
            for (int m = d << 1, i = 0; i < len; i += m)
                for (int j = 0; j < d; ++j) {
                    int x = a[i + j], y = 1ll * a[i + j + d] * w[len / m * j] % p;
                    a[i + j] = (x + y >= p ? x + y - p : x + y);
                    a[i + j + d] = (x - y < 0 ? x - y + p : x - y);
                }
    }
}
inline poly operator*(const poly &va, const poly &vb) {
    using namespace Core;
    int len = 1; while (len < (int)va.size() + (int)vb.size() - 1) len <<= 1;
    for (int i = 0; i < len; ++i) a[i] = (i < (int)va.size() ? va[i] : 0);
    for (int i = 0; i < len; ++i) b[i] = (i < (int)vb.size() ? vb[i] : 0);
    for (int i = 1; i < len; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? len >> 1 : 0);
    w[0] = 1; w[1] = Qmi(3, (p - 1) / len);
    for (int i = 2; i < len; ++i) w[i] = 1ll * w[i - 1] * w[1] % p;
    NTT(a, len); NTT(b, len);
    for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * b[i] % p;
    reverse(a + 1, a + len); NTT(a, len);
    poly c(va.size() + vb.size() - 1);
    for (int i = 0, invlen = Qmi(len); i < (int)c.size(); ++i) c[i] = 1ll * a[i] * invlen % p;
    return c;
}
inline poly Fix(poly a, int n) {
    a.resize(n);
    return a;
}
inline poly Inv(poly f, int n) {
    poly g(1, Qmi(f[0]));
    while ((int)g.size() < n) {
        int nlen = min<int>(g.size() << 1, n);
        poly tmp(Fix(Fix(f, nlen) * g, nlen));
        for (int i = 0; i < nlen; ++i) tmp[i] = (p - tmp[i] + (i == 0 ? 2 : 0)) % p;
        g = Fix(g * tmp, nlen);
    }
    return g;
}
inline poly Deri(poly f) {
    for (int i = 1; i < (int)f.size(); ++i) f[i] = 1ll * f[i] * i % p;
    f.erase(f.begin());
    return f;
}
inline poly Inte(poly f) {
    f.insert(f.begin(), 0);
    for (int i = 1; i < (int)f.size(); ++i) f[i] = 1ll * f[i] * inv[i] % p;
    return f;
}
inline poly Ln(poly f, int n) {
    return Inte(Fix(Deri(f) * Inv(f, n - 1), n - 1));
}
inline poly Exp(poly f, int n) {
    f.resize(n);
    poly g(1, 1);
    while ((int)g.size() < n) {
        int nlen = min<int>(g.size() << 1, n);
        poly tmp = Ln(g, nlen);
        for (int i = 0; i < nlen; ++i) tmp[i] = (f[i] - tmp[i] + !i + p) % p;
        g = Fix(g * tmp, nlen);
    }
    return g;
}

Combo<N, M> C;
mint ctln(int n) { return C.C(2 * n, n) / (n + 1); }
int c[N];
int n;
int main() {
    int n; mint k; cin >> n >> k;
    poly f(n + 2), g(n + 2), h(n + 2);
    g[1] = k.v;
    // gcd has to be either 2 * n or <= n
    for (int i = 1; 2 * i <= n; i++) {
        f[2 * i] = (ctln(i - 1) * k * (k - 1).exp(i - 1)).v;
        h[2 * i] = (mint{f[2 * i]} * -1).v;
        g[i * 2 + 1] = (C.C(2 * i, i) * k * (k - 1).exp(i)).v;
    }
    h[0] += 1;
    poly gf = f * Inv(h, n);
    gf.resize(n + 1);
    gf[0] += 1;
    g[0] += 1;
    gf = gf * g;
    // poly gf = (f / (f * -1 + 1) + 1).slice(n) * (g + 1); // [i] -> # of colorings for RBS + extra stuff of len i
    for (int i = 1; i <= 2 * n; i++) ++c[gcd(i, 2 * n)];
    mint tmp = 0;
    for (int i = 1; i <= n; i++) tmp += mint{i} / (2 * n - i) * C.C(2 * n - i, n) * (k - 1).exp(n - i) * k.exp(i);
    gf[2 * n] = tmp.v;
    mint r = 0;
    for (int i = 1; i <= 2 * n; i++) {
        r += mint{gf[i]} * c[i];
    }
    // cout << r << endl;
    cout << r / (2 * n) << endl;
    // inv[0] = inv[1] = 1; for (int i = 2; i < N; ++i) inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    // poly a(n);
    // for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    // a = Exp(a, n);
    // for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    return 0;
}
