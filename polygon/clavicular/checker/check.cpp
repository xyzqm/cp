#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

// Checks if a subarray of length k is k-good
int cnt_k_good(const std::vector<int>& a, int k) {
    int rt = k - 1, tot = 0; // rightmost possible point
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] == k) tot += rt <= i;
        else rt = max(rt, i + k - a[i]);
    }
    return tot;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();

    for (int test = 0; test < t; ++test) {
        setTestCase(test + 1);
        int n = inf.readInt();
        int k = inf.readInt();
        int x = inf.readInt();
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = inf.readInt();
        }

        // Read output
        std::vector<int> perm(n, 1);
        for (int i = 0; i < n; i++) if (perm[0]) {
            perm[i] = ouf.readInt(0, k);
        }

        // Check permutation validity
        auto sorted_a = a;
        int mx = cnt_k_good(sorted_a, k);
        int mn = count(a.begin(), a.end(), k) - (k - 1);
        for (int v : a) if (v != k) mn -= k - (v + 1);
        if (!perm[0]) {
            if (x < mn || x > mx) continue;
            quitf(_wa, "Test %d: Reported impossible, but jury found a construction.", test);
        }
        auto sorted_perm = perm;
        sort(sorted_a.begin(), sorted_a.end());
        sort(sorted_perm.begin(), sorted_perm.end());
        if (sorted_a != sorted_perm)
            quitf(_wa, "Test %d: Output is not a valid permutation of input array.", test);

        // Count k-good subarrays
        if (int cnt = cnt_k_good(perm, k); cnt != x)
            quitf(_wa, "Test %d: Permutation contains %d k-good subarrays, expected %d.", test, cnt, x);
    }
    quitf(_ok, "All test cases passed.");
}
