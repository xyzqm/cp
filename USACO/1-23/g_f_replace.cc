#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 1e6;
const int M = 256;
vector<int> g[N];
int l, r, q, I, D[N], A[N], B[N], X[N], R[N], F[M], L[M], C[M];
char S[N], ans[N];
string W[N];
int dfs(int x, int L) {
    int _ = L;
    if (g[x].size() == 1 && !S[g[x][0]] && !g[g[x][0]].size()) { // x is a leaf
        if (L > 0 && L <= r) {
            ans[L] = S[x];
            A[x] = L;
        }
        ++L;
    } else if (D[x] && L + D[x] < 1 || L > r) { // this subtree can be completely skipped
        L += D[x];
    } else if (L > 0 && A[x]) {
        int z = A[x];
        while (z && L <= r) {
            ans[L++] = ans[z];
            z = ++z * (z - A[x] < D[x]);
        }
    } else {
        for (int y : g[x]) {
            L = dfs(y, L);
            if (L > r) break;
        }
        if (_ > 0 && L <= r) A[x] = _; 
    }
    D[x] = L - _;
    return L;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> l >> r >> q;
    L['a'] = ++I; S[0] = 'a';
    g[0].push_back(1);
    while (q--) {
        char c; string s;
        cin >> c >> s;
        if (!L[c]) continue;
        int i = L[c]; L[c] = 0;
        for (char x : s) {
            g[i].push_back(++I); S[I] = x;
            g[I].push_back(L[x] = (L[x] ? L[x] : ++I));
        }
    }
    r -= l - 1;
    dfs(I = 0, -l + 2);
    for (int i = 1; i <= r; i++) cout << ans[i];
    return 0;
}