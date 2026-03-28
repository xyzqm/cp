#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct node { int tot, sm, ones; };

struct st : array<multiset<int, greater<int>>, 2> { // split into two types of elts
    int size() { return at(0).size() + at(1).size(); }
    int sm = 0;
    array<int, 2> pop_front() {
        assert(size());
        int fst;
        if (
            at(0).size() &&
            (!at(1).size() || *at(0).begin() > *at(1).begin())
        ) fst = 0;
        else fst = 1;
        array<int, 2> val = {fst, *at(fst).begin()};
        erase(val);
        return val;
    }
    array<int, 2> pop_back() {
        assert(size());
        int lst;
        if (
            at(0).size() &&
            (!at(1).size() || *at(0).rbegin() < *at(1).rbegin())
        ) lst = 0;
        else lst = 1;
        array<int, 2> val = {lst, *at(lst).rbegin()};
        erase(val);
        return val;
    }
    void insert(array<int, 2> val) {
        at(val[0]).insert(val[1]);
        sm += val[1];
    }
    bool erase(array<int, 2> val) {
        if (!at(val[0]).count(val[1])) return false;
        at(val[0]).erase(at(val[0]).find(val[1]));
        return sm -= val[1], true;
    }
};

int ac() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> vs;
    for (auto &[a, b] : vs) cin >> a >> b;
    ranges::sort(vs, greater<>());
    st front, back; // maintain two heaps
    for (auto &[a, b] : vs) front.insert({0, a + b});
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int s, t; cin >> s >> t;
    while (t--) cout << ac() << "\n";
}
