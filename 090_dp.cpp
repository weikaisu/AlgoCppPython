#include "leetcode.h"

//Count Different Palindromic Subsequences
//Given a string S, find the number of different non-empty palindromic subsequences in S
class lc730 { //Hard
public:
    int CountDifferentPalindromicSubsequences(string S) {

    }
};

//Edit Distance
//Given two words word1 and word2, find the minimum number of steps
//required to convert word1 to word2.
class lc072 { //Hard
public:
    //time(l1*l2) space(l1*l2)
    int EditDistance(string word1, string word2) {
        int i, l1=word1.size();
        int j, l2=word2.size();
        vector<vector<int>> dis(l1+1, vector<int>(l2+1,0));

        for(i=0;i<=l1;i++) dis[i][0]=i; //init boundary conditions
        for(j=0;j<=l2;j++) dis[0][j]=j; //init boundary conditions
        for(i=1;i<=l1;i++)
            for(j=1;j<=l2;j++) {
                dis[i][j]=(word1[i-1]==word2[j-1]?0:1)+ //last char the same
                          min(dis[i-1][j-1], //replace
                          min(dis[i][j-1], //insert
                              dis[i-1][j]) //delete
                              )+1;
        }
        return dis[l1][l2];
    }
};

//Strange Printer
//Given a string consists of lower English letters only,
//count the minimum number of turns the printer needed in order to print it.
class lc664 { //Hard
private:
    vector<vector<int>> min_times;
    int printer(string &s, int l, int r) {
        if(l>r) return 0;
        if(min_times[l][r]>0) return min_times[l][r];

        //step 1, remove the right most char
        int times=printer(s,l,r-1)+1;
        //step 2, find the min times in the sub string (string without the right most char)
        for(auto k=l;k<r;k++)
            if(s[k]==s[r])
                times=min(times, printer(s,l,k)+printer(s,k+1,r-1));
        return min_times[l][r]=times;
    }
public:
    // time(N^3) space(N^2)
    int StrangePrinter(string s) {
        int len=s.size(); if(!len) return 0;
        min_times=vector<vector<int>>(len,vector<int>(len,0));
        return printer(s,0,len-1);
    }
};

//Valid Parenthesis String
//Given a string containing only three types of characters: '(', ')' and '*',
//write a function to check whether this string is valid.
class lc678 { //Medium
public:
    // time(N)
    bool ValidParenthesisString(string s) {
        //最終需消除所有括號，令左右括號各有一個變數來紀錄其消長
        int l_par=0; //需要被消除的量
        int r_par=0; //可用來消除的量
        for(auto c:s) {
            l_par+= c=='(' ? 1 : -1;
            r_par+= c==')' ? 1 : -1;
            if(r_par>0) return false; //右括號前沒有左括號
        }
        if (l_par>0) return false; //左括號後沒有右括號
        return true;
    }
};

//Different Ways to Add Parentheses
//Given a string of numbers and operators, return all possible results from computing
//all the different possible ways to group numbers and operators. The valid operators
//are +, - and *.
namespace myOP {
    int myAdd(int a, int b) { return a+b; }
    int mySub(int a, int b) { return a-b; }
    int myMul(int a, int b) { return a*b; }
}
class lc241 { //Medium
private:
    unordered_map<string, vector<int>> mem_;
    std::function<int(int,int)> opfun_; //https://shininglionking.blogspot.tw/2017/01/stdfunction-c11.html

    //int compute(int a, int b, std::function op) { return op(a, b); }
    vector<int> _ways(string input) {
        vector<int> res;
        if(mem_.count(input)) return mem_[input];
        for(auto i=0;i<input.size();i++) {
            char op=input[i];
            // Split the input by an op
            if(op=='+'||op=='-'||op=='*') {
                string left=input.substr(0,i);
                string right=input.substr(i+1);
                vector<int> left_res=_ways(left);
                vector<int> right_res=_ways(right);

                switch(op) {
                    case '+': opfun_ = myOP::myAdd; break;
                    case '-': opfun_ = myOP::mySub; break;
                    case '*': opfun_ = myOP::myMul; break;
                }

                // combine the solution
                for(auto l:left_res)
                    for(auto r:right_res)
                        res.push_back(opfun_(l,r));
            }
        }
        // single number, e.g. s="3"
        if(res.empty())
            res.push_back(stoi(input));
        // memorize the answer for input
        mem_[input].swap(res);
        return mem_[input];
    }
public:
    vector<int> DifferentWaysToAddParentheses(string input) {
        return _ways(input);
    }
};

