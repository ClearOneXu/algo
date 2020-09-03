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

struct Node {
    int val;
    vector<Node> adj;
};

// 计算从起点 start 到终点 target 的最近距离
int BFS(Node start, Node target) {
    queue<Node> q; // 核心数据结构
    set<Node> visited; // 避免走回头路

    q.push(start); // 将起点加入队列
    visited.insert(start);
    int step = 0; // 记录扩散的步数

    while (!q.empty()) {
        int sz = q.size();
        /* 将当前队列中的所有节点向四周扩散 */
        for (int i = 0; i < sz; i++) {
            Node cur = q.front();
            q.pop();
            /* 划重点：这里判断是否到达终点 */
            if (&cur == &target)
                return step;
            /* 将 cur 的相邻节点加入队列 */
            for (auto x : cur.adj)
                if (visited.find(x) == visited.end()) {
                    q.push(x);
                    visited.insert(x);
                }
        }
        /* 划重点：更新步数在这里 */
        step++;
    }
    return step;
}


//密码锁问题
//双向BFS
// 将 s[j] 向上拨动一次
string plusOne(string s, int j) {
    if (s[j] == '9')
        s[j] = '0';
    else
        s[j] = 1;
    return string(s);
}
// 将 s[i] 向下拨动一次
string minusOne(string s, int j) {
    if (s[j] == '0')
        s[j] = '9';
    else
        s[j] -= 1;
    return string(s);
}

int openLock(vector<string> deadends, string target) {
    set<string> deads;
    for (auto s : deadends) deads.insert(s);
    // 用集合不用队列，可以快速判断元素是否存在
    set<string> q1;
    set<string> q2;
    set<string> visited;

    int step = 0;
    q1.insert("0000");
    q2.insert(target);

    while (!q1.empty() && !q2.empty()) {
        // 哈希集合在遍历的过程中不能修改，用 temp 存储扩散结果
        set<string> temp;
        /* 将 q1 中的所有节点向周围扩散 */
        for (string cur : q1) {
            /* 判断是否到达终点 */
            if (deads.find(cur) != deads.end())
                continue;
            if (q2.find(cur) != q2.end())
                return step;
            visited.insert(cur);
            
            /* 将一个节点的未遍历相邻节点加入集合 */
            for (int j = 0; j < 4; j++) {
                string up = plusOne(cur, j);
                if (visited.find(up) == visited.end())
                    temp.insert(up);
                string down = minusOne(cur, j);
                if (visited.find(down) == visited.end())
                    temp.insert(down);
            }
        }
        /* 在这里增加步数 */
        step++;
        // temp 相当于 q1
        // 这里交换 q1 q2，下一轮 while 就是扩散 q2
        q1 = q2;
        q2 = temp;
    }
    return -1;
}
