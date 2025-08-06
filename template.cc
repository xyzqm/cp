#include <bits/stdc++.h>
using namespace std;

#define int int64_t

template <typename F>
struct BIT : vector<int> {
    F op;
    int id;
    BIT(int n, int id, F f) : vector(n + 1, id), op(f), id(id) {}
    void upd(int i, int v) { // updates index i by value v
        for (++i; i < size(); i += i & -i) at(i) = op(at(i), v);
    }

    int query(int r) { // query op([0...r))
        int v = id;
        for (; r; r -= r & -r) v = op(v, at(r));
        return v;
    }

    int walk(int v) { // find largest r s.t. op([0...r)) < v
        int r = 0, cur = id;
        for (int k = __lg(size()); v > 0 && r < size(); k--) {
            if (int nr = r + (1 << k); nr < size() && op(cur, at(nr)) < v) cur = op(cur, at(nr));
        }
        return r;
    }
};

void ac() {

}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
