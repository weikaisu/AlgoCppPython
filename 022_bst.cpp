#include "leetcode.h"

using namespace std;

//Range Module
//Tracks ranges of numbers.
class lc715 { //Hard
    // map
public:
    RangeModule() {}
    void RangeModuleaddRange(int left, int right) {}
    bool RangeModulequeryRange(int left, int right) {}
    void RangeModuleremoveRange(int left, int right) {}
};

//The Skyline Problem
//Write a program to output the skyline formed by these buildings collectively
class lc218 { // Hard
    // multiset
public:
    vector<pair<int, int>> Skyline(vector<vector<int>>& buildings) {

    }
};

//Sliding Window Median
//Median is the middle value in an ordered integer list. If the size of the list is even,
//there is no middle value. So the median is the mean of the two middle value.
class lc480 { //Hard
    // multiset
public:
    vector<double> SlidingWindowMedian(vector<int>& nums, int k) {

    }
};

//Sliding Window Maximum
//Given an array nums, there is a sliding window of size k which is moving from the very
//left of the array to the very right. You can only see the k numbers in the window. Each
//time the sliding window moves right by one position.
class lc239 { //Hard
public:
    vector<int> SlidingWindowMaximum(vector<int>& nums, int k) {
        if(nums.empty()) return {};

        //time(N^2), brute force
        vector<int> res;
        for(int i=k-1;i<nums.size();i++)
            res.push_back(*max_element(nums.begin()+i-k+1, nums.begin()+i+1));
        return res;

        // time(NlogN), BST, multiset
        multiset<int> win;
        for(int i=0;i<nums.size();i++) {
            win.insert(nums[i]);
            if(i-k+1>=0) {
                res.push_back(*win.rbegin());
                win.erase(win.equal_range(nums[i-k+1]).first); //only delete the 1th element
            }
        }
        return res;
    }
};

//Serialize and Deserialize BST
//each node 4 bytes, totally 4N bytes, use pre-order
// 5(root)[2 1 4](left)[6 8](right)
class lc449 { //Medium
private:
    void encode(TreeNode* root, string &s) {
        if(!root) return;
        s.append(reinterpret_cast<const char*>(&root->val), sizeof(root->val));
        encode(root->left,s);
        encode(root->right,s);
    }
    TreeNode* decode(string &s, int &pos, int min_val, int max_val) {
        if(pos>=s.size()) return nullptr;
        int val=*reinterpret_cast<const int*>(s.data()+pos);
        if(val<min_val||val>max_val) return nullptr;
        pos+=sizeof(val);
        TreeNode* root=new TreeNode(val);
        root->left=decode(s, pos, min_val, val);
        root->right=decode(s, pos, val, max_val);
        return root;
    }
public:

    // Encodes a tree to a single string.
    string SerializeBST(TreeNode* root) {
        string bitstream;
        encode(root, bitstream);
        return bitstream;
    }

    // Decodes your encoded data to tree.
    TreeNode* DeserializeBST(string bitstream) {
        int pos=0;
        return decode(bitstream, pos, INT_MIN, INT_MAX);
    }
};

//Validate Binary Search Tree
//Determine if it is a valid binary search tree
class lc098 { //Medium
private:
    bool _inorder(TreeNode* root, TreeNode* pre_node)
    {
        if(!root) return true;
        if(!_inorder(root->left, pre_node)) return false;
        if(pre_node&&pre_node->val>=root->val) return false;
        pre_node=root;
        if(!_inorder(root->right, pre_node)) return false;
    }
public:
    bool ValidateBinarySearchTree(TreeNode* root) {
        //result of inorder travel a BST is a ascending sequence
        //time(N) space(logN)
        TreeNode* pre_node=nullptr;
        return _inorder(root, pre_node);
    }
};

//Minimum Distance Between BST Nodes
//Given a Binary Search Tree (BST) with the root node root, return the minimum difference
//between the values of any two different nodes in the tree.
class lc783 { //Easy
private:
    int min_diff=INT_MAX;
    int* pre_val=nullptr;
    void _dist(TreeNode* root) { // InOrder traversal
        if(!root) return;
        _dist(root->left);
        if(pre_val)
            min_diff=min(min_diff, abs(*pre_val-root->val));
        pre_val=&root->val;
        _dist(root->right);
    }
public:
    int MinimumDistanceBetweenBSTNodes(TreeNode* root) {
        _dist(root);
        return min_diff;
    }
};

