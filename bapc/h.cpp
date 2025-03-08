#include <bits/stdc++.h>
using namespace std;

int highB(int x){
  int res = 0;
  while (x>=2){
    res ++;
    x/=2;
  }
  return res;
}

void solve() {
  int n,x;
  string s;
  cin >> n >> x;
  cin >> s;

  for (auto c : s){
    int curB = highB(x);
    int numBelow = ((n&(~((1<<curB)-1))) >> curB)-1;
    if ((x-(1<<curB)) <= (n & ((1<<curB)-1))) {
      //cout << "leq\n";
    } else {
      //cout << "gt\n";
      numBelow --;
    }
    //cout << n << " " << x << " " << numBelow << '\n';
    if (c=='L') {
      if (numBelow % 2 == 0) {
        x += (1<<(curB+1));
      } else {
        x -= (1<<curB);
        x += (1<<(curB+1));
      }
    } else if (c=='R') {
      if (numBelow % 2 == 0) {
        x -= (1<<curB);
        x += (1<<(curB+1));
      } else {
        x += (1<<(curB+1));
      }
    } else {
      if (x==1) {
        cout << "-1\n";
        return;
      } else {
        int oX = x;
        x = (1<<(curB-1))+(((1<<(curB-1))-1)&x);
        //cout << "before " << oX << " after " << x << endl;
      }
    }

    if (x>n){
      cout << "-1\n";
      return;
    }
  }
  cout << x <<endl;
}

int32_t main() {
  int q;
  cin >> q;
  for (int i = 0;i<q;i++) {
    solve();
  }
}