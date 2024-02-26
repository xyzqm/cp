#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
// https://dmoj.ca/problem/dmopc19c7p5
#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>
using namespace std;
#define all(x) x.begin(), x.end()
#define pi pair<int, int>
using P = pair<int, int>;
using ll = long long;
const int N = 5e5 + 1;
int n, a[N], p[N];
// index of largest value <= x in v (sorted)
// if v = [1, 2, 4], ind(v, 3) would return 1
int ind(vector<int> v, int x) { 
  return upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
}
template<class T, int SZ> struct OffBIT2D {
	bool mode = 0; // mode = 1 -> initialized
	vector<pair<int, int>> todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vector<int> val; vector<T> bit; // store all BITs in single vector
	void init() { assert(!mode); mode = 1;
		int lst[SZ]; for (int i = 0; i < SZ; i++) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) {
			return a.second < b.second; });
		for (auto t : todo) for (int x = t.first; x < SZ; x += x&-x)
			if (lst[x] != t.second) lst[x] = t.second, cnt[x] ++;
		int sum = 0; for (int i = 0; i < SZ; i++) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.resize(sum); bit.resize(sum); reverse(all(todo));
		for (auto t : todo) for (int x = t.first; x < SZ; x += x&-x)
			if (lst[x] != t.second) lst[x] = t.second, val[--st[x]] = t.second;
	}
	int rank(int y, int l, int r) {
		return upper_bound(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y)
			bit[st[x]+y-1] += t; }
	void upd(int x, int y, T t) {
		if (!mode) todo.push_back({x,y});
		else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
	int QUERY(int x, int y) { T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
		return res; }
	T query(int x, int y) { assert(mode);
		T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
		return res; }
	T query(int xl, int xr, int yl, int yr) {
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};
// modeled after https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/2D%20Range%20Queries%20(15.2)/BIT2DOff%20(15.2).h
// struct BIT2D {
//   bool mode = 0; // 0 -> offline, 1 -> initialized
//   vector<P> todo;
//   vector<int> vals[N], bit[N];
//   void init() {
//     // assert(!mode);
//     // sort points by y-coordinate
//     sort(todo.begin(), todo.end(), [](P a, P b) { return a.second < b.second; });
//     for (int i = 1; i <= n; i++) vals[i].push_back(0);
//     for (auto [x, y] : todo) {
//       for (int z = x; z <= n; z += z & -z) {
//         if (vals[z].back() != y) { vals[z].push_back(y); }
//       }
//     }
//     for (int i = 1; i <= n; i++) bit[i].resize(vals[i].size());
//     mode = 1;
//   }
//   void upd(int x, int y) {
//     if (!mode) todo.push_back({x, y});
//     else {
//       for (; x <= n; x += x & -x) {
//         int z = ind(vals[x], y);
//         // assert(z && vals[x][z] == y);
//         for (; z < bit[x].size(); z += z & -z) {
//           ++bit[x][z];
//         }
//       }
//     }
//   }
//   int query(int x, int y) {
//     // assert(mode);
//     int tot = 0;
//     for (; x > 0; x -= x & -x) {
//       for (int z = ind(vals[x], y); z > 0; z -= z & -z) {
//         tot += bit[x][z];
//       }
//     }
//     return tot;
//   }
//   int query(int x1, int x2, int y1, int y2) {
//     if (x1 > x2 || y1 > y2) return 0;
//     else return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
//   }
// } bit;
OffBIT2D<int, N> bit;
signed main() {
  // cin.tie(0)->sync_with_stdio(0);
  scan(n);
  for (int i = 1; i <= n; i++) scan(a[i]);
  for (int i = 1; i <= n; i++) scan(p[i]);
  for (int i = 1; i <= n; i++) bit.upd(i, a[i], 1);
  bit.init();
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    // ans += bit.query(1, p[i], a[p[i]] + 1, n);
    // ans += bit.query(p[i], n, 1, a[p[i]] - 1);
    ans += bit.query(p[i], n) - bit.query(p[i], a[p[i]]);
    ans += bit.query(n, a[p[i]] - 1) - bit.query(p[i], a[p[i]] - 1);
    printf("%lld\n", ans);
    bit.upd(p[i], a[p[i]], 1);
  }
  return 0;
}