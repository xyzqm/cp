#include "testlib.h"
#include <vector>
#include <unordered_set>
#include <cstdint>
#include <string>

using namespace std;

// Simple DSU for checking connectivity and cycles.
struct DSU {
    int n;
    vector<int> p, r;
    int components;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n+1);
        r.assign(n+1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
        components = n;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    // returns true if merged, false if already in same set
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        --components;
        return true;
    }
};

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    long long total_n = 0;
    long long total_q = 0;

    for (int tc = 0; tc < t; ++tc) {
        setTestCase(tc + 1);

        // Read n and q for this test case
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int q = inf.readInt(1, 300000, "q");
        inf.readEoln();

        total_n += n;
        total_q += q;
        ensure(total_n <= 100000);
        ensure(total_q <= 300000);

        // Read tree edges: n-1 lines of u v
        DSU dsu(n);
        unordered_set<uint64_t> edgeSet;
        if (n >= 2) {
            for (int i = 0; i < n - 1; ++i) {
                int u = inf.readInt(1, n, "u");
                inf.readSpace();
                int v = inf.readInt(1, n, "v");
                inf.readEoln();

                // No self-loops
                ensure(u != v);

                int a = min(u, v);
                int b = max(u, v);
                uint64_t key = ( (uint64_t)a << 32 ) | (uint64_t)b;
                // No duplicate edges
                ensure(edgeSet.find(key) == edgeSet.end());
                edgeSet.insert(key);

                // No cycles: unite should succeed for a tree
                bool merged = dsu.unite(u, v);
                ensure(merged);
            }
        }

        // For n == 1, there must be zero edges (we read none above).
        // After reading edges, graph must be connected (1 component).
        if (n >= 1) {
            ensure(dsu.components == 1);
        }

        // Read q queries: each line l r (1 <= l <= r <= n)
        for (int i = 0; i < q; ++i) {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(1, n, "r");
            inf.readEoln();
            ensure(l <= r);
        }
    }

    inf.readEof();
    return 0;
}