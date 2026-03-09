# HPI 2026 Editorial

Thank you to everyone who attended this year's Harker Programming Invitational (HPI)! [Novice](https://codeforces.com/gym/106410) and [Advanced](https://codeforces.com/gym/106409) problems have been uploaded to the Gym for upsolving.

*Note:* Only solutions for the Advanced division are presented here, but solutions for Novice-only problems (Yash is Cross-Eyed, Repetition, Skills) can be provided upon request.

## Harker!!

<spoiler summary="Solution">
Pretty straightforward: most languages have a standard library function for finding a given substring in a string, so you can just use that.
</spoiler>

<spoiler summary="Code (Team Aarav)">
```python
def solution(s):
    if "harker" in s:
        return 1
    return 0
    
T = int(input())
 
for _ in range(T):
    s = input()
    print(solution(s))
```
</spoiler>

## String Runs

<spoiler summary="Solution">
Observe that when concatenating strings $a$ and $b$, $|f(a + b)| = |f(a)| + |f(b)|$ unless the last character of $a$ equals the first character of $b$, in which case $|f(a + b)| = |f(a)| + |f(b)| - 1$. Therefore, for each string $w_i$, we only need to maintain three values: its first character, last character, and $|f(w_i)|$.
</spoiler>

<spoiler summary="Code (eevee0)">
```python
mod = int(1e9+7)
t = int(input())
for _ in range(t):
    ans = []
    n = int(input())
    w = []
    for i in range(n):
        a = input().split()
        if a[0] == "1":
            s = a[1]
            count = 1
            for j in range(1, len(s)):
                if s[j] != s[j-1]:
                    count += 1
                    count %= mod
            w.append([count, s[0], s[-1]])
            ans.append(count)
        else:
            for j in range(len(a)): a[j] = int(a[j])
            cur = w[a[2]-1][0]
            if a[1] == 1:
                ans.append(w[a[2]-1][0])
            else:
                for j in range(3, len(a)):
                    cur += w[a[j]-1][0]
                    if w[a[j-1]-1][2] == w[a[j]-1][1]: cur -= 1
                    cur %= mod
                ans.append(cur)
            w.append([cur, w[a[2]-1][1], w[a[-1]-1][-1]])
    print(' '.join(map(str, ans)))
```
</spoiler>

*Prepared by [user:TheYashB,2026-03-09]*

## Reverse Suffix

<spoiler summary="Hint 1">
How can we get the first character of $a$ to match the first character of $b$ in 2 operations?
</spoiler>

<spoiler summary="Hint 2">
Can we apply this to the remaining indices?
</spoiler>

<spoiler summary="Solution">
If we want to make $a_1$ match $b_1$, we can use the following procedure:

1. Find an $i$ such that $a_i = b_1$. After operating on index $i$, $a_n$ will equal $b_1$.
2. Operate on index $1$, which reverses the entire string. Now, we have that $a_1 = b_1$.

Similar logic follows for the other indices. In particular, if we already have $a_j = b_j$ for all $j < i$ and we want to get $a_i = b_i$, we do the following:

1. Find a $j \geq i$ such that $a_j = b_i$. Operate on index $j$.
2. Operate on index $i$.

We perform these pairs of operations at most $n$ times, so we use at most $2n$ operations in total, which is sufficient to solve the problem. Note that this also means that the transformation is possible iff the multisets of characters in $a$ and $b$ are equal.
</spoiler>

<spoiler summary="Code (Team Aarav)">
```python
def solution(N, a, b):
    sequences = []
    for i in range(N):        
        found = -1
        for j in range(i, N):
            if a[j] == b[i]:
                sequences.append(j + 1)
                sequences.append(i + 1)
                
                a = a[0:j] + "".join(reversed(a[j:]))
                a = a[0:i] + "".join(reversed(a[i:]))
                found = j
                break
        
        if found == -1:
            return -1
    
    return sequences
 
N = int(input())
a = input()
b = input()
 
ans = solution(N, a, b)
if ans == -1:
    print(-1)
else:
    l = len(ans)
    print(l)
    for i in range(l):
        print(ans[i])
```
</spoiler>

