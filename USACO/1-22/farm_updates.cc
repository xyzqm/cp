// http://www.usaco.org/index.php?page=viewproblem2&cpid=1186
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e5 + 1;
const int Q = 2e5;
vector<int> adj[N];
bool removed[Q], relevant[N];
int n, q, ans[N];
void mark_cmp_relevant(int x) {
    relevant[x] = true;
    ans[x] = q;
    for (int y : adj[x]) 
        if (!relevant[y]) mark_cmp_relevant(y);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    fill(relevant + 1, relevant + n + 1, true);
    vector<pii> added;
    vector<pii> rev;
    for (int i = 0; i < q; i++) {
        char op; cin >> op;
        int x, y;
        if (op == 'A') {
            cin >> x >> y;
            added.push_back({x, y});
            rev.push_back({-1, -1}); // dummy
        } else if (op == 'R') {
            cin >> x;
            rev.push_back(added[x - 1]);
            removed[x - 1] = true;
        } else {
            cin >> x;
            rev.push_back({0, x});
            relevant[x] = false;
        }
    }
    for (int i = 1; i <= n; i++) if (relevant[i]) ans[i] = q;
    for (int i = 0; i < added.size(); i++) {
        if (removed[i]) continue;
        auto [a, b] = added[i];
        if (!relevant[a]) swap(a, b);
        if (relevant[a] && !relevant[b]) mark_cmp_relevant(b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    while (q--) {
        auto [a, b] = rev[q];
        if (a == 0) {
            if (!relevant[b]) mark_cmp_relevant(b);
        } else if (a != -1) {
            if (!relevant[a]) swap(a, b);
            if (relevant[a] && !relevant[b]) mark_cmp_relevant(b);
            adj[a].push_back(b); adj[b].push_back(a);
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
}