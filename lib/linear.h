#pragma once
#include "constants.h"
template <typename T>
struct Line  {
  T w, b;
  T operator()(T x) { return w * x + b; }
  Line<T> operator()(Line<T> x) { return {w * x.w, w * x.b + b }; }
};
