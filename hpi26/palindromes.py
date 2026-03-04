import sys

def solve():
    # Read input
    line1 = sys.stdin.readline().strip()
    if not line1: return
    n = int(line1)
    s = sys.stdin.readline().strip()

    # rem[i][j] = min characters remaining in S[i...j]
    # ops[i][j] = min operations to achieve rem[i][j]
    rem = [[0] * n for _ in range(n)]
    ops = [[0] * n for _ in range(n)]

    for length in range(1, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1

            if length == 1:
                rem[i][j] = 1
                ops[i][j] = 0
                continue

            # 1. Initialize with a basic split (single character S[i] + the rest)
            best_r = 1 + rem[i+1][j]
            best_o = ops[i+1][j]

            # 2. General Split transitions
            for k in range(i + 1, j):
                curr_r = rem[i][k] + rem[k+1][j]
                curr_o = ops[i][k] + ops[k+1][j]
                if curr_r < best_r:
                    best_r, best_o = curr_r, curr_o
                elif curr_r == best_r and curr_o < best_o:
                    best_o = curr_o

            # 3. Check matching ends S[i] == S[j]
            if s[i] == s[j]:
                r, o = 1e9, 1e9
                if length == 2:
                    r, o = 0, 1
                else:
                    inner_r = rem[i+1][j-1]
                    inner_o = ops[i+1][j-1]
                    if inner_r == 0:
                        r, o = 0, max(1, inner_o)
                    elif inner_r == 1:
                        r, o = 0, inner_o + 1

                if r < best_r:
                    best_r, best_o = r, o
                elif r == best_r and o < best_o:
                    best_o = o

            rem[i][j] = best_r
            ops[i][j] = best_o

    # Final Answers
    print(n - rem[0][n-1])
    print(ops[0][n-1])

solve()
