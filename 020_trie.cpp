#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define ALPHABET_SIZE 26
#define SIZE(a) (int)(sizeof(a)/sizeof(a[0]))
#define DIST(c) ((int)c - (int)'a')

//Implement Trie (Prefix Tree)
class lc208 { //Medium
public:
    /** Initialize your data structure here. */
    Trie() {

    }

    /** Inserts a word into the trie. */
    void insert(string word) {

    }

    /** Returns if the word is in the trie. */
    bool search(string word) {

    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {

    }
};

class TrieNode
{
private:
    vector<TrieNode*> child;
    bool leaf;
public:
    TrieNode(int size) : child(size, NULL), leaf(false) {}
    void insertKey_Trie(TrieNode *root, string key);
    bool searchKey_Trie(TrieNode *root, string key);
    bool deleteKey_Trie(TrieNode *root, string key, int pivot, int len);
    bool isEmptyChild_Trie(TrieNode *node);
};
bool TrieNode::isEmptyChild_Trie(TrieNode *node)
{
    return all_of(node->child.begin(),node->child.end(), bind2nd(equal_to<bool>(),NULL));
}
void TrieNode::insertKey_Trie(TrieNode *root, string key)
{
    for(auto i=0; i<(int)key.size(); i++) {
        int idx=DIST(key[i]);
        if(!root->child[idx]) root->child[idx]=new TrieNode(ALPHABET_SIZE);
        root=root->child[idx];
    }
    root->leaf=true;
}
bool TrieNode::searchKey_Trie(TrieNode *root, string key)
{
    cout<<"Search string("<<key<<") : ";
    for(auto i=0; i<(int)key.size(); i++) {
        int idx=DIST(key[i]);
        if(!root->child[idx]) return false;
        root=root->child[idx];
    }
    return (root&&root->leaf);
}
bool TrieNode::deleteKey_Trie(TrieNode *root, string key, int pivot, int len)
{
    if(!root) return false;

    if(pivot!=len) {
        int idx=DIST(key[pivot]);
        if(deleteKey_Trie(root->child[idx], key, pivot+1, len)) {
            // last node marked, delete it.
            delete root->child[idx];
            // recursively climb up, and delete eligible nodes
            return (!root->leaf&&isEmptyChild_Trie(root));
        }
    }else if(pivot==len&&root->leaf){
        root->leaf=false; //unmark leaf
        if(isEmptyChild_Trie(root)) return true;
        return false;
    }
    return false;
}
int main_trie(void)
{
    string keys[]={"the", "a", "there", "answer", "any", "by", "bye", "their"};
    TrieNode* root=new TrieNode(ALPHABET_SIZE);
    for(auto i=0; i<SIZE(keys); i++)
        root->insertKey_Trie(root, keys[i]);
    root->searchKey_Trie(root, "the") ? cout<<"Yes\n" : cout<<"No\n";
    root->searchKey_Trie(root, "good") ? cout<<"Yes\n" : cout<<"No\n";
    root->deleteKey_Trie(root, "the", 0, sizeof("the")-1);
    root->searchKey_Trie(root, "the") ? cout<<"Yes\n" : cout<<"No\n";

    cout<<endl<<"Hello Trie";
    return 0;
}
