#include "leetcode.h"

//Number of Atoms
class lc726 { //Hard
public:
    string countOfAtoms(string formula) {

    }
};

//Prefix and Suffix Search
//Return the word with given prefix and suffix with maximum weight.
class lc745 { //Hard
public:
    WordFilter(vector<string> words) {

    }

    int f(string prefix, string suffix) {

    }
};

//Shortest Palindrome
class lc214 { //Hard
public:
    string shortestPalindrome(string s) {

    }
};

//Implement Magic Dictionary
//given a word, and judge whether you modify exactly one character into another character
//in this word, the modified word is in the dictionary you just built.
class lc676 { //Medium
public:
    /** Initialize your data structure here. */
    MagicDictionary() {

    }

    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {

    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {

    }
};

//Partition Labels
//A string S of lowercase letters is given. We want to partition this string into as many parts
//as possible so that each letter appears in at most one part.
//return a list of integers representing the size of these parts.
class lc763 { //Medium
public:
    vector<int> partitionLabels(string S) {
        // time(N^2) 找到最後一次出現和當前相同的字符
        // time(N) 將每個字符最後出現的位置記下來
        vector<int> last_idx(128,0); // 128 ASCII char
        vector<int> res;
        for(int i=0;i<S.size();i++)
            last_idx[S[i]]=i;
        int start=0, end=0;
        for(int i=0;i<S.size();i++) {
            end=max(end,last_idx[i]);
            if(end==i) { //當前idx就是目前最大間距的char的最後的位置，所以可以自成一chunk
                res.push_back(start-end+1);
                start=end+1;
            }
        }
        return res;
    }
};

//Exclusive Time of Functions
class lc636 { //Medium
public:
    // use stack to simulate function calls
    vector<int> ExclusiveTimeOfFunctions(int n, vector<string>& logs) {
        vector<int> res;
        char action[6];
        int fid, pre_time, cur_time;
        stack<int> call_stack;

        for(auto log:logs) {
            sscanf(log.c_str(), "%d:%[a-z]:%d", &fid, action, &cur_time);
            if(action=="start") {
                if(call_stack.size())
                    res[call_stack.top()]+=cur_time-pre_time;
                call_stack.push(fid);
            }
            if(action=="end") {
                res[call_stack.top()]+=cur_time-pre_time+1;
                call_stack.pop();
                pre_time=cur_time+1;
            }
        }
        return res;
    }
};

//Shortest Completing Word
class lc748 { //Medium
private:
    int min_len=INT_MAX;
    vector<int> l_table;
    string res;
    bool _match(string str){
        vector<int> w_table(26,0);
        for(auto c:str)
            w_table[tolower(c)-'a']++;
        for(int i=0;i<26;i++)
            if(w_table[i]<l_table[i]) return false;
        return true;
    }
public:
    string ShortestCompletingWord(string licensePlate, vector<string>& words) {
        l_table=vector<int>(26,0);
        for(auto c:licensePlate)
            if(isalpha(c)) l_table[tolower(c)-'a']++;
        for(auto s:words) {
            if(s.size()>=min_len) continue;
            if(!_match(s)) continue;
            min_len=s.size();
            res=s;
        }
        return res;
    }
};

//Map Sum Pairs
//Return the sum of all the pairs' value whose key starts with the prefix.
class lc677 { //Medium
private:
    unordered_map<string,int> dict;
    unordered_map<string,int> prefix;
public:
    MapSumPairs(){}
    void MapSumPairsInsert(string key, int val) {
        int inc=val;
        if(dict.count(key))
            inc-=dict[key];
        dict[key]=val;
        for(int i=1;i<=key.size();i++)
            prefix[key.substr(0,i)]+=inc;
    }
    int MapSumPairsSum(string str) {
        return prefix[str];
    }
};

//Given an integer, return its base 7 string representation.
string convertToBase7(int num)
{
    bool isNega=num<0; string res;
    num=abs(num);
    do {
        res=to_string(num%7)+res;
        num/=7;
    } while(num>0); // when num is 0, this loop run at least once
    if(isNega) res='-'+res;
    return res;
} // leetcode504

//You are given a string representing an attendance record for a student.
//The record only contains the following three characters:
//'A' : Absent. 'L' : Late. 'P' : Present.
//A student could be rewarded if his attendance record doesn't contain more
//than one 'A' (absent) or more than two continuous 'L' (late).
bool checkRecord_regex_search(string s)
{
#if 1
    // C++11 regular expression
    return regex_search(s, regex("A.*A|LLL"));
#else
    int abse_cnt=0; int late_cnt=0;
    for(const char i:s) {
        if(i=='A') abse_cnt++;
        if(i=='L') late_cnt++;
        else late_cnt=0;
        if(abse_cnt>1||late_cnt>2) return false;
    }
    return true;
#endif // 1
} // leetcode 551

//Initially, there is a Robot at position (0, 0). Given a sequence of its moves,
//judge if this robot makes a circle, which means it moves back to the original place.
bool judgeCircle(string moves)
{   //time(1), space(1)
    unordered_map<char, int> table;
    table['L']=table['R']=table['U']=table['D']=0;
    for(const char move:moves)
        table[move]++;
    return table.count('L')==table.count('R')&&
           table.count('U')==table.count('D');
} //leetcode 657

//Given two lists A and B, and B is an anagram of A. B is an anagram of A means B
//is made by randomizing the order of the elements in A.
//We want to find an index mapping P, from A to B. A mapping P[i] = j means the
//ith element in A appears in B at index j.
vector<int> anagramMappings(vector<int>& A, vector<int>& B)
{
    vector<int> res; map<int,int> table;
    for(auto i=0; i<B.size(); i++)
        table[B[i]]=i;
    for(auto a:A)
        res.push_back(table[a]);
    return res;

}//leetcode 760 Easy

//Valid Palindrome II
//Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
class lc680 { //Easy
private:
    bool isPalindrome(string s, int l, int r)
    {
        while(l<r) if(s[l++]!=s[r--]) return false;
        return true;
    }
public:
    bool ValidPalindromeII(string s) {
        //time(N)
        int l=-1, r=s.size();
        while(++l<--r)
            if(s[l]!=s[r]) return isPalindrome(s,l+1,r)||isPalindrome(s,l,r-1);
        return true;
    }
};

//Jewels and Stones
class lc771 { //Easy
private:
    set<char> dict;
public:
    int JewelsAndStones(string J, string S) {
        dict=set<char>(J.begin(),J.end());
        int res=0;
        for(auto c:S)
            res+=dict.count(c);
        return res;
//        return count_if(S.begin(),S.end(),
//                        [&dict](char c){return dict.count(c);});
    }
};

//Longest Word in Dictionary
class lc720 { //Easy
    unordered_set<string> dict;
    string lst_word;
public:
    string LongestWordInDictionary(vector<string>& words) {
        // Sort by length DESC, if there is a tie, sort by lexcial order.
        sort(words.begin(),words.end(),
             [](string& x, string& y){
                if(x.size()!=y.size()) return x.size()>y.size();
                return x<y;});
        dict=unordered_set<string>(words.begin(), words.end());
        for(auto word:words) {
            string pre_word; bool valid=true;
            for(int i=0;i<word.size();i++) {
                pre_word+=word[i];
                if(!dict.count(pre_word)) valid=false;
            }
            if(valid) return word;
        }
        return "";
    }
};

//Bold Words in String
//Given a set of keywords words and a string S, make all appearances of all
//keywords in S bold. Any letters between <b> and </b> tags become bold.
class lc758 { //Easy
private:
    int MaxKWordLen=10;
    unordered_set<string> dict;
    vector<bool> bold;
    string res;
public:
    string BoldWordsInString(vector<string>& words, string S) {
        int len=S.size();
        dict=unordered_set<string>(words.begin(),words.end());
        bold=vector<bool>(len+2,0);

        for(int i=0;i<len;i++)
            for(int j=1;j<=min(len-i,MaxKWordLen);j++)
                if(dict.count(S.substr(i,j)))
                    fill(bold.begin()+i, bold.begin()+i+j, true);
        for(int i=0;i<len;i++) {
            if(!bold[i-1]&&bold[i]) res+="<b>";
            res+=S[i];
            if(bold[i]&&!bold[i+1]) res+="</b";
        }
        return res;
    }
};

//Baseball Game
//Given a list of strings, each string can be one of the 4 types
//return the sum of the points you could get in all the rounds.
class lc682 { //Easy
public:
    int BaseballGame(vector<string>& ops) {
        vector<int> score;
        for(const string op:ops) {
            if(op=="C") score.pop_back();
            else if(op=="D") score.push_back(score.back()*2);
            else if(op=="+") score.push_back(score.end()[-1]+score.end()[-2]);
            else score.push_back(stoi(op));
        }
        return accumulate(score.begin(),score.end(),0);
    }
};

//Longest Palindrome
//Given a string which consists of lowercase or uppercase letters, find
//the length of the longest palindromes that can be built with those letters.
class lc409 { //Easy
public:
    int LongestPalindrome(string s) {
        //time(N) space(64)
        vector<int> cnts(128,0); int even=0, odd=0;
        for(const char c:s) cnts[c]++;
        for(const int cnt:cnts) {
            //even += cnt % 2 == 0 ? freq : freq - 1;
            //even += cnt / 2 * 2;
            //even += ((cnt >> 1) << 1);
            //even += cnt & (INT_MAX - 1);
            even+=cnt&(~1); //clear the last bit
            odd |=cnt&( 1);
        }
        return even+odd;
    }
};

//=============================================================================cci+
//chap 01/09
bool _isUniqueChars(string str)
{
    // N^2
    // Check every char of the string with every other char of the string for duplicate occurrences

    // NlogN
//    sort(str.begin(), str.end());
//    for(auto i=0; i<(int)str.size()-1; i++)
//        if(str[i]==str[i+1]) return true;
//    return false;

    // N
    bitset<256> hit;
    for(auto i=0; i<(int)str.size(); i++) {
        if(hit.test(str[i])) return true;
        else hit.set(str[i]);
    }
    return false;
}
void _reverseString(string str)
{
    // N
    cout<<str<<endl;
    for(auto i=0; i<str.size()/2; i++)
        swap(str[i], str[str.size()-1-i]);
    cout<<str<<endl;
}
void _RemoveDuplicateChar(string str)
{
    int len=str.size(), i, pivot, tail;
    if(len<2) return;

    // N^2
    cout<<str<<endl;

//    for(tail=pivot=1; pivot<len; pivot++){
//        for(i=0; i<tail; i++) {
//            if(str[i]==str[pivot]) break;
//        }
//        if(i==tail)
//            str[tail++]=str[pivot];
//    }
    // N
    bitset<256> hit;
    hit[str[0]]=true;
    for(tail=pivot=1; pivot<len; pivot++)
        if(!hit[str[pivot]]) {
            hit[str[pivot]]=true;
            str[tail++]=str[pivot];
        }

    str.resize(tail);
    cout<<str<<endl;
}
bool _checkAnagram(string x, string y)
{
//    sort(x.begin(), x.end()); sort(y.begin(), y.end());
//    return x==y;

    vector<int> x_cnt(256,0), y_cnt(256,0); int i;
    for(i=0; i<x.size(); i++) x_cnt[x[i]]++;
    for(i=0; i<y.size(); i++) y_cnt[y[i]]++;
    return x_cnt==y_cnt;
}
void _replaceString(string str)
{
    int space_cnt=0; int len=str.size(); int i, new_len;

    cout<<str<<endl;
    for(i=0; i<len; i++)
        if(str[i]==' ') space_cnt++;
    str.resize(new_len=len+space_cnt*2);
    new_len--;
    for(i=len-1; i>=0; i--) {
        if(str[i]==' ') {
            str[new_len--]='#';
            str[new_len--]='$';
            str[new_len--]='%';
        }
        else
            str[new_len--]=str[i];
    }
    cout<<str<<endl;
}
void _mergeBtoA(vector<int> a, vector<int> b)
{
    int idx_a=a.size()-1, idx_b=b.size()-1, n;

    while(idx_a>=0&&idx_b>=0)
        (a[idx_a]>b[idx_b]) ? a[n--]=a[idx_a--] : a[n--]=b[idx_b--];
    while(idx_b>=0)
        a[n--]=b[idx_b--];
}
bool _isAnagram(string x, string y)
{
    sort(x.begin(), x.end()); sort(y.begin(), y.end());
    return x==y;
}
void _alphabetSort(string str)
{
    cout<<str<<endl;
    sort(str.begin(), str.end());
    cout<<str<<endl;
}
void _alphabetSortList(list<string> str_list)
{
    str_list.sort();
    for(auto i=str_list.begin(); i!=str_list.end(); i++)
        cout<<*i<<endl;
}
void _alphabetSortVector(vector<string> str_vector)
{
    sort(str_vector.begin(), str_vector.end(), _isAnagram);
    for(auto i=str_vector.begin(); i!=str_vector.end(); i++)
        cout<<*i<<endl;
}
//=============================================================================cci-

#if 0
int main(void)
{
    list<string> l;
    l.push_back("dbcdef");
    l.push_back("bdkfj");
    l.push_back("adkfj");
    l.push_back("cdkfj");
//    alphabetSort("kldjfkljsiofjej");
//    alphabetSortList(l);
    vector<string> v;
    v.push_back("abcdef");
    v.push_back("fghijk");
    v.push_back("defabc");
    v.push_back("ijkfgh");
    alphabetSortVector(v);

//    cout<<isUniqueChars("atx/.,mbzc")<<endl;
//    reverseString("abcdefg");
//    removeDuplicate("aaaaabcadaaaa");
//    cout<<checkAnagram("abcdef", "defabc")<<endl;
//    replaceString("a  b");

    cout<<endl<<"Hello String";
    return 0;
}
#endif
