#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
  Generator for "Tree Queries".

  Output format (per statements):
    t
    for each test case:
      n q
      n-1 lines: edges (u v) of the tree (1-indexed)
      q lines: queries l r with 1 <= l <= r <= n

  Constraints respected across all test cases:
    sum n <= 1e5
    sum q <= 3e5
    1 <= t <= 1e4

  The generator takes one integer parameter (opt<int>(1)), which is used as a
  target / typical size for `n`. The generator produces multiple test cases
  so that the total number of nodes is bounded by 1e5 and the total number of
  queries by 3e5.
*/

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int TARGET_N = opt<int>(1); // typical/target size for n passed by polygon
    const int MAX_SUM_N = 100000;
    const int MAX_SUM_Q = 300000;
    const int MAX_T = 10000;

    int N = max(1, TARGET_N);

    // Decide number of test cases so that sum of n approx <= MAX_SUM_N
    int t;
    if (N >= MAX_SUM_N) {
        t = 1;
    } else {
        t = MAX_SUM_N / N;
        if (t <= 0) t = 1;
        if (t > MAX_T) t = MAX_T;
    }

    // Track remaining quotas
    int remainingN = MAX_SUM_N;
    int remainingQ = MAX_SUM_Q;

    cout << t << "\n";
    for (int i = 0; i < t; ++i) {
        // Ensure at least 1 node remains for each remaining test
        int tests_left = t - i;
        int min_allowed_n = 1;
        int max_allowed_n = max(min_allowed_n, remainingN - (tests_left - 1));
        // Prefer producing around N nodes but cap to remaining
        int prefer_low = max(1, N / 2);
        int prefer_high = min(max_allowed_n, N + N/2);
        int n;
        if (prefer_low > prefer_high) {
            // fallback
            n = max_allowed_n;
        } else {
            n = rnd.next(prefer_low, prefer_high);
            if (n > max_allowed_n) n = max_allowed_n;
            if (n < min_allowed_n) n = min_allowed_n;
        }

        // Adjust if this would exhaust remainingN leaving not enough for later tests
        if (remainingN - n < (tests_left - 1)) {
            n = remainingN - (tests_left - 1);
        }
        if (n <= 0) n = 1;

        // Decide q: at least 1, at most 3*n, and respecting remainingQ
        int max_q_possible = min(3 * n, remainingQ - (tests_left - 1));
        if (max_q_possible < 1) max_q_possible = 1;
        int q = rnd.next(1, max_q_possible);

        // Print n and q
        cout << n << " " << q << "\n";

        // Generate a random tree on n nodes
        // Use a simple random tree generator: for v = 2..n connect to random u in [1, v-1]
        for (int v = 2; v <= n; ++v) {
            int u = rnd.next(1, v - 1);
            cout << u << " " << v << "\n";
        }

        // Generate q queries: random ranges [l, r], sometimes biased to small/large
        for (int qi = 0; qi < q; ++qi) {
            int type = rnd.next(1, 10);
            int l, r;
            if (type <= 6) {
                // general random range
                l = rnd.next(1, n);
                r = rnd.next(l, n);
            } else if (type <= 8) {
                // small range near random position
                int a = rnd.next(1, n);
                int len = rnd.next(0, min(10, n - a));
                l = a;
                r = min(n, a + len);
            } else {
                // large range biased to whole tree or prefix/suffix
                int choice = rnd.next(1,3);
                if (choice == 1) { l = 1; r = n; }
                else if (choice == 2) { l = 1; r = rnd.next(1, n); }
                else { r = n; l = rnd.next(1, n); if (l>r) swap(l,r); }
            }
            cout << l << " " << r << "\n";
        }

        remainingN -= n;
        remainingQ -= q;
        // safety: if remainingN or remainingQ is exhausted, put remaining tests with n=1 q=1
        if (remainingN <= 0) remainingN = 0;
        if (remainingQ <= 0) remainingQ = 0;
    }

    return 0;
}
