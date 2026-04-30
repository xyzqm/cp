#ifdef ONLINE_JUDGE
#include "dna.h"
#endif
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

int n;
string a, b, chars = "ACT";
using A = array<int, 3>;
using T = array<A, 3>;
vector<A> frq;
vector<T> psum;
A operator-(A a, A b) {
    for (int i = 0; i < 3; i++) a[i] -= b[i];
    return a;
}
T operator-(T a, T b) {
    for (int i = 0; i < 3; i++) a[i] = a[i] - b[i];
    return a;
}

int idx(char c) { return chars.find(c); }

void init(string a, string b) {
    ::a = a, ::b = b, n = a.size();
    a.insert(a.begin(), '0');
    b.insert(b.begin(), '0');
    frq.resize(n + 1), psum.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        frq[i] = frq[i - 1];
        psum[i] = psum[i - 1];
        ++frq[i][idx(a[i])];
        --frq[i][idx(b[i])];
        ++psum[i][idx(a[i])][idx(b[i])];
    }
    DBG(frq);
}

int get_distance(int x, int y) {
    // DBG(frq[y + 1] - frq[x]);
    if (frq[++y] - frq[x++] != array{0, 0, 0}) return -1;
    auto pairs = psum[y] - psum[x - 1];
    // DBG(pairs);
    int res = 0;
    vector<int> rem;
    for (int i = 0; i < 3; i++) for (int j = i + 1; j < 3; j++) {
        res += min(pairs[i][j], pairs[j][i]);
        rem.push_back(max(pairs[i][j], pairs[j][i]) - min(pairs[i][j], pairs[j][i]));
    }
    // DBG(rem);
    assert(ranges::adjacent_find(rem, not_equal_to()) == rem.end());
    return rem[0] * 2 + res;
}

#ifndef ONLINE_JUDGE
int32_t main() {
    init("ATACAT", "ACTATA");
    DBG(get_distance(1, 3));
    DBG(get_distance(4, 5));
    DBG(get_distance(3, 5));
}
#endif
