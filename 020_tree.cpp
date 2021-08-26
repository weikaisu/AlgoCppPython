#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class TreeNode
{
private:
//    int val;
//    int height; // for AVLTree
//    TreeNode *left, *right;

public:
    TreeNode(int val) {
        this->val=val;
        this->height=1; // for AVLTree
        left=right=NULL;
    }
    int val;
    int height; // for AVLTree
    TreeNode *left, *right, *parent;
};
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//==================================BinaryTree+
void _00_tree_dfsInorder(TreeNode *root)
{
    if(root->left) _00_tree_dfsInorder(root->left);
    cout << root->val << ' ';
    if(root->right) _00_tree_dfsInorder(root->right);
}

void _00_tree_dfsPreorder(TreeNode *root)
{
    cout << root->val << ' ';
    if(root->left) _00_tree_dfsPreorder(root->left);
    if(root->right) _00_tree_dfsPreorder(root->right);
}

void _00_tree_dfsPostorder(TreeNode *root)
{
    if(root->left) _00_tree_dfsPostorder(root->left);
    if(root->right) _00_tree_dfsPostorder(root->right);
    cout << root->val << ' ';
}
void _00_tree_bfsLevelorder(TreeNode* root)
{
    queue<TreeNode*> q;
    TreeNode *node;

    q.push(root);
    while(!q.empty()) {
        node=q.front();q.pop();
        cout << node->val << ' ';
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
}
void _00_tree_traUpDown(TreeNode *root)
{
    queue<TreeNode*> q;
    int queue_size=0;

    if(!root) return;

    q.push(root);
    while(queue_size=q.size()) {
        while(queue_size--) {
            TreeNode *node=q.front(); q.pop();
            cout<<node->val<<' ';
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout<<endl;
    }
}
void _00_tree_traDownUp(TreeNode *root)
{
    queue<TreeNode*> q;
    stack<TreeNode*> s;
    TreeNode *node, *dummy_node=NULL;
    int queue_size=0;

    q.push(root);

    while(queue_size=q.size()) {
        while(queue_size--) {
            node=q.front(); q.pop();
            s.push(node);
            if(node->right) q.push(node->right); //right child first
            if(node->left) q.push(node->left);
        }
        s.push(dummy_node);
    }

    while(!s.empty()) {
        node=s.top();
        if(node!=dummy_node) cout<<node->val<<' ';
        else cout<<endl;
        s.pop();
    }
}
int _00_tree_getMaxDepth(TreeNode *root)
{
    return (root) ? max(_00_tree_getMaxDepth(root->left), _00_tree_getMaxDepth(root->right))+1 : 0;
}
int _00_tree_getMinDepth(TreeNode *root)
{
    return (root) ? min(_00_tree_getMinDepth(root->left), _00_tree_getMinDepth(root->right))+1 : 0;
}
int _00_tree_getTreeDepth(TreeNode *root)
{
    if(!root) return 0;
    return max(_00_tree_getTreeDepth(root->left), _00_tree_getTreeDepth(root->right))+1;
}
int _00_tree_getTreeDepth(TreeNode *root, bool &isBalance)
{
    if(!root) return 0;
    int left_h =_00_tree_getTreeDepth(root->left, isBalance);
    int right_h=_00_tree_getTreeDepth(root->right, isBalance);
    if(abs(left_h-right_h)>1) isBalance=false;
    return max(left_h, right_h)+1;
}
void _00_tree_deleteTreeNode(TreeNode* &root)
{
    if(!root) return;
    _00_tree_deleteTreeNode(root->left);
    _00_tree_deleteTreeNode(root->right);
    delete root;
    root=nullptr;
}

TreeNode* _01_tree_findLeastCommonAncestor(TreeNode *root, int node1, int node2)
{
    if(!root) return nullptr;
    if(root->val==node1||root->val==node2) return root;

    TreeNode* l_lca=_01_tree_findLeastCommonAncestor(root->left, node1, node2);
    TreeNode* r_lca=_01_tree_findLeastCommonAncestor(root->right, node1, node2);
    if(l_lca&&r_lca) return root;
    else return (l_lca)?l_lca:r_lca;
}

bool _01_tree_checkIdentical(TreeNode* root_x, TreeNode* root_y)
{
    if(!root_x&&!root_y) return true;
    if(!root_x||!root_y) return false;
    return(root_x->val==root_y->val&&
           _01_tree_checkIdentical(root_x->left, root_y->left)&&
           _01_tree_checkIdentical(root_x->right,root_y->right));
}

bool _01_tree_isSubtree(TreeNode* tree, TreeNode* subtree)
{   // N^2
    if(!tree) return false;
    if(!subtree||_01_tree_checkIdentical(tree, subtree)) return true;
    return (_01_tree_isSubtree(tree->left, subtree)||_01_tree_isSubtree(tree->right, subtree));
}

void _01_tree_storeInorder(TreeNode *root, vector<int> &seq)
{
    if(root->left) _01_tree_storeInorder(root->left, seq);
    seq.push_back(root->val);
    if(root->right) _01_tree_storeInorder(root->right, seq);
}

void _01_tree_storePreorder(TreeNode *root, vector<int> &seq)
{
    seq.push_back(root->val);
    if(root->left) _01_tree_storePreorder(root->left, seq);
    if(root->right) _01_tree_storePreorder(root->right, seq);
}

bool _01_tree_isSubtree_fast(TreeNode* tree, TreeNode* subtree)
{   // N
    vector<int> seq_t, seq_s;

    _01_tree_storeInorder(tree, seq_t);
    _01_tree_storeInorder(subtree, seq_s);
    auto pos_in=search(seq_t.begin(), seq_t.end(), seq_s.begin(), seq_s.end());
    if(pos_in==seq_t.end()) return false;

    _01_tree_storePreorder(tree, seq_t);
    _01_tree_storePreorder(subtree, seq_s);
    auto pos_pre=search(seq_t.begin(), seq_t.end(), seq_s.begin(), seq_s.end());
    if(pos_pre==seq_t.end()) return false;
    else return true;
}

//print the path from root that equal to the given sum
void _01_tree_PrintPathSum(TreeNode *root, vector<int> &seq, int sum)
{
    if(!root) return;

    sum-=root->val;
    seq.push_back(root->val);
    if(!sum) {
        for_each(seq.begin(), seq.end(), [](int n){cout<<n<<' ';});
        cout<<endl;
    } else {
        vector<int>  l_seq(seq), r_seq(seq);
        _01_tree_PrintPathSum(root->left, l_seq, sum);
        _01_tree_PrintPathSum(root->right, r_seq, sum);
    }
}

TreeNode* _01_tree_buildTreeFromArray(vector<int> arr, int l, int r)
{
    if(l>r) return nullptr;

    int m=(l+r)/2;
    TreeNode *root=new TreeNode(arr[m]);
    root->left=_01_tree_buildTreeFromArray(arr, l, m-1);
    root->right=_01_tree_buildTreeFromArray(arr, m+1, r);
    return root;
}

void _01_tree_findLevelLinedList(TreeNode* root, vector<list<TreeNode*>> &node_list)
{
    queue<TreeNode*> que;
    int que_size=0, i=0;

    que.push(root);
    while(que_size=que.size())
        while(que_size) {
            TreeNode *node=que.front(); que.pop();
            node_list[i].push_back(node);
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
            que_size--; i++;
        }
}

TreeNode* _01_tree_findLeftMostChild(TreeNode *node)
{
    if(!node) return nullptr;
    while(node->left) node=node->left;
    return node;
}

//Given two binary trees, write a function to check if they are the same or not.
bool _01_tree_isSameTree(TreeNode* p, TreeNode* q)
{
    if(!p&&!q) return true;
    if((!p||!q) || (p->val!=q->val)) return false;
    return _01_tree_isSameTree(p->left,q->left)&&_01_tree_isSameTree(p->right,q->right);
}//leetcode 100 Easy

//Given a binary tree, determine if it is height-balanced.
bool _01_tree_isBalanced(TreeNode* root)
{
    //time(NlogN), two recursion
    if(!root) return true;
    return ( (abs(_00_tree_getTreeDepth(root->left)-_00_tree_getTreeDepth(root->right)<=1)) &&
             (_01_tree_isBalanced(root->left) && _01_tree_isBalanced(root->right)) );
    //time(N)
    if(!root) return true;
    bool isBalance=true;
    _00_tree_getTreeDepth(root, isBalance);
    return isBalance;
}//leetcode 110 Easy

//Given a non-empty special binary tree consisting of nodes with the
//non-negative value, where each node in this tree has exactly two or
//zero sub-node. If the node has two sub-nodes, then this node's value
//is the smaller value among its two sub-nodes.
//Given such a binary tree, you need to output the second minimum value
//in the set made of all the nodes' value in the whole tree.
int findSecondMinimumValue(TreeNode* root)
{
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
}//leetcode 671 Easy

//Given a non-empty binary tree, return the average value of the nodes
//on each level in the form of an array.
vector<double> _01_tree_averageOfLevels(TreeNode* root)
{
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
}//leetcode 637 Easy

//Given a binary tree, find the length of the longest path where each node in
//the path has the same value. This path may or may not pass through the root.
int uniValuePath(TreeNode* root, int &len_root)
{
    if(!root) return 0;
    int len_left=0, len_right=0;
    if(root->left&&root->val==root->left->val)
        len_left=uniValuePath(root->left, len_root)+1;
    if(root->right&&root->val==root->right->val)
        len_right=uniValuePath(root->right, len_root)+1;
    len_root=max(len_root, len_left+len_right); // max(a->a->a, a<-a->a)
    return max(len_left,len_right);
}
int _01_tree_longestUniValuePath(TreeNode* root)
{
    if(!root) return 0;
    int root_len=0;
    uniValuePath(root, root_len);
    return root_len;
}//leetcode 687 Easy

//Compute the length of the diameter of the tree. The diameter of a binary tree
//is the length of the longest path between any two nodes in a tree. This path
//may or may not pass through the root.
int diameter(TreeNode* root, int &len_root)
{
    if(!root) return -1;
    int len_left=diameter(root->left, len_root)+1;
    int len_right=diameter(root->right, len_root)+1;
    len_root=max(len_root, len_left+len_right);
    return max(len_left, len_right);
}
int _01_tree_diameterOfBinaryTree(TreeNode* root)
{
    int len=0;
    diameter(root, len);
    return len;
}//leetcode 543 Easy

//Path Sum
//Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all
//the values along the path equals the given sum.
bool _01_tree_FindAPathSum(TreeNode* root, int sum)
{   //time(N)
    if(!root) return false;
    if(!root->left&&!root->right) return root->val==sum;
    return _01_tree_FindAPathSum(root->left, sum-root->val) ||
           _01_tree_FindAPathSum(root->right, sum-root->val);
}//leetcode 112 Easy

//Given two binary trees and imagine that when you put one of them
//to cover the other, some nodes of the two trees are overlapped while
//the others are not.
//You need to merge them into a new binary tree. The merge rule is that
//if two nodes overlap, then sum node values up as the new value of the
//merged node. Otherwise, the NOT null node will be used as the node of new tree.
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
    TreeNode* root=t1; // merge t2 into t1

    if(!t1) return t2; if(!t2) return t1;
    // root=new TreeNode(t1->val,t2->val); if t1/t2 can't be over-write
    root->val+=t2->val;
    root->left=mergeTrees(t1->left, t2->left);
    root->right=mergeTrees(t1->right, t2->right);
    return root;
}//leetcode 617 Easy

//You need to construct a string consists of parenthesis and integers
//from a binary tree with the preorder traversing way.
string tree2str(TreeNode* t)
{
    if(!t) return "";
    const string s=to_string(t->val);
    const string l=tree2str(t->left);
    const string r=tree2str(t->right);
    // case : s
    if(!t->left&&!t->right) return s;
    // case : s(l)
    if(!t->right) return s+"("+l+")";
    // general: s(l)(r)
    return s + "("+l+")" + "("+r+")";
}//leetcode 606 Easy

//Given a linked list, determine if it has a cycle in it.
bool hasCycle_fast_slow_pointers(ListNode *head)
{
    // time(N) space(N)
    unordered_set<ListNode*> visited;
    while(head) {
        if(visited.count(head)) return true;
        visited.insert(head);
        head=head->next;
    }
    return false;

    // fast/slow pointers, no need extra space
    ListNode *fast, *slow;
    fast=slow=head;
    while(fast) {
        if(!fast->next) return false;
        if((fast=fast->next->next)==(slow=slow->next)) return true;
    }
    return false;
}//leetcode 141 Easy

//Path Sum II
//Given a binary tree and a sum, find all root-to-leaf paths where each path's
//sum equals the given sum.
void pathSum(TreeNode* root, int sum, vector<int> &curr, vector<vector<int>> &res)
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
    pathSum(root->left, sum-root->val, curr, res);
    pathSum(root->right, sum-root->val, curr, res);
    curr.pop_back();
}
vector<vector<int>> _01_tree_FindAllPathSum(TreeNode* root, int sum)
{
    vector<int> curr; vector<vector<int>> res;
    pathSum(root, sum, curr, res);
    return res;
}//leetcode 113 Medium