//Decode Ways II
//Given the encoded message containing digits and the character '*',
//return the total number of ways to decode it.
class lc639 { //Hard
private:
    int isValid(char c) {
        if(c=='0') return 0;
        if(c=='*') return 9;
        return 1;
    }
    int isValid(char c1, char c2) {
        if(c1=='*'&&c2=='*') {
            return 15;
        }
        if(c1=='*'&&c2!='*') {
            return (c2>='0'&&c2<='6')? 2 : 1;
        }
        if(c1!='*'&&c2=='*') {
            switch(c1) {
            case '1':return 9;
            case '2':return 6;
            default :return 0;
            }
        }
        if(c1!='*'&&c2!='*') {
            int num=(c1-'0')*10+(c2-'0');
            return num>=10 && num<=26;
        }
    }
    static constexpr int kMod = 1000000007;
public:
    // time(N) space(1)
    int DecodeWaysII(string s) {
        if(s.empty()||s[0]=='0') return 0;

        int sCurr=0, sPre1=1, sPre2=isValid(s[0]), len=s.size();
        for(int i=1;i<len;i++) {
            sCurr=isValid(s[i])*sPre1+isValid(s[i-1],s[i])*sPre2;
            sCurr%=kMod;
            sPre2=sPre1; sPre1=sCurr;
        }
        return sCurr;
    }
};

//Decode Ways
//Given an encoded message containing digits,
//return the total number of ways to decode it.
//Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
//The number of ways decoding "12" is 2.
class lc091 { //Medium
private:
    bool isValid(char c) {return c!='0';}
    bool isValid(char c1, char c2) {
        int num=(c1-'0')*10+(c2-'0');
        return num>=10 && num<=26;
    }
public:
    // time(N) space(1)
    int DecodeWaysI(string s) {
        if(s.empty()||s[0]=='0') return 0;
        if(s.size()==1) return 1;

        int sCurr=0, sPre1=1, sPre2=1, len=s.size();
        for(int i=1;i<len;i++) {
            sCurr=isValid(s[i])*sPre1+isValid(s[i-1],s[i])*sPre2;
            sPre2=sPre1; sPre1=sCurr;
        }
        return sCurr;
    }
};

//Word Break II
//Given a non-empty string s and a dictionary wordDict containing a list of non-empty
//words, add spaces in s to construct a sentence where each word is a valid dictionary
//word. You may assume the dictionary does not contain duplicate words.
//Return all such possible sentences.
class lc140 { //Hard
private:
    unordered_map<string, vector<string>> mem_;
    unordered_set<string> dict_;

    const vector<string>& _break(string s) {
        vector<string> res;
        if(mem_.count(s)) return mem_[s];
        // s in dict, add it to the answer array
        if(dict_.count(s)) res.push_back(s);
        for(int i=1; i<s.size(); i++) {
            // Check whether left part is a word
            const string left=s.substr(0,i);
            if(!dict_.count(left)) continue;
            const string right=s.substr(i);
            for(auto right_res:_break(right)) res.push_back(left+" "+right_res);
        }
        mem_[s].swap(res);
        return mem_[s];
    }

    vector<string> append(const vector<string> &prefixes, const string &word) {
        vector<string> concat;
        for(const auto &prefix:prefixes)
            concat.push_back(prefix+" "+word);
        return concat;
    }
public:
    vector<string> WordBreakII(string s, vector<string>& wordDict) {
        dict_=unordered_set<string>(wordDict.begin(),wordDict.end());
        return _break(s);
    }
};

//Word Break
//Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
//Determine if s can be segmented into a space-separated sequence of one or more dictionary words.
class lc139 { //Medium
private:
    unordered_map<string,bool> mem_;
    unordered_set<string> dict_;

