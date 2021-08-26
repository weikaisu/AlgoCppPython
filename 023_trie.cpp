#include "leetcode.h"

//Implement Trie (Prefix Tree)
class lc208 { //Medium
private:
    struct TrieNode{
        unordered_map<char,TrieNode*> child;

        bool leaf;
        TrieNode(){leaf=false;}
       ~TrieNode(){for(auto c:child) if(c.second) delete c.second;}
    };

    TrieNode* root;

    TrieNode* find(string &prefix) {
        TrieNode* p=root;
        for(auto c:prefix) {
            if(!p->child.count(c)) return nullptr;
            p=p->child.at(c);
        }
        return p;
    }
public:
    void Trie(void){root=new TrieNode;}

    void insert(string word) {
        TrieNode* p=root;
        for(auto c:word) {
            if(!p->child.count(c))
                p->child[c]=new TrieNode;
            p=p->child[c];
        }
        p->leaf=true;
    }

    void remove(string word) {
        remove(root, word, 0, word.size());
    }

    bool remove(TrieNode *root, string key, int pivot, int len){
        if(!root) return false;

        if(pivot!=len) {
            if(remove(root->child[key[pivot]], key, pivot+1, len)) {
                char c=key[pivot];
                // last node marked, delete it.
                delete root->child[c];
                root->child.erase(c);
                // recursively climb up, and delete eligible nodes
                return (!root->leaf&&root->child.empty());
            }
        }else if(pivot==len&&root->leaf) {
            root->leaf=false; //unmark leaf
            if(root->child.empty()) return true;
            return false;
        }
        return false;
    }

    bool search(string word) {
        TrieNode* p=find(word);
        return p&&p->leaf;
    }

    bool startsWith(string prefix) {
        TrieNode* p=find(prefix);
        return p!=nullptr;
    }
};

#define ALPHABET_SIZE 26
#define SIZE(a) (int)(sizeof(a)/sizeof(a[0]))
#define DIST(c) ((int)c - (int)'a')
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