//Given an integer array with no duplicates. A maximum tree building on this
//array is defined as follow:
//1. The root is the maximum number in the array.
//2. The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
//3. The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
//Construct the maximum tree by the given array and output the root node of this tree.
TreeNode* constructMBT(vector<int>& nums, int l, int r)
{
    if(l>=r) return nullptr;
    auto root_idx=max_element(nums.begin()+l, nums.begin()+r);
    TreeNode* root=new TreeNode(*root_idx);
    int m=distance(nums.begin(), root_idx);
    root->left=constructMBT(nums, l, m);
    root->right=constructMBT(nums, m+1, r);
    return root;
}
TreeNode* _01_tree_constructMaximumBinaryTree(vector<int>& nums)
{   // time(NlogN) space(N)
    return constructMBT(nums, 0, nums.size());
}//leetcode 654 Medium

//Given a binary tree, return the level order traversal of its nodes' values.
//(ie, from left to right, level by level).
vector<vector<int>> _01_tree_levelOrder(TreeNode* root)
{
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
}//leetcode 102 Medium

//Given a binary tree, return all duplicate subtrees. For each kind of duplicate
//subtrees, you only need to return the root node of any one of them.
int findDuplicateSubtrees_getId(TreeNode* root,
                                unordered_map<long, pair<int,int>>& counts,
                                vector<TreeNode*>& res)
{
    if(!root) return 0;
    long key=(static_cast<long>(root->val) << 32) |
             (findDuplicateSubtrees_getId(root->left, counts, res) << 16) |
              findDuplicateSubtrees_getId(root->right, counts, res);
    auto it = counts.find(key);
    if (it == counts.end())
        it = counts.insert({key, {counts.size() + 1, 0}}).first;

    if (++it->second.second == 2)
        res.push_back(root);

    return it->second.first;
}
vector<TreeNode*> _01_tree_findDuplicateSubtrees(TreeNode* root)
{   // Key: (root.val, id(root.left), id(root.right))
    unordered_map<long, pair<int,int>> counts; // key -> {id, count}
    vector<TreeNode*> res;
    findDuplicateSubtrees_getId(root, counts, res);
    return res;
}//leetcode 652 Medium