    bool _break(string s) {
#if 1
        if(mem_.count(s)) return mem_[s];
         // Whole string is a word, memorize and return.
        if(dict_.count(s)) return mem_[s]=true;
        // Try every break point.
        for(auto i=1; i<s.size(); i++) {
            const string left=s.substr(0,i);
            const string right=s.substr(i);
            if(dict_.count(right) && _break(left))
                return mem_[s]=true;
        }
        return mem_[s]=false;
#else // no mem_
        if(dict_.count(s)) return true;
        // try every break point.
        for(auto i=1; i<s.size(); i++)
            if(dict_.find(s.substr(0,i))!=dict_.end()&&_break(s.substr(i)))
                return true;
            else return false;
#endif
    }
public:
    bool WordBreakI(string s, vector<string>& wordDict) {
        // Create a hashset of words for fast query.
        dict_=unordered_set<string>(wordDict.begin(),wordDict.end());
        return _break(s);
    }
};


//Cherry Pickup
//collect maximum number of cherries possible
class lc741 { //Hard
public:
    int CherryPickup(vector<vector<int>>& grid) {

    }
};

//Burst Balloons
//Find the maximum coins you can collect by bursting the balloons wisely.
class lc312 { //Hard
public:
    int BurstBalloons(vector<int>& nums) {
        //c[i][j] : maxCoins(nums[i]~nums[j]), ans=c[1][n]
        //c[i][j] : c[i][k-1]+nums[i-1]*nums[k]*nums[j+1]+c[k+1][j], i<=k<=j
        int n=nums.size();
        // padding 1, right and left most
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> c(n+2, vector<int>(n+2, 0));

        int i, j, k, len; //len: length between i and j, from 1 to n
        for(len=1;len<=n;len++)
            for(i=1;i<n-len+1;i++)
                for(j=i+len-1, k=i;k<=j;k++)
                    c[i][j]=max(c[i][j], c[i][k-1]+nums[i-1]*nums[k]*nums[j+1]+c[k+1][j]);
        return c[1][n];
    }
};

//Target Sum
//Find out how many ways to assign symbols to make sum of integers equal to target S.
class lc494 { //Medium
public:
    // time(N^2) space(N)
    int TargetSum(vector<int>& nums, int S) {
        //w[i][j] : # of ways to sum up to j using nums [0~i]
        //Let P denote a set of nums have + sign
        //Let N denote a set of nums have - sign
        //sum(P)-sum(N)=target, 出現在P的不會出現在N，所以這裡用-的
        //w[i][j]=w[i-1][j-nums[i]]+w[i-1][j+nms[i]], w[i][j]的值從這些pull過來
        //w[i+1][j+nums[i]]+=w[i][j]
        //w[i+1][j-nums[i]]+=w[i][j], 用w[i][j]去push(更新)那些值

        //以上會產生一個很大的sparse matrix來做為dp table, 以下做簡化
        //sum(P)-sum(N)=target
        //sum(P)-sum(N)+sum(P)+sum(N)=target+sum(P)+sum(N)
        //2sum(P)=target+sum(nums)
        // sum(P)=(target+sum(nums))/2
        // reduce to the 0/1 knapsack problem
        int n=nums.size();
        int tgt=abs(S), sum=accumulate(nums.begin(),nums.end(),0);
        int sumP=(tgt+sum)/2;
        if(sum<tgt||(sum+tgt)%2) return 0; //sum+tgt is a even num

        vector<int> w(tgt+1,0);
        w[0]=1;
        for(auto num:nums)
            for(int j=sumP;j>=num;j--) //從後往前算就可以不需要搬動上一state的資料
                w[j]+=w[j-num];
        return w[sumP];
    }
};

//Combination Sum IV
//Given an integer array with all positive numbers and no duplicates, find the
//number of possible combinations that add up to a positive integer target.
class lc377 { //Medium
public:
    int CombinationSumIV(vector<int>& nums, int target) {
        vector<int> state(target+1, 0);
        state[0]=1; // {} take none num
        for(int i=1;i<=target;i++)
            for(auto num:nums)
                if(i-num>=0)
                    state[i]+=state[i-num];
        return state[target];
    }
};

//Partition Equal Subset Sum
//Given a non-empty array containing only positive integers, find if the array
//can be partitioned into two subsets such that the sum of elements in both
//subsets is equal.
class lc416 { //Medium
public:
    bool PartitionEqualSubsetSum(vector<int>& nums) {
        int sum=accumulate(nums.begin(),nums.end(),0);
        if(sum%2) return false; //odd num can't equal partition

        vector<int> state(sum+1,0);
        state[0]=1; // taking none num can make 0
        //count all possible sum, once we found sum/2 is true,
        //there exists equal partition subset
        for(auto num:nums) {
            for(int i=sum;i>=0;i--)
                if(state[i]) state[i+num]=1;
            if(state[sum/2]) return true;
        }
        return false;
    }
};

