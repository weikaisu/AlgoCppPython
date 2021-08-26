#include "leetcode.h"

//Create Maximum Number
//Given two arrays of length m and n with digits 0-9 representing two numbers.
//Create the maximum number of length k <= m + n from digits of the two.
class lc321 { //Hard
public:
    vector<int> CreateMaximumNumber(vector<int>& nums1, vector<int>& nums2, int k) {

    }
};

//Valid Triangle Number
class lc611 { //Medium
public:
    int ValidTriangleNumber(vector<int>& nums) {
        //time(N^2)
        int n=nums.size(); if(n<3) return 0;
        //sort the nums then find sum of any two smaller edges bigger
        //than the biggest edge
        sort(nums.rbegin(),nums.rend()); //descending sort

        int res=0, biggest,bigger,smallest;
        for(biggest=0; biggest<n-2; biggest++) {
            bigger  =biggest+1;
            smallest=n-1;
            while(bigger<smallest) {
                if(nums[bigger]+nums[smallest]>nums[biggest]) {res+=(smallest-bigger);bigger++;}
                else {smallest--;}
            }
        }
        return res;
    }
};

//Assign Cookies
//Assume you are an awesome parent and want to give your children some cookies.
//But, you should give each child at most one cookie. Each child i has a greed
//factor gi, which is the minimum size of a cookie that the child will be content
//with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to
//the child i, and the child i will be content. Your goal is to maximize the number
//of your content children and output the maximum number.
class lc455 { //Easy
public:
    int AssignCookies(vector<int>& g, vector<int>& s) {
        // greedy algo, time(NlogN), space(1)
        int child_num=0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        for(auto i=0; i<g.size(); i++)
            for(auto j=0; j<s.size(); j++)
                if(g[i]<=s[j]) {child_num++; break;}
    }
};
