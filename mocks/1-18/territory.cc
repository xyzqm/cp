#include <bits/stdc++.h>
#define int int64_t
using namespace std;

using R = pair<int, int>;
map<pair<int, int>, vector<R>> mp;

int dx, dy, k;
void add(int x, int y) {
    int z = dy ? y / dy : 0;
    if (dy && y - z * dy < 0) --z;
    mp[{x - z * dx, y - z * dy}].push_back({z, z + k});
    if (y - z * dy == 0) { // also want to add copy at dy for convenience
        --z, mp[{x - z * dx, y - z * dy}].push_back({z, z + k});
    }
}

// make ranges disjoint
void process(vector<R> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<R> q;
    for (auto [l, r] : v) {
        if (q.size() && q.back().second >= l) {
            int l = q.back().first; q.pop_back();
            q.push_back({l, r});
        }
        else q.push_back({l, r});
    }
    v.resize(q.size());
    copy(q.begin(), q.end(), v.begin());
}

vector<R> isect(vector<R> a, vector<R> b) {
    int A = 0, B = 0;
    vector<R> c;
    while (A < a.size() && B < b.size()) {
        if (a[A].first > b[B].first) swap(A, B), a.swap(b);
        if (b[B].first < a[A].second) {
            if (b[B].second < a[A].second) c.push_back(b[B++]);
            else c.push_back({b[B].first, a[A++].second});
        }
        else A++;
    }
    return c;
}


int32_t main() {
    int n; cin >> n >> k;
    string s; cin >> s;
    vector<R> p = {{0, 0}};
    for (char c : s) {
        if (c == 'N') ++dy;
        if (c == 'S') --dy;
        if (c == 'E') ++dx;
        if (c == 'W') --dx;
        p.push_back({dx, dy});
    }
    if (!dy) {
        swap(dx, dy);
        for (auto &[x, y] : p) swap(x, y);
    }
    if (!dy) k = 1; // dx = dy = 0
    if (dy < 0) {
        dx = -dx, dy = -dy;
        for (auto &[x, y] : p) x = -x, y = -y;
    }
    for (auto [x, y] : p) add(x, y);
    for (auto &[_, v] : mp) process(v);
    int t = 0;
    for (auto &[c, v] : mp) {
       auto [x, y] = c; // check if this can be bottom left corner
       if (!mp.count({x, y + 1}) || !mp.count({x + 1, y}) || !mp.count({x + 1, y + 1})) continue;
       vector<R> r = isect(isect(v, mp[{x, y + 1}]), isect(mp[{x + 1, y}], mp[{x + 1, y + 1}]));
       for (auto [a, b] : r) t += b - a;
    }
    cout << t << endl;
}
