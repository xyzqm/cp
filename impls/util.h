#pragma once
#include <vector>
#include <set>
using namespace std;

template <typename T>
void add(vector<T> &v, T x) { v.push_back(x); }
template <typename T>
void add(set<T> &v, T x) { v.insert(x); }

template <typename T>
void erase(vector<T> &v, T x) { v.erase(find(v.begin(), v.end(), x)); }
template <typename T>
void erase(set<T> &v, T x) { v.erase(x); }

