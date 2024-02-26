#include <iostream>
#include <set>
using namespace std;
using pii = pair<int, int>;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int X, n;
    cin >> X >> n;
    multiset<int> len;
    set<pii> r;
    r.insert({0, X});
    len.insert(X);
    int x;
    auto add = [&](int a, int b) { 
        r.insert({a, b});
        len.insert(b - a);
    };
    for (int i = 0; i < n; i++) {
        cin >> x;
        auto it = prev(r.upper_bound({x, 0}));
        add(it->first, x);
        add(x, it->second);
        len.erase(len.find(it->second - it->first));
        r.erase(it);
        cout << *len.rbegin() << " ";
    }
    cout << endl;
}