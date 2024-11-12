// https://www.acmicpc.net/problem/17169
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 1;
const int inf = 1e18;
int n, l[N], d[N], v[N];

vector<int> a, b;
priority_queue<pair<int, int>> A, B;

void sync(vector<int> &v) { while (::v[v.back()]) v.pop_back(); }

void add_a() {
    int i = a.back();
    v[i] = true;
    A.push({l[i] - d[i], i});
}
void add_b() {
    int i = b.back();
    v[i] = true;
    B.push({d[i] - l[i], i});
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < 2 * n; i++) cin >> l[i] >> d[i];
    a.resize(2 * n);
    b.resize(2 * n);
    iota(a.begin(), a.end(), 0);
    iota(b.begin(), b.end(), 0);
    sort(a.begin(), a.end(), [](int i, int j) { return l[i] > l[j]; });
    sort(b.begin(), b.end(), [](int i, int j) { return d[i] > d[j]; });
    int r = 0;
    for (int i = 1; i <= n; i++) {
        for (int t = 0; t < 2; t++) {
            sync(a), sync(b);
            int w = l[a.back()], x = d[b.back()];
            int y = (A.size() ? -A.top().first : inf) + w, z = (B.size() ? -B.top().first : inf) + x;
            if (A.size() == i) w = z = inf;
            if (B.size() == i) x = y = inf;
            int del = min({w, x, y, z});
            r += del;
            if (del == w) add_a();
            else if (del == x) add_b();
            else if (del == y) {
                auto [dif, j] = A.top();
                A.pop(), B.push({-dif, j});
                add_a();
            }
            else {
                auto [dif, j] = B.top();
                B.pop(), A.push({-dif, j});
                add_b();
            }
        }
        assert(A.size() == i && B.size() == i);
        cout << r << endl;
    }
}
