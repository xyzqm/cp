// https://usaco.org/index.php?page=viewproblem2&cpid=1452
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
int n, K;

/**
 * Description: Modular arithmetic.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mi a = MOD+5; cout << (int)inv(a); // 400000003
 */
int MOD = 1e9 + 7;
struct mi {
 	int v; explicit operator int() const { return v; }
	mi():v(0) {}
	mi(int _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) {
	if ((a.v += b.v) >= MOD) a.v -= MOD;
	return a; }
mi& operator-=(mi& a, mi b) {
	if ((a.v -= b.v) < 0) a.v += MOD;
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((int)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
mi pow(mi a, int p) { assert(p >= 0); // won't work for negative p
	return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
mi inv(mi a) { assert(a.v != 0); return pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
bool operator==(mi a, mi b) { return a.v == b.v; }

using fn = vector<mi>;

void sos(fn &f, bool sup, bool dif) {
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < f.size(); i++) if ((i >> k & 1) ^ sup) {
            if (dif) f[i] -= f[i ^ (1 << k)];
            else f[i] += f[i ^ (1 << k)];
        }
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> K;

    // preprocess our function
    fn invs(K + 1);
    for (int i = 1; i <= K; i++) invs[i] = inv(i);
    fn f(1 << K);
    for (int i = 1; i < f.size(); i++) f[i] = invs[__builtin_popcount(i)];
    sos(f, 1, 1); // superset difference

    vector<int> a(n);
    fn b(1 << K), c(1 << K);
    for (int &x : a) {
        cin >> x;
        b[x] += __builtin_popcount(x), c[x] += 1;
    }
    sos(b, 0, 0), sos(c, 0, 0); // subset sum
    for (auto v : {&b, &c}) for (int i = 0; i < v->size(); i++) (*v)[i] *= f[i];
    sos(b, 1, 0), sos(c, 1, 0); // superset sum
    for (int &x : a) {
        cout << int(__builtin_popcount(x) * c[x] + b[x] - n) << endl;
    }
}
