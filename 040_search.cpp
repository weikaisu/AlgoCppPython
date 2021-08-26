#include "leetcode.h"

//Contain Virus
//A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
class lc749 { //Hard
public:
    int ContainVirus(vector<vector<int>>& grid) {

    }
};

//Sudoku Solver
//Write a program to solve a Sudoku puzzle by filling the empty cells.
class lc037 { //Hard
public:
    void SudokuSolver(vector<vector<char>>& board) {

    }
};

//Zuma Game
class lc488 { //Hard
public:
    int ZumaGame(string board, string hand) {

    }
};

//Cut Off Trees for Golf Event
//You are asked to cut off all the trees in this forest in the order of tree's
//height - always cut off the tree with lowest height first
class lc675 { //Hard
public:
    int CutOffTreesForGolfEvent(vector<vector<int>>& forest) {

    }
};

//N-Queens
//Placing n queens on an n��n chessboard such that no two queens attack each other.
class lc051 { //Hard
public:
    vector<vector<string>> NQueen(int n) {

    }
};

//==================================DFS +
//Cracking the Safe
//Return any string of minimum length that is guaranteed to open the box after the entire string is inputted.
class lc753 { //Hard
private:
    unordered_set<string> visited;
    string res;
    int max_digit;
    void _dfs(const string& node) {
        for(char c='0';c<max_digit+'0';c++) {
            string next=node+c;
            if(visited.count(next)) continue;
            visited.insert(next);
            _dfs(next.substr(1));
            res.push_back(c);
        }
    }
public:
    string CrackingSafe(int n, int k) {
        //�b De Bruijn Graph ���� Hamiltonian Path �Y�� De Bruijn Sequence
        string node(n-1,0);
        _dfs(node);
        return res+node;
    }
};

//Remove Invalid Parentheses
//Remove the minimum number of invalid parentheses in order to make the input string valid.
class lc301 { //Hard
private:
    vector<string> res;
    bool _valid(const string& s) { // check whether a string is valid
        int cnt=0;
        for(auto ch:s) {
            if(ch=='(') cnt++;
            if(ch==')') cnt--;
            if(cnt<0) return false; // �k�A���e�S�����A��
        }
        return !cnt;
    }
    void _dfs(const string& word, int start_idx, int l, int r) {
        // no illegal left/right parentheses, push the word the the res
        if(!l&&!r) {if (_valid(word)) res.push_back(word); return;}

        for(int i=start_idx;i<word.size();i++) {
            //sikp consecutive pare, only hand the 1st one
            if(i!=start_idx&&word[i]==word[i-1]) continue;
            //skip none-pare
            if(word[i]!='('||word[i]!=')') continue;
            //handle illegal right pare first
            if(r && word[i]==')') _dfs(word.substr(1), i, l, r-1);
            if(l && word[i]=='(') _dfs(word.substr(1), i, l-1, r);
        }
    }
public:
    vector<string> RemoveInvalidParentheses(string s) {
        int l_par=0, r_par=0;

        //step 1, count illegal left/right parentheses
        for(char ch:s) {
            l_par+=(ch=='(');
            (!l_par) ? r_par+=(ch==')') : l_par-=(ch==')');
        }
        _dfs(s, 0, l_par, r_par);
        return res;
    }
};

//Expression Add Operators
//Given a string that contains only digits 0-9 and a target value, return all possibilities
//to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
class lc282 { //Hard ,advanced version of lc494
public:
    vector<string> ExpressionAddOperators(string num, int target) {

    }
};

//Next Closest Time
class lc681 { //Medium
private:
    vector<int> curr;
    int tgt_time, min_time;
    int _timeMin(int h, int m) {return h*60+m;}
    int _timeDif(int t1, int t2) {
        if(t1==t2) return INT_MAX;
        return ((t2-t1)+24*60)%(24*60);
    }
    void _dfs(vector<int>& digits, int d) {
        if(d==4) {
            int h=curr[0]*10+curr[1];
            int m=curr[2]*10+curr[3];
            int time=_timeMin(h,m);

            if(h>23||m>59) return;
            if(_timeDif(time,tgt_time)<_timeDif(min_time,tgt_time))
                min_time=time;
            return;
        }
        for(auto digit:digits) {
            curr[d]=digit;
            _dfs(digits,d+1);
        }

    }
public:
    string NextClosestTime(string time) {
        vector<int> digits={time[0]-'0', time[1]-'0', time[3]-'0', time[4]-'0'};
        int h=digits[0]*10+digits[1];
        int m=digits[2]*10+digits[3];
        tgt_time=min_time=_timeMin(h,m);
        _dfs(digits,0);

        char buff[5];
        sprintf(buff, "%02d:%02d", min_time/60, min_time%60);
    }
};