//Trim a Binary Search Tree
//Given a binary search tree and the lowest and highest boundaries as L and R,
//trim the tree so that all its elements lies in [L, R] (R >= L). You might
//need to change the root of the tree, so the result should return the new root
//of the trimmed binary search tree.
class lc669 { //Easy
private:
    void _deleteTreeNode(TreeNode* &root)
    {
        if(!root) return;
        _deleteTreeNode(root->left);
        _deleteTreeNode(root->right);
        delete root;
        root=nullptr;
    }
public:
    TreeNode* TrimABinarySearchTree(TreeNode* root, int L, int R) {
        TreeNode* new_root;
        if(!root) return nullptr;
        // root->val not in the range, return the left/right subtrees
        if(root->val<L) {
            new_root=TrimABinarySearchTree(root->right, L, R);
            _deleteTreeNode(root->left);
            delete root; root=nullptr;
            return new_root;
        }
        if(root->val>R) {
            new_root=TrimABinarySearchTree(root->left, L, R);
            _deleteTreeNode(root->right);
            delete root; root=nullptr;
            return new_root;
        }
        // root->val int the range, recursively trim left/right subtrees
        root->left=TrimABinarySearchTree(root->left, L, R);
        root->right=TrimABinarySearchTree(root->right, L, R);
        return root;
    }
};

//Two Sum IV ¡V Input is a BST
//Given a Binary Search Tree and a target number, return true if there exist two elements
//in the BST such that their sum is equal to the given target.
class lc653 { //Easy
private:
    void _inorder(TreeNode* root, vector<int> &sorted)
    {
        if(!root) return;
        _inorder(root->left, sorted);
        sorted.push_back(root->val);
        _inorder(root->right, sorted);
    }
public:
    bool TwoSumIV(TreeNode* root, int k) {
        vector<int> sorted;
        _inorder(root, sorted);
        int l=0, r=sorted.size()-1;
        while(l<r) {
            int sum=sorted[l]+sorted[r];
            if(sum==k) return true;
            else if(sum<k) l++;
            else r--;
        }
        return false;
    }
};

//Minimum Absolute Difference in BST
//Given a binary search tree with non-negative values, find the minimum absolute
//difference between values of any two nodes.
class lc530 { //Easy
private:
    void _inorder(TreeNode* root, int* pre_val, int &min_diff)
    {   //BST after inorder DFS is a sorted sequence
        if(!root) return;
        _inorder(root->left, pre_val, min_diff);
        if(pre_val) min_diff=min(min_diff, root->val-*pre_val);
        pre_val=&root->val;
        _inorder(root->right, pre_val, min_diff);
    }
public:
    int MinimumAbsoluteDifference(TreeNode* root) {
        //time(N) space(logN)
        int *pre_val=nullptr, min_diff=INT_MAX;
        _inorder(root, pre_val, min_diff);
        return min_diff;
    }
};

//fnd the ‘next’ node (ie, in-order successor) of a given node in
//a binary search tree where each node has a link to its p
TreeNode* _FindInorderSucc(TreeNode *node)
{
    TreeNode *succ_node;
    if(!node) return nullptr;

    // Found right children -> return 1st inorder node on right
    if(!node->parent||node->right)
        succ_node=_FindInorderSucc(node->right);
    else {
        // Go up until we're on left instead of right
        while(succ_node=node->parent) {
            // if i'm the left child of my parent node
            // then my parent is my succ_node
            if(succ_node->left==node) break;
            node=node->parent;
        }
    }
    return succ_node;
}

//=============================================================================BinarySearch+
//K-th Smallest Prime Fraction
//A sorted list A contains 1, plus some number of primes.
//Then, for every p < q in the list, we consider the fraction p/q.
//What is the K-th smallest fraction considered?
class lc786 { //Hard
public:
    vector<int> KthSmallestPrimeFraction(vector<int>& nums, int k) {

    }
};

//Find K-th Smallest Pair Distance
//Given an integer array, return the k-th smallest distance among all the pairs.
//The distance of a pair (A, B) is defined as the absolute difference between A and B.
class lc719 { //Hard
public:
    int KthSmallestPairDistance(vector<int>& nums, int k) {

    }
};

