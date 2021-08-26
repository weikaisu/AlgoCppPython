#include "leetcode.h"

//LFU Cache
//Design and implement a data structure for Least Frequently Used (LFU) cache.
class lc460 { //Hard
private:
    struct CacheNode {
        int key; int val; int freq;
        list<int>::const_iterator it; //pointer to the node in the list
    };
    unordered_map<int, CacheNode> map_key; //key->CacheNode
    unordered_map<int, list<int>> map_freq; //freq->key list (keys that have the same freq)
    int cap;
    int min_freq;
    void touch(CacheNode &node) {
        // step 1, update the frequency
        int old_freq=  node.freq;
        int new_freq=++node.freq;
        // step 2, remove the entry from freq list
        map_freq[old_freq].erase(node.it);
        if(map_freq[old_freq].empty()&&old_freq==min_freq) {
            map_freq.erase(old_freq);
            min_freq++;
        }
        // step 3, insert the key into the front of the new freq list
        map_freq[new_freq].push_front(node.key);
        // step 4, update the pointer in the CacheNode
        node.it=map_freq[new_freq].cbegin();
    }

public:
    LFUCache(int capacity) {cap=capacity; min_freq=0;}

    int get(int key) {
        auto it=map_key.find(key);
        if(it==map_key.cend()) return -1;
        touch(it->second);
        return it->second.val;
    }

    void put(int key, int value) {
        if(!cap) return;
        auto it=map_key.find(key);
        if(it!=map_key.cend()) { //key already exist, update the value
            it->second.val=value;
            touch(it->second);
            return;
        }
        if(map_key.size()==cap) { //cache full, remove the least freq/used entry
            // step 1, remove the node from min_freq list
            int node=map_freq[min_freq].back();
            map_freq[min_freq].pop_back();
            // step 2, remove the key from cach;
            map_key.erase(node);
        }
        min_freq=1; //new item has frequency 1
        map_freq[min_freq].push_front(key);
        map_key[key]={key,value,min_freq,map_freq[min_freq].cbegin()}; // create a new entry in cache
    }
};

//LRU Cache
//Design and implement a data structure for Least Recently Used (LRU) cache.
class lc146 { //Hard
private:
    //use a hash table to map the key and the pointer (point to the value node in the list)
    unordered_map<int, list<pair<int,int>>::iterator> map; //<val, idx in the list>
    list<pair<int,int>> cache; //use list to keep most recently used in the front
    int cap; //cache size;
public:
    LRUCache(int capacity) {cap=capacity;}

    int get(int key) {
        auto it=map.find(key);
        if(it==map.cend()) return -1; //the key does not exist
        cache.splice(cache.begin(),cache,it->second); // Move this key to the front of the list
        return it->second->second;
    }
    void put(int key, int val) {
        if(!cap) return ;
        auto it=map.find(key);
        if(it!=map.cend()) { //key already exist, update the value
            it->second->second=val;
            cache.splice(cache.begin(),cache,it->second); // Move this key to the front of the list
        }
        if(cache.size()==cap) { //cache full, remove the oldest entry
            auto node=cache.back();
            map.erase(node.first);
            cache.pop_back();
        }
        cache.emplace_front(key, val);
        map[key]=cache.begin();
    }
};

//Insert Delete GetRandom O(1) - Duplicates allowed
//Design a data structure that supports all following operations in average O(1) time.
//insert(val): Inserts an item val to the collection.
//remove(val): Removes an item val from the collection if present.
//getRandom: Returns a random element from current collection of elements. The probability
//of each element being returned is linearly related to the number of same value the collection contains.
class lc381 { //Hard
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {

    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {

    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {

    }

    /** Get a random element from the collection. */
    int getRandom() {

    }
};

//Insert Delete GetRandom O(1)
//Design a data structure that supports all following operations in average O(1) time.
//insert(val): Inserts an item val to the set if not already present.
//remove(val): Removes an item val from the set if present.
//getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
class lc380 { //Medium
private:
    unordered_map<int,int> val_table; //<val, idx in the vector>
    vector<int> val_vector; //for random access
public:
    InsertDeleteGetRandom() {}
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(val_table.count(val)) return false;
        val_table[val]=val_vector.size();
        val_vector.push_back(val);
        return true;
    }
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(!val_table.count(val)) return false;
        swap(val_vector.back(), val_vector[val_table[val]]);
        val_table[val_vector.back()]=val_table[val];
        val_table.erase(val);
        val_vector.pop_back();
        return true;
    }
    /** Get a random element from the set. */
    int getRandom() {
        return val_vector[rand()%val_vector.size()];
    }
};

//=============================================================================Heap+
//Find Median from Data Stream
//Design a data structure that supports the following two operations:
//void addNum(int num) - Add a integer number from the data stream to the data structure.
//double findMedian() - Return the median of all elements so far.
class lc295 { //Hard
    // priority_queue, min/max-heap
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {

    }

    double findMedian() {

    }
};

//Top K Frequent Words
//Given a non-empty list of words, return the k most frequent elements.
class lc692 { //Medium
private:
    unordered_map<string,int> cnts;
    typedef pair<string,int> node;
    struct cmp {
        bool operator()(node &a, node &b){ if (a.second!=b.second) return a.second>b.second; else return a.first<b.first;}
    };
    priority_queue<node, vector<node>, cmp> min_heap; //typedef pair<string,int> node;
public:
    vector<string> TopKFrequentWords(vector<string>& words, int k) {
        for(auto word:words)
            ++cnts[word];
        // always keep the most freq k words to save space complicity
        // use min heap to quickly pop the least freq word
        for(auto cnt:cnts) {
            min_heap.push(cnt);
            if(min_heap.size()>k) min_heap.pop();
        }
        vector<string> res;
        while(min_heap.size()) {
            res.push_back(min_heap.top().first); min_heap.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};

//=============================================================================Heap-

#define MAX_TABLE_SIZE 128
class TrivialHash
{
private:
    bool table[MAX_TABLE_SIZE+1][2] = {};
public:
    TrivialHash(void) {
    }
    bool search(int x) {
        if(x>=0) {
            if(table[x][0]) return true;
            else return false;
        } else {
            if(table[int(abs(x))][1]) return true;
            else return false;
        }
    }

    void insert(int x) {
        if(x>=0) {
            table[x][0] = true;
        } else {
            table[int(abs(x))][1] = true;
        }
    }
};

#if 0
int main(void)
{
    TrivialHash *hash;

    hash = new TrivialHash;
    hash->insert(5);
    hash->insert(-5);
    if(!hash->search(5)) cout<<"Not exists"<<endl;
    if(!hash->search(-5)) cout<<"Not exists"<<endl;
    if(!hash->search(50))  cout<<"50 Not exists"<<endl;
    delete hash;

    cout<<endl<<"Hello Hash";
    return 0;
}
#endif
