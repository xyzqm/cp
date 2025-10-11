#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;
struct mint { int v; };
mint operator+(mint a, mint b) { return {(a.v + b.v) % M}; }
void operator+=(mint &a, mint b) { a.v = (a.v + b.v) % M; }

struct BIT : vector<mint> {
    BIT(int n) : vector(n) {}
    void upd(int i, mint x) {
        for (++i; i < size(); i += i & -i) at(i) += x;
    }
    mint query(int r) {
        mint q{0};
        for (; r > 0; r -= r & -r) q += at(r);
        return q;
    }
};

const int MX = 2e6 + 1;

int32_t main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto v : {ref(a), ref(b)}) for (int &x : v.get()) cin >> x;
    mint res{0};
    BIT bit(MX);
    for (int i = n; i --> 0; ) {
        mint w = bit.query(a[i] * b[i] + 1) + mint{1};
        res += w;
        bit.upd(a[i] * b[i], w);
    }
    cout << res.v << endl;
}