//Median of Two Sorted Arrays
//There are two sorted arrays nums1 and nums2 of size m and n respectively.
//Find the median of the two sorted arrays.
class lc004 { //Hard
public:
    double MedianOfTwoSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1=nums1.size(), n2=nums2.size();
        if(n1>n2) MedianOfTwoSortedArrays(nums2,nums1); //search the smaller array

        int median=(n1+n2+1)/2; //the median of two arrays
        int l=0, r=n1, m1, m2;
        while(l<r) {
            m1=(l+r)/2; m2=median-m1;
            if(nums1[m1]<nums2[m2-1]) l=m1+1;
            else r=m1;
        }

        m1=l; m2=median-m1;
        int left_median=max(m1<=0 ? INT_MIN : nums1[m1-1],
                            m2<=0 ? INT_MIN : nums2[m2-1]);
        if((n1+n2)%2)
            return left_median; // there are total odd num, median comes from one number

        int right_median=min(m1>=n1 ? INT_MAX : nums1[m1],
                             m2>=n2 ? INT_MAX : nums2[m2]);
        return (left_median+right_median)/2;
    }
};

//Find Minimum in Rotated Sorted Array II
class lc154 { //Hard
private:
    int _findMin(vector<int>& nums, int l, int r) {
        //only 1 or 2 elements
        if(l+1>=r) return min(nums[l],nums[r]);
        //sorted
        if(nums[l]<nums[r]) return nums[l];
        int m=(l+r)/2;
        return min(_findMin(nums,l,m-1),_findMin(nums,m,r));
    }
public:
    int FindMinimumInRotatedSortedArrayII(vector<int>& nums) {
        //time(logN), recursive
        return _findMin(nums, 0, nums.size()-1);

        //time(logN), iterative
        int l=0, r=nums.size()-1;
        while(r-l>1) {
            //only 1 or 2 elements
            if(l+1>=r) return min(nums[l],nums[r]);
            //sorted
            if(nums[l]<nums[r]) return nums[l];
            int m=(l+r)/2;
            if(nums[l]==nums[m]) l++;
            else if(nums[l]<nums[m]) l=m;
            else r=m;
        }
    }
};

//Find Minimum in Rotated Sorted Array
class lc153 { //Medium
private:
    int _findMin(vector<int>& nums, int l, int r) {
        //only 1 or 2 elements
        if(l+1>=r) return min(nums[l],nums[r]);
        //sorted
        if(nums[l]<nums[r]) return nums[l];
        int m=(l+r)/2;
        return min(_findMin(nums,l,m-1),_findMin(nums,m,r));
    }
public:
    int FindMinimumInRotatedSortedArrayI(vector<int>& nums) {
        //time(logN), recursive
        return _findMin(nums, 0, nums.size()-1);

        //time(logN), iterative
        int l=0, r=nums.size()-1;
        while(r-l>1) {
            //only 1 or 2 elements
            if(l+1>=r) return min(nums[l],nums[r]);
            //sorted
            if(nums[l]<nums[r]) return nums[l];

            int m=(l+r)/2;
            if(nums[l]<nums[m]) l=m;
            else r=m;
        }
    }
};

//My Calendar III
class lc732 { //Hard
private:
    map<int,int> booked;
public:
    MyCalendarIII(){}
    //time(N^2)
    int book(int start, int end) {
        ++booked[start];
        --booked[end];
        int cnt=0, max_cnt=0;
        for(auto it:booked)
            max_cnt=max(max_cnt,cnt+=it.second);
        return max_cnt;
    }
};

//My Calendar II
class lc731 { //Medium
private:
    vector<pair<int,int>> booked;
    vector<pair<int,int>> overlaped; //record the overlaped time slot
public:
    //time(N^2)
    bool MyCalendarII(int start, int end) {
        for(auto it:overlaped)
            if(max(it.first,start)<min(it.second,end)) return false;
        for(auto it:booked) {
            int s=max(it.first,start);
            int e=max(it.second, end);
            if(s<e) overlaped.emplace_back(s,e);
        }
        booked.emplace_back(start,end);
    }
};

//My Calendar I
//Implement a MyCalendar class to store your events.
class lc729 { //Medium
private:
    vector<pair<int,int>> booked1;
    map<int,int>          booked2;
public:

    bool MyCalendarI(int start, int end) {
        //time(N^2)
        for(auto it:booked1)
            if(max(it.first,start)<min(it.second,end)) return false; //time slots overlap
        booked1.emplace_back(start,end);
        return true;

        //time(NlogN), binary search
        // key=q.start
        // floor  :  largest entry whose key <= query key
        // ceiling: smallest entry whose key >  query key
        auto it=booked2.lower_bound(start); // return a ceiling entry
        // ceiling.start < q.end
        if(it!=booked2.cend()  && it->first <end)   return false;

        it--;// since no overlap, floor is it--;

        //    floor.end > q.start
        if(it!=booked2.cbegin()&& it->second>start) return false;
        booked2[start]=end;
        return true;
    }
};

//Single Element in a Sorted Array
//Given a sorted array consisting of only integers where every element appears
//twice except for one element which appears once. Find this single element that
//appears only once.
class lc540 { //Medium
public:
    int SingleElementInSortedArray(vector<int>& nums) {
        //time(logN)
        int l=0, r=nums.size(), m, n;
        while(l<r) {
            m=(l+r)/2;
            n=m^1; //n = !(m%2) ? m + 1 : m - 1;
            if(nums[m]==nums[n]) l=m+1;
            else r=m;
        }
        return nums[l];
    }
};

//Kth Smallest Element in a Sorted Matrix
//Given a n x n matrix where each of the rows and columns are sorted in ascending order,
//find the kth smallest element in the matrix.
class lc378 { //Medium
public:
    int KthSmallestElementInSortedMatrix(vector<vector<int>>& matrix, int k) {
        int n=matrix.size();
        long l=matrix[0][0];
        long r=matrix[n-1][n-1];
        while(l<r) {
            int m=(l+r)/2, m_idx=0;
            for(int i=0;i<n;i++)
                m_idx+=upper_bound(matrix[i].cbegin(),matrix[i].cend(),m)-matrix[i].cbegin();
            if(m_idx<k) l=m+1;
            else r=m;
        }
        return l;
    }
};

//Valid Perfect Square
class lc367 { //Easy
public:
    bool ValidPerfectSquare(int num) {
        int l=0, r=num, m;
        while(l<=r) {
            m=l+(r-1)/2;
            if(m*m==num) return true;
            if(m*m<num) l=m+1;
            else r=m-1;
        }
        return false;
    }
};

//Sqrt(x)
//Implement int sqrt(int x)
class lc069 { //Easy
public:
    int Sqrt(int x) {
        //time(logN)
        int l=0, r=x, m;
        while(l<=r) {
            m=l+(r-1)/2; //(l+r)/2
            if(m*m==x) return m;
            if(m*m<x) l=m+1;
            else r=m-1;
        }
        return r;
    }
};

//Two Sum II - Input array is sorted
//Given an array of integers that is already sorted in ascending order,
//find two numbers such that they add up to a specific target number.
class lc167 { //Easy
public:
    vector<int> TwoSumII(vector<int>& nums, int tgt) {
        //time(N)
        int l=0, r=nums.size()-1;
        while(l<r) {
            int res=nums[l]+nums[r];
            if(res==tgt) break;
            else if(res<tgt) l++;
            else r--;
        }
        return {l+1,r+1}; // 1-based
    }
};

//Find Smallest Letter Greater Than Target
//Given a list of sorted characters letters containing only lowercase letters, and
//given a target letter target, find the smallest element in the list that is larger
//than the given target.
class lc744 { //Easy
public:
    char FindSmallestLetterGreaterThanTarget(vector<char>& letters, char key) {
        //time(logN) binary search
        int l=0, r=letters.size(), m;
        while(l<r) {
            m=(l+r)/2;
            if(key>=letters[m]) l=m+1;
            else r=m;
        }
        return letters[l%letters.size()];
    }
};

int _SearchRotatedArray(vector<int> seq, int x)
{
    int l=0, r=seq.size()-1, m;

    while(l<r) {
        m=(l+r)/2;
        if(x==seq[m]) return m;
        if(seq[l]<seq[m]) {
            if(x>seq[m]||x<seq[r]) l=m+1;
            else r=m-1;
        } else if(seq[l]>seq[m]) {
            if(x<seq[m]||x>seq[r]) r=m-1;
            else l=m+1;
        }
    }
    return -1;
}
//=============================================================================BinarySearch-

#if 0
int main()
{
    lc069 *p=new lc069;
    int res=p->Sqrt(7);
    return 0;
}
#endif
