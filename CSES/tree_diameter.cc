#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 1;
vector<int> adj[N];
int ans = 0;
int dfs(int x, int p) {
    int A = 0, B = 0;
    for (int y : adj[x]) {
        if (y == p) continue;
        int a = dfs(y, x);
        if (a + 1 > A) B = A, A = a + 1;
        else B = max(B, a + 1);
    }
    ans = max(ans, A + B);
    return A;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    cout << ans << endl;
}