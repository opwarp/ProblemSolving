/*Facebook*/
#ifndef _L_MOVE_IDX_COMBINATION_IN_MATRIX_H
#define _L_MOVE_IDX_COMBINATION_IN_MATRIX_H
#include "Debug.h"
/*
Given a matrix like this.
012
345
678
.9.
You can move L shape (0->5 or 7), (1->6 or 8), (3->2 or 8) starting from 0.
Given number of moves, count number of different combination of index sequences.

Leetcode: Knight Dialer
A chess knight can move as indicated in the chess diagram below:
This time, we place our chess knight on any numbered key of a phone pad (indicated above), and the knight makes N-1 hops.
Each hop must be from one key to another numbered key.
Each time it lands on a key (including the initial placement of the knight), it presses the number of that key, pressing N digits total.
How many distinct numbers can you dial in this manner?
Since the answer may be large, output the answer modulo 10^9 + 7.
Example 1:
Input: 1
Output: 10
Example 2:
Input: 2
Output: 20
Example 3:
Input: 3
Output: 46
 */
class LMoveIdxSeqCombinationInMatrix
{
public:
    LMoveIdxSeqCombinationInMatrix(){}

    int DP(int N)
    {
        std::vector<std::vector<int>> dest(10, std::vector<int>());//dest[i]: a list of indices that can be reached from index i
        dest[0] = {5, 7};
        dest[1] = {6, 8};
        dest[2] = {3, 7};
        dest[3] = {2, 8, 9};
        dest[4] = {};
        dest[5] = {0, 6, 9};
        dest[6] = {1, 5};
        dest[7] = {0, 2};
        dest[8] = {1, 3};
        dest[9] = {3, 5};

        std::vector<std::vector<int>> dp(10, std::vector<int>(N+1, 0));//dp[i][j]: num of ways at index i at move j
        dp[0][0] = 1;//start from index 1
        for (int moves = 1; moves <= N; ++moves)
        {
            for (int i = 0; i < 10; ++i)
            {
                for (int nxt : dest[i])
                    dp[nxt][moves] += dp[i][moves-1];
            }
        }

        int res = 0;
        for (int i = 0; i < 10; ++i)
            res += dp[i][N];

        Debug::Print2D<int>()(dp, false);
        std::cout << "LMoveIdxSeqCombinationInMatrix DP for moves=" << N << ": " << res << std::endl;
        return res;
    }

    int Recur(int N)
    {
        std::vector<std::vector<int>> dest(10, std::vector<int>());//dest[i]: a list of indices that can be reached from index i
        dest[0] = {5, 7};
        dest[1] = {6, 8};
        dest[2] = {3, 7};
        dest[3] = {2, 8, 9};
        dest[4] = {};
        dest[5] = {0, 6, 9};
        dest[6] = {1, 5};
        dest[7] = {0, 2};
        dest[8] = {1, 3};
        dest[9] = {3, 5};

        int count = recur(0, N, dest);
        std::cout << "LMoveIdxSeqCombinationInMatrix Recur for moves=" << N << ": " << count << std::endl;
        return count;
    }
    int recur(int cur, int move, const std::vector<std::vector<int>> & dest)
    {
        if (move == 0) return 1;
        int count = 0;
        for (auto & nxt : dest[cur])
            count += recur(nxt, move-1, dest);
        return count;
    }
};
class KnightDialer
{
public:
    KnightDialer() = default;

    int DP(int N)
    {
        std::vector<std::vector<int>> dest(10, std::vector<int>());//dest[i]: a list of indices that can be reached from index i
        dest[0] = {5, 7};
        dest[1] = {6, 8};
        dest[2] = {3, 7};
        dest[3] = {2, 8, 9};
        dest[4] = {};
        dest[5] = {0, 6, 9};
        dest[6] = {1, 5};
        dest[7] = {0, 2};
        dest[8] = {1, 3};
        dest[9] = {3, 5};

        //DP: O(N) time
        std::vector<std::vector<int>> dp(10, std::vector<int>(N+1, 0));//dp[i][j]: num of ways at index i at move j
        for (int i = 0; i < 10; ++i)
            dp[i][1] = 1;//start from index i
        for (int moves = 2; moves <= N; ++moves)
        {
            for (int i = 0; i < 10; ++i)
            {
                for (int nxt : dest[i])
                {
                    dp[nxt][moves] += dp[i][moves-1];
                    dp[nxt][moves] %= 1000000007;
                }
            }
        }

        int res = 0;
        for (int i = 0; i < 10; ++i)
        {
            res += dp[i][N];
            res %= 1000000007;
        }

        Debug::Print2D<int>()(dp, false);
        std::cout << "KnightDialer DP for moves=" << N << ": " << res << std::endl;
        return res;
        //there is a O(logN) solution
    }