*Prepared by [user:TheYashB,2026-03-09]*

## Regina's Task

<spoiler summary="Hint">
With $b$ and $c$ fixed, how many $(a, d)$ pairs do you really have to check?
</spoiler>

<spoiler summary="Solution">
Let's fix $(b, c)$. If there are no options for $a$ or $d$, it's clearly impossible. Otherwise, if there are at least two options for either $a$ or $d$, it's always possible. If not, there is exactly one option for both $a$ and $d$, so we can just check this manually. Therefore, we do a constant amount of work for each $(b, c)$ pair, and the number of $(b, c)$ pairs is bounded by the number of edges. Therefore, the problem is solved in $\mathcal{O}(n + m)$.

**Note**: For ease of implementation, we can just find up to two candidates for both $a$ and $b$, then brute force all pairs.
</spoiler>

<spoiler summary="Code (shsh)">
```python
import itertools
 
n, m = map(int, input().split())
g = [[] for _ in range(n + 1)]
edges = []
 
for _ in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)
    edges.append((u, v))
 
for (b, c) in edges:
    opt_a, opt_d = [], []
    for u in g[b]:
        if len(opt_a) > 1: break
        if u != c: opt_a.append(u)
    for u in g[c]:
        if len(opt_d) > 1: break
        if u != b: opt_d.append(u)
 
    for (a, d) in itertools.product(opt_a, opt_d):
        if a != d:
            print(a, b, c, d, sep="\n")
            quit()
print(-1)
```
</spoiler>

*Prepared by [user:andrewgopher,2026-03-09]*

## Tung Tung String

<spoiler summary="Solution">

First, familiarize yourself with the concept of inversions, which are used to solve the following problem:

> Given a permutation $p$ of length $n$, find the minimum number of adjacent swaps to sort it.

It turns out that the minimum number of swaps is precisely the number of pairs of indices $(i, j)$ such that $i < j$ and $p_i > p_j$: in other words, the number of pairs of indices whose paths must "cross", i.e. inversions.