//Given a binary tree, return the postorder traversal of its nodes' values.
vector<int> _01_tree_postorderTraversal(TreeNode* root)
{
    if(!root) return{};
    deque<int> res; // for reverse postorder
    stack<TreeNode*> s;

    s.push(root);
    while(s.size()) {
        auto node=s.top(); s.pop();
        res.push_front(node->val); // reverse postorder
        if(node->left) s.push(node->left);
        if(node->right) s.push(node->right);
    }
    return vector<int>(res.begin(),res.end());
}//leetcode 145 Hard

//==================================BinaryTree-

//==================================NaryTree+
TreeNode* _00_ntree_insertNode(TreeNode *node, int val)
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
void _00_ntree_dfs(TreeNode *root)
{
    if(!root) return;

    while(root) {
        cout << " " << root->val;
        if (root->left) _00_ntree_dfs(root->left);
        root = root->right;
    }
}
void _00_ntree_bfs(TreeNode *root)
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
//==================================NaryTree-

//==================================BinarySearchTree+
TreeNode* _00_bst_insertNode(TreeNode *root, int val)
{
    if(!root) return new TreeNode(val);

    if(val<root->val)
        root->left=_00_bst_insertNode(root->left, val);
    else if (val>root->val)
        root->right=_00_bst_insertNode(root->right, val);
    else
        return root;
}
TreeNode* _00_bst_findMinNode(TreeNode *root)
{
    while(root->left) root=root->left;
    return root;
}
TreeNode* _00_bst_findMaxNode(TreeNode *root)
{
    while(root->right) root=root->right;
    return root;
}
TreeNode* _00_bst_deleteNode(TreeNode *root, int val)
{
    TreeNode *node;

    if(!root) return root;

    if(val<root->val)
        root->left=_00_bst_deleteNode(root->left, val);
    else if(val>root->val)
        root->right=_00_bst_deleteNode(root->right, val);
    else { // val=root->val
        if(root->right) {
            node=_00_bst_findMinNode(root->right); // replace by the min right child
            root->val=node->val;
            root->right=_00_bst_deleteNode(root->right, node->val);
        } else if(root->left) {
            node=_00_bst_findMaxNode(root->left); // replace by the max left child
            root->val=node->val;
            root->left=_00_bst_deleteNode(root->left, node->val);
        } else {
            delete root;
            root=nullptr;
        }
    }
    return root;
}

