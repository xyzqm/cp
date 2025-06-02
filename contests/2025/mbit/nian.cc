#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;

int w, sgt[4 * N];

// add 1 to [l, r)
void inc(int x, int y, int p = 1, int l = 1, int r = w) {
    if (x <= l && r <= y) ++sgt[p];
    else if (x >= r || y <= l);
    else {
        int m = (l + r) >> 1;
        inc(x, y, p << 1, l, m);
        inc(x, y, p << 1 | 1, m, r);
    }
}

int query(int i, int p = 1, int l = 1, int r = w) {
    if (l + 1 == r) return sgt[p];
    int m = (l + r) >> 1;
    return sgt[p] + (i < m ? query(i, p << 1, l, m) : query(i, p << 1 | 1, m, r));
}

void ac() {
    int n, m; cin >> n >> m >> w;
    fill(sgt, sgt + 4 * w, 0);
    vector<array<int, 3>> fw(n);
    int idx = 0; for (auto &[h, a, i] : fw) {
        cin >> a >> h;
        i = idx++;
    }
    map<int, vector<array<int, 3>>> bn;
    while (m--) {
        int y, l, r; cin >> l >> r >> y;
        bn[y].push_back({l, r, 0});
    }
    sort(fw.begin(), fw.end(), greater<>());
    for (auto &[_, v] : bn) sort(v.begin(), v.end());
    set<int> div; // current dividers
    div.insert({0, w});
    auto it = bn.rbegin();
    vector<bool> ans(n);
    set<int> tmp; int lst = -1;
    for (auto &[h, a, i] : fw) {
        if (lst != h) {
            div.insert(tmp.begin(), tmp.end());
            lst = h, tmp.clear();
        }
        while (it != bn.rend() && it->first > h) {
           int lb = 0;
           vector<array<int, 2>> b(it->second.size());
           idx = 0; for (auto &[l, r, i] : it->second) {
                i = idx++;
                lb = max(lb, *prev(div.upper_bound(r)));
                b[i][0] = r - l + 2 + lb;
                lb += r - l + 1;
            }
           reverse(it->second.begin(), it->second.end());
           int ub = w;
           for (auto &[l, r, i] : it->second) {
               ub = min(ub, *div.upper_bound(r));
               b[i][1] = ub - (r - l + 1);
               ub -= (r - l + 1);
           }
           for (auto &[l, r] : b) if (r < l) {  inc(r, l); }
           it++;
       }
       ans[i] = !query(a);
       if (!ans[i]) tmp.insert(a);
    }
    for (int x : ans) cout << x;
    cout << endl;
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
