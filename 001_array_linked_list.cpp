#include "leetcode.h"

//Maximum Gap
//Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
class lc164 { //Hard
public:
    int MaximumGap(vector<int>& nums) {
        //Bucket sort. Use n buckets to store all the numbers. For each bucket, only track the min / max value.
        int n=nums.size();
        if(n<2) return 0;

        vector<int> min_bin(n,INT_MAX);
        vector<int> max_bin(n,INT_MIN);
        auto mm=minmax_element(nums.begin(),nums.end());
        int bin_size=(*mm.second-*mm.first)/n+1;
        for(auto num:nums) {
            int idx=(num-*mm.first)/bin_size;
            min_bin[idx]=min(min_bin[idx], num);
            max_bin[idx]=max(max_bin[idx], num);
        }

        int max_gap=0;
        int pre_max=max_bin[0];
        for(int i=1;i<n;i++)
            if(min_bin[i]!=INT_MAX) {
                max_gap=max(max_gap, min_bin[i]-pre_max);
                pre_max=max_bin[i];
            }
        return max_gap;
    }
};

//Max Chunks To Make Sorted II
//the integers of the given array are not necessarily distinct,
//the input array could be up to length 2000, and the elements could be up to 10**8.
class lc768 { //Hard
public:
    int MaxChunksToMakeSortedII(vector<int>& arr) {
        //Reduce the problem to 769. by creating a mapping from number to index in the sorted array.
        vector<int> map(arr.size());
        iota(map.begin(),map.end(),0); // assign idx to the mapping, start from 0. iota:用顺序递增的值赋值指定范围内的元素
        sort(map.begin(),map.end(), // sort the idx according the value
             [&arr](int x,int y){return arr[x]==arr[y] ? x<y : arr[x]<arr[y];});
        // then the same as 769
        int max_val=0, chunk_num=0;
        for(int i=0;i<map.size();i++) {
            max_val=max(max_val, map[i]);
            if(max_val==i) chunk_num++;
        }
        return chunk_num;
    }
};

//Max Chunks To Make Sorted
//Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split
//the array into some number of "chunks" (partitions), and individually sort each chunk.
//After concatenating them, the result equals the sorted array.
//What is the most number of chunks we could have made?
class lc769 { //Medium
public:
    int MaxChunksToMakeSortedI(vector<int>& arr) {
        int max_val=0, chunk_num=0;
        for(int i=0;i<arr.size();i++) {
            max_val=max(max_val, arr[i]);
            if(max_val==i) chunk_num++; //目前最大值所屬之index出現了，表示在這之前的都可以自成一個chunk
        }
        return chunk_num;
    }
};

//Toeplitz Matrix
//A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.
//Given an M x N matrix, return True if and only if the matrix is Toeplitz.
class lc766 { //Easy
private:
    int m,n;
public:
    bool ToeplitzMatrix(vector<vector<int>>& matrix) {
        m=matrix.size(); if(!m) return false;
        n=matrix[0].size(); if(!n) return false;

        for(int y=1;y<m;y++)
            for(int x=1;x<n;x++)
                if(matrix[y][x]!=matrix[y-1][x-1]) return false;
        return true;
    }
};

//Two Sum
//Given an array of integers, return indices of the two numbers such that
//they add up to a specific target.
class lc001 { //Easy
public:
    vector<int> TwoSum(vector<int>& nums, int target) {
        //time(N), space(N)
        unordered_map<int, int> table;
        for(auto i=0; i<nums.size(); i++)
            table[nums[i]]=i;
        for(auto i=0; i<nums.size(); i++) {
            int diff=target-nums[i];
            if(table.count(diff)&&table[diff]!=i)
                return {i, table[diff]};
        }
        return {};
    }
};

//Largest Number At Least Twice of Others
//In a given integer array nums, there is always exactly one largest element.
//Find whether the largest element in the array is at least twice as much as
//every other number in the array.
class lc747 { //Easy
public:
    int LargestNumberAtLeastTwiceOfOthers(vector<int>& nums) {
        int max1=-1, max2;
        auto i=max_element(nums.begin(),nums.end());
        swap(max1, *i);
        max2=*max_element(nums.begin(),nums.end());
        *i=max1;
        return max1>=max2*2 ? distance(nums.begin(),i) : -1;
    }
};

