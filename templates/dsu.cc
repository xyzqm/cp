struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return 1;
    }
};

// with info
struct info {
    int fa = -1; // MANDATORY FIELD---fa < 0 stores -sz
    int rem = 0; // unpaired
    int operator+=(info &o) {
        if (this == &o) return 0;
        return rem += o.rem;
    }
};

struct dsu : vector<info> {
    using vector::vector;
    int rep(int x) { return at(x).fa < 0 ? x : at(x).fa = rep(at(x).fa); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    int join(int x, int y) {
        x = rep(x), y = rep(y);
        if (at(x).fa > at(y).fa) ::swap(x, y);
        if (x != y) at(x).fa += at(y).fa, at(y).fa = x;
        return at(x) += at(y);
    }
};
