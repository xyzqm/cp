#include <cassert>
#include <vector>
#include "message.h"
using namespace std;

void send_message(vector<bool> M, vector<bool> C) {
  vector<int> x;
  for (int i = 0; i < 31; i++) if (!C[i]) x.push_back(i);
  assert(x.size() == 16);
  vector<vector<bool>> c(31);
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < x[i + 1] - x[i]; j++) c[x[i]].push_back(0);
    c[x[i]].back() = 1;
  }
  for (int i = 0; i < x[0] + 31 - x.back(); i++) c[x.back()].push_back(0);
  c[x.back()].back() = 1;
  M.push_back(!M.back());
  while (M.size() <= 1024) M.push_back(M.back());
  auto it = x.begin();
  for (bool y : M) {
    if (c[*it].size() == 66) ++it;
    c[*it].push_back(y);
  }
  for (int i = 0; i < 66; i++) {
    vector<bool> a;
    for (int j = 0; j < 31; j++) a.push_back(!C[j] && c[j][i]);
    send_packet(a);
  }
}

vector<bool> receive_message(vector<vector<bool>> R) {
  vector<int> x(31, 1);
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 66 && !R[j][i]; j++) ++x[i];
  }
  auto nx = [&](int i) { return (i + x[i]) % 31; };
  vector<bool> r;
  vector<int> g;
  for (int i = 0; i < 31; i++) {
    g = {i};
    while (g.size() < 16 && nx(g.back()) != i) g.push_back(nx(g.back()));
    if (g.size() == 16 && nx(g.back()) == i) break;
  }
  assert(g.size() == 16 && nx(g.back()) == g[0]);
  for (int i : g) {
    for (int j = x[i]; j < 66; j++) r.push_back(R[j][i]);
  }
  bool b = r.back();
  while (r.back() == b) r.pop_back();
  return r;
}
