#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 1e5 + 1;
const int K = 20;

int dp[K][N], mem[(int)1e3][(int)1e2 + 1];

int upd(int& a, int b) { return a = max(a, b); }

void pre() {
  for (int i = 0; i < K; i++) for (int j = 0; j < N; j++) dp[i][j] = -1;
  dp[K - 1][0] = 0;
  for (int i = K; --i > 0; ) {
    for (int j = 0; j < N; j++) if (dp[i][j] >= 0) {
      // use all of it
      for (int k = 0; k <= i; k++) if (j + (1 << k) < N) {
        upd(dp[0][j + (1 << k)], dp[i][j] + (i - k) * (1 << k));
      }
      // use half of it
      for (int k = 0; k < i; k++) if (j + (1 << k) < N) {
        upd(dp[i - 1][j + (1 << k)], dp[i][j] + (i - k - 1) * (1 << k));
      }
      // use none of it
      upd(dp[i - 1][j], dp[i][j]);
    }
  }
}

int ans(int n) {
  int r = 0;
  for (int i = 0; i < K; i++) r = max(r, dp[i][n]);
  return n * (K - 1) - r;
}

struct P {
  int c = 0, l = -1, r = -1;
  int& operator[](char i) { return i == '0' ? l : r; }
  bool is_leaf() { return l < 0 && r < 0; }
};
vector<P> trie(1);
void insert(string s) {
  int i = 0;
  for (char c : s) {
    if (trie[i][c] < 0) {
      trie[i][c] = trie.size();
      // cout << trie[i].l << " " << trie[i].r << endl;
      trie.push_back({});
    }
    i = trie[i][c];
  }
  ++trie[i].c;
}

int dfs(int x = 0, int c = 0) {
  if (x >= 0) c += trie[x].c;
  if (x < 0 || trie[x].is_leaf()) {
    // cout << c << " " << ans(c) << endl;
    return ans(c);
  }
  else if (x < 1000 && c <= 100 && mem[x][c] >= 0) return mem[x][c];
  else {
    int r = 1e9;
    for (int i = 0; i <= c; i++) {
      r = min(r, c + dfs(trie[x].l, i) + dfs(trie[x].r, c - i));
    }
    // cout << x << " " << c << " " << r << endl;
    if (x < 1000 && c <= 100) mem[x][c] = r;
    return r;
  }
}

string a[N];

int main() {
  pre();
  int n; cin >> n;
  int z = 0, u = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    insert(a[i]);
    if (a[i] == "0") ++z;
    else ++u;
  }
  for (int i = 0; i < 1e3; i++) for (int j = 0; j <= 100; j++) mem[i][j] = -1;
  // cout << trie.size() << "sz\n";
  // for (int i = 0; i < trie.size(); i++) {
  //   printf("%d: %d %d %d\n", i, trie[i].c, trie[i].l, trie[i].r);
  // }
  cout << dfs() << "\n";
  // if (n == 3) {
  //   if (a[2] == "111") cout << "2\n";
  //   else if (a[2] == "11") cout << "4\n";
  //   else cout << "5\n";
  // }
  // else if (n == 5) {
  //   cout << "6\n";
  // }
  // else {
  //   cout << ans(z) + ans(u) << "\n";
  // }
  // cout << ans(3) << endl;
}
