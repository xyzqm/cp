// https://oj.uz/problem/view/NOI18_safety
#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    int n; ll k, dl = 0, dr = 0, mn = 0;
    cin >> n >> k;
    // {l} + dl and {r} + dr store points at which slope changes
    multiset<ll> l, r;
    for (int i = 0; i < n; i++) {
        ll s; cin >> s;
        if (l.size() && s < *l.rbegin() + dl) {
            l.insert({s - dl, s - dl}); // insert value twice
            r.insert(*l.rbegin() + dl - dr);
            mn += *l.rbegin() + dl - s;
            l.erase(--l.end());
        }
        else if (r.size() && s > *r.begin() + dr) {
            r.insert({s - dr, s - dr}); // insert value twice
            l.insert(*r.begin() + dr - dl);
            mn += s - *r.begin() - dr;
            r.erase(r.begin());
        }
        else l.insert(s - dl), r.insert(s - dr);
        dl -= k, dr += k;
    }
    cout << mn << endl;
}

