#include "leetcode.h"

int getTreeDepth(TreeNode *root)
{
    if(!root) return 0;
    return max(getTreeDepth(root->left), getTreeDepth(root->right))+1;
}
int getTreeDepth(TreeNode *root, bool &isBalance)
{
    if(!root) return 0;
    int left_h =getTreeDepth(root->left, isBalance);
    int right_h=getTreeDepth(root->right, isBalance);
    if(abs(left_h-right_h)>1) isBalance=false;
    return max(left_h, right_h)+1;
}
void deleteTreeNode(TreeNode* &root)
{
    if(!root) return;
    deleteTreeNode(root->left);
    deleteTreeNode(root->right);
    delete root;
    root=nullptr;
}
//=============================================================================










