// https://atcoder.jp/contests/arc194/tasks/arc194_d
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

using mint = atcoder::modint998244353;

const int N = 5e3 + 1;

int n, fa[N];
string s;
mint fac[N], ans = 1;

vector<int> g[N];

map<vector<int>, int> mp;
int solve(int x) {
    vector<int> v;
    for (int y : g[x]) v.push_back(solve(y));
    sort(v.begin(), v.end());
    ans *= fac[v.size()];
    v.push_back(-2);
    for (int i = 1, sz = 1; i < v.size(); i++) {
        if (!i || v[i] == v[i - 1]) ++sz;
        else ans /= fac[sz], sz = 1;
    }
    if (!mp[v]) mp[v] = mp.size();
    return mp[v];
}

int main() {
   cin >> n >> s;
   s.insert(s.begin(), '\0');
   fac[0] = 1;
   for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
   int rt = 0;
   for (int i = 1; i <= n; i++) {
       if (s[i] == '(') {
           g[fa[i] = rt].push_back(i);
           rt = i;
       } else rt = fa[rt];
   }
   solve(0);
   cout << ans.val() << endl;
}
