#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
  gen_max for "tree-queries" problem:
  - Produces a single test case (t = 1) with a large n and many queries q.
  - The tree is a long path (1 - 2 - 3 - ... - n) which is a common
    worst-case shape for many tree algorithms.
  - Queries are a mixture of:
      * full-range queries,
      * very long ranges (covering about half..all of the nodes),
      * many single-node queries,
      * many small ranges,
      * many random ranges.
    This mix aims to stress range-handling and path-related logic.
  - The generator reads `n` from generator option 1 (opt<int>(1)).
    It sets q = min(300000, n * 6) to hit large q while respecting
    the stated sum constraints.
*/

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = opt<int>(1);
    // Bound q so that sum of q over all tests doesn't exceed limits.
    const int Q_LIMIT = 300000;
    int q = min(Q_LIMIT, n * 6);

    // We'll produce exactly one test case.
    cout << 1 << "\n";
    cout << n << " " << q << "\n";

    // Output edges of a path: 1-2, 2-3, ..., (n-1)-n
    for (int i = 1; i <= n - 1; ++i) {
        cout << i << " " << i + 1 << "\n";
    }

    // Prepare query generation quotas.
    int remaining = q;
    int cnt_full = max(1, q / 10);         // ~10% full-range queries
    int cnt_single = max(1, q / 5);        // ~20% single-node queries
    int cnt_long = max(1, q / 5);          // ~20% long ranges
    int cnt_small = max(1, q / 5);         // ~20% small ranges (length <= 10)
    int cnt_random = remaining - (cnt_full + cnt_single + cnt_long + cnt_small);
    if (cnt_random < 0) {
        // If q is small, scale things down proportionally
        cnt_full = cnt_single = cnt_long = cnt_small = 0;
        cnt_random = remaining;
    }

    auto rnd_int = [&](int L, int R) {
        if (L > R) swap(L, R);
        return rnd.next(L, R);
    };

    // 1) Full-range queries [1, n]
    for (int i = 0; i < cnt_full && remaining > 0; ++i) {
        cout << 1 << " " << n << "\n";
        --remaining;
    }

    // 2) Many single-node queries [x, x]
    for (int i = 0; i < cnt_single && remaining > 0; ++i) {
        int x = rnd_int(1, n);
        cout << x << " " << x << "\n";
        --remaining;
    }

    // 3) Long ranges (length roughly between n/2 and n)
    for (int i = 0; i < cnt_long && remaining > 0; ++i) {
        int len = rnd_int(max(1, n / 2), n);
        int l = rnd_int(1, max(1, n - len + 1));
        int r = l + len - 1;
        cout << l << " " << r << "\n";
        --remaining;
    }

    // 4) Small ranges (length up to 10)
    for (int i = 0; i < cnt_small && remaining > 0; ++i) {
        int len = rnd_int(1, min(10, n));
        int l = rnd_int(1, max(1, n - len + 1));
        int r = l + len - 1;
        cout << l << " " << r << "\n";
        --remaining;
    }

    // 5) Random ranges for the rest
    for (int i = 0; i < cnt_random && remaining > 0; ++i) {
        int l = rnd_int(1, n);
        int r = rnd_int(l, n);
        cout << l << " " << r << "\n";
        --remaining;
    }

    // Safety: if anything remains (due to rounding), emit random queries.
    while (remaining > 0) {
        int l = rnd_int(1, n);
        int r = rnd_int(l, n);
        cout << l << " " << r << "\n";
        --remaining;
    }

    return 0;
}