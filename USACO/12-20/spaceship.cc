// https://usaco.org/index.php?page=viewproblem2&cpid=1069
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define loop(i, l, r) for (int i = l; i < r; i++)
#define pool(i, l, r) for (int i = r; i --> l; )
#define seq(a, op, b) a = a op (b)

const int M = 1e9 + 7;

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
	operator int() { return v; }
    mint operator+(const mint o) const { return v + o.v; }
    mint operator*(const mint o) const { return v * o.v; }
    mint operator-(const mint o) const { return v - o.v; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

int n;
using Vec = vector<mint>;
Vec operator+(Vec a, Vec b) { return transform(a.begin(), a.end(), b.begin(), a.begin(), plus<mint>()), a; }
Vec operator-(Vec a, Vec b) { return transform(a.begin(), a.end(), b.begin(), a.begin(), minus<mint>()), a; }
Vec operator*(Vec a, mint v) {
    return transform(a.begin(), a.end(), a.begin(), std::bind(std::multiplies<mint>(), std::placeholders::_1, v)), a;
}
using Mat = vector<Vec>;
Mat operator+(Mat a, Mat b) { return transform(a.begin(), a.end(), b.begin(), a.begin(), plus<Vec>()), a; }
Mat operator-(Mat a, Mat b) { return transform(a.begin(), a.end(), b.begin(), a.begin(), minus<Vec>()), a; }

ostream& operator<<(ostream &os, Vec v) {
    for (int x : v) os << x << " ";
    return os << endl;
}

ostream& operator<<(ostream &os, Mat m) {
    for (Vec v : m) {
        os << v;
    }
    return os;
}
Mat operator*(Mat a, Mat b) {
    Mat c(n, Vec(n));
    loop(i, 0, n) loop(k, 0, n) loop(j, 0, n) seq(c[i][j], +, a[i][k] * b[k][j]);
    return c;
}
Vec operator|(Vec a, Vec b) {
    Vec c(a.size() + b.size());
    copy(a.begin(), a.end(), c.begin());
    copy(b.begin(), b.end(), c.begin() + a.size());
    return c;
}
Mat operator|(Mat a, Mat b) {
    Mat c(n);
    loop(i, 0, n) c[i] = a[i] | b[i];
    return c;
}
Mat gauss(Mat m) {
    loop(i, 0, n) {
        int r = -1;
        loop(j, i, n) if (m[j][i]) { r = j; break; }
        if (r < 0) {
            throw logic_error("rank < n");
        }
        swap(m[i], m[r]);
        seq(m[i], *, m[i][i].inv());
        loop(j, i + 1, n) {
            seq(m[j], -, m[i] * m[j][i]);
        }
    }
    pool(i, 0, n) {
        loop(j, 0, i) {
            seq(m[j], -, m[i] * m[j][i]);
        }
    }
    return m;
}

Mat eye(int n) {
    Mat I(n, Vec(n));
    loop(i, 0, n) I[i][i] = 1;
    return I;
}

Mat inv(Mat m) {
    Mat tmp = gauss(m | eye(n));
    Mat r(n, Vec(n));
    loop(i, 0, n) copy(tmp[i].begin() + n, tmp[i].begin() + 2 * n, r[i].begin());
    return r;
}

const int N = 61;

Mat G, dp[N];

int32_t main() {
    int k, q; cin >> n >> k >> q;
    G = Mat(n, Vec(n));
    loop(i, 0, n) loop(j, 0, n) {
        char c; cin >> c;
        G[i][j] = (c == '1');
    }
    // dp[i] -> number of unconstrained paths whose max button is <= i
    dp[0] = G;
    loop(i, 0, k) {
        dp[i + 1] = dp[i] * dp[i] + dp[i];
    }
    while (q--) {
        int bs, s, bt, t;
        cin >> bs >> s >> bt >> t;
        --s, --t;
        mint r = 0;
        // case 1: max button > max(bs, bt)
        if (max(bs, bt) < k) {
            Mat A =
                inv(dp[bs - 1] + eye(n)) * (dp[k] - dp[max(bs, bt)]) * inv(dp[bt - 1] + eye(n));
            r = A[s][t];
        }
        // case 2: max button = max(bs, bt)
        if (bs < bt) seq(r, +, (inv(dp[bs - 1] + eye(n)) * dp[bt - 1])[s][t]);
        else if (bs > bt) seq(r, +, (dp[bs - 1] * (inv(dp[bt - 1] + eye(n))))[s][t]);
        else if (s == t) seq(r, +, mint(s == t));
        cout << r << endl;
    }
}
