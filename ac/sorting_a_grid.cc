// https://atcoder.jp/contests/agc037/tasks/agc037_d
#include <iostream>
#include <algorithm>
using namespace std;
using P = pair<int, int>;
const int N = 1e2;
int n, m, v[N], A[N][N], B[N][N], C[N][N];
P mt[N];

bool kuhn(int i) {
  if (v[i]) return false;
  v[i] = true;
  for (int j = 0; j < m; j++) if (A[i][j]) {
    int I = (A[i][j] - 1) / m;
    if (mt[I].first < 0 || kuhn(mt[I].first)) return mt[I] = {i, j}, true;
  }
  return false;
}

void solve(int col) {
  fill(mt, mt + n, P{-1, -1});
  for (int i = 0; i < n; i++) {
    fill(v, v + n, 0);
    kuhn(i);
  }
  for (int i = 0; i < n; i++) {
    auto [r, c] = mt[i];
    B[r][col] = C[(A[r][c] - 1) / m][col] = A[r][c];
    A[r][c] = 0;
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> A[i][j];
  for (int i = 0; i < m; i++) solve(i);
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cout << B[i][j] << " \n"[j == m - 1];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cout << C[i][j] << " \n"[j == m - 1];
}
