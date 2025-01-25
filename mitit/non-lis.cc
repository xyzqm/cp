#include <bits/stdc++.h>
using namespace std;

int n, k;
int lis(vector<int> v) {
    bool w = 0;
    for (auto it = v.begin(); next(it) != v.end(); it++) if (*it > *next(it)) w = 1;
    if (k > 1 && !w) return n + 1;
    set<int> M;
    for(int x : v) {
        auto it = M.lower_bound(x);
        if(it == M.end()) M.insert(x);
        else M.erase(it), M.insert(x);
        if (M.size() > (k + 1) / 2) return n + 1;
    }
    return M.size();
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void ac() {
    cin >> n >> k;
    vector<int> v(n); for (int &x : v) cin >> x;
    v.insert(v.begin(), 0);
    int q = 250 * n / k;
    while (q--) {
        vector<int> I(1, 0);
        for (int i = k; i > 0; i--) {
            // we have i values to pick out of (I.back(), n]
            // so our current index has to be less than n - i
            I.push_back(rng() % (n - i - I.back() + 1) + I.back() + 1);
        }
        vector<int> s;
        for (int i : I) if (i) s.push_back(v[i]);
        if (lis(s) <= (k + 1) / 2) {
            cout << "YES\n";
            for (int i : I) if (i) cout << i << " ";
            cout << endl;
            return;
        }
    }
    cout << "NO\n";
}


int main() {
    int t; cin >> t;
    while (t--) ac();
}