//Letter Combinations of a Phone Number
//Given a digit string, return all possible letter combinations that the number could represent.
class lc017 { //Medium
private:
    string curr;
    vector<string> ans;
    vector<vector<char>> phone{{' '},
                               {},
                               {'a','b','c'},
                               {'d','e','f'},
                               {'g','h','i'},
                               {'j','k','l'},
                               {'m','n','o'},
                               {'p','q','r','s'},
                               {'t','u','v'},
                               {'w','x','y','z'}};

    void _dfs(string digits, int d) {
        if(d==digits.size()) {ans.push_back(curr);return;}

        for(auto c:phone[digits[d]-'0']) {
            curr.push_back(c);
            _dfs(digits, d+1);
            curr.pop_back();
        }
    }
public:
    vector<string> LetterCombinationsOfPhoneNumber(string digits) {
        if(digits.empty()) return {};

        _dfs(digits, 0);
        return ans;
    }
};

//Friend Circles
//Output the total number of friend circles among all the students.
class lc547 { //Medium
private:
    int n, num=0;
    void _dfs(vector<vector<int>>& M, int curr) {
        for(int i=0;i<n;i++) {
            if(!M[curr][i]) continue;
            M[curr][i]=M[curr][i]=0;
            _dfs(M, i);
        }
    }
public:
    int FindCircleNum(vector<vector<int>>& M) {
        if(M.empty()) return 0;
        n=M.size();

        for(int i=0;i<n;i++) {
            if(!M[i][i]) continue; // take M[i][i] as the visited[i];
            num++;
            _dfs(M, i);
        }
    }
};

//Coin Change
//Write a function to compute the fewest number of coins that you need to make up that amount.
class lc322 { //Medium
private:
    int min_coins=INT_MAX;
    void _dfs(vector<int>& coins, int start_idx, int coin_cnt, int lave) {
        if(start_idx==coins.size()) return; // no coin could be used
        if(!lave) {min_coins=min(min_coins,coin_cnt); return;}

        int coin=coins[start_idx];
        for(int i=lave/coin;i>=0&&i+coin_cnt<min_coins;i--) // pruning : i+coin_cnt<min_coins
            _dfs(coins, start_idx+1, i+coin_cnt, lave-i*coin);
    }
public:
    int CoinChange(vector<int>& coins, int amount) {
        // greedy+dfs+pruning
        sort(coins.rbegin(),coins.rend()); // descending sort
        _dfs(coins, 0, 0, amount);
        return min_coins==INT_MAX ? -1 : min_coins;
    }
};

//Number of Islands
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
class lc200 { //Medium
private:
    int m,n;
    void _dfs(vector<vector<char>> &grid,int x,int y)
    {
        if(x<0||x==n||y<0||y==m||grid[y][x]=='0') return;
        grid[y][x]='0';
        _dfs(grid,x-1,y);
        _dfs(grid,x+1,y);
        _dfs(grid,x,y-1);
        _dfs(grid,x,y+1);
    }
public:
    int NumOflands(vector<vector<char>>& grid) {
        //For every land, visit its neighbor land using DFS until there is no such land
        //Mark every visited node as 0
        if(grid.empty()) return 0;
        m=grid.size(); if(!m) return 0;
        n=grid[0].size(); if(!n) return 0;

        int res=0;
        for(auto y=0; y<m; y++)
            for(auto x=0; x<n; x++) {
                res+=grid[y][x]-'0';
                _dfs(grid,x,y);
            }
        return res;
    }
};