//fnd the ‘next’ node (ie, in-order successor) of a given node in
//a binary search tree where each node has a link to its p
TreeNode* _01_bst_findInorderSucc(TreeNode *node)
{
    TreeNode *succ_node;
    if(!node) return nullptr;

    // Found right children -> return 1st inorder node on right
    if(!node->parent||node->right)
        succ_node=_01_bst_findInorderSucc(node->right);
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

//Given a binary search tree and the lowest and highest boundaries as L and R,
//trim the tree so that all its elements lies in [L, R] (R >= L). You might
//need to change the root of the tree, so the result should return the new root
//of the trimmed binary search tree.
TreeNode* _01_bst_trimBST(TreeNode* root, int L, int R)
{
    TreeNode* new_root;
    if(!root) return nullptr;
    // root->val not in the range, return the left/right subtrees
    if(root->val<L) {
        new_root=_01_bst_trimBST(root->right, L, R);
        _00_tree_deleteTreeNode(root->left);
        delete root; root=nullptr;
        return new_root;
    }
    if(root->val>R) {
        new_root=_01_bst_trimBST(root->left, L, R);
        _00_tree_deleteTreeNode(root->right);
        delete root; root=nullptr;
        return new_root;
    }
    // root->val int the range, recursively trim left/right subtrees
    root->left=_01_bst_trimBST(root->left, L, R);
    root->right=_01_bst_trimBST(root->right, L, R);
    return root;
}//leetcode 669 Easy

//Given a binary search tree with non-negative values, find the minimum absolute
//difference between values of any two nodes.
void getMinimumDifference_inorder(TreeNode* root, int* pre_val, int &min_diff)
{   //BST after inorder DFS is a sorted sequence
    if(!root) return;
    getMinimumDifference_inorder(root->left, pre_val, min_diff);
    if(pre_val) min_diff=min(min_diff, root->val-*pre_val);
    pre_val=&root->val;
    getMinimumDifference_inorder(root->right, pre_val, min_diff);
}
int  _01_bst_getMinimumDifference(TreeNode* root)
{   //time(N) space(logN)
    int *pre_val=nullptr, min_diff=INT_MAX;
    getMinimumDifference_inorder(root, pre_val, min_diff);
    return min_diff;
}//leetcode 530 Easy

//Two Sum IV ¡V Input is a BST
//Given a Binary Search Tree and a target number, return true if there exist two elements
//in the BST such that their sum is equal to the given target.
void findTarget_inorder(TreeNode* root, vector<int> &sorted)
{
    if(!root) return;
    findTarget_inorder(root->left, sorted);
    sorted.push_back(root->val);
    findTarget_inorder(root->right, sorted);
}
bool _01_bst_twoSumFindTarget(TreeNode* root, int k)
{
    vector<int> sorted;
    findTarget_inorder(root, sorted);
    int l=0, r=sorted.size()-1;
    while(l<r) {
        int sum=sorted[l]+sorted[r];
        if(sum==k) return true;
        else if(sum<k) l++;
        else r--;
    }
    return false;

}//leetcode 653 Easy

//Determine if it is a valid binary search tree
bool isValidBST_inorder(TreeNode* root, TreeNode* pre_node)
{
    if(!root) return true;
    if(!isValidBST_inorder(root->left, pre_node)) return false;
    if(pre_node&&pre_node->val>=root->val) return false;
    pre_node=root;
    if(!isValidBST_inorder(root->right, pre_node)) return false;
}
bool _01_bst_isValidBST(TreeNode* root)
{   //result of inorder travel a BST is a ascending sequence
    //time(N) space(logN)
    TreeNode* pre_node=nullptr;
    return isValidBST_inorder(root, pre_node);
}//leetcode 98 Medium

//Serialize and Deserialize BST
//each node 4 bytes, totally 4N bytes, use pre-order
// 5(root)[2 1 4](left)[6 8](right)
class CodecBST{
public:
    string _01_bst_enode(TreeNode* root) {
        string bitstream;
        encode(root, bitstream);
        return bitstream;
    }
    TreeNode* _01_bst_decode(string bitstream) {
        int pos=0;
        return decode(bitstream, pos, INT_MIN, INT_MAX);
    }
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
};//leetcode 449 Medium

//==================================BinarySearchTree-

//==================================AVLBinarySearchTree+
int _00_avl_getHeight(TreeNode *node)
    {return (node) ? node->height : 0;}
int _00_avl_getBalanceFactor(TreeNode *node)
    {return (node) ? _00_avl_getHeight(node->left) - _00_avl_getHeight(node->right) : 0;}
TreeNode* _00_avl_lRotate(TreeNode *x)
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
    x->height = 1+max(_00_avl_getHeight(x->left), _00_avl_getHeight(x->right));
    y->height = 1+max(_00_avl_getHeight(y->left), _00_avl_getHeight(y->right));

    return y;
}
TreeNode* _00_avl_rRotate(TreeNode *x)
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
    x->height = 1+max(_00_avl_getHeight(x->left), _00_avl_getHeight(x->right));
    y->height = 1+max(_00_avl_getHeight(y->left), _00_avl_getHeight(y->right));

    return y;
}
TreeNode* _00_avl_insertNode(TreeNode *node, int val)
{
    if(!node) return new TreeNode(val);

    if(val<node->val)
        node->left=_00_avl_insertNode(node->left, val);
    else if (val>node->val)
        node->right=_00_avl_insertNode(node->right, val);
    else
        return node;

    int lChildH=_00_avl_getHeight(node->left);
    int rChildH=_00_avl_getHeight(node->right);
    int bFactor=lChildH-rChildH;
    node->height=1+max(lChildH,rChildH);

    // LL case
    if(bFactor> 1 && val<node->left->val) {
        return _00_avl_rRotate(node);
    }
    // LR case
    if(bFactor> 1 && val>node->left->val) {
        node->left =  _00_avl_lRotate(node->left);
        return _00_avl_rRotate(node);
    }
    // RR case
    if(bFactor<-1 && val>node->right->val) {
        return _00_avl_lRotate(node);
    }
    // RL case
    if(bFactor<-1 && val<node->right->val) {
        node->right = _00_avl_rRotate(node->right);
        return _00_avl_lRotate(node);
    }

    return node;
}
TreeNode* _00_avl_deleteNode(TreeNode *root, int val)
{
    TreeNode *node;

    if(!root) return root;

    if(val<root->val)
        root->left=_00_avl_deleteNode(root->left, val);
    else if(val>root->val)
        root->right=_00_avl_deleteNode(root->right, val);
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
        node=_00_bst_findMinNode(root->right);
        root->val=node->val;
        root->right=_00_avl_deleteNode(root->right, node->val);
    }

    if(!root) return root;
    else node=root;

    node->height=1+max(_00_avl_getHeight(node->left),_00_avl_getHeight(node->right));

    // LL case
    if(_00_avl_getBalanceFactor(node)>1 && _00_avl_getBalanceFactor(node->left)>=0) {
        return _00_avl_rRotate(node);
    }
    // LR case
    if(_00_avl_getBalanceFactor(node)>1 && _00_avl_getBalanceFactor(node->left)<0) {
        node->left =  _00_avl_lRotate(node->left);
        return _00_avl_rRotate(node);
    }
    // RR case
    if(_00_avl_getBalanceFactor(node)<-1 && _00_avl_getBalanceFactor(node->right)<=0) {
        return _00_avl_lRotate(node);
    }
    // RL case
    if(_00_avl_getBalanceFactor(node)<-1 && _00_avl_getBalanceFactor(node->left)>0) {
        node->right = _00_avl_rRotate(node->right);
        return _00_avl_lRotate(node);
    }
    return node;
}
//==================================AVLBinarySearchTree-

