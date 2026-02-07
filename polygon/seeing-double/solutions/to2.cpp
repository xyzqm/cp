#include "bits/stdc++.h"
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")
#define fast ios_base::sync_with_stdio(0) , cin.tie(0) , cout.tie(0)
#define endl '\n'
#define int long long
#define f first
#define s second
using namespace std;

struct BIT{
   vector <int> ft;
   int n;
   void build(int N){ft = vector<int>(N + 5, 0); n = N;}
   void update(int x, int v){while(x <= n) ft[x] += v, x += (x & -x);}
   int query(int x){return x > 0 ? ft[x] + query(x-(x & -x)) : 0;}
};

int CountSteps(string s1, string s2, int size)
{
    int i = 0, j = 0;
    int result = 0;

    // Iterate over the first string and convert
    // every element equal to the second string
    while (i < size) {
        j = i;

        // Find index element of first string which
        // is equal to the ith element of second string
        while (s1[j] != s2[i]) {
            j += 1;
        }

        // Swap adjacent elements in first string so
        // that element at ith position becomes equal
        while (i < j) {

            // Swap elements using temporary variable
            char temp = s1[j];
            s1[j] = s1[j - 1];
            s1[j - 1] = temp;
            j -= 1;
            result += 1;
        }
        i += 1;
    }
    return result;
}

void ac(){
   string str; cin >> str;
   int n = str.size();
   BIT bit; bit.build(n + 5);
   str = ' ' + str;
   int cnt[26], tot[26];
   for(int i = 0; i < 26; i++) cnt[i] = tot[i] = 0;
   for(int i = 1; i <= n; i++) cnt[str[i] - 'a']++;
   int ans = 0;
   vector <int> v, b;
   for(int i = 1; i <= n; i++){
      int c = str[i] - 'a';
      tot[c]++;
      if(tot[c] > cnt[c]/2) bit.update(i, 1), b.push_back(c);
      else ans += bit.query(i), v.push_back(c);
   }
   string s1, s2;
   for(int i = 0; i < v.size(); i++) s1 += (char)(v[i] + 'a');
   for(int i = 0; i < b.size(); i++) s2 += (char)(b[i] + 'a');
   // cout << ans << endl;
   // cout << s1 << endl << s2 << endl;
   ans += CountSteps(s1, s2, v.size());
   cout << ans << endl;
}

signed main()
{
   fast;
   int t; cin >> t;
   while(t--) ac();
}