//Knight Probability in Chessboard
//On an NxN chessboard, a knight starts at the r-th row and c-th
//column and attempts to make exactly K moves
//Return the probability that the knight remains on the board
//after it has stopped moving.
class lc688 { //Medium
public:
    //time(kN^2)
    double KnightProbabilityInChessboard(int N, int K, int r, int c) {
        vector<vector<int>> ways(N,vector<int>(N,0));
        int moves[8][2]={{1,2},{1,-2},{-1,2},{-1,-2},
                         {2,1},{2,-1},{-2,1},{-2,-1}};

        ways[0][0]=1;
        for(auto k=0;k<K;k++) {
            vector<vector<int>> way(N,vector<int>(N,0));
            for(auto i=0;i<N;i++)
                for(auto j=0;j<N;j++)
                    for(auto m=0;m<8;m++) {
                        int x=j+moves[m][0];
                        int y=i+moves[m][0];
                        if(x<0||y<0||x>=N||y>=N) continue;
                        way[i][j]+=ways[y][x];
                    }
            ways=way;
        }
        double total=0;
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                total+=ways[i][j];
        return total/pow(8,K);
    }
};

//Range Sum Query 2D - Immutable
//Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by
//its upper left corner (row1, col1) and lower right corner (row2, col2).
class lc304 { //Medium
private:
    vector<vector<int>> sums;
public:
    NumMatrix(vector<vector<int>> matrix) {
        int m=matrix.size(); if(!m) return 0;
        int n=matrix[0].size();
        sums=vector<vector<int>>(m+1, vector<int>(n+1, 0));
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<=n;x++)
                sums[y][x]=matrix[y-1][x-1] +
                           sums[y-1][x] +
                           sums[y][x-1] -
                           sums[y-1][x-1];
    }

    int RangeSumQuery2D(int row1, int col1, int row2, int col2) {
        return sums[row2+1][col2+1] -
               sums[row2+1][col1] -
               sums[row1][col2+1] +
               sums[row1][col1];
    }
};

//Range Sum Query - Immutable
//Given an integer array nums, find the sum of the elements between index i and j (i ≤ j), inclusive.
class lc303 { //Easy
private:
    vector<int> sums; // use 1-d table to do dp.
public:
    // time(n+m) space(n)
    lc303(vector<int> nums) {
        if(nums.empty()) return;
        sums=vector<int>(nums.size(),0);
        sums[0]=nums[0];
        for(auto i=1; i<nums.size(); i++)
            sums[i]=sums[i-1]+nums[i];
    }
    int RangeSumQuery1D(int i, int j) {
        if(!i) return sums[i];
        return sums[j]-sums[i-1];
    }
};

//Maximal Square
//Given a 2D binary matrix filled with 0's and 1's, find the largest
//square containing only 1's and return its area.
class lc221 { //Medium
public:
    int MaximalSquare(vector<vector<char>>& matrix) {
        int area=0,max_area=0;
        int m=matrix.size(); if(!m) return 0;
        int n=matrix[0].size();
        vector<vector<int>> areas(m+1, vector<int>(n+1,0));

        //time(N^3)
        //this methond can count any square/rectangle/matrix elements not 1
        //use dp to count the area between matrix[0][0]~matrix[y-1][x-1]
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<=n;x++)
                areas[y][x]=matrix[y-1][x-1]-'0' + areas[y-1][x] + areas[y][x-1]
                            - areas[y-1][x-1];
        //count any square area based above dp table, big square - little square
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<=n;x++)
                for(auto k=min(m-y-1,n-x-1);k>0;k--) { //from big k to little k
                    max_area=areas[y-1+k][x-1+k] -
                             areas[y-1+k][x-1] -
                             areas[y-1][x-1+k] +
                             areas[y-1][x-1];
                    if(k*k==area) //if area equal to k*k, mean all 1's within this square
                        {max_area=max(max_area,area);break;}//大的找到了，小的就不用找了
                }
        //==============================
        //time(N^2) space(N^2)
        //sine the matrix elements are all 1, find the max square during building dp table
        //find the min square among left/up/left-up + itself
        vector<vector<int>> square(m, vector<int>(n,0));
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<=n;x++) {
                square[y][x]=matrix[y][x]-'0';
                if(!square[y][x]) continue; //this element is 0, can't increase the area when including it.
                if(!y&&!x) continue; //square[0][0]
                if(!y) square[y][x]=square[y][x-1]+1; //square[0][j]
                else if(!x) square[y][x]=square[y-1][x]+1; //square[i][0]
                else square[y][x]=min(min(square[y-1][x],square[y][x-1]),square[y-1][x-1]) + 1;

                max_area=max(max_area, square[y][x]<<1);
            }
        return max_area;
    }
};