//==================================FenwickTree+
//Range Sum Query - Mutable
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
class NumArray { //lc307 Medium
public:
    NumArray(vector<int> nums) {}
    void update(int i, int val) {}
    int sumRange(int i, int j) {}
};

//Count of Smaller Numbers After Self
//You are given an integer array nums and you have to return a new counts array.
//The counts array has the property where counts[i] is the number of smaller
//elements to the right of nums[i].
class lc315 { //Hard
public:
    vector<int> countSmaller(vector<int>& nums) {

    }
};
//==================================FenwickTree-

//==================================Graph+
// The perimeter of the island
int _01_graph_islandPerimeter(vector<vector<int>>& grid)
{
    // 一個格子4個邊，若這個格子有一個neighbor就減少一個邊
    int m,n,area=0,nbor=0;

    if(grid.empty()) return 0;
    m=grid.size(); n=grid[0].size();
    for(auto i=0; i<m; i++)
        for(auto j=0; j<n; j++)
            if(grid[i][j]) {
                area++;
                if((i>0  &&grid[i-1][j]) || // up nbor
                   (i<m-1&&grid[i+1][j]) || // down nbor
                   (j>0  &&grid[i][j-1]) || // left nbor
                   (j<n-1&&grid[i][j+1]))    // right nbor
                    nbor++;
            }
    return area*4-nbor;
} //leetcode 463

