#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 1e6 + 1;

vector<int> f[N];

bool valid(vector<int> &s) {
    int p = s.size();
    auto ck = [&](int d) {
        if (d == p) return 0;
        for (int i = 0; i + d < p; i++) if (s[i] != s[i + d]) return 0;
        return 1;
    };
    for (int x : f[p]) if (ck(x)) return 0;
    return 1;
}

int rngc = 0;
void rng(vector<int> &s) {
    do {
        ++rngc;
        for (int &c : s) c = rand() % 2;
    } while (!valid(s));
}

int gcd(int a, int b) { if (a < b) swap(a, b); return b ? gcd(a % b, b) : a; }

vector<int> v[N];

void ac() {
    int a, b, c; cin >> a >> b >> c;
    vector<int> A(a), B(b), C(c);
    if (a == b) {
        if (b % c != 0 || (a == c && a == 2)) goto no;
        A.back() = C.back() = 1;
        if (a == c) C.back() = 0, C[0] = 1;
        for (int i = 0; i < b; i++) {
            B[i] = A[i] ^ C[i % c];
        }
    }
    else {
        if (c != lcm(a, b)) goto no;
        A.back() = B.back() = 1;
        for (int i = 0; i < c; i++) {
            C[i] = A[i % a] ^ B[i % b];
        }
    }
    cout << "YES\n";
    for (auto &v : {A, B, C}) {
        for (int x : v) cout << x;
        cout << endl;
    }
    // cout << rngc << endl;
    return;
no: cout << "NO\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    // precompute factors
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) f[j].push_back(i);
    }
    int t; cin >> t;
    while (t--) ac();
}