![inversions](https://hackmd.io/_uploads/HyCR-vqKbe.png)

_Here, the five inversions of $p = [4, 2, 3, 1]$ are marked in red._

It's not difficult to show that swapping an adjacent inversion (e.g. indices $(1, 2)$ or $(3, 4)$) removes exactly one inversion. However, a less commonly utilized fact is that swapping **any inversion** will decrease the total number of inversions. For instance, swapping $1$ and $4$ in the example above would decrease the number of inversions to 0.

Now, we return to the problem of Tung Tung String. Some preliminary notation:
- Let $|s| = 2n$.
- Let $(0, i)$ denote position $i$, and $(1, i)$ denote position $i + n$.

Then, note that if a character appears $2k$ times, we must move $k$ occurrences to $(0, i_1), (0, i_2), ... ,(0, i_k)$ and the other $k$ to $(1, i_1), (1, i_2), ... , (1, i_k)$. Also note that if we move index $x$ to $(0, ?)$ and index $y$ to $(1, ?)$ and $y > x$, it's always optimal to move $y$ to $(0, ?)$ and $x$ to $(1, ?)$ instead, since this uncrosses an inversion. Therefore:
> We should move the first $k$ occurrences of each character to the first half of $s$, and the last $k$ occurrences of each character to the second half of $s$.

After performing these moves, $s$ will something like `"acbd|cadb"`, where the two halves of the string are anagrams. The problem then reduces to the following:
> You are given two strings, and in one operation you are allowed to perform an adjacent swap in **exactly one of the two strings**. Find the minimum number of operations required to make the two strings equal.

For instance in the case of $s =$ `"acbd|cadb"`, the two strings would be `"acbd"` and `"cadb"`. We now make a crucial observation: there always exists an optimal solution which **never operates on the first string at all.**

**Proof:** Let the two strings be $s_1$ and $s_2$, and let's say we want to transform both strings into $t$. Then, if we let $I(s, t)$ denote the number of inversions between strings $s$ and $t$, the total required number of operations is $\Sigma = I(s_1, t) + I(s_2, t)$. For now, assume each character appears at most once in either string, and consider a pair of characters $(a, b)$:
- If $a$ appears before $b$ in both strings, we want $a$ to appear before $b$ in $t$ as well, as this would contribute $0$ to $\Sigma$.
- Similar if $a$ appears after $b$ in both strings.
- Otherwise, no matter how $a$ and $b$ are ordered in $t$, **exactly $1** inversion will be contributed to $\Sigma$. Therefore, we can order these two characters however we want.

To finish, note that one way to satisfy all of the above requirements is just to set $t = s_1$ or $t = s_2$!

**Note:** It's not difficult to generalize this to cases in which characters may appear more than once, as we can simply relabel the $i$th occurrence of $a$ in all strings as $a_i$ and consider all $a_i$ as distinct. This labelling is optimal as it ensures there are no inversions between identical characters.
</spoiler>

<spoiler summary="TL;DR">
1. First, we assign $0/1$ to every character: $0$s to the first $k$ occurrences of each character, and $1$s to the last $k$. Then, we count the number of swaps required to move all $0$s to the first half of the string and all $1$s to the second half.
2. Then, we find the number of swaps required to make the second half of the string equal to the first.

> Note that this problem is NP-Hard if we want $s = t + t + t$ instead. Indeed, that would reduce to the 3-wise [Kemeny problem](https://en.wikipedia.org/wiki/Kemeny_method) (make **3** strings equal via adjacent swaps) which is substantially more difficult than the 2-wise version we just solved.
</spoiler>

<spoiler summary="Code (shsh)">
``` cpp
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) + 1;
    }
    int query(int r) {
        int res = 0;
        for (; r; r -= r & -r) res = res + at(r);
        return res;
    }
};

int ac() {
    string s; cin >> s;
    vector<int> frq(26);
    for (char c : s) ++frq[c - 'a'];
    for (int &x : frq) {
        assert(!(x % 2));
        x >>= 1;
    }
    vector<int> mp(s.size());
    vector<queue<int>> pos(26);
    int half = s.size() / 2, fst = 0;
    for (int i = 0; i < s.size(); i++) {
        if (pos[s[i] - 'a'].size() == frq[s[i] - 'a']) {
            mp[i] = pos[s[i] - 'a'].front() + half;
            pos[s[i] - 'a'].pop();
        }
        else mp[i] = fst++;
        pos[s[i] - 'a'].push(mp[i]);
    }
    bit fen(s.size());
    int inv = 0;
    for (int x : mp) {
        inv += fen.query(s.size() - 1 - x);
        fen.upd(s.size() - 1 - x, 1);
    }
    return inv;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << "\n";
}
```
</spoiler>

*Prepared by [user:shsh,2026-03-09]*

## Pace Pushers


<spoiler summary="Solution">
Let a *mini-step* represent an update in which we only increment a *single* incrementable beacon rather than all of them simultaneously, which we will just refer to as a *full-step*. We claim that running *mini-steps* until convergence will yield the same result as running normal *full-steps* until convergence.

To do this, we will show two claims:
1. Performing $n$ mini-steps does not yield greater powers than performing $n$ full-steps.
2. If we obtain powers $p_i$ after performing $n$ full-steps, there exists an integer $n' \geq n$ such that *any sequence* of $n'$ mini-steps yields $p'_i \geq p_i$.

Both claims can be proved by induction. Now, let $n$ be the number of *full-steps* required to reach convergence, and also define the corresponding $n'$ so that running $n'$ mini-steps yields $p'_i \geq p_i$. However, we also know that $p_i$ after $n'$ steps the same as $p_i$ after $n$ steps, therefore we also have that $p'_i \leq p_i$ by Claim 1. Therefore, $p_i' = p_i$.   

To simulate efficiently, we can maintain a sorted list of the disjoint ranges currently covered, as well as the power of each range. When we perform a mini-step, we merge one range into another, and since each range is merged only once, we only need to perform $\mathcal{O}(N)$ merges.

Because we have to sort by position initially, time complexity is $\mathcal{O}(N \log N)$.
</spoiler>

<spoiler summary="Code (AksLolCoding)">
```python
n = int(input())
a = []
for i in range(n):
	x, p = map(int, input().split())
	a.append((x, p))
a.sort(key=lambda i: i[0])
b = []
def merge():
	if len(b) < 2:
		return False
	l1 = b[-1][0] - b[-1][2]
	r2 = b[-2][1] + b[-2][2]
	if l1 > r2:
		return False
	a1 = b.pop()
	a2 = b.pop()
	b.append((a2[0], max(a1[1], a2[1]), max(a1[2], a2[2])))
	return True
 
for x,p in a:
	b.append((x, x, p))
	while merge():
		pass
 
ans = 0
for l, r, p in b:
	ans += r - l + 2 * p + 1
 
print(ans)
```
</spoiler>

*Prepared by [user:noodlesoodles,2026-03-09]*

## Skating with Alysa Liu

<spoiler summary="Hint 1">
Invariant?
</spoiler>

<spoiler summary="Hint 2">
Can you derive a necessary and sufficient condition for whether it's possible to transform $a$ into some array $a'$?
</spoiler>


<spoiler summary="Solution">
Let $S_i$ denote the set of indices $j$ such that $j \equiv i \bmod k$. Then, note that each operation operates on exactly one index in each of $S_0, S_1, ..., S_{k - 1}$. Therefore, the total amount added to each group is constant. Hence, if $\Sigma_i$ and $\Sigma_i'$ denote the initial and final sums of group $S_i$ respectively, then it is necessary that $(\Sigma_i' - \Sigma_i) \bmod m$ is equal for all $i$. 

Notably, this condition is sufficient. If we consider a final array $a'$ which satisfies this property, we can always transform $a$ into $a'$ by operating index $1$ until $a_1 = a'_1$, index $2$ until $a_2 = a'_2$, ... etc. until index $n - k + 1$, after which the above property guarantees the remaining $k - 1$ unoperated indices are equal.

Therefore, let's fix the common difference $d = (\Sigma_i' - \Sigma_i) \bmod m$, which in turn fixes $\Sigma_i'$ for each group. This leads to the next important observation:
> If $\Sigma \bmod m$ for a group is fixed, we can maximize the sum for that group by setting all but one value to $m - 1$.