//Given a binary tree where every node has a unique value, and a target key k, find
//the value of the closest leaf node to target k in the tree.
void findClosestLeaf_buildGraph(TreeNode* node, TreeNode* par_node, TreeNode* &start, int k,
                                unordered_map<TreeNode*, vector<TreeNode*>> &graph)
{
    if(!node) return;
    if(node->val==k) start=node;
    if(par_node) {
        graph[node].push_back(par_node);
        graph[par_node].push_back(node);
    }
    findClosestLeaf_buildGraph(node->left, node, start, k, graph);
    findClosestLeaf_buildGraph(node->right, node, start, k, graph);
}
int _01_graph_findClosestLeaf(TreeNode* root, int k)
{   //use DFS to construct the undirected graph and find the start node. O(N)
    //Use BFS to search the graph from start node to any leaf node (shortest path). O(N)
    //Each node has most 3 edges
    //time(N) space(N)
    unordered_map<TreeNode*, vector<TreeNode*>> graph;
    unordered_set<TreeNode*> visited;
    queue<TreeNode*> q;
    TreeNode* start;
    int queue_size=0;

    findClosestLeaf_buildGraph(root, nullptr, start, k, graph);
    q.push(start);
    while(queue_size=q.size()) {
        while(queue_size--) {
            TreeNode* curr=q.front(); q.pop();
            visited.insert(curr);
            if(!curr->left&&!curr->right) return curr->val;
            for(auto node:graph[curr])
                if(!visited.count(node)) q.push(node);
        }
    }
    return 0;
}//leetcode 742 Medium