//Reshape the Matrix
//You're given a matrix represented by a two-dimensional array,
//and two positive integers r and c representing the row number and column number
//of the wanted reshaped matrix, respectively.
//The reshaped matrix need to be filled with all the elements of the original matrix
//in the same row-traversing order as they were.
class lc566 { //Easy
public:
    vector<vector<int>> ReshapeTheMatrix(vector<vector<int>>& nums, int r, int c) {
        //time(MN), space(MN)
        vector<vector<int>> matrix(r, vector<int>(c,0));
        int m,n;

        if(nums.empty()) return nums;
        if((m=nums.size())*(n=nums[0].size()) != r*c) return nums;
        for(auto i=0; i<m*n; i++)
            matrix[i/c][i%c]=nums[i/n][i%n];
        return matrix;
    }
};

//Array Partition I
//Given an array of 2n integers, your task is to group these integers into
//n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes
//sum of min(ai, bi) for all i from 1 to n as large as possible.
class lc561 { //Easy
public:
    int ArrayPartitionI(vector<int>& nums) {
        //time(NlogN), space(1)
        int sum=0;
        //先sort過，每個搭配比它大一點的數，也就是sort後的下一個
        sort(nums.begin(),nums.end());
        for(auto i=0; i<nums.size(); i+=2)
            sum+=nums[i];
        return sum;
    }
};

// 90: transpose, vertically    swap(A[m,n], A[n,m]), swap(A[m,n], A[m, dim-1-n])
//180: vertically, horizontally swap(A[m,n], A[m, dim-1-n]), swap(A[m,n], A[dim-1-m, n])
//270: transpose, horizontally  swap(A[m,m], A[n,m]), swap(A[m,n], A[dim-1-m, n])
void _ARotateMatrix90degree(vector<vector<int>> matrix)
{
    int m,n,dim=matrix.size();
    // swap(A[m,n], A[n,m]), transpose
    for(m=0; m<dim-1; m++)
        for(n=m+1; n<dim; n++)
            swap(matrix[m][n],matrix[n][m]);
    // swap(A[m,n], A[m, dim-n]), vertically
    for(m=0; m<dim; m++)
        for(n=0; n<dim/2; n++)
            swap(matrix[m][n],matrix[m][dim-1-n]);

    for(m=0; m<dim; m++) {
        for(n=0; n<dim; n++)
            cout<<matrix[m][n]<<' ';
        cout<<endl;
    }
}

//if an element is 0, set all its row/col to 0;
void _ASetRowColZero(vector<vector <int>> matrix)
{
    int i, j, row_p, col_p, n=matrix.size();
    bitset<4> row_z,col_z;

    row_p=col_p=1;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            row_p*=matrix[i][j];
            col_p*=matrix[j][i];
        }
        if(!row_p) row_z.set(i);
        if(!col_p) col_z.set(i);
        row_p=col_p=1;
    }

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(row_z.test(i)||col_z.test(j))
                matrix[i][j]=0;
            cout<<matrix[i][j]<<' ';
        }
        cout<<endl;
    }
}

//=============================================================================LinkList+

//Split Linked List in Parts
//Given a (singly) linked list with head node root,
//write a function to split the linked list into k consecutive linked list "parts".
class lc725 { //Medium
public:
    vector<ListNode*> SplitLinkedListInParts(ListNode* root, int k) {
        vector<ListNode*> res(k);
        ListNode *head, *prev;
        int len=0;

        head=root;
        while(head) {len++;head=head->next;}

        int q=len/k; int r=len%k;
        head=root;prev=nullptr;
        for(int i=0;i<k;i++,r--) {
            res[i]=head;
            for(int j=0;j<q+(r>0);j++) {
                prev=head;
                head=head->next;
            }
            if(prev) prev->next=nullptr;
        }
        return res;
    }
};

//Merge Two Sorted Lists
//Merge two sorted linked lists and return it as a new list.
//The new list should be made by splicing together the nodes of the first two lists.
class lc021 { //Easy
public:
    ListNode* MergeTwoSortedLists(ListNode* l1, ListNode* l2) {
        //time(N), iterative
        ListNode head(0);
        ListNode *tail=&head;
        while(l1&&l2) {
            if(l1->val<l2->val) { tail->next=l1; l1=l1->next; }
            else { tail->next=l2; l2=l2->next; }
            tail=tail->next;
        }
        if(l1) tail->next=l1; if(l2) tail->next=l2;
        return head.next;

        //==============================
        //time(N) recursion
        if(!l1||!l2) return l1?l1:l2;
        if(l1->val<l2->val) {l1->next=MergeTwoSortedLists(l1->next,l2); return l1;}
        else {l2->next=MergeTwoSortedLists(l1, l2->next); return l2;}
    }
};

