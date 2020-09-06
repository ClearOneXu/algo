#ifndef dp_h
#define dp_h

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
//dp[n] = min{dp[n-ci]+1 | i=1,2,..,m}
int coinChange(vector<int>& coins, int amount) {
    // 数组大小为 amount + 1，初始值也为 amount + 1
    vector<int> dp(amount + 1, amount + 1);
    // base case
    dp[0] = 0;
    // 外层 for 循环在遍历所有状态的所有取值
    for (int i = 0; i < dp.size(); i++) {
        // 内层 for 循环在求所有选择的最小值
        for (int coin : coins) {
            // 子问题无解，跳过
            if (i - coin < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
    }
    return (dp[amount] == amount + 1) ? -1 : dp[amount];
}


//股票买卖问题
/**
 dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
               max(   选择 rest  ,             选择 sell      )

 解释：今天我没有持有股票，有两种可能：
 要么是我昨天就没有持有，然后今天选择 rest，所以我今天还是没有持有；
 要么是我昨天持有股票，但是今天我 sell 了，所以我今天没有持有股票了。

 dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
               max(   选择 rest  ,           选择 buy         )

 解释：今天我持有着股票，有两种可能：
 要么我昨天就持有着股票，然后今天选择 rest，所以我今天还持有着股票；
 要么我昨天本没有持有，但今天我选择 buy，所以今天我就持有股票了。
 */
// k == 1
int maxProfit_k_1(vector<int> prices) {
    int n = prices.size();
    // base case: dp[-1][0] = 0, dp[-1][1] = -infinity
    int dp_i_0 = 0, dp_i_1 = INT_MIN;
    for (int i = 0; i < n; i++) {
        // dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
        // dp[i][1] = max(dp[i-1][1], -prices[i])
        dp_i_1 = max(dp_i_1, -prices[i]);
    }
    return dp_i_0;
}
//k = Infinity
/**
 如果 k 为正无穷，那么就可以认为 k 和 k - 1 是一样的。
 dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
             = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i])
 我们发现数组中的 k 已经不会改变了，也就是说不需要记录 k 这个状态了：
 dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
 dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
 */
/** k = 2
 原始的动态转移方程，没有可化简的地方
 dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 */

int maxProfit_k_2(vector<int> prices) {
    int dp_i10 = 0, dp_i11 = INT_MIN;
    int dp_i20 = 0, dp_i21 = INT_MIN;
    for (int price : prices) {
        dp_i20 = max(dp_i20, dp_i21 + price);
        dp_i21 = max(dp_i21, dp_i10 - price);
        dp_i10 = max(dp_i10, dp_i11 + price);
        dp_i11 = max(dp_i11, -price);
    }
    return dp_i20;
}


//0-1背包问题
int knapsack(int W, int N, vector<int>& wt, vector<int>& val) {
    // vector 全填入 0，base case 已初始化
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - wt[i-1] < 0) {
                // 当前背包容量装不下，只能选择不装入背包
                dp[i][w] = dp[i - 1][w];
            } else {
                // 装入或者不装入背包，择优
                dp[i][w] = max(dp[i - 1][w - wt[i-1]] + val[i-1],
                               dp[i - 1][w]);
            }
        }
    }

    return dp[N][W];
}

//完全背包
int change(int amount, vector<int> coins) {
    int n = coins.size();
    int* dp = new int[amount + 1];
    dp[0] = 1; // base case
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= amount; j++)
            /**
             dp[i][j] = dp[i - 1][j] + dp[i][j-coins[i-1]];
             j块钱 = i没用凑j方法 + 凑j-(coints[i-1])的方法
             */
            if (j - coins[i] >= 0)
                dp[j] = dp[j] + dp[j-coins[i]];

    return dp[amount];
}

#endif /* dp_h */
