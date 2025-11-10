#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int MOD = 1e9 + 7;

void ad(int &a, int b) { a = (a + b) % MOD; }

template <int N, int M>
struct mat : array<array<int, M>, N> {};

template <int A, int B, int C>
mat<A, C> operator*(mat<A, B> a, mat<B, C> b) {
    mat<A, C> c{};
    for (int i = 0; i < A; i++) for (int k = 0; k < B; k++) for (int j = 0; j < C; j++) {
        ad(c[i][j], a[i][k] * b[k][j]);
    }
    return c;
}

template <int N, int K = 0>
constexpr mat<N, N> id() {
    mat<N, N> m{};
    for (int i = K; i < N; i++) m[i][i - K] = 1;
    return m;
}

template <int N>
mat<N, N> operator^(mat<N, N> m, int pw) {
    auto r = id<N>();
    for (; pw; pw >>= 1, m = m * m) if (pw & 1) r = r * m;
    return r;
}

const int N = 101;

void ac() {
    int n, dep;
    cin >> n >> dep;
    mat<1, N> p{};
    auto tr = id<N, 1>(); // offset by 1
    int cur = -1;
    while (n--) {
        char c; cin >> c;
        if (c == '(') ++cur;
        else if (c == '|') ++p[0][cur];
        else if (c == 'O') ++tr[0][cur];
        else --cur;
    }
    tr[0][N - 1] = 1;
    tr[N - 1][N - 2] = 0; // get rid of shift for this one
    tr[N - 1][N - 1] = 1;
    tr = tr ^ dep;
    p = p * tr;
    cout << p[0][N - 1] << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
