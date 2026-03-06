#include <bits/stdc++.h>
using namespace std;

// -------- Bitset ordered set over positions [0..n-1] --------
// Supports: set/clear, prevStrict(p), nextStrict(p), firstPos(), lastPos()
// All in ~O(1) using 2-level bitsets and ctz/clz.
// IMPORTANT: avoids any shift-by-64 UB.
struct BitsetOrder {
    int n = 0;
    int blocks = 0; // number of 64-bit blocks
    int supers = 0; // number of 64-bit superblocks over blocks
    vector<uint64_t> b;   // blocks
    vector<uint64_t> sb;  // superblocks: bit j set if block (i*64+j) is non-empty

    void init(int n_) {
        n = n_;
        blocks = (n + 63) >> 6;
        supers = (blocks + 63) >> 6;
        b.assign(blocks, 0);
        sb.assign(supers, 0);
    }

    inline void syncSuper(int bi) {
        int si = bi >> 6;
        int off = bi & 63;
        if (b[bi]) sb[si] |= (1ULL << off);
        else       sb[si] &= ~(1ULL << off);
    }

    inline void setBit(int p) {
        int bi = p >> 6, off = p & 63;
        uint64_t before = b[bi];
        b[bi] |= (1ULL << off);
        if (!before) syncSuper(bi);
    }

    inline void clearBit(int p) {
        int bi = p >> 6, off = p & 63;
        b[bi] &= ~(1ULL << off);
        if (!b[bi]) syncSuper(bi);
    }

    inline int firstPos() const {
        for (int si = 0; si < supers; si++) {
            uint64_t m = sb[si];
            if (!m) continue;
            int bj = __builtin_ctzll(m);
            int bi = (si << 6) + bj;
            uint64_t x = b[bi];
            int off = __builtin_ctzll(x);
            int p = (bi << 6) + off;
            return (p < n ? p : -1);
        }
        return -1;
    }

    inline int lastPos() const {
        for (int si = supers - 1; si >= 0; si--) {
            uint64_t m = sb[si];
            if (!m) continue;
            int bj = 63 - __builtin_clzll(m);
            int bi = (si << 6) + bj;
            uint64_t x = b[bi];
            int off = 63 - __builtin_clzll(x);
            int p = (bi << 6) + off;
            return (p < n ? p : -1);
        }
        return -1;
    }

    // next set bit strictly > p, or -1
    inline int nextStrict(int p) const {
        int bi = p >> 6, off = p & 63;

        // same block: bits after off (guard shift-by-64)
        uint64_t x = (off == 63) ? 0ULL : (b[bi] & (~0ULL << (off + 1)));
        if (x) {
            int o = __builtin_ctzll(x);
            int res = (bi << 6) + o;
            return (res < n ? res : -1);
        }

        // next non-empty block in same superblock
        int si = bi >> 6, boff = bi & 63;
        uint64_t m = (boff == 63) ? 0ULL : (sb[si] & (~0ULL << (boff + 1)));
        if (m) {
            int bj = __builtin_ctzll(m);
            int nb = (si << 6) + bj;
            uint64_t y = b[nb];
            int o = __builtin_ctzll(y);
            int res = (nb << 6) + o;
            return (res < n ? res : -1);
        }

        // later superblocks
        for (int ns = si + 1; ns < supers; ns++) {
            uint64_t mm = sb[ns];
            if (!mm) continue;
            int bj = __builtin_ctzll(mm);
            int nb = (ns << 6) + bj;
            uint64_t y = b[nb];
            int o = __builtin_ctzll(y);
            int res = (nb << 6) + o;
            return (res < n ? res : -1);
        }
        return -1;
    }

    // previous set bit strictly < p, or -1
    inline int prevStrict(int p) const {
        int bi = p >> 6, off = p & 63;

        // same block: bits before off
        uint64_t mask = (off == 0) ? 0ULL : ((1ULL << off) - 1);
        uint64_t x = b[bi] & mask;
        if (x) {
            int o = 63 - __builtin_clzll(x);
            return (bi << 6) + o;
        }

        // previous non-empty block in same superblock
        int si = bi >> 6, boff = bi & 63;
        uint64_t m = (boff == 0) ? 0ULL : (sb[si] & ((1ULL << boff) - 1));
        if (m) {
            int bj = 63 - __builtin_clzll(m);
            int nb = (si << 6) + bj;
            uint64_t y = b[nb];
            int o = 63 - __builtin_clzll(y);
            return (nb << 6) + o;
        }

        // earlier superblocks
        for (int ps = si - 1; ps >= 0; ps--) {
            uint64_t mm = sb[ps];
            if (!mm) continue;
            int bj = 63 - __builtin_clzll(mm);
            int nb = (ps << 6) + bj;
            uint64_t y = b[nb];
            int o = 63 - __builtin_clzll(y);
            return (nb << 6) + o;
        }
        return -1;
    }
};

// -------- Hilbert order for Mo sorting --------
static inline long long hilbertOrder(int x, int y, int pow = 17, int rot = 0) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg;
    if (x < hpow) seg = (y < hpow) ? 0 : 3;
    else          seg = (y < hpow) ? 1 : 2;
    seg = (seg + rot) & 3;
    static const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (hpow - 1);
    int ny = y & (hpow - 1);
    int nrot = (rot + rotateDelta[seg]) & 3;
    long long sub = hilbertOrder(nx, ny, pow - 1, nrot);
    long long add = 1LL * seg * (1LL << (2 * pow - 2));
    if (seg == 1 || seg == 2) return add + sub;
    return add + ((1LL << (2 * pow - 2)) - 1 - sub);
}

