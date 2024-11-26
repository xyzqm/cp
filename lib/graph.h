#pragma once
#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#ifdef WEIGHTED
struct W { // weighted edge
    int v; ll w;
    friend istream& operator>>(istream& is, W &e) { return is >> e.v >> e.w; }
    friend ostream& operator<<(ostream& os, W &e) { return os << e.v << ":" << e.w; }
    bool operator==(const W o) const { return make_pair(v, w) == make_pair(o.v, o.w); }
    operator int() const { return v; }
    bool operator<(const W &o) const { return make_pair(v, w) < make_pair(o.v, o.w); }
    bool operator<(int x) const { return v < x; }
};
#endif

template <int N, typename T = int>
struct Graph {
    int n, m;
    Graph() {}
    Graph(int n, int m) : n(n), m(m) {}
    Graph& init(int n, int m) { return this->n = n, this->m = m, *this; }
    vector<T> g[N];
    void add(int u, T e) { g[u].push_back(e); }
    void u(int u, int v) {
        if constexpr (is_same_v<T, int>) {
            add(u, v);
            add(v, u);
        }
        else assert(false);
    }
    // undirected input
    Graph& input() {
        for (int i = 0; i < m; i++) {
        int u; T v; cin >> u >> v;
        g[u].push_back(v);
        #ifdef WEIGHTED
        g[v].push_back({u, v.w});
        #else
        g[v].push_back(u);
        #endif
        }
        return *this;
    }
};

#ifdef LCA
#define EULER
#include "sparse.h"
#endif

template <int N, typename T = int>
struct Tree : Graph<N, T> {
    int r, s[N], p[N];
    ll d[N]{};
    Tree() {}
    Tree& init(int n) {
        Graph<N, T>::init(n, n - 1);
        fill(s, s + n + 1, 1); // TODO: allow initializing weighted nodes later
        return *this;
    }
    Tree& root(int x) { return r = p[x] = x, *this; }
    #ifdef EULER
    int I[N], o[2 * N]{}, t = 0;
    #endif
    #ifdef LCA
    ST<2 * N> st{[&](int x, int y) { return d[x] < d[y] ? x : y; }};
    #endif
    int dfs(int x) {
        for (T e : this->g[x]) {
        #ifdef EULER
        o[I[x] = t++] = x;
        #endif
        if (e == p[x]) continue;
        #ifdef WEIGHTED
        ll w = 1;
        if constexpr (is_same_v<T, W>) w = e.w;
        d[e] = d[p[e] = x] + w;
        #else
        d[e] = d[p[e] = x] + 1;
        #endif
        s[x] += dfs(e);
        }
        #ifdef LCA
        if (x == r) st.build(o);
        #endif
        return s[x];
    }
    Tree& dfs() { return dfs(r), *this; }
    #ifdef LCA
    int lca(int u, int v) {
        if (I[u] > I[v]) swap(u, v);
        return st.F(I[u], I[v] + 1);
    }
    ll D(int u, int v) {
        return d[u] + d[v] - 2 * d[lca(u, v)];
    }
    #endif
    #ifdef CENTROID
    int cr, cp[N]{}, rem[N]{}; // cp: centroid parent
    vector<int> cg[N];
    int sz(int x, int p = -1) {
        s[x] = 0;
        for (int y : this->g[x]) if (!rem[y] && y != p) s[x] += sz(y, x);
        return ++s[x];
    }
    int decompose(int x, int n, int p = -1) {
        for (int y : this->g[x]) if (!rem[y] && y != p) {
        if (s[y] > n / 2) return decompose(y, n, x);
        }
        rem[x] = true;
        for(int y : this->g[x]) if (!rem[y]) {
        y = decompose(y, sz(y));
        cg[cp[y] = x].push_back(y);
        }
        return x;
    }
    Tree& decompose() { return cr = decompose(r, sz(r)), *this; }
    #endif

    Tree& input() { return Graph<N, T>::input(), *this; }
};