**Proof**: If there exist two values not equal to $m - 1$, consider increasing one to $m - 1$ and decreasing the other so the sum remains unchanged. If the decreased value goes below $0$, we can add $m$ to it, and therefore $\Sigma$ increases. Otherwise, $\Sigma$ remains the same.

Finally, we can note that in addition, at least one group must have *all values* equal to $m - 1$. Otherwise, we can just increment every group by 1 and obtain a strictly larger sum. Therefore, we can just iterate over which group is all $m - 1$ and calculate the corresponding sum. This can be done in $\mathcal{O}(n + k \log k)$ time.
</spoiler>

<spoiler summary="Code (shsh)">
```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define int int64_t
 
void ac() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> sms(k);
    for (int i = 0, v; i < n; i++) {
        cin >> v;
        sms[i % k] += v - (m - 1);
    }
    for (int &sm : sms) {
        sm %= m;
        if (sm < 0) sm += m;
    }
    ranges::sort(sms);
    int res = 0;
    for (int i = k, ad = 0, cur = accumulate(sms.begin(), sms.end(), 0LL); i --> 0; ) {
        cur += k * (m - 1 - sms[i] - ad);
        res = max(res, cur);
        ad = m - sms[i], cur += k - m;
    }
    cout << res + (n - k) * (m - 1) << "\n";
}
 
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
```
</spoiler>