//Minimum Path Sum
//Given a m x n grid filled with non-negative numbers, find a path from top left to bottom
//right which minimizes the sum of all numbers along its path.
class lc064 { //Medium
public:
    // time(MN) space(1)
    int MinimumPathSum(vector<vector<int>>& grid) {
        int m=grid.size(); if(!m) return 0;
        int n=grid[0].size();

        for(int y=0;y<m;y++)
            for(int x=0;x<n;x++) {
                if(!y&&!x) continue;
                else if(!y) grid[y][x]+=grid[y][x-1];
                else if(!x) grid[y][x]+=grid[y-1][x];
                else grid[y][x]+=min(grid[y][x-1], grid[y-1][x]);
            }
        return grid[m-1][n-1];
    }
};

//Unique Paths II
//If some obstacles are added to the grids. How many unique paths would there be?
class lc063 { //Medium
public:
    int UniquePathsII(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(); if(!m) return 0;
        int n=obstacleGrid[0].size();
        vector<vector<int>> state(m+1,vector<int>(n+1,0));

        state[1][1]=1-obstacleGrid[0][0];
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<n;x++) {
                if(y==1&&x==1) continue;
                else if(obstacleGrid[y-1][x-1]) state[y][x]=0;
                else state[y][x]=state[y-1][x]+state[y][x-1];
            }
        return state[m][n];
    }
};

//Unique Paths
//The robot can only move either down or right at any point in time.
//The robot is trying to reach the bottom-right corner of the grid
//How many possible unique paths are there?
class lc062 { //Medium
public:
    int UniquePathsI(int m, int n) {
        if(m<=0||n<=0) return 0;
        vector<vector<int>> state(m+1, vector<int>(n+1,0));
        for(auto y=1;y<=m;y++)
            for(auto x=1;x<=n;x++)
                (y==1&&x==1) ? state[y][x]=1 : state[y][x]=state[y-1][x]+state[y][x-1];
    return state[m][n];
    }
};

//Predict the Winner
//Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from
//either end of the array followed by the player 2 and then player 1 and so on. Each time a player
//picks a number, that number will not be available for the next player. This continues until all
//the scores have been chosen. The player with the maximum score wins.
//Given an array of scores, predict whether player 1 is the winner. You can assume each player
//plays to maximize his score.
class lc486 { //Medium
private:
    unordered_map<int,int> scores;
    int _score(vector<int>& nums, int l, int r) //回傳這樣條件下能拿到最高的分數
    {
        if(l==r) return nums[l];
        int k = l*100 + r;
        if (!scores.count(k))
            //看從左邊拿得到的分數減去對手拿到的分數比較高，還是從右邊拿
            scores[k] = max(nums[l] - _score(nums, l+1, r), nums[r] - _score(nums, l, r-1));
        return scores[k];
    }
public:
    bool PredictTheWinner(vector<int>& nums) {
        return _score(nums, 0, nums.size()-1) >= 0; //大於0表示拿的分數比對手多
    }
};

//Longest Consecutive Sequence
//Unsorted array, find the length of longest "consecutive" sequence.
//[100, 4, 200, 1, 3, 2]->[1, 2, 3, 4]. Return its length: 4
class lc128 { //Hard
public:
    int LongestConsecutiveSequence(vector<int>& nums) {
        unordered_map<int, int> state;
        int l,r,max_len=0;
        for(auto n:nums) {
            if(state.count(n)) continue;
            if(state.count(n-1)&&state.count(n+1)) {
                l=state[n-1];r=state[n+1];
                state[n-1]=state[n]=state[n+1]=r+l+1;
            }else if(state.count(n-1)) {
                l=state[n-1];
                state[n-1]=state[n]=l+1;
            }else if(state.count(n+1)) {
                r=state[n+1];
                state[n]=state[n+1]=r+1;
            }else {
            }
            max_len=max(max_len, state[n]);
        }
        return max_len;
    }
};

