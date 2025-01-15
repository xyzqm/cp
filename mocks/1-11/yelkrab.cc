#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 5e5 + 1;

int n, a[N], xr;
vector<int> f[N], sz;
vector<array<int, 26>> tr;

void inc(int i) {
    for (int j : f[++sz[i]]) {
        xr ^= (a[j] * j);
        xr ^= (++a[j] * j);
    }
}

void insert(string s) {
    int x = 0;
    for (char c : s) {
        int i = c - 'a';
        if (!tr[x][i]) {
            sz.push_back(0);
            tr[x][i] = tr.size();
            tr.push_back({});
        }
        inc(x = tr[x][i]);
    }
}

void ac() {
    // input + reset variables
    int n; cin >> n;
    fill(a, a + n + 1, 0), xr = 0;
    sz.assign(1, 0), tr.assign(1, {});
    // win
    while (n--) {
        string s; cin >> s;
        cout << (insert(s), xr) << " ";
    }
    cout << endl;
}

int32_t main() {
    // precompute factors of every number
    for (int i = 1; i < N; i++) for (int j = i; j < N; j += i) f[j].push_back(i);
    // solve
    int t; cin >> t;
    while (t--) ac();
}
