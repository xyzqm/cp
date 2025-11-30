#include <bits/stdc++.h>
using namespace std;

#define int uint64_t

template <int N, int M>
struct mat : array<array<int, M>, N> {};


template <int A, int B, int C>
mat<A, C> operator*(mat<A, B> a, mat<B, C> b) {
    mat<A, C> c{};
    for (int i = 0; i < A; i++) for (int k = 0; k < B; k++) for (int j = 0; j < C; j++) {
        c[i][j] += a[i][k] * b[k][j];
    }
    return c;
}

const int MX = 210;

mat<MX, MX> mt{};
mat<1, MX> init{};

int32_t main() {
    int n, p, k; cin >> n >> p >> k;
    if (n < k) {
        cout << pow(p, n) << endl;
        return 0;
    }
    else if (k == 1) {
        int r = 1, base = p;
        for ( ; n; n /= 2, base = base * base) if (n & 1) r = r * base;
        cout << r << endl;
        return 0;
    }
    auto decode = [&](int code) {
        vector<int32_t> vals;
        vector<bool> av(p, 1);
        for (int i = 0, b = p; i < k; i++, b--) {
            int cnt = code % b;
            for (int j = 0; j < p; cnt -= av[j++]) if (!cnt && av[j]) {
                vals.push_back(j);
                av[j] = 0;
                break;
            }
            code /= b;
        }
        return vals;
    };
    auto valid = [&](int code) {
        auto vals = decode(code);
        int cnt = 0;
        for (int i = 1; i + 1 < vals.size(); i++) if (vals[i] < min(vals[i - 1], vals[i + 1]) || vals[i] > max(vals[i - 1], vals[i + 1])) ++cnt;
        if (cnt > 1) return false;
        for (int i = 0; i + 1 < vals.size(); i++) if (abs(vals[i + 1] - vals[i]) > 5) return false;
        return true;
    };
    auto nx = [&](int code) {
        auto vals = decode(code);
        int base = 1, mul = p, res = 0;
        for (int i = 1; i < vals.size(); i++) {
            int cur = vals[i];
            for (int j = 1; j < i; j++) if (vals[j] < vals[i]) --cur;
            res += cur * base;
            base *= mul--;
        }
        return res;
    };
    int mx = 1;
    for (int i = p; i > p - k + 1; i--) mx *= i;
    for (int i = 0; i < mx; i++) {
        init[0][i] = 1;
        for (int j = 0; j < p - k + 1; j++) {
            if (int x = i + j * mx; valid(x)) mt[i][nx(x)] = 1;
        }
    }
    // println("{}", init);
    // println("{}", mt);
    for (int pw = n - k + 1; pw; pw /= 2, mt = mt * mt) if (pw & 1) init = init * mt;
    int ans = 0;
    for (int x : init[0]) ans += x;
    cout << ans << endl;
    // println("{}", init);
}
