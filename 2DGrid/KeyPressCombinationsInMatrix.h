#ifndef KEY_PRESS_COMBINATIONS_IN_MATRIX_H
#define KEY_PRESS_COMBINATIONS_IN_MATRIX_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/mobile-numeric-keypad-problem/
Given the mobile numeric keypad.
{ '1', '2', '3' },
{ '4', '5', '6' },
{ '7', '8', '9' },
{ '*', '0', '#' }
You can only press buttons that are up, left, right, or down to the current button.
You are not allowed to press '*' and '#'.
Given a number of movements n, find out the count of all possible number combinations.
For n=1, all possible number combinations are {0,1,2,3,4,5,6,7,8,9}, total count is 10.
For n=2, all possible number combinations are {00,08,11,12,14,22,21,23,25,...}, total count is 36.

DFS Recur: exponential time
DP3D: O(n) time, O(n) space
*/
class KeyPressCombinationsInMatrix
{
public:
	KeyPressCombinationsInMatrix(){}
	~KeyPressCombinationsInMatrix(){}

	int DFS_Recur(const std::vector<std::vector<char> > & keypad, int n)
	{
		if (n <= 0)
			return 0;
		int count = 0;
		for (int row = 0; row <= 3; ++row)
		{
			for (int col = 0; col <= 2; ++col)
			{
				if (keypad[row][col] != '*' && keypad[row][col] != '#')
					count += dfs_recur(keypad, row, col, n);
			}
		}
		Debug::Print2D<char>()(keypad, false);
		std::cout << "KeyPressCombinationsInMatrix DFS_Recur for \"" << n << "\" moves: " << count << std::endl;
		return count;
	}
private:
	int dfs_recur(const std::vector<std::vector<char> > & keypad, int rowY, int colX, int n)
	{
		if (n == 1)
			return 1;

		int count = 0;
		static std::vector<std::vector<int>> dir({{0,0},{-1,0},{1,0},{0,1},{0,-1}});
		for (int d = 0; d < 5; ++d)
		{
			int i = rowY + dir[d][0];
			int j = colX + dir[d][1];
			if (i >= 0 && i <= 3 && j >= 0 && j <= 2 && keypad[i][j] != '*' && keypad[i][j] != '#')
				count += dfs_recur(keypad, i, j, n-1);
		}

		return count;
	}

public:
	int DP3D(const std::vector<std::vector<char> > & keypad, int n)
	{
		if (n <= 0)
			return 0;
		if (n == 1)
			return 10;

		std::vector<std::vector<int>> dir({{0,0},{-1,0},{1,0},{0,1},{0,-1}});
		std::vector<std::vector<std::vector<int> > > dp(4, std::vector<std::vector<int> >(3, std::vector<int>(n + 1)));
		for (int row = 0; row <= 3; ++row)
		{
			for (int col = 0; col <= 2; ++col)
			{
				dp[row][col][0] = 0;
				dp[row][col][1] = 1;
			}
		}
		
		for (int move = 2; move <= n; ++move)
		{
			for (int row = 0; row <= 3; ++row)
			{
				for (int col = 0; col <= 2; ++col)
				{
					if (keypad[row][col] != '*' && keypad[row][col] != '#')
					{
						dp[row][col][move] = 0;

						for (int d = 0; d < 5; ++d)
						{
							int i = row + dir[d][0];
							int j = col + dir[d][1];
							if (i >= 0 && i <= 3 && j >= 0 && j <= 2 && keypad[i][j] != '*' && keypad[i][j] != '#')
								dp[row][col][move] += dp[i][j][move-1];
						}
					}
				}
			}
		}

		int count = 0;
		for (int row = 0; row <= 3; ++row)
		{
			for (int col = 0; col <= 2; ++col)
			{
				count += dp[row][col][n];
			}
		}
		Debug::Print2D<char>()(keypad, false);
		Debug::Print3D<int>()(dp, false);
		std::cout << "KeyPressCombinationsInMatrix DP3D for \"" << n << "\" moves: " << count << std::endl;
		return count;
	}
};
/*
[rY][cX]
Row#0	= 1, 2, 3
Row#1	= 4, 5, 6
Row#2	= 7, 8, 9
Row#3	= *, 0, #

KeyPressCombinationsInMatrix DFS_Recur for "3" moves: 138
[rY][cX]
Row#0	= 1, 2, 3
Row#1	= 4, 5, 6
Row#2	= 7, 8, 9
Row#3	= *, 0, #

[rY][cX][dZ]
Row#0	= 0,1,3,11.	0,1,4,15.	0,1,3,11.
Row#1	= 0,1,4,15.	0,1,5,22.	0,1,4,15.
Row#2	= 0,1,3,12.	0,1,5,18.	0,1,3,12.
Row#3	= 0,1,0,0.	0,1,2,7.	0,1,0,0.

KeyPressCombinationsInMatrix DP3D for "3" moves: 138
*/
#endif