#pragma once
#include "constants.h"
#include <utility>
#include <cassert>
#include <iostream>
using namespace std;
#ifdef SQRT
template <int M>
struct mint;
template <int M>
using P = pair<mint<M>, mint<M>>;
#endif
template <int M>
struct mint {
    ll v = 0;
    mint() {}
    mint(ll v) { this->v = (v % M + M) % M; }
    mint operator+(const mint &o) const { return v + o.v; }
    mint& operator+=(const mint& o) { v = (v + o.v) % M; return *this; }
    mint operator*(const mint &o) const { return v * o.v; }
    mint& operator*=(const mint& o) { v = (v * o.v) % M; return *this; }
    mint operator-(const mint &o) const { return v - o.v; }
    mint& operator-=(const mint& o) { mint t = v - o.v; v = t.v; return *this; }
    mint exp(int y) const { mint r = 1, x = v; for (y <<= 1; y >>= 1; x = x * x) if (y & 1) r = r * x; return r; }
    mint operator/(mint o) { return *this * o.inv(); }
    mint inv() const { assert(v); return exp(M - 2); }
    #ifdef SQRT
    mint sym() { return *this ^ (M - 1) / 2; } // legendre symbol: 1 -> qresidue, -1 -> non-residue
    #endif
    friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
    friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
    #ifdef SQRT
    mint sqrt() {
    if (!v) return 0;
    mint i = 1;
    while ((i * i - v).sym().v != M - 1) i = i + 1;
    mint w = i * i - v;
    auto mul = [&](P<M> x, P<M> y) { return P<M>{
        x.first * y.first + x.second * y.second * w,
        x.first * y.second + x.second * y.first
    }; };
    P<M> c = {i, 1}, r = {1, 0};
    for (int i = 1; i < 2 * M; i <<= 1) {
        if (((M + 1) / 2) & i) r = mul(r, c);
        c = mul(c, c);
    }
    assert(r.second.v == 0 && (r.first * r.first).v == v);
    if (r.first.v < M / 2) return r.first;
    return r.first * -1;
    }
    #endif
};
#define mint mint<M>
