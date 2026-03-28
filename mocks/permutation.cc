#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

using ll = long long;

vector<int> construct(ll k, int mn) {
    if (k == 1) return {};
    auto v = construct(k >> 1, mn + 1 + (k & 1));
    v.insert(v.begin(), mn + (k & 1));
    if (k & 1) v.push_back(mn);
    return v;
}

vector<int> construct_permutation(ll k) {
    return construct(k, 0);
}

#ifndef ONLINE_JUDGE
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    DBG(construct_permutation(1e18).size());
}
#endif
