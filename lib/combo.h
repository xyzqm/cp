#pragma once
#include "constants.h"
#include "mint.h"
using namespace std;

template <int A, int M>
struct Combo {
  mint F[A], F_i[A];
  Combo() { F[0] = F_i[0] = 1; for (int i = 1; i < A; i++) F_i[i] = (F[i] = F[i - 1] * i).inv(); }
  mint C(int n, int k) { return n < k ? 0 : F[n] * F_i[n - k] * F_i[k]; }
};