//Number of Longest Increasing Subsequence
//Unsorted array, find the "number" of longest increasing subsequence.
//[1,3,5,4,7]->[1, 3, 4, 7] and [1, 3, 5, 7] return num 2
class lc673 { //Medium
public:
    int NumberOfLongestIncreasingSubsequence(vector<int>& nums) {
        // time(N^2) space(N)
        int n=nums.size(); if(!n) return 0;
        vector<int> state_len(n,1);
        vector<int> state_num(n,1);
        for(auto i=0;i<n;i++)
            for(auto j=0;j<i;j++)
                if(nums[i]>nums[j]) {
                    if(state_len[i]=state_len[j]+1)
                        {state_num[i]+=state_num[j];}
                    if(state_len[i]<state_len[j]+1)
                        {state_num[i] =state_num[j];state_len[i]=state_len[j]+1; }
                }
        int max_len=*max_element(state_len.begin(),state_len.end());
        int max_len_num=0;
        for(auto i=0;i<n;i++)
            if(state_len[i]==max_len)
                max_len_num+=state_num[i];
        return max_len_num;
    }
};

//Longest Increasing Subsequence
//Unsorted array, find the length of longest increasing subsequence.
//[10, 9, 2, 5, 3, 7, 101, 18]->[2, 3, 7, 101], return length 4
class lc300 { //Medium
public:
    int LongestIncreasingSubsequence(vector<int>& nums) {
        // time(N^2) space(N)
        int n=nums.size(); if(!n) return 0;
        vector<int> state(n,1);
        for(auto i=1;i<n;i++)
            for(auto j=0;j<i;j++)
                if(nums[i]>nums[j])
                    state[i]=max(state[i], state[j]+1);
        return *max_element(state.begin(),state.end());
    }
};

//Longest Continuous Increasing Subsequence
//Unsorted array, find the length of longest "continuous" increasing subsequence.
//[1,3,5,4,7]->[1,3,5], return length 3.
class lc674 { //Easy
public:
    int LongestContinuousIncreasingSubsequence(vector<int>& nums) {
        //time(N) space(1)
        int len_cur=1, len_max=INT_MIN;
        if(nums.empty()) return 0;
        for(auto i=1; i<nums.size(); i++) {
            if(nums[i]>nums[i-1]) len_cur++;
            else len_cur=1;
            len_max=max(len_max, len_cur);
        }
        return len_max;
    }
};

//Find Pivot Index
//Given an array of integers nums, write a method that returns the "pivot" index of this array.
//Pivot index is the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.
class lc724 { //Easy
public:
    int FindPivotIndex(vector<int>& nums) {
        int l=0, r=accumulate(nums.begin(),nums.end(),0);
        for(int i=0;i<nums.size();i++) {
            r-=nums[i];
            if(r==l) return i;
            l+=nums[i];
        }
        return -1;
    }
};

//Delete and Earn
//In each operation, you pick any nums[i] and delete it to earn nums[i] points.
//After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.
//Return the maximum number of points you can earn by applying such operations.
class lc740 { //Medium
public:
    int DeleteAndEarn(vector<int>& nums) {
        if(nums.empty()) return 0;
        // reduce the problem to lc198
        auto range=minmax_element(nums.begin(),nums.end());
        int l=*(range.first); int r=*(range.second);
        vector<int> points(l-r+1,0);
        for(auto num:nums)
            points[num-l]+=num;
        // then do the same thing as lc198
        int sCurr=0, sPre1=0, sPre2=0;
        for(int i=0;i<points.size();i++) {
            sCurr=max(points[i]+sPre2, sPre1);
            sPre2=sPre1; sPre1=sCurr;
        }
        return sCurr;
    }
};

//House Robber
//Given a list of non-negative integers representing the amount of money of
//each house, determine the maximum amount of money you can rob tonight without
//alerting the police.
class lc198 { //Easy
public:
    // time(N) space(1)
    int HouseRobber(vector<int>& nums) {
        int n=nums.size(); if(!n) return 0;

        int sCurr=0, sPre1=0, sPre2=0;
        for(int i=0;i<n;i++) {
            sCurr=max(nums[i]+sPre2, sPre1);
            sPre2=sPre1;sPre1=sCurr;
        }
        return sCurr;
    }
};

