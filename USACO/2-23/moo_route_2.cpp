#include <bits/stdc++.h>
using namespace std;
struct edge {
    int r, s, dest;
    edge(int r, int s, int dest) : r(r), s(s), dest(dest) {}
};
bool cmp(edge a, edge b) { return a.r > b.r; }
const int N = 2e5 + 1;
vector<edge> adj[N]; // sorted in descending order of arrival
int a[N]; // layover
int e[N]; // index of first unprocessed edge of node i
int t[N]; // earliest time to arrive at node i
void dfs(int x) {
    while (e[x] < adj[x].size()) {
        edge cur = adj[x][e[x]];
        if (cur.r < t[x] + a[x]) break; // impossible to use this edge
        if (cur.s < t[cur.dest]) {
            t[cur.dest] = cur.s;
            e[x]++;
            dfs(cur.dest);
        }
        else e[x]++;
    }
}
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, r, y, s; cin >> x >> r >> y >> s;
        adj[x].push_back(edge(r, s, y));
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; 
        sort(adj[i].begin(), adj[i].end(), cmp);
        t[i] = INT_MAX;
    }
    t[1] = -a[1]; dfs(1);
    for (int i = 1; i <= n; i++) {
        if (t[i] == INT_MAX) cout << "-1\n";
        else if (i == 1) cout << "0\n";
        else cout << t[i] << "\n";
    }
}