//Given a list of airline tickets represented by pairs of departure and arrival
//airports [from, to], reconstruct the itinerary in order. All of the tickets
//belong to a man who departs from JFK.
void findItinerary_visit(string src, unordered_map<string,deque<string>> &trips, vector<string> &route)
{
    auto dsts=trips[src];
    while(dsts.size()) {
        auto dst=dsts.front(); dsts.pop_front();
        findItinerary_visit(dst, trips, route);
    }
    route.push_back(src);
}
vector<string> _01_graph_findItinerary(vector<pair<string, string>> tickets)
{
    unordered_map<string,deque<string>> trips; // src -> {dst1, dest2, ..., destn}
    vector<string> route;

    for(auto pair:tickets)
        trips[pair.first].push_back(pair.second);
    for(auto pair:trips)
        sort(pair.second.begin(),pair.second.end());

    findItinerary_visit("JFK", trips, route);
    return vector<string>(route.crbegin(),route.crend());
}//leetcode 332 Medium

//Network Delay Time
int _01_graph_networkDelayTime(vector<vector<int>>& times, int N, int K)
{   //Dijkstra time(N^2->NlogN+E) space(N+E)

    //Bellman-Ford time(NE) space(N)
    constexpr int MAX_TIME = 101 * 100;
    vector<int> dist(N, MAX_TIME);
    dist[K - 1] = 0;
    for (int i = 0; i < N; ++i)
        for (const auto& time : times) {
            int u = time[0] - 1, v = time[1] - 1, w = time[2];
            dist[v] = min(dist[v], dist[u] + w);
        }
    int max_dist = *max_element(dist.begin(), dist.end());
    return max_dist == MAX_TIME ? -1 : max_dist;

    //Floyd-Warshall (all pairs) time(N^3) space(N^2)
    //constexpr int MAX_TIME = 101 * 100;
    vector<vector<int>> d(N, vector<int>(N, MAX_TIME));

    for (auto time : times)
        d[time[0] - 1][time[1] - 1] = time[2];

    for (int i = 0; i < N; ++i)
        d[i][i] = 0;

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int max_time = *max_element(d[K - 1].begin(), d[K - 1].end());
    return max_time >= MAX_TIME ? - 1 : max_time;

}//leetcode 743 Medium