*Prepared by [user:TheYashB,2026-03-09]* 

## Looksmaxxing with Clavicular

For concision, I will use the term "good stream" to refer to a stream which stream-mogs Clavicular.

<spoiler summary="Hint">
Consider which positions are possible for the end of a *good stream*.
</spoiler>

<spoiler summary="Solution">
First, note that all good streams must end with $a_i = k$. Also note that if $a_i = k - v$, the next $v - 1$ indices *cannot* end a good stream. Also, the first $k - 1$ indices are trivially eliminated. With these preliminaries, we can now move to finding the maximum and minimum possible value of $x$.

Observe that sorting $a$ produces a maximal configuration. This is because if we have $a_i > a_{i + 1}$, we will definitely not eliminate more values by swapping these two. 

In a minimal configuration, we want as many elements $k - v$ to delete $v - 1$ $k$s as possible. For instance, if $k = 4$, a minimal configuration may look something like
```
4 4 4 1 4 4 2 4 3
```

Now comes the most important observation: *we can achieve **all $x$** between the minimum and maximum feasible values.*

One elegant way to achieve this is the following. Start from the maximum configuration, i.e. sort $a$. Also, let $x_e$ denote the number of ending positions which are eliminated *solely* by element $e$. Then, for each element $e = k - v$ from right to left, move $e$ to the rightmost index before the one at which $x_e$ would drop below $v - 1$. It can be shown that with each movement of $e$ to the right, the number of good streams either stays the same or decreases by 1. Therefore, we can just repeat this until we hit exactly $x$ good streams. With some care, this can be implemented in $\mathcal{O}(n \log n)$.  
</spoiler>

<spoiler summary="Code (shsh)">
```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define int int64_t
 
int cnt_k_good(const std::vector<int>& a, int k) {
    int rt = k - 1, tot = 0; // rightmost possible point
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] == k) tot += rt <= i;
        else rt = max(rt, i + k - a[i]);
    }
    return tot;
}
 
vector<int> ac() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> vals(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vals[i];
    }
    ranges::sort(vals);
    vector<int> rt(n + 1);
    int fst = rt[0] = k; // first ending index
    for (int i = 1; i <= n; i++) {
        if (vals[i] < k) fst = max(fst, i + k - vals[i]);
        rt[i] = fst;
    }
    int non_ks = min(fst - 1, n);
    for (int i = non_ks, lst = vals.size(); i > 0 && lst - rt[i] > x; i--) { // lst = one idx after position of last undeleted k
        if (vals[i] == k) continue;
        int del = max((int)0, k - vals[i] - 1);
        if (lst - del - 1 - rt[i - 1] > x) {
            swap(vals[i], vals[lst - 1 - del]);
            lst -= del + 1;
        }
        else {
            int j = i;
            while (lst - rt[i] > x) {
                j++;
                rt[i] = max(rt[i], j + k - vals[i]);
            }
            assert(lst - rt[i] == x);
            swap(vals[i], vals[j]);
            break;
        }
    }
    vals.erase(vals.begin());
    if (cnt_k_good(vals, k) != x) return {0};
    else return vals;
}
 
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        for (int v : ac()) cout << v << " ";
        cout << "\n";
    }
}

```
</spoiler>

*Prepared by [user:shsh,2026-03-09]*

## Daniel Saves Yash

<spoiler summary="Hint">
Range DP?
</spoiler>

<spoiler summary="Solution">
First, note that for every pair of deleted palindromes, either the two are disjoint or one must contain the other. For instance, if `s = "abccddba"` and we delete `cc`, `dd`, then `abba`, the pair (`cc`, `dd`) is disjoint while `abba` contains both `cc` and `dd`.

**Proof:** If two palindromes were to overlap, we would have to delete the second one before deleting the first. However, we would also have to delete the first one before the second. Contradiction.