//Linked List Cycle
//Given a linked list, determine if it has a cycle in it.
class lc141 { //Easy
public:
    bool LinkedListCycle(ListNode *head) {
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
    }
};

ListNode* _LFindLoopStart(ListNode* node)
{
//    if no duplicated key value, use hash table, like in BFS/DFS Graph traverse

//    k: length of non-looped part
//    n: length of looped part
//    x: length from loop start to meet point
//
//    Prove: k=n-x;
//    Known: 1st meet: 2x(steps of slower)=(steps of faster)
//    =>2(k+x)=(k+n+x)
//    =>k=n-x
    ListNode *slow, *fast;

    slow=fast=node;
    while(fast) { // find meeting point
        if(!fast->next) return nullptr; // no loop
        if((slow=slow->next)==(fast=fast->next->next)) break;
    }

    while(node!=fast) { // k=n-x
        node=node->next;
        fast=fast->next;
    }
    return node;
}

void _LRemoveDuplicate(ListNode *node)
{
    ListNode *pivot=node, *prev;

    // time(N^2), no temp buff
    while(pivot) {
        node=pivot->next;
        while(node) {
            if(pivot->val!=node->val) {
                prev=node;
                node=node->next;
            } else {
                prev->next=node->next;
                delete node;
                node=prev->next;
            }
        }
        pivot=pivot->next;
    }
    //==============================
    // time(N)
    bitset<100> table;
    while(node) {
        if(!table.test(node->val)) {
            table.set(node->val);
            prev=node;
            node=node->next;
        } else {
            prev->next=node->next;
            delete node;
            node=prev->next;
        }
    }
}
ListNode* _LFindLastNNode(ListNode* node, int n)
{
    ListNode *fr_node, *rr_node;

    if(!node||n<1) return nullptr;
    else fr_node=rr_node=node;
    for(auto i=0; i<n-1; i++) { // skip n-1 steps ahead
        if(!rr_node) return nullptr;
        rr_node=rr_node->next; // not found since list size < n
    }
    while(rr_node->next) {
        fr_node=fr_node->next;
        rr_node=rr_node->next;
    }
    return fr_node;
}

bool _LRemoveNode(ListNode* node)
{
    ListNode *nx_node;

    if(!node||!node->next) return false; //this algo can't handle the case of removing the last node

    nx_node=node->next;
    delete node;
    node->val=nx_node->val;
    node->next=nx_node->next;

    return true;
}

ListNode* _LAddTwoNumber(ListNode *x, ListNode *y, ListNode *sum)
{
    ListNode *result=sum;
    int carry=0;

    if(!x||!y||!sum) return nullptr;

    while(x||y) {
        if(x) {carry+=x->val; x=x->next;}
        if(y) {carry+=y->val; y=y->next;}
        sum->val=carry%10;carry/=10;
        sum=sum->next;
    }
    if(carry) sum->val=carry;
    return result;
}

//=============================================================================LinkList-
#if 0
int main()
{
    vector<vector<int>> m{{1,  2,  3,  4},
                          {5,  6,  7,  8},
                          {9,  0, 11, 12},
                          {13, 14, 15, 16}};
//    _ARotateMatrix90degree(m);
    _ASetRowColZero(m);

    ListNode *node, *root;
    node=root=new ListNode(1);
    while(node->next) node=node->next;
    node->next=new ListNode(2);
    node=root;
    while(node->next) node=node->next;
    node->next=new ListNode(3);
    node=root;
    while(node->next) node=node->next;
    node->next=new ListNode(6);
    node=root;
    while(node->next) node=node->next;
    node->next=new ListNode(2);

    node=root;
    while(node) {
        cout<<node->val<<' ';
        node=node->next;
    }
    node=root;
//    _LRemoveDuplicate(node);
//    node=_LFindLastNNode(node, 2);
//    _LRemoveNode(node3);
    node=_LAddTwoNumber(node,node,node);
//    node=root;
    cout<<endl;
    while(node) {
        cout<<node->val<<' ';
        node=node->next;
    }
    cout<<endl<<"Hello 02";
    return 0;
}
#endif
