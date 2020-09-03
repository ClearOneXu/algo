#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

/**
 result = []
 def backtrack(路径, 选择列表):
     if 满足结束条件:
         result.add(路径)
         return

     for 选择 in 选择列表:
         将该选择从选择列表移除
         路径.add(选择)
         backtrack(路径, 选择列表)
         # 撤销选择
         路径.remove(选择)
         将该选择再加入选择列表
 */
//全排列问题
int num_size;
vector<vector<int>> result;
void backtrack(int nums[], vector<int> track) {
    //结束条件
    if (track.size() == num_size) {
        result.push_back(track);
        return;
    }
    for (int i = 0; i < num_size; i++) {
        // 排除不合法的选择
        vector<int>::iterator it = find(track.begin(), track.end(), nums[i]);
        if (it != track.end())
            continue;
        //路径选择
        track.push_back(nums[i]);
        backtrack(nums, track);
        //取消选择
        track.pop_back();
    }
}
//N皇后问题
vector<vector<string>> res;
/* 是否可以在 board[row][col] 放置皇后？ */
bool isValid(vector<string>& board, int row, int col) {
    int n = board.size();
    // 检查列是否有皇后互相冲突
    for (int i = 0; i < n; i++) {
        if (board[i][col] == 'Q')
            return false;
    }
    // 检查右上方是否有皇后互相冲突
    for (int i = row - 1, j = col + 1;
            i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q')
            return false;
    }
    // 检查左上方是否有皇后互相冲突
    for (int i = row - 1, j = col - 1;
            i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q')
            return false;
    }
    return true;
}
// 路径：board 中小于 row 的那些行都已经成功放置了皇后
// 选择列表：第 row 行的所有列都是放置皇后的选择
// 结束条件：row 超过 board 的最后一行
void backtrack2(vector<string>& board, int row) {
    // 触发结束条件
    if (row == board.size()) {
        res.push_back(board);
        return;
    }

    int n = board[row].size();
    for (int col = 0; col < n; col++) {
        // 排除不合法选择
        if (!isValid(board, row, col))
            continue;
        // 做选择
        board[row][col] = 'Q';
        // 进入下一行决策
        backtrack2(board, row + 1);
        // 撤销选择
        board[row][col] = '.';
    }
}

/* 输入棋盘边长 n，返回所有合法的放置 */
vector<vector<string>> solveNQueens(int n) {
    // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
    vector<string> board(n, string(n, '.'));
    backtrack2(board, 0);
    return res;
}