// -------- LCA via Euler tour + RMQ (O(1) per query) --------
struct LCA_RMQ {
    vector<int> first, euler, dep, lg;
    vector<vector<int>> st; // indices into euler

    void build(const vector<vector<int>>& g, const vector<int>& parent,
               const vector<int>& depth, int root = 1) {
        int n = (int)g.size() - 1;
        first.assign(n + 1, -1);
        euler.clear(); dep.clear();
        euler.reserve(2 * n);
        dep.reserve(2 * n);

        vector<pair<int,int>> stk;
        stk.reserve(n);
        stk.push_back({root, 0});
        first[root] = 0;
        euler.push_back(root);
        dep.push_back(depth[root]);

        while (!stk.empty()) {
            int u = stk.back().first;
            int &it = stk.back().second;
            if (it == (int)g[u].size()) {
                stk.pop_back();
                if (!stk.empty()) {
                    int p = stk.back().first;
                    euler.push_back(p);
                    dep.push_back(depth[p]);
                }
                continue;
            }
            int v = g[u][it++];
            if (v == parent[u]) continue;
            stk.push_back({v, 0});
            if (first[v] == -1) first[v] = (int)euler.size();
            euler.push_back(v);
            dep.push_back(depth[v]);
        }

        int m = (int)euler.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;
        int K = lg[m];
        st.assign(K + 1, vector<int>(m));
        for (int i = 0; i < m; i++) st[0][i] = i;

        for (int k = 1; k <= K; k++) {
            int len = 1 << k, half = len >> 1;
            for (int i = 0; i + len <= m; i++) {
                int a = st[k - 1][i];
                int b = st[k - 1][i + half];
                st[k][i] = (dep[a] < dep[b]) ? a : b;
            }
        }
    }

    inline int lca(int u, int v) const {
        int L = first[u], R = first[v];
        if (L > R) swap(L, R);
        int k = lg[R - L + 1];
        int a = st[k][L];
        int b = st[k][R - (1 << k) + 1];
        return (dep[a] < dep[b]) ? euler[a] : euler[b];
    }
};

struct Query {
    int l, r, id;
    long long ord;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // parent/depth + traversal order
        vector<int> parent(n + 1, 0), depth(n + 1, 0), order;
        order.reserve(n);
        {
            vector<int> st;
            st.reserve(n);
            st.push_back(1);
            parent[1] = 0;
            depth[1] = 0;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                order.push_back(u);
                for (int v : g[u]) if (v != parent[u]) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    st.push_back(v);
                }
            }
        }

        // subtree sizes + heavy child
        vector<int> sz(n + 1, 1), heavy(n + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            int best = 0;
            sz[u] = 1;
            for (int v : g[u]) if (v != parent[u]) {
                sz[u] += sz[v];
                if (sz[v] > best) best = sz[v], heavy[u] = v;
            }
        }

        // HLD order (heavy-first preorder) => pos[u] in [0..n-1]
        vector<int> pos(n + 1, 0), invPos(n, 0);
        int timer = 0;
        {
            vector<pair<int,int>> st;
            st.reserve(n);
            st.push_back({1, 1});
            while (!st.empty()) {
                auto [u, h] = st.back();
                st.pop_back();
                for (int x = u; x != -1; x = heavy[x]) {
                    pos[x] = timer;
                    invPos[timer] = x;
                    timer++;
                    for (int v : g[x]) if (v != parent[x] && v != heavy[x]) {
                        st.push_back({v, v});
                    }
                }
            }
        }

        // LCA
        LCA_RMQ rmq;
        rmq.build(g, parent, depth, 1);
        auto dist = [&](int u, int v) -> int {
            int w = rmq.lca(u, v);
            return depth[u] + depth[v] - 2 * depth[w];
        };

        // read queries
        vector<Query> qs;
        qs.reserve(q);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            qs.push_back({l, r, i, hilbertOrder(l - 1, r - 1, 17, 0)});
        }
        sort(qs.begin(), qs.end(), [](const Query& a, const Query& b) {
            return a.ord < b.ord;
        });

        BitsetOrder os;
        os.init(n);

        long long cyc = 0; // cyclic sum of dist between consecutive active nodes in pos-order
        int curSz = 0;

        auto addNode = [&](int u) {
            int p = pos[u];
            if (curSz == 0) {
                os.setBit(p);
                curSz = 1;
                return;
            }
            int prvP = os.prevStrict(p);
            int nxtP = os.nextStrict(p);
            if (prvP == -1) prvP = os.lastPos();
            if (nxtP == -1) nxtP = os.firstPos();

            int a = invPos[prvP];
            int b = invPos[nxtP];
            cyc += (long long)dist(a, u) + dist(u, b) - dist(a, b);

            os.setBit(p);
            curSz++;
        };

        auto removeNode = [&](int u) {
            int p = pos[u];
            if (curSz == 1) {
                os.clearBit(p);
                curSz = 0;
                cyc = 0;
                return;
            }
            int prvP = os.prevStrict(p);
            int nxtP = os.nextStrict(p);
            if (prvP == -1) prvP = os.lastPos();
            if (nxtP == -1) nxtP = os.firstPos();

            int a = invPos[prvP];
            int b = invPos[nxtP];
            cyc -= (long long)dist(a, u) + dist(u, b) - dist(a, b);

            os.clearBit(p);
            curSz--;
        };

        int L = 1, R = 0; // active label interval [L,R], empty initially
        vector<long long> ans(q);

        for (const auto& qu : qs) {
            while (L > qu.l) addNode(--L);
            while (R < qu.r) addNode(++R);
            while (L < qu.l) removeNode(L++);
            while (R > qu.r) removeNode(R--);
            ans[qu.id] = cyc / 2;
        }

        for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    }
    return 0;
}
