#ifndef other_h
#define other_h
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <set>
using namespace std;
//二分查找
/**
 分析二分查找的一个技巧是：不要出现 else，而是把所有情况用 else if 写清楚，这样可以清楚地展现所有细节。
 */
//一、寻找一个数（基本的二分搜索）
int binarySearch(vector<int> nums, int target) {
    int left = 0;
    int right = nums.size() - 1; // 注意

    while(left <= right) { //[left, right]
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1; // 注意
        else if (nums[mid] > target)
            right = mid - 1; // 注意
    }
    return -1;
}
//二、寻找左侧边界的二分搜索
int left_bound(vector<int> nums, int target) {
    if (nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size(); // 注意

    while (left < right) { // 注意 [left, right)
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid; // 注意
        }
    }
    // target 比所有数都大
    if (left == nums.size()) return -1;
    // 类似之前算法的处理方式
    return nums[left] == target ? left : -1;
}


//滑动窗口
/**
 int left = 0, right = 0;
 while (right < s.size()) {`
     // 增大窗口
     window.add(s[right]);
     right++;

     while (window needs shrink) {
         // 缩小窗口
         window.remove(s[left]);
         left++;
     }
 }
 */
/* 滑动窗口算法框架 */
//void slidingWindow(string s, string t) {
//    unordered_map<char, int> need, window;
//    for (char c : t) need[c]++;
//
//    int left = 0, right = 0;
//    int valid = 0;
//    while (right < s.size()) {
//        // c 是将移入窗口的字符
//        char c = s[right];
//        // 右移窗口
//        right++;
//        // 进行窗口内数据的一系列更新
//        ...
//
//        /*** debug 输出的位置 ***/
//        printf("window: [%d, %d)\n", left, right);
//        /********************/
//
//        // 判断左侧窗口是否要收缩
//        while (window needs shrink) {
//            // d 是将移出窗口的字符
//            char d = s[left];
//            // 左移窗口
//            left++;
//            // 进行窗口内数据的一系列更新
//            ...
//        }
//    }
//}

string slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0, start = 0;
    //int valid = 0;
    int len = INT_MAX;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新 ...
        if (need.count(c) != 0) {
            window[c] = (window.count(c)==0) ? 0 : window[c] + 1;
        }
        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/
        
        char d = s[left];
        if (need.count(d) == 0) left++;
        // 判断左侧窗口是否要收缩
        while (window == need) {
            if (right - left < len) {
                start = left;
                len = right - left;
            }
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            if (need.count(d) != 0) {
                window[c]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}

/* 滑动窗口算法框架 */
bool checkInclusion(string t, string s) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        if (need.count(c) !=0 ) {
            window[c] = (window.count(c)==0) ? 0 : window[c] + 1 ;
            if (window[c] == need[c]) valid++;
        }
        else{
            left++;
        }

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/
        
        // 判断左侧窗口是否要收缩
        while (right - left > t.size()) {
            if (valid == need.size()) return true;
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            if (need.count(d)!=0) {
                if (window[c] == need[c]) valid--;
                window[c]--;
            }
        }
    }
    return false;
}

//nSum问题
/* 注意：调用这个函数之前一定要先给 nums 排序 */
vector<vector<int>> nSumTarget(
    vector<int>& nums, int n, int start, int target) {

    int sz = nums.size();
    vector<vector<int>> res;
    // 至少是 2Sum，且数组大小不应该小于 n
    if (n < 2 || sz < n) return res;
    // 2Sum 是 base case
    if (n == 2) {
        // 双指针那一套操作
        int lo = start, hi = sz - 1;
        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            int left = nums[lo], right = nums[hi];
            if (sum < target) {
                while (lo < hi && nums[lo] == left) lo++;
            } else if (sum > target) {
                while (lo < hi && nums[hi] == right) hi--;
            } else {
                res.push_back({left, right});
                while (lo < hi && nums[lo] == left) lo++;
                while (lo < hi && nums[hi] == right) hi--;
            }
        }
    } else {
        // n > 2 时，递归计算 (n-1)Sum 的结果
        for (int i = start; i < sz; i++) {
            vector<vector<int>>
                sub = nSumTarget(nums, n - 1, i + 1, target - nums[i]);
            for (vector<int>& arr : sub) {
                // (n-1)Sum 加上 nums[i] 就是 nSum
                arr.push_back(nums[i]);
                res.push_back(arr);
            }
            while (i < sz - 1 && nums[i] == nums[i + 1]) i++;
        }
    }
    return res;
}



#endif /* other_h */
