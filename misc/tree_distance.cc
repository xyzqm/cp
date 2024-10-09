#define LCA
#define CENTROID
#include "centroid.h"
using namespace std;

const int N = 2e5 + 1;

int main() {
  int n; cin >> n;
  Tree<N, W, set<W, less<>>> t(n);
  t.input().root(1).dfs().decompose();
}