//==================================Graph -


int main_tree(void)
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

    _00_tree_dfsInorder(root);cout<<"(DF Inorder)"<<endl;
    _00_tree_dfsPreorder(root);cout<<"(DF Preorder)"<<endl;
    _00_tree_dfsPostorder(root);cout<<"(DF Postorder)"<<endl;
    _00_tree_bfsLevelorder(root);cout<<"(BF)"<<endl;
    //==============================BinaryTree-
#endif // 0
#if 0
    //==============================BinarySearchTree+
    root = new TreeNode(50);
    _00_bst_insertNode(root, 30);
    _00_bst_insertNode(root, 20);
    _00_bst_insertNode(root, 40);
    _00_bst_insertNode(root, 70);
    _00_bst_insertNode(root, 60);
    _00_bst_insertNode(root, 80);
    _00_bst_insertNode(root, 90);
    _00_bst_insertNode(root, 10);

//    _00_bst_deleteNode(root, 40);
//    _00_bst_deleteNode(root, 20);
//    _00_bst_deleteNode(root, 10);

    _00_tree_traUpDown(root); cout<<endl;
    _00_tree_traDownUp(root); cout<<endl;
    cout<<"Min Depth: "; cout<<_00_tree_getMinDepth(root)<<endl;
    cout<<"Max Depth: "; cout<<_00_tree_getMaxDepth(root)<<endl;
    cout<<"Min Node: "; node=_00_bst_findMinNode(root);cout<<node->val<<endl;
    cout<<"Max Node: "; node=_00_bst_findMaxNode(root);cout<<node->val<<endl;

    cout<<_01_tree_findLeastCommonAncestor(root, 20, 40)->val<<endl;

    //==============================BinarySearchTree-
#endif // 0
#if 0
    //==============================AVLBinarySearchTree+
    root = new TreeNode(10);
    root = _00_avl_insertNode(root, 20);
    root = _00_avl_insertNode(root, 30);
    root = _00_avl_insertNode(root, 40);
    root = _00_avl_insertNode(root, 50);
    root = _00_avl_insertNode(root, 25);
    root = _00_avl_insertNode(root, 35);
    //root = root->_00_avl_insertNode(root, 60);
    _00_tree_traUpDown(root);

    //root = root->_00_avl_deleteNode(root, 35);
    //_00_tree_traUpDown(root);
    _00_tree_dfsInorder(root); cout<<endl;
    _00_tree_dfsPreorder(root); cout<<endl;
    _00_tree_dfsPostorder(root); cout<<endl;
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
    TreeNode *n1 = _00_ntree_insertNode(root,2);
    TreeNode *n2 = _00_ntree_insertNode(root,3);
    TreeNode *n3 = _00_ntree_insertNode(root,4);
    TreeNode *n4 = _00_ntree_insertNode(n3,6);
    TreeNode *n5 = _00_ntree_insertNode(root,5);
    TreeNode *n6 = _00_ntree_insertNode(n5,7);
    TreeNode *n7 = _00_ntree_insertNode(n5,8);
    TreeNode *n8 = _00_ntree_insertNode(n5,9);
    cout<<"DFS: "; traverseDFS_NaT(root); cout<<endl;
    cout<<"BFS: "; traverseBFS_NaT(root); cout<<endl;
#endif // 1
    cout<<endl<<"Hello Tree";
    return 0;
}