//Word Search
//Given a 2D board and a word, find if the word exists in the grid.
class lc079 { //Medium
private:
    int m,n;
    bool _dfs(vector<vector<char>>& board, string word, int x, int y, int d) {
        if(x<0||x==n||y<0||y==m||board[y][x]!=word[d]) return false;
        if(d==word.size()-1) return true;

        char curr=board[y][x];
        board[y][x]= 0;
        bool found=_dfs(board, word, x+1, y, d+1) ||
                   _dfs(board, word, x-1, y, d+1) ||
                   _dfs(board, word, x, y+1, d+1) ||
                   _dfs(board, word, x, y-1, d+1);
        board[y][x]=curr;
        return found;
    }
public:
    bool WordSearch(vector<vector<char>>& board, string word) {
        if(!word.size()) return false;
        m=board.size(); if(!m) return false;
        n=board[0].size(); if(!n) return false;

        for(int y=0;y<m;y++)
            for(int x=0;x<n;x++) {
                if(_dfs(board, word, x, y, 0)) return true;
            }
        return false;
    }
};

//Flood Fill
//Given a coordinate (sr, sc) representing the starting pixel (row and column)
//of the flood fill, and a pixel value newColor, "flood fill" the image.
class lc733 { //Easy
private:
    int m,n,old_color,new_color;
    void _dfs(vector<vector<int>>& img, int x, int y){
        if(x<0||x>=n||y<0||y>=m||img[y][x]!=old_color) return;
        img[y][x]=new_color;
        _dfs(img,x-1,y);
        _dfs(img,x+1,y);
        _dfs(img,x,y-1);
        _dfs(img,x,y+1);
    }
public:
    vector<vector<int>> FloodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        old_color=image[sr][sc];new_color=newColor; if(old_color==new_color) return image;
        m=image.size(); if(!m) return {};
        n=image[0].size(); return {};

        _dfs(image, sc, sr);
        return image;
    }
};

//Max Area of Island
class lc695 { //Easy
private:
    int m,n,max_area=0;
    int _dfs(vector<vector<int>>& grid, int x, int y) {
        if(x<0||x==m||y<0||y==n||!grid[y][x]) return 0;
        grid[y][x]=0;
        return _dfs(grid, x-1, y) +
               _dfs(grid, x+1, y) +
               _dfs(grid, x, y-1) +
               _dfs(grid, x, y+1) + 1;
    }
public:
    int MaxAreaOfIsland(vector<vector<int>>& grid) {
        m=grid.size(); if(!m) return 0;
        n=grid[0].size();

        for(int y=0;y<m;y++)
            for(int x=0;x<n;x++)
                max_area=max(max_area, _dfs(grid, x, y));
        return max_area;
    }
};

//Letter Case Permutation
//Given a string S, we can transform every letter individually to be lowercase or
//uppercase to create another string.  Return a list of all possible strings we could create.
class lc784 { //Easy
    // upper case A-Z: 65-90
    // lower case a-z: 97-122
    // 'a'-'A'=97-65=32(0x100000)
private:
    vector<string> res;
    void _dfs(string str, int d) {
        if(d=str.size()) {res.push_back(str); return;}
        _dfs(str, d+1); //don't care d is alpha/digit, ask for d+1

        if(!isalpha(str[d])) return;
        str[d]^=32; // if d isn't digit, change to lower/upper case and ask for d+1
        _dfs(str, d+1);
        str[d]^=32;
    }
public:
    vector<string> LetterCasePermutation(string S) {
        _dfs(S,0);
        return res;
    }
};
//==================================DFS -

//==================================BFS +
//Sliding Puzzle
//Given a puzzle board, return the least number of moves required so that the state of the board is solved.
class lc773 { //Hard
public:
    int SlidingPuzzle(vector<vector<int>>& board) {

    }
};

//Word Ladder II
//Find all shortest transformation sequence(s) from beginWord to endWord
class lc126 { //Hard
public:
    vector<vector<string>> WordLadderII(string beginWord, string endWord, vector<string>& wordList) {

    }
};

//Word Ladder
//Find the shortest transformation sequence from beginWord to endWord
class lc127 { //Medium
public:
    int WordLadderI(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(),wordList.end());
        if(!dict.count(endWord)) return 0;
        int len=beginWord.size(), steps=0;