//Prime Number of Set Bits in Binary Representation
//Given two integers L and R, find the count of numbers in the range [L, R] (inclusive)
//having a prime number of set bits in their binary representation.
class lc762 { //Easy
private:
    int bits(int n) { // count how many 1s in a number's binary representation
        int cnt=0;
        while(n){ cnt += n&1; n>>=1;}
        return cnt;
    }
public:
    // time(N) space(1)
    //10^6最多需要20bits來表示，共有2,3,5,7,11,13,17,19這七種1個數為質數
    //665772其第2,3,5,7,11,13,17,19個bit為1
    int PrimeNumberOfSetBitsInBinaryRepresentation(int L, int R) {
        constexpr int MAGIC=665772; int cnt=0;
        for(int n=L;n<=R;n++)
            if(MAGIC&(1<<bits(n))) cnt++;
        return cnt;
    }
};

//Best Time to Buy and Sell Stock with Cooldown
//Design an algorithm to find the maximum profit.
class lc309 { //Medium
public:
    int BestTimeBuySellStockCooldown(vector<int>& prices) {
        //time(N),
        //3 actions: buy,sell,down
        //3 states after some action : hold, sold, rest.
        //sold[i]=hold[i-1]+prices[i]
        //hold[i]=max(hold[i-1],rest[i-1]-prices[i])
        //rest[i]=max(rest[i-1],sold[i-1])
        //ans:max(rest[i], sold[i])
        int sold_prev=0, rest_prev=0, hold_prev=INT_MIN;
        int sold_curr, rest_curr, hold_curr;
        for(auto price:prices) {
            sold_curr=hold_prev+price;
            hold_curr=max(hold_prev, rest_prev-price);
            rest_curr=max(rest_prev, sold_prev);
            sold_prev=sold_curr;
            hold_prev=hold_curr;
            rest_prev=rest_curr;
        }
        return max(rest_curr,sold_curr);
    }
};

//Best Time to Buy and Sell Stock
//If you were only permitted to complete at most one transaction (ie, buy one
//and sell one share of the stock), design an algorithm to find the maximum profit.
class lc121 { //Easy
public:
    // time(N) space(1)
    int BestTimeBuySellStock(vector<int>& prices) {
        int n=prices.size(); if(n<2) return 0;
        int min_price=INT_MAX, max_profit=INT_MIN;
        for(int i=0;i<n;i++){
            min_price =min(min_price,prices[i]);
            max_profit=max(max_profit,prices[i]-min_price);
        }
        return max_profit;
    }
};

//Min Cost Climbing Stairs
//Find minimum cost to reach the top of the floor, and you can either start
//from the step with index 0, or the step with index 1.
class lc746 { //Easy
public:
    // time(N) space(1)
    int MinCostClimbingStairs(vector<int>& cost) {
        int n=cost.size(); if(!n) return 0;

        //dp(n):min cost to climb to n-th stair
        //dp(n)=min(dp(n-1)+cost[n-1], dp(n-1)+cost[n-2)
        int sCurr=0, sPre1=0, sPre2=0;
        for(int i=2;i<=n;i++) {
            sCurr=min(cost[i-1]+sPre1, cost[i-2]+sPre2);
            sPre2=sPre1;sPre1=sCurr;
        }
        return sCurr;
    }
};

//Climbing Stairs
//It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps.
//In how many distinct ways can you climb to the top?
class lc070 { //Easy
public:
    int ClimbingStairs(int n) {
        // time(N) space(N)
        vector<int> state(n+1,0);
        state[0]=1; state[1]=1; state[2]=2;
        for(auto i=3; i<=n; i++)
            state[i]=state[i-1]+state[i-2];
        return state[n];
        //==============================
        // time(N) space(1)
        int sCurr, sPre1=1, sPre2=2;
        for(auto i=3; i<=n; i++) {
            sCurr=sPre1+sPre2;
            sPre2=sPre1;sPre1=sCurr;
        }
        return sCurr ;
    }
};

