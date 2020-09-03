#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <set>
using namespace std;

/**
 # 初始化 base case
 dp[0][0][...] = base
 # 进行状态转移
 for 状态1 in 状态1的所有取值：
     for 状态2 in 状态2的所有取值：
         for ...
             dp[状态1][状态2][...] = 求最值(选择1，选择2...)
 */

//凑零钱问题
//暴力递归
int coinChange(set<int> coins, int amount, int num) {
    if (coins.find(amount) == coins.end()) return 0;
    int minNum = INT_MAX;
    for (auto c : coins) {
        int n = coinChange(coins, amount - c, num);
        minNum = (n < minNum) ? n : minNum;
    }
    return minNum + num;
}
//动态规划 --> 有子集合重叠
/**
 # 伪码框架
 def coinChange(coins: List[int], amount: int):

     # 定义：要凑出金额 n，至少要 dp(n) 个硬币
     def dp(n):
         # 做选择，选择需要硬币最少的那个结果
         for coin in coins:
             res = min(res, 1 + dp(n - coin))
         return res

     # 题目要求的最终结果是 dp(amount)
     return dp(amount)
 */
int coinChange_dp(set<int> coins, int amount) {
    if (coins.find(amount) == coins.end()) return 0;
    int *dp = new int[amount];
    memset(dp, 0, amount);
    for (auto c : coins) {
        dp[c] = 1;
    }
    for (int i = 1; i <= amount; i++) {
        if (dp[i] != 0) continue;
        int minNum = INT_MAX;
        for (auto c : coins) {
            if (i-c > 0) {
                int& n = dp[i-c] + 1;
                minNum = (n < minNum) ? n : minNum;
            }
        }
    }
}