        //BFS
        queue<string> q; int q_size=0; q.push(beginWord);
        while(q_size=q.size()) {
            steps++;
            while(q_size--) {
                string word=q.front(); q.pop();
                for(int i=0;i<len;i++) { // 0~word_length
                    char ch=word[i];
                    for(int j='a';j<='z';j++) { // a~z
                        word[i]=j;
                        if(word==endWord) return steps+1; //hit the endWord
                        if(!dict.count(word)) continue; //not in dict, skip
                        dict.erase(word); //in dict, remove the word from dict
                        q.push(word);
                    }
                    word[i]=ch;
                }
            }
        }
        return 0;

        //Bidirectional BFS
        unordered_set<string> q_top{beginWord};
        unordered_set<string> q_bot{endWord};
        while(q_top.size()||q_bot.size()) {
            steps++;
            if(q_top.size()>q_bot.size())
                swap(q_top,q_bot);// always handle smaller queue first
            unordered_set<string> q;
            for(auto word:q_top) {
                for(int i=0;i<len;i++) { // 0~word_length
                    char ch=word[i];
                    for(int j='a';j<='z';j++) {
                        word[i]=j;
                        if(q_bot.count(word)) return steps+1; //hit the word also in bottom queue
                        if(!dict.count(word)) continue; //not in dict.skip
                        dict.erase(word); //in dict, remove the word from dict
                        q.insert(word);
                    }
                    word[i]=ch;
                }
            }
            swap(q,q_top);
        }
        return 0;
    }
};

//Open the Lock
//Given a target representing the value of the wheels that will unlock the lock,
//return the minimum total number of turns required to open the lock
class lc752 { //Medium
public:
    int OpenLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());
        unordered_set<string> visited{"0000"};

        if(dead.count("0000")) return -1;
        if(target=="0000") return 0;

        int steps=0;
        queue<string> q; int q_size=0; q.push("0000");
        while(q_size=q.size()) {
            steps++;
            while(q_size--) {
                string next=q.front(); q.pop();
                for(int i=0;i<4;i++) // digits 1~4
                    for(int j=-1;j<=1;j+=2) { // -1, +1
                        next[i]=(next[i]-'0'+j+10)%10 + '0';
                        if(dead.count(next)||visited.count(next)) continue;
                        if(next==target) return steps;
                        q.push(next); visited.insert(next);
                    }
            }
        }
        return -1;
    }
};

//Given a data structure of employee information
//return the total importance value of this employee and all his subordinates.
class lc690 { //Easy
public:
    //Build the relation tree and do BFS using queue
    int GetImportance(vector<Employee*> employees, int id) {
        //time(N) space(N)
        unordered_map<int, Employee*> id_table;
        for(auto e:employees)
            id_table.emplace(e->id,e);

        queue<int> q; q.push(id); int value=0;
        while(q.size()) {
            auto i=id_table[q.front()]; q.pop();
            value+=i->importance;
            for(auto sub:i->subordinates) q.push(sub);
        }
        return value;
    }
};
//==================================BFS -

//==================================Permutation/Combination +
//Can I Win
//The player who first causes the running total to reach or exceed 100 wins.
class lc464 { //Medium
private:
    int size, tgt;
    vector<char> tried; // 0: unknown, 1: won, -1: lost
    // reduce the problem from permutation to combination
    bool _com(int tgt, int used) { // less than 32 nums, use int to recorded the used nums
        if(tgt<0) return false;
        if(tried[used]) return tried[used]==1;

        for(int i=0;i<size;i++) {
            if(used&(1<<i)) continue; // number i used
            if(!_com(tgt-i,used|(1<<i))) return tried[used]=true; // The next player can not win, current player wins
        }
        return tried[used]=false; // Current player loses
    }
public:
    bool CanIWin(int maxChoosableInteger, int desiredTotal) {
        size=maxChoosableInteger; tgt=desiredTotal;
        if(size*(size+1)/2 < tgt) return false;
        if(tgt<=0) return true;

        tried=vector<char>(1<<size, 0);
        return _com(tgt,0);
    }
};