    int Recur(int N)
    {
        std::vector<std::vector<int>> dest(10, std::vector<int>());//dest[i]: a list of indices that can be reached from index i
        dest[0] = {5, 7};
        dest[1] = {6, 8};
        dest[2] = {3, 7};
        dest[3] = {2, 8, 9};
        dest[4] = {};
        dest[5] = {0, 6, 9};
        dest[6] = {1, 5};
        dest[7] = {0, 2};
        dest[8] = {1, 3};
        dest[9] = {3, 5};
        int res = 0;
        for (int i = 0; i < 10; ++i)
        {
            res += recur(i, N, dest);
            res %= 1000000007;
        }

        std::cout << "KnightDialer Recur for moves=" << N << ": " << res << std::endl;
        return res;
    }
    int recur(int cur, int move, const std::vector<std::vector<int>> & dest)
    {
        if (move == 1) return 1;
        int count = 0;
        for (auto & nxt : dest[cur])
        {
            count += recur(nxt, move-1, dest);
            count %= 1000000007;
        }
        return count;
    }
};
/*
[rY][cX]
Row#0	= 1, 0
Row#1	= 0, 0
Row#2	= 0, 0
Row#3	= 0, 0
Row#4	= 0, 0
Row#5	= 0, 1
Row#6	= 0, 0
Row#7	= 0, 1
Row#8	= 0, 0
Row#9	= 0, 0

LMoveIdxSeqCombinationInMatrix DP for moves=1: 2
LMoveIdxSeqCombinationInMatrix Recur for moves=1: 2
[rY][cX]
Row#0	= 1, 0, 2
Row#1	= 0, 0, 0
Row#2	= 0, 0, 1
Row#3	= 0, 0, 0
Row#4	= 0, 0, 0
Row#5	= 0, 1, 0
Row#6	= 0, 0, 1
Row#7	= 0, 1, 0
Row#8	= 0, 0, 0
Row#9	= 0, 0, 1

LMoveIdxSeqCombinationInMatrix DP for moves=2: 5
LMoveIdxSeqCombinationInMatrix Recur for moves=2: 5
[rY][cX]
Row#0	= 1, 0, 2, 0
Row#1	= 0, 0, 0, 1
Row#2	= 0, 0, 1, 0
Row#3	= 0, 0, 0, 2
Row#4	= 0, 0, 0, 0
Row#5	= 0, 1, 0, 4
Row#6	= 0, 0, 1, 0
Row#7	= 0, 1, 0, 3
Row#8	= 0, 0, 0, 0
Row#9	= 0, 0, 1, 0

LMoveIdxSeqCombinationInMatrix DP for moves=3: 10
LMoveIdxSeqCombinationInMatrix Recur for moves=3: 10
[rY][cX]
Row#0	= 1, 0, 2, 0, 7
Row#1	= 0, 0, 0, 1, 0
Row#2	= 0, 0, 1, 0, 5
Row#3	= 0, 0, 0, 2, 0
Row#4	= 0, 0, 0, 0, 0
Row#5	= 0, 1, 0, 4, 0
Row#6	= 0, 0, 1, 0, 5
Row#7	= 0, 1, 0, 3, 0
Row#8	= 0, 0, 0, 0, 3
Row#9	= 0, 0, 1, 0, 6

LMoveIdxSeqCombinationInMatrix DP for moves=4: 26
LMoveIdxSeqCombinationInMatrix Recur for moves=4: 26
[rY][cX]
Row#0	= 1, 0, 2, 0, 7, 0
Row#1	= 0, 0, 0, 1, 0, 8
Row#2	= 0, 0, 1, 0, 5, 0
Row#3	= 0, 0, 0, 2, 0, 14
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 1, 0, 4, 0, 18
Row#6	= 0, 0, 1, 0, 5, 0
Row#7	= 0, 1, 0, 3, 0, 12
Row#8	= 0, 0, 0, 0, 3, 0
Row#9	= 0, 0, 1, 0, 6, 0

LMoveIdxSeqCombinationInMatrix DP for moves=5: 52
LMoveIdxSeqCombinationInMatrix Recur for moves=5: 52

[rY][cX]
Row#0	= 0, 1
Row#1	= 0, 1
Row#2	= 0, 1
Row#3	= 0, 1
Row#4	= 0, 1
Row#5	= 0, 1
Row#6	= 0, 1
Row#7	= 0, 1
Row#8	= 0, 1
Row#9	= 0, 1

KnightDialer DP for moves=1: 10
[rY][cX]
Row#0	= 0, 1, 2
Row#1	= 0, 1, 2
Row#2	= 0, 1, 2
Row#3	= 0, 1, 3
Row#4	= 0, 1, 0
Row#5	= 0, 1, 3
Row#6	= 0, 1, 2
Row#7	= 0, 1, 2
Row#8	= 0, 1, 2
Row#9	= 0, 1, 2

KnightDialer DP for moves=2: 20
KnightDialer Recur for moves=1: 10
KnightDialer Recur for moves=2: 20
 */
#endif
