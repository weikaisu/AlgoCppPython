#include <iostream>
#include <algorithm>
#include <stack>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "leetcode.h"

//=============================================================================BinaryTree+
void _tree_dfsInorder(TreeNode *root)
{
    if(root->left) _tree_dfsInorder(root->left);
    cout << root->val << ' ';
    if(root->right) _tree_dfsInorder(root->right);
}

void _tree_dfsPreorder(TreeNode *root)
{
    cout << root->val << ' ';
    if(root->left) _tree_dfsPreorder(root->left);
    if(root->right) _tree_dfsPreorder(root->right);
}

void _tree_dfsPostorder(TreeNode *root)
{
    if(root->left) _tree_dfsPostorder(root->left);
    if(root->right) _tree_dfsPostorder(root->right);
    cout << root->val << ' ';
}

void _tree_bfsLevelorder(TreeNode* root)
{
    if(!root) return;
    queue<TreeNode*> q;

    q.push(root);
    while(!q.empty()) {
        TreeNode *node=q.front();q.pop();
        cout << node->val << ' ';
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
}

void _tree_traUpDown(TreeNode *root)
{
    if(!root) return;
    queue<TreeNode*> q;
    int q_size=0;

    q.push(root);
    while(q_size=q.size()) {
        while(q_size--) {
            TreeNode *node=q.front(); q.pop();
            cout<<node->val<<' ';
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout<<endl;
    }
}

void _tree_traDownUp(TreeNode *root)
{
    if(!root) return;
    stack<TreeNode*> s;
    queue<TreeNode*> q;
    int q_size=0;

    q.push(root);
    while(q_size=q.size()) {
        while(q_size--) {
            TreeNode *node=q.front(); q.pop();
            if(node->right) q.push(node->right); //right child first
            if(node->left) q.push(node->left);
            s.push(node);
        }
        s.push(nullptr);
    }

    while(s.size()) {
        TreeNode *node=s.top(); s.pop();
        if(node==nullptr) cout<<endl;
        else cout<<node->val<<' ';
    }
}

int _tree_getMaxDepth(TreeNode *root)
{
    return root ? max(_tree_getMaxDepth(root->left), _tree_getMaxDepth(root->right))+1 : 0;
}

int _tree_getMinDepth(TreeNode *root)
{
    return root ? min(_tree_getMinDepth(root->left), _tree_getMinDepth(root->right))+1 : 0;
}

int _tree_getTreeDepth(TreeNode *root)
{
    return root ? max(_tree_getTreeDepth(root->left), _tree_getTreeDepth(root->right))+1 : 0;
}

void _tree_deleteTreeNode(TreeNode* &root)
{
    if(!root) return;
    _tree_deleteTreeNode(root->left);
    _tree_deleteTreeNode(root->right);
    delete root;
    root=nullptr;
}

TreeNode* _FindLeastCommonAncestor(TreeNode *root, int node1, int node2)
{
    if(!root) return nullptr;
    if(root->val==node1||root->val==node2) return root;

    TreeNode* l_lca=_FindLeastCommonAncestor(root->left, node1, node2);
    TreeNode* r_lca=_FindLeastCommonAncestor(root->right, node1, node2);
    if(l_lca&&r_lca) return root;
    else return (l_lca)?l_lca:r_lca;
}

bool _IsIdenticalTree(TreeNode* root_x, TreeNode* root_y)
{
    if(!root_x&&!root_y) return true;
    if(!root_x||!root_y) return false;
    return(root_x->val==root_y->val&&
           _IsIdenticalTree(root_x->left, root_y->left)&&
           _IsIdenticalTree(root_x->right,root_y->right));
}

bool _IsSubtree(TreeNode* tree, TreeNode* subtree)
{   // N^2
    if(!tree) return false;
    if(!subtree||_IsIdenticalTree(tree, subtree)) return true;
    return (_IsSubtree(tree->left, subtree)||_IsSubtree(tree->right, subtree));
}

void _StoreInorder(TreeNode *root, vector<int> &seq)
{
    if(root->left) _StoreInorder(root->left, seq);
    seq.push_back(root->val);
    if(root->right) _StoreInorder(root->right, seq);
}

void _StorePreorder(TreeNode *root, vector<int> &seq)
{
    seq.push_back(root->val);
    if(root->left) _StorePreorder(root->left, seq);
    if(root->right) _StorePreorder(root->right, seq);
}

bool _IsSubtreeFast(TreeNode* tree, TreeNode* subtree)
{   // N
    vector<int> seq_t, seq_s;

    _StoreInorder(tree, seq_t);
    _StoreInorder(subtree, seq_s);
    auto pos_in=search(seq_t.begin(), seq_t.end(), seq_s.begin(), seq_s.end());
    if(pos_in==seq_t.end()) return false;

    _StorePreorder(tree, seq_t);
    _StorePreorder(subtree, seq_s);
    auto pos_pre=search(seq_t.begin(), seq_t.end(), seq_s.begin(), seq_s.end());
    if(pos_pre==seq_t.end()) return false;
    else return true;
}

//print the path from root that equal to the given sum
void _PrintPathSum(TreeNode *root, vector<int> &seq, int sum)
{
    if(!root) return;

    sum-=root->val;
    seq.push_back(root->val);
    if(!sum) {
        for_each(seq.begin(), seq.end(), [](int val){cout<<val<<' ';});
        cout<<endl;
    } else {
        _PrintPathSum(root->left, seq, sum);
        _PrintPathSum(root->right, seq, sum);
    }
    seq.pop_back();
    sum+=root->val;
}

TreeNode* _BuildTreeFromArray(vector<int> arr, int l, int r)
{
    if(l>r) return nullptr;

    int m=(l+r)/2;
    TreeNode *root=new TreeNode(arr[m]);
    root->left=_BuildTreeFromArray(arr, l, m-1);
    root->right=_BuildTreeFromArray(arr, m+1, r);
    return root;
}

void _PrintTreeLevelToList(TreeNode* root, vector<list<TreeNode*>> &node_list)
{
    if(!root) return;
    queue<TreeNode*> q;
    int q_size=0;

    q.push(root);
    while(q_size=q.size()) {
        int i=0;
        while(q_size--) {
            TreeNode *node=q.front(); q.pop();
            node_list[i].push_back(node);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        i++;
    }
}

TreeNode* _FindLeftMostChild(TreeNode *node)
{
    if(!node) return nullptr;
    while(node->left) node=node->left;
    return node;
}

//Serialize and Deserialize Binary Tree
class lc297 { //Hard
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {

    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {

    }
};

//Binary Tree Maximum Path Sum
class lc124 { //Hard
private:
    int max_sum=INT_MIN;
    int _max(TreeNode* root) {
        if(!root) return 0;
        int l=max(0, _max(root->left)); // compare with 0, discard the negative values
        int r=max(0, _max(root->right));// compare with 0, discard the negative values
        max_sum=max(max_sum, root->val+l+r);
        return root->val+max(l,r);
    }
public:
    int PathSumMax(TreeNode* root) {
        if(!root) return 0;
        _max(root);
        return max_sum;
    }
};

//Binary Tree Postorder Traversal
//Use iterative way
class lc145 { //Hard
public:
    vector<int> TraversalPostorderIterative(TreeNode* root) {
        if(!root) return{};
        deque<int> res; // for reverse postorder
        stack<TreeNode*> s;

        s.push(root);
        while(s.size()) {
            auto node=s.top(); s.pop();
            //reverse postorder: root, right, left.
            res.push_front(node->val);
            if(node->left) s.push(node->left); // stak is LIFO
            if(node->right) s.push(node->right);
        }
        return vector<int>(res.begin(),res.end());
    }
};

//Maximum Binary Tree
//Given an integer array with no duplicates. A maximum tree building on this
//array is defined as follow:
//1. The root is the maximum number in the array.
//2. The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
//3. The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
//Construct the maximum tree by the given array and output the root node of this tree.
class lc654 { //Medium
private:
    TreeNode* _construct(vector<int>& nums, int l, int r)
    {
        if(l>=r) return nullptr;
        auto root_idx=max_element(nums.begin()+l, nums.begin()+r);
        TreeNode* root=new TreeNode(*root_idx);
        int m=distance(nums.begin(), root_idx);
        root->left=_construct(nums, l, m);
        root->right=_construct(nums, m+1, r);
        return root;
    }
public:
    TreeNode* MaximumBinaryTree(vector<int>& nums) {
        // time(NlogN) space(N)
        return _construct(nums, 0, nums.size());
    }
};

//Find Duplicate Subtrees
//Given a binary tree, return all duplicate subtrees. For each kind of duplicate
//subtrees, you only need to return the root node of any one of them.
class lc652 { //Medium
private:
    int _getid(TreeNode* root,
               unordered_map<long, pair<int,int>>& counts,
               vector<TreeNode*>& res)
    {
        if(!root) return 0;
        long key=(static_cast<long>(root->val) << 32) |
                 (_getid(root->left, counts, res) << 16) |
                  _getid(root->right, counts, res);
        auto it = counts.find(key);
        if (it == counts.end())
            it = counts.insert({key, {counts.size() + 1, 0}}).first;

        if (++it->second.second == 2)
            res.push_back(root);

        return it->second.first;
    }
public:
    vector<TreeNode*> FindDuplicateSubtrees(TreeNode* root) {
        // Key: (root.val, id(root.left), id(root.right))
        unordered_map<long, pair<int,int>> counts; // key -> {id, count}
        vector<TreeNode*> res;
        _getid(root, counts, res);
        return res;
    }
};

//Binary Tree Level Order Traversal
//Given a binary tree, return the level order traversal of its nodes' values.
//(ie, from left to right, level by level).
class lc102 { //Medium
public:
    vector<vector<int>> TraversalLevelOrder(TreeNode* root) {
        if(!root) return {};
        vector<vector<int>> res; vector<TreeNode*> curr, next;

        curr.push_back(root);
        while(curr.size()) {
            res.push_back({});
            for(const auto& node:curr) {
                res.back().push_back(node->val);
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
            }
            curr.swap(next);
            next.clear();
        }
        return res;
    }
};

//Path Sum II
//Given a binary tree and a sum, find all root-to-leaf paths where each path's
//sum equals the given sum.
class lc113 { //Medium
private:
    void _sum(TreeNode* root, int sum, vector<int> &curr, vector<vector<int>> &res)
    {
        if(!root) return;
        if(!root->left&&!root->right) {
            if(root->val==sum) {
                res.push_back(curr);
                res.back().push_back(root->val);
            }
            return;
        }
        curr.push_back(root->val);
        _sum(root->left, sum-root->val, curr, res);
        _sum(root->right, sum-root->val, curr, res);
        curr.pop_back();
    }
public:
    vector<vector<int>> PathSumAll(TreeNode* root, int sum) {
        vector<int> curr; vector<vector<int>> res;
        _sum(root, sum, curr, res);
        return res;
    }
};

//Path Sum
//Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all
//the values along the path equals the given sum.
class lc112 { //Easy
public:
    bool PathSum(TreeNode* root, int sum) {
        //time(N)
        if(!root) return false;
        if(!root->left&&!root->right) return root->val==sum;
        return PathSum(root->left, sum-root->val) ||
               PathSum(root->right, sum-root->val);
    }
};

//Longest Univalue Path
//Given a binary tree, find the length of the longest path where each node in
//the path has the same value. This path may or may not pass through the root.
class lc687 { //Easy
private:
    int _path(TreeNode* root, int &len_root)
    {
        if(!root) return 0;
        int len_left=0, len_right=0;
        if(root->left&&root->val==root->left->val)
            len_left=_path(root->left, len_root)+1;
        if(root->right&&root->val==root->right->val)
            len_right=_path(root->right, len_root)+1;
        len_root=max(len_root, len_left+len_right); // max(a->a->a, a<-a->a)
        return max(len_left,len_right);
    }
public:
    int LongestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        int root_len=0;
        _path(root, root_len);
        return root_len;
    }
};

//Second Minimum Node In a Binary Tree
//Given a non-empty special binary tree consisting of nodes with the
//non-negative value, where each node in this tree has exactly two or
//zero sub-node. If the node has two sub-nodes, then this node's value
//is the smaller value among its two sub-nodes.
//Given such a binary tree, you need to output the second minimum value
//in the set made of all the nodes' value in the whole tree.
class lc671 { //Easy
public:
    int SecondMinimumNodeInABinaryTree(TreeNode* root) {
        // BFS
        if(!root) return -1;
        int min1=root->val, min2=INT_MAX;
        bool found=false;
        queue<TreeNode*> q; q.push(root);

        while(q.size()) {
            TreeNode *node=q.front(); q.pop();
            if(min1<node->val&&node->val>min2) {
                min2=node->val;
                found=true;
                continue;
            }
            if(!node->left) continue;
            q.push(root->left); q.push(root->right);
        }
        return found ? min2 : -1;
    }
};

//Average of Levels in Binary Tree
//Given a non-empty binary tree, return the average value of the nodes
//on each level in the form of an array.
class lc637 { //Easy
public:
    vector<double> AverageOfLevelsInBinaryTree(TreeNode* root) {
        if(!root) return {};
        vector<double> res; vector<TreeNode*> curr, next;
        long long sum=0;

        curr.push_back(root);
        while(curr.size()) {
            for(const auto& node : curr) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                sum+=node->val;
            }
            res.push_back(sum/curr.size());
            curr.swap(next);
            next.clear();
        }
        return res;
    }
};

//Merge Two Binary Trees
//Given two binary trees and imagine that when you put one of them
//to cover the other, some nodes of the two trees are overlapped while
//the others are not.
//You need to merge them into a new binary tree. The merge rule is that
//if two nodes overlap, then sum node values up as the new value of the
//merged node. Otherwise, the NOT null node will be used as the node of new tree.
class lc617  { //Easy
public:
    TreeNode* MergeTwoBinaryTrees(TreeNode* t1, TreeNode* t2) {
        TreeNode* root=t1; // merge t2 into t1

        if(!t1) return t2; if(!t2) return t1;
        // root=new TreeNode(t1->val,t2->val); if t1/t2 can't be over-write
        root->val+=t2->val;
        root->left=MergeTwoBinaryTrees(t1->left, t2->left);
        root->right=MergeTwoBinaryTrees(t1->right, t2->right);
        return root;
    }
};

//Construct String from Binary Tree
//You need to construct a string consists of parenthesis and integers
//from a binary tree with the preorder traversing way.
class lc606 { //Easy
public:
    string ConstructStringFromBinaryTree(TreeNode* t) {
        if(!t) return "";
        const string s=to_string(t->val);
        const string l=ConstructStringFromBinaryTree(t->left);
        const string r=ConstructStringFromBinaryTree(t->right);
        // case : s
        if(!t->left&&!t->right) return s;
        // case : s(l)
        if(!t->right) return s+"("+l+")";
        // general: s(l)(r)
        return s + "("+l+")" + "("+r+")";
    }
};

//Diameter of Binary Tree
//Compute the length of the diameter of the tree. The diameter of a binary tree
//is the length of the longest path between any two nodes in a tree. This path
//may or may not pass through the root.
class lc543 { //Easy
private:
    int _diameter(TreeNode* root, int &len_root)
    {
        if(!root) return -1;
        int len_left=_diameter(root->left, len_root)+1;
        int len_right=_diameter(root->right, len_root)+1;
        len_root=max(len_root, len_left+len_right);
        return max(len_left, len_right);
    }
public:
    int DiameterOfBinaryTree(TreeNode* root) {
        int len=0;
        _diameter(root, len);
        return len;
    }
};

//Sum of Left Leaves
//Find the sum of all left leaves in a given binary tree.
class lc404 { //Easy
public:
    int SumOfLeftLeaves(TreeNode* root) {
        // time(N) space(logN)
        int sum=0;
        if(!root) return sum;
        if(root->left&&!root->left->left&&!root->left->right)
            sum+=root->left->val;
        return sum+SumOfLeftLeaves(root->left)+SumOfLeftLeaves(root->right);
    }
};

//Balanced Binary Tree
//Given a binary tree, determine if it is height-balanced.
class lc110 { //Easy
private:
    int _getTreeDepth(TreeNode *root, bool &isBalance)
    {
        if(!root) return 0;
        int left_h =_getTreeDepth(root->left, isBalance);
        int right_h=_getTreeDepth(root->right, isBalance);
        if(abs(left_h-right_h)>1) isBalance=false;
        return max(left_h, right_h)+1;
    }
public:
    bool BalancedBinaryTree(TreeNode* root) {
        //time(NlogN), two recursion
        if(!root) return true;
        return ( (abs(_tree_getTreeDepth(root->left)-_tree_getTreeDepth(root->right)<=1)) &&
                 (BalancedBinaryTree(root->left) && BalancedBinaryTree(root->right)) );
        //time(N)
        if(!root) return true;
        bool isBalance=true;
        _getTreeDepth(root, isBalance);
        return isBalance;
    }
};

//Same Tree
//Given two binary trees, write a function to check if they are the same or not.
class lc100 { //Easy
public:
    bool SameTree(TreeNode* p, TreeNode* q) {
        if(!p&&!q) return true;
        if((!p||!q) || (p->val!=q->val)) return false;
        return SameTree(p->left,q->left)&&SameTree(p->right,q->right);
    }
};
//=============================================================================BinaryTree-

//=============================================================================BinaryIndexedTree(FenwickTree)+
//https://www.youtube.com/watch?v=WbafSgetDDk
//https://en.wikipedia.org/wiki/Fenwick_tree
class BinaryIndexedTree {
private:
    vector<int> sums;
    int lowbit(int x) {return x&(-x);}
public:
    // BinaryIndexdTree is indexed from 1, not 0, so size is n+1
    BinaryIndexedTree(int n):sums(n+1,0){}
    //time(logN), add k to element i (and thus Fen_sum(a, j) for all j > i)
    void add(int idx, int delta) {
        while(idx<sums.size()) {
            sums[idx]+=delta;
            idx+=lowbit(idx);
        }
    }
    //time(logN), return the sum of the first i elements, 0 through i-1.
    int sum(int idx) {
        int s=0;
        while(idx>0) {
            s+=sums[idx];
            idx-=lowbit(idx);
        }
        return s;
    }
};

//Count of Smaller Numbers After Self
//You are given an integer array nums and you have to return a new counts array.
//The counts array has the property where counts[i] is the number of smaller
//elements to the right of nums[i].
class lc315 { //Hard
public:
    vector<int> CountOfSmallerNumbersAfterSelf(vector<int>& nums) {

    }
};

//Range Sum Query - Mutable
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
class lc307 { //Medium
private:
    vector<int>nums;
    BinaryIndexedTree tree;
public:
    lc307(vector<int> seq) : nums(move(seq)), tree(seq.size()) {
        for(int i=0;i<=seq.size();i++)
            tree.add(i+1,seq[i]);
    }
    void RangeSumQueryMutableUpdate(int i, int val) {
        tree.add(i+1, val-nums[i]);
        nums[i]=val;
    }
    int RangeSumQueryMutable(int i, int j) {
        return tree.sum(j+1)-tree.sum(i);
    }
};
//=============================================================================BinaryIndexedTree(FenwickTree)-

//=============================================================================NaryTree+
TreeNode* _ntree_insertNode(TreeNode *node, int val)
{
    if(!node) return NULL;
    if(node->left) {
        node=node->left;
        while(node->right) node=node->right;
        return node->right=new TreeNode(val);
    } else {
        return node->left=new TreeNode(val);
    }
}
void _ntree_dfs(TreeNode *root)
{
    if(!root) return;

    while(root) {
        cout << " " << root->val;
        if (root->left) _ntree_dfs(root->left);
        root = root->right;
    }
}
void _ntree_bfs(TreeNode *root)
{
    if(!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        root=q.front();q.pop();
        cout<<' '<<root->val;
        if(root->left) q.push(root->left);
        root=root->right;
        while(root) {
            cout<<' '<<root->val;
            if(root->left) q.push(root->left);
            root=root->right;
        }
    }
}
//=============================================================================NaryTree-

//=============================================================================BinarySearchTree+
TreeNode* _bst_insertNode(TreeNode *root, int val)
{
    if(!root) return new TreeNode(val);

    if(val<root->val)
        root->left=_bst_insertNode(root->left, val);
    else if (val>root->val)
        root->right=_bst_insertNode(root->right, val);
    else
        return root;
}
TreeNode* _bst_findMinNode(TreeNode *root)
{
    while(root->left) root=root->left;
    return root;
}
TreeNode* _bst_findMaxNode(TreeNode *root)
{
    while(root->right) root=root->right;
    return root;
}
TreeNode* _bst_deleteNode(TreeNode *root, int val)
{
    TreeNode *node;

    if(!root) return root;

    if(val<root->val)
        root->left=_bst_deleteNode(root->left, val);
    else if(val>root->val)
        root->right=_bst_deleteNode(root->right, val);
    else { // val=root->val
        if(root->right) {
            node=_bst_findMinNode(root->right); // replace by the min right child
            root->val=node->val;
            root->right=_bst_deleteNode(root->right, node->val);
        } else if(root->left) {
            node=_bst_findMaxNode(root->left); // replace by the max left child
            root->val=node->val;
            root->left=_bst_deleteNode(root->left, node->val);
        } else {
            delete root;
            root=nullptr;
        }
    }
    return root;
}
//=============================================================================BinarySearchTree-

//=============================================================================AVLBinarySearchTree+
int _avl_getHeight(TreeNode *node)
    {return (node) ? node->height : 0;}
int _avl_getBalanceFactor(TreeNode *node)
    {return (node) ? _avl_getHeight(node->left) - _avl_getHeight(node->right) : 0;}
TreeNode* _avl_lRotate(TreeNode *x)
{
/*
      x           y
       \         / \
        y   =>  x   w
       / \       \
      z   w       z
*/
    TreeNode *y = x->right;
    TreeNode *z = y->left;

    // left rotate
    y->left = x;
    x->right = z;
    //  update heights
    x->height = 1+max(_avl_getHeight(x->left), _avl_getHeight(x->right));
    y->height = 1+max(_avl_getHeight(y->left), _avl_getHeight(y->right));

    return y;
}
TreeNode* _avl_rRotate(TreeNode *x)
{
/*
          x       y
         /       / \
        y   =>  w   x
       / \         /
      w   z       z
*/
    TreeNode *y = x->left;
    TreeNode *z = y->right;

    // right rotate
    y->right = x;
    x->left = z;
    // update heights
    x->height = 1+max(_avl_getHeight(x->left), _avl_getHeight(x->right));
    y->height = 1+max(_avl_getHeight(y->left), _avl_getHeight(y->right));

    return y;
}
TreeNode* _avl_insertNode(TreeNode *node, int val)
{
    if(!node) return new TreeNode(val);

    if(val<node->val)
        node->left=_avl_insertNode(node->left, val);
    else if (val>node->val)
        node->right=_avl_insertNode(node->right, val);
    else
        return node;

    int lChildH=_avl_getHeight(node->left);
    int rChildH=_avl_getHeight(node->right);
    int bFactor=lChildH-rChildH;
    node->height=1+max(lChildH,rChildH);

    // LL case
    if(bFactor> 1 && val<node->left->val) {
        return _avl_rRotate(node);
    }
    // LR case
    if(bFactor> 1 && val>node->left->val) {
        node->left =  _avl_lRotate(node->left);
        return _avl_rRotate(node);
    }
    // RR case
    if(bFactor<-1 && val>node->right->val) {
        return _avl_lRotate(node);
    }
    // RL case
    if(bFactor<-1 && val<node->right->val) {
        node->right = _avl_rRotate(node->right);
        return _avl_lRotate(node);
    }

    return node;
}
TreeNode* _avl_deleteNode(TreeNode *root, int val)
{
    TreeNode *node;

    if(!root) return root;

    if(val<root->val)
        root->left=_avl_deleteNode(root->left, val);
    else if(val>root->val)
        root->right=_avl_deleteNode(root->right, val);
    else {
        if(!root->left) { //has only one right child
            node = root->right;
            delete root;
            return node;
        }
        else if(!root->right) { //has only one left child
            node = root->left;
            delete root;
            return node;
        }

        // has both right/left children
        node=_bst_findMinNode(root->right);
        root->val=node->val;
        root->right=_avl_deleteNode(root->right, node->val);
    }

    if(!root) return root;
    else node=root;

    node->height=1+max(_avl_getHeight(node->left),_avl_getHeight(node->right));

    // LL case
    if(_avl_getBalanceFactor(node)>1 && _avl_getBalanceFactor(node->left)>=0) {
        return _avl_rRotate(node);
    }
    // LR case
    if(_avl_getBalanceFactor(node)>1 && _avl_getBalanceFactor(node->left)<0) {
        node->left =  _avl_lRotate(node->left);
        return _avl_rRotate(node);
    }
    // RR case
    if(_avl_getBalanceFactor(node)<-1 && _avl_getBalanceFactor(node->right)<=0) {
        return _avl_lRotate(node);
    }
    // RL case
    if(_avl_getBalanceFactor(node)<-1 && _avl_getBalanceFactor(node->left)>0) {
        node->right = _avl_rRotate(node->right);
        return _avl_lRotate(node);
    }
    return node;
}
//=============================================================================AVLBinarySearchTree-

#if 0
int main(void)
{
    TreeNode *root=NULL, *node=NULL;

#if 1
    //==============================BinaryTree+
    root = new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    node=root->left;
    node->left=new TreeNode(4);
    node->right=new TreeNode(5);
    node=root->right;
    node->left=new TreeNode(6);
    node->right=new TreeNode(7);

    _tree_dfsInorder(root);cout<<"(DF Inorder)"<<endl;
    _tree_dfsPreorder(root);cout<<"(DF Preorder)"<<endl;
    _tree_dfsPostorder(root);cout<<"(DF Postorder)"<<endl;
    _tree_bfsLevelorder(root);cout<<"(BF)"<<endl;
    _tree_traUpDown(root); cout<<endl;
    _tree_traDownUp(root); cout<<endl;
    //==============================BinaryTree-
#endif // 0
#if 0
    //==============================BinarySearchTree+
    root = new TreeNode(50);
    _bst_insertNode(root, 30);
    _bst_insertNode(root, 20);
    _bst_insertNode(root, 40);
    _bst_insertNode(root, 70);
    _bst_insertNode(root, 60);
    _bst_insertNode(root, 80);
    _bst_insertNode(root, 90);
    _bst_insertNode(root, 10);

//    _bst_deleteNode(root, 40);
//    _bst_deleteNode(root, 20);
//    _bst_deleteNode(root, 10);

    _tree_traUpDown(root); cout<<endl;
    _tree_traDownUp(root); cout<<endl;
    cout<<"Min Depth: "; cout<<_tree_getMinDepth(root)<<endl;
    cout<<"Max Depth: "; cout<<_tree_getMaxDepth(root)<<endl;
    cout<<"Min Node: "; node=_bst_findMinNode(root);cout<<node->val<<endl;
    cout<<"Max Node: "; node=_bst_findMaxNode(root);cout<<node->val<<endl;

    cout<<_FindLeastCommonAncestor(root, 20, 40)->val<<endl;

    //==============================BinarySearchTree-
#endif // 0
#if 0
    //==============================AVLBinarySearchTree+
    root = new TreeNode(10);
    root = _avl_insertNode(root, 20);
    root = _avl_insertNode(root, 30);
    root = _avl_insertNode(root, 40);
    root = _avl_insertNode(root, 50);
    root = _avl_insertNode(root, 25);
    root = _avl_insertNode(root, 35);
    //root = root->_avl_insertNode(root, 60);
    _tree_traUpDown(root);

    //root = root->_avl_deleteNode(root, 35);
    //_tree_traUpDown(root);
    _tree_dfsInorder(root); cout<<endl;
    _tree_dfsPreorder(root); cout<<endl;
    _tree_dfsPostorder(root); cout<<endl;
    //==============================AVLBinarySearchTree-
#endif // 0
#if 0
    /*   Let us create below tree
    *           10
    *     /   /    \   \
    *    2  3      4   5
    *              |   /  | \
    *              6   7  8  9   */

    // Left child right sibling
    /*  10
    *    |
    *    2 -> 3 -> 4 -> 5
    *              |    |
    *              6    7 -> 8 -> 9  */
    root = new TreeNode(10);
    TreeNode *n1 = _ntree_insertNode(root,2);
    TreeNode *n2 = _ntree_insertNode(root,3);
    TreeNode *n3 = _ntree_insertNode(root,4);
    TreeNode *n4 = _ntree_insertNode(n3,6);
    TreeNode *n5 = _ntree_insertNode(root,5);
    TreeNode *n6 = _ntree_insertNode(n5,7);
    TreeNode *n7 = _ntree_insertNode(n5,8);
    TreeNode *n8 = _ntree_insertNode(n5,9);
    cout<<"DFS: "; traverseDFS_NaT(root); cout<<endl;
    cout<<"BFS: "; traverseBFS_NaT(root); cout<<endl;
#endif // 1
    cout<<endl<<"Hello Tree";
    return 0;
}
#endif