//Combination Sum III
//k numbers that add up to a number n, only use num 1~9
class lc216 { //Medium
private:
    vector<int> curr;
    vector<vector<int>> ans;
    void _com(int k, int tgt, int start_pos) {
        if(!k&&!tgt) {ans.push_back(curr);return;}
        for(int i=start_pos;i<10;i++) {
            if(i>tgt) break;
            curr.push_back(i);
            _com(k-1, tgt-i, i+1);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> CombinationSum3(int k, int n) {
        _com(k, n, 1);
        return ans;
    }
};

//Combination Sum II
//Each number may only be used once in the combination.
class lc040 { //Medium
private:
    vector<int> curr;
    set<vector<int>> ans;

    void _com(vector<int> &nums, int tgt, int start_pos) {
        if(!tgt) {ans.insert(curr);return;}

        for(int i=start_pos;i<nums.size();i++) {
            if(nums[i]>tgt) break;
            curr.push_back(nums[i]);
            _com(nums,tgt-nums[i],i+1); //number can NOT be chosen repeatedly
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> CombinationSum2(vector<int>& candidates, int tgt) {
        sort(candidates.begin(),candidates.end());
        _com(candidates,tgt,0);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};

//Combination Sum
//The same repeated number may be chosen unlimited number of times.
class lc039 { //Medium
private:
    vector<int> curr;
    vector<vector<int>> ans;

    void _com(vector<int> &nums, int tgt, int start_pos) {
        if(!tgt) {ans.push_back(curr);return;}

        for(int i=start_pos;i<nums.size();i++) {
            if(nums[i]>tgt) break;
            curr.push_back(nums[i]);
            _com(nums,tgt-nums[i],i); //number can be chosen repeatedly
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> CombinationSum1(vector<int>& candidates, int tgt) {
        sort(candidates.begin(),candidates.end());
        _com(candidates,tgt,0);
        return ans;
    }
};

void _per(vector<int> &nums, int depth, int m,
          vector<int> &curr, vector<vector<int>> &ans,
          vector<bool> &used)
{
    if(depth==m)// && (accumulate(curr.begin(),curr.end(),0)==8)) //a target needed to be satisfied
        {ans.push_back(curr); return;}
    for (int i=0;i<nums.size();i++) {
        if(used[i]) continue;
        curr.push_back(nums[i]); used[i]=true;
        _per(nums, depth+1, m, curr, ans, used);
        curr.pop_back(); used[i]=false;
    }
}
void _com(vector<int> &nums, int depth, int m,
          vector<int> &curr, vector<vector<int>> &ans,
          int start_pos)
{
    if(depth==m)
        {ans.push_back(curr); return;}
    for(int i=start_pos;i<nums.size();i++) {
        curr.push_back(nums[i]);
        _com(nums, depth+1, m, curr, ans, i+1);
        curr.pop_back();
    }
}
void permutation(vector<int> nums, int n, int m)
{
    vector<int> curr;
    vector<vector<int>> ans;
    vector<bool> used(nums.size(),false);
    _per(nums, 0, m, curr, ans, used);

    for(int i=0;i<ans.size();i++) {
        for(int j=0;j<ans[i].size();j++)
            cout<<ans[i][j]<<' ';
        cout<<endl;
    }
    cout<<"P("<<n<<","<<m<<")="<<ans.size()<<endl;
}
void combination(vector<int> nums, int n, int m)
{
    vector<int> curr;
    vector<vector<int>> ans;
    _com(nums, 0, m, curr, ans, 0);

    for(int i=0;i<ans.size();i++) {
        for(int j=0;j<ans[i].size();j++)
            cout<<ans[i][j]<<' ';
        cout<<endl;
    }
    cout<<"C("<<n<<","<<m<<")="<<ans.size()<<endl;
}
//==================================Permutation/Combination -

#if 0
int main(void)
{
    int  data[]={10, 1, 2, 7, 6, 1, 5};
    //int  data[]={2, 3, 6, 7};
    vector<int> nums; vector<vector<int>> ans;
    nums.assign(data, data+(sizeof(data)/4));
    //permutation(nums, 5, 3);
    //combination(nums, 5, 3);
    lc040 question;
    ans=question.combinationSum2(nums, 8);
    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++)
            cout<<ans[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl<<"Hello Search";
    return 0;
}
#endif
