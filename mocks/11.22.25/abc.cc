#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e8 + 7;

inline void mul(int &a, const int b) { a = a * b % M; }
inline void ad(int &a, const int b) { a = (a + b) % M; }
int exp(int x, int y) {
    int r = 1;
    for (; y; y >>= 1, mul(x, x)) if (y & 1) mul(r, x);
    return r;
}

struct mat : array<array<int, 3>, 3> {};
mat A = {{{
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 1}
}}};
mat B = {{{
    {0, 0, 0},
    {0, 0, 1},
    {0, 0, 1}
}}};
mat C = {{{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 0}
}}};
mat id = {{{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
}}};

mat operator*(mat a, mat b) {
    mat c{};
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) ad(c[i][j], a[i][k] * b[k][j] % M);
        }
    }
    return c;
}
mat operator+(mat a, mat b) {
    mat c = a;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ad(c[i][j], b[i][j]);
        }
    }
    return c;
}

int32_t main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    int i = 0;
    auto solve = [&](auto &&f, int mark) -> mat {
        mat a = id, b = id, c = id;
        int cur = v[i];
        while (i < n && v[i] != mark) {
            if (v[i] == cur) a = a * A, b = b * B, c = c * C, i++;
            else {
                mat d = f(f, cur);
                a = a * d, b = b * d, c = c * d;
            }
        }
        return a + b + c;
    };
    mat res = solve(solve, -1);
    println("{}", res);
}