This property motivates a Range DP. Specifically, let `dp[l][r] = {C, R}` represent that, when only considering the substring $S[l...r)$, we can remove all but $C$ characters using only $R$ operations (we want to minimize $C$ first, then minimize $R$). Now, consider a few cases.

1. **We delete $l$ and $r$ in the same palindrome.** 
- If this palindrome has length 2 or length greater than 3, then it must be possible for $S[l + 1, r - 1)$ to be entirely deleted: that is, `dp[l + 1][r - 1][0] = 0`. Also note that unless $r - l = 2$, we can always "attach" $l$ and $r$ to an existing palindrome for no additional cost.
- The only remaining case is if the palindrome has length exactly 3. In this case, we can just iterate over all possible midpoints for the palindrome. If this midpoint is $m$, we also have that $S[l + 1, m)$ and $S[m + 1, r - 1)$ must be fully deletable as well.

2. **We delete $l$ and $r$ via different palindromes (or don't delete one of them at all).** In this case, there must exist some $m$ such that all palindromes lie either within $S[l...m)$ or $S[m...r)$ . Therefore, we can just iterate over all possible choices for $m$.

In total, this takes $\mathcal{O}(N^3)$ time.
</spoiler>

<spoiler summary="Code (shsh)">
```cpp
#include <bits/stdc++.h>
using namespace std;
 
using T = array<int, 2>;
void smin(T &a, T b) { a = min(a, b); }
T operator+(T a, T b) {
    return {a[0] + b[0], a[1] + b[1]};
}
 
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    string s; cin >> s;
    auto dp = vector(n + 1, vector(n + 1, array{0, 0}));
    for (int l = n; l --> 0; ) for (int r = l + 1; r <= n; r++) {
        dp[l][r] = {r - l, 0};
        if (r > l + 1) if (s[l] == s[r - 1]) {
            if (dp[l + 1][r - 1][0] == 0) { // if we can delete all characters
                smin(dp[l][r], array{0, int(r - l == 2)} + dp[l + 1][r - 1]);
            }
            for (int m = l + 1; m + 1 < r; m++) {
                auto &lef = dp[l + 1][m], &rig = dp[m + 1][r - 1];
                if (!lef[0] && !rig[0]) {
                    smin(dp[l][r], array{0, 1} + lef + rig);
                }
            }
        }
        for (int m = l + 1; m < r; m++) {
            smin(dp[l][r], dp[l][m] + dp[m][r]);
        }
    }
    cout << n - dp[0][n][0] << "\n" << dp[0][n][1] << "\n";
}
```
</spoiler>

*Prepared by [user:andrewgopher,2026-03-09]*

## Tree Queries

<spoiler summary="Hint 1">
Can we represent the required edges to unite $[l, r]$ as the union of some paths?
</spoiler>

<spoiler summary="Hint 2">
Would it help to process queries in increasing order of $r$?
</spoiler>

<spoiler summary="Solution">
Let $P(u, v)$ denote the set of edges along the path from $u$ to $v$. We claim that in order to unite all pairs $(u, v)$ for $u, v \in [l, r]$, the set of required edges is precisely $P(l, l + 1) \cup P(l + 1, l + 2)... \cup  P(r - 1, r)$.

**Proof:** Evidently, all of these edges are necessary, otherwise node $i$ will not be connected to node $i + 1$. However, they are also sufficient because all adjacent indices can reach each other, therefore all indices can reach each other.

So, the problem reduces to the following:
> Given $n$ paths on a tree, query for the size of range unions (i.e. the union of paths $l$ through $r$).

Now, consider offlining queries and processing in increasing order of $r$. Then, for each edge $e$, we want to mark it with the greatest index $i < r$ such that $e \in P(i, i + 1)$. To answer a query $[l, r]$, we then only need to query for how many edges are marked with $i \geq l$ (this is very similar to the core idea for [range distinct value queries](https://judge.yosupo.jp/problem/static_range_count_distinct)). Then, when we increase $r$ to $r + 1$, we need to "paint over" all edges in $P(r, r + 1)$ and mark them with $r$ instead.

To finish, note that if the tree is a chain, this "painting-over" process can be easily simulated by an `std::set` in total $\mathcal{O}(n \log n)$ time, while frequencies for each mark can be maintained in any PURS data structure to answer queries in total $\mathcal{O}(q \log n)$ time. Then, to extend this a general tree, we can utilize HLD to break the tree into $\mathcal{O}(n)$ chains such that each path lies on at most $\mathcal{O}(\log n)$ chains. This adds an extra $\log$ factor to our painting process, bringing our final complexity to $\mathcal{O}(n \log^2 n + q \log n)$.
</spoiler>

<spoiler summary="Code (shsh)">
```cpp
#include <bits/stdc++.h>
using namespace std;

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) + x;
    }
    int query(int r) {
        int res = 0;
        for (; r; r -= r & -r) res = res + at(r);
        return res;
    }
};

void ac() {
    int n, q; cin >> n >> q;
    // input tree
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // dfs + HLD
    vector<int> d(n + 1, 0), chain(n + 1), par(n + 1), sz(n + 1, 1), rt;
    auto dfs = [&](this auto dfs, int x, int p) -> void {
        d[x] = d[par[x] = p] + 1;
        pair<int, int> mx = {-1, 0};
        for (int y : g[x]) if (y != p) {
            dfs(y, x);
            sz[x] += sz[y];
            mx = max(mx, {sz[y], y});
        }
        if (mx.second) chain[x] = chain[mx.second];
        else chain[x] = rt.size(), rt.emplace_back();
        rt[chain[x]] = x;
    };
    dfs(1, 0);
    // answer queries
    auto qs = vector(n + 1, vector<array<int, 2>>());
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[r].push_back({l, i});
    }
    bit frq(n + 1); // how many of each color are there?
    auto colors = vector(n + 1, set<array<int, 3>>()); // {left, right, color}
    vector<int> res(q);

    auto paint = [&](set<array<int, 3>> &s, array<int, 3> nw) {
        while (true) {
            auto it = s.lower_bound({nw[1] + 1, nw[1], 0});
            if (it == s.begin()) break;
            it = prev(it);
            assert((*it)[0] <= nw[1]);
            if ((*it)[1] < nw[0]) break; // no overlap
            auto overlap = array{max((*it)[0], nw[0]), min((*it)[1], nw[1]), (*it)[2]};
            frq.upd(overlap[2], -(overlap[1] - overlap[0] + 1));
            auto prv = *it;
            s.erase(it);
            if (overlap != prv) { // some parts need to be added back
                if (prv[0] < overlap[0]) s.insert({prv[0], overlap[0] - 1, prv[2]});
                if (overlap[1] < prv[1]) s.insert({overlap[1] + 1, prv[1], prv[2]});
            }
        }
        s.insert(nw);
        frq.upd(nw[2], nw[1] - nw[0] + 1);
    };

    for (int r = 1; r <= n; r++) {
        for (auto &[l, i] : qs[r]) {
            res[i] = frq.query(r) - frq.query(l);
            if (l == r) ++res[i];
            assert(res[i]);
        }
        if (r == n) break;
        // color path from r to r + 1 with color r
        int u = r, v = r + 1;
        while (chain[u] != chain[v]) {
            if (d[rt[chain[u]]] < d[rt[chain[v]]]) swap(u, v); // make u the deeper root
            paint(colors[chain[u]], {d[rt[chain[u]]], d[u], r});
            u = par[rt[chain[u]]];
        }
        if (d[u] < d[v]) swap(u, v);
        paint(colors[chain[u]], {d[v], d[u], r});
    }

    for (int i = 0; i < q; i++) cout << res[i] - 1 << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
```
</spoiler>

*Prepared by [user:shsh,2026-03-09]*
