// https://www.acmicpc.net/problem/15604
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;
const int A = 1e7 + 1;
bitset<A> c; // composite
int n, a[N], l[N], r[N], p[N], x[A], f[A];
vector<int> pr;

int dnq(int l, int r) {
    if (l > r) return 0;
    if (l == r) return l;
    auto ck = [&](int i) {
        if (::l[i] >= l || ::r[i] <= r) return 0;
        int j = dnq(l, i - 1), k = dnq(i + 1, r);
        if (min(j, k) == -1) return -1;
        else return p[j] = p[k] = i;
    };
    for (int lb = l, rb = r; lb <= rb; ++lb, --rb) {
        if (int x = ck(lb)) return x;
        else if (int x = ck(rb)) return x;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 2; i < A; i++) {
        if (!f[i]) f[i] = i, pr.push_back(i);
        for (int p : pr) {
            if (p > f[i] || i * p >= A) break;
            f[i * p] = p;
        }
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        r[i] = n + 1;
        while (int f = ::f[a[i]]) {
            l[i] = max(l[i], x[f]);
            r[x[f]] = min(r[x[f]], i);
            x[f] = i;
            while (a[i] % f == 0) a[i] /= f;
        }
    }
    if (dnq(1, n) < 0) cout << "impossible\n";
    else for (int i = 1; i <= n; i++) cout << p[i] << " \n"[i == n];
}