//Maximum Subarray
//Find the contiguous subarray within an array (containing at least
//one number) which has the largest sum.
class lc053 { //Easy
public:
    int MaximumSubarray(vector<int>& nums) {
        // time(N) space(N)
        // accu[i]=accu[i-1]>0 ? nums[i]+accu[i-1] : nums[i], 若前一個是負數則捨棄不加入
        vector<int> accu(nums.size());
        accu[0]=nums[0];
        for(auto i=1; i<nums.size(); i++)
            accu[i] = (accu[i-1]>0) ? nums[i]+accu[i-1] : nums[i];
        return *max_element(accu.begin(), accu.end());
        //==============================
        // time(N) space(1)
        int sCurr, sPre1=nums[0], max_val=INT_MIN;
        for(auto i=1; i<nums.size(); i++) {
            sCurr = max(nums[i]+sPre1 , nums[i]);
            max_val=max(max_val,sCurr);
            sPre1 = sCurr
        }
        return max_val;
    }
};

//Given 3 numbers {1, 3, 5}, we need to tell
//the total number of ways we can form a number 'N'
int _Num_1_3_5_FormN(int n)
{
    if(n<0) return 0;
    else if(n==0) return 1;
    else return _Num_1_3_5_FormN(n-1)+_Num_1_3_5_FormN(n-3)+_Num_1_3_5_FormN(n-5);
    //==============================
    vector<int> state(128,-1);
    // memoization, top down
    if(n<0) return 0;
    else if(n==0) return 1;
    else if(state[n]!=-1) return state[n];
    else return state[n]=_Num_1_3_5_FormN(n-1)+_Num_1_3_5_FormN(n-3)+_Num_1_3_5_FormN(n-5);
    //==============================
    // tabulation, bottom up
    state[0]=1;state[1]=1;state[2]=1;state[3]=2;state[4]=3;
    for(auto i=5; i<=n; i++)
        state[i]=state[i-1]+state[i-3]+state[i-5];
    return state[n];
}

int _FibonacciNum(int n)
{
    vector<int> state(128,-1);
    // memoization, top down
    if(n<=1) return n;
    else if(state[n]!=-1) return state[n];
    else return state[n]=_FibonacciNum(n-1)+_FibonacciNum(n-2);
    //==============================
    // tabulation, bottom up
    state[0]=0;state[1]=1;
    for(auto i=2;i<=n;i++)
        state[i]=state[i-1]+state[i-2];
    return state[n];
    //==============================
    // space(1)
    int sCurr=0, sPre1=1, sPre2=0;
    for(auto i=2;i<=n;i++) {
        sCurr=sPre1+sPre2;
        sPre2=sPre1; sPre1=sCurr;
    }
}

int _BinomialCoeff_PascalTriangle(int n, int k)
{
    vector<int> coeff(k+1, 0);

    coeff[0]=1;
    // Compute next row of pascal triangle using the previous row
    for(auto i=1; i<=n; i++)
        for(auto j=min(i,k); j>0; j--)
            coeff[j]=coeff[j]+coeff[j-1];
    return coeff[k];
}

void _LongestCommonSubsequence(string x,string y)
{
    int m=x.size(), n=y.size();
    vector<vector<int>> state(m+1, vector<int>(n+1,0));
    stack<char> s;

    for(auto i=1; i<=m; i++)
        for(auto j=1; j<=n; j++) {
            if(x[i-1]==y[j-1]) state[i][j]=state[i-1][j-1]+1;
            else state[i][j]=max(state[i-1][j], state[i][j-1]);
        }
    cout<<"the length of s is "<<state[m][n]<<endl;

    for(auto i=m, j=n; i>0&&j>0; ){
        // If current character in X[] and Y are same, then current character is part of S
        if (x[i-1]==y[j-1]) {
          s.push(x[i-1]); // Put current character in result
          i--; j--;         // reduce values of i, j and index
        }
        // If not same, then find the larger of two and go in the direction of larger value
        else if (state[i-1][j]>state[i][j-1])
            i--;
        else
            j--;
    }
    while(!s.empty()) {cout<<s.top();s.pop();}
}

#if 0
int main(void)
{
    //cout<<Num_1_3_5_FormN(6)<<endl;
    //cout<<FibonacciNum(9)<<endl;
    //cout<<BinomialCoeff(5, 2)<<endl;
    _LongestCommonSubsequence("AGGTAB", "GXTXAYB");

    cout<<endl<<"Hello";
    return 0;
}
#endif
