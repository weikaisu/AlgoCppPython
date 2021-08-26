#include "leetcode.h"

//==================================MonotonicQueue+
class MonotonicQueue {
private:
    deque<int> dq;
public:
    //pop all elements smaller than val when push a val
    void push(int val) {
        while(dq.size()&&val>dq.back()) dq.pop_back();
        dq.push_back(val);
    }
    void pop() { dq.pop_front();}
    int max() { return dq.front();}
};
//Sliding Window Maximum
//Given an array nums, there is a sliding window of size k which is moving from the very
//left of the array to the very right. You can only see the k numbers in the window. Each
//time the sliding window moves right by one position.
class lc239 { //Hard
public:
    vector<int> SlidingWindowMaximum(vector<int>& nums, int k) {
        vector<int> res;

        //time(N)
        MonotonicQueue mq;
        for(int i=0;i<nums.size();i++) {
            mq.push(nums[i]);
            if(i-k+1>=0) {
                res.push_back(mq.max());
                if(mq.max()==nums[i-k+1]) mq.pop();
            }
        }
        return res;
        //==============================
        deque<int> dq;
        //time(N), use deque directly, keep value
        for(int i=0;i<nums.size();i++) {
            while(dq.size()&&nums[i]>dq.back())dq.pop_back();
            dq.push_back(nums[i]);
            if(i-k+1>=0) {
                res.push_back(dq.front());
                if(dq.front()==nums[i-k+1]) dq.pop_front();
            }
        }
        return res;
        //==============================
        //time(N), use deque directly, keep index
        for(int i=0;i<nums.size();i++) {
            while(dq.size()&&nums[i]>=nums[dq.back()]) dq.pop_back();
            dq.push_back(i);
            if(i-k+1>=0) res.push_back(nums[dq.front()]);
            if(i-k+1>=dq.front()) dq.pop_front();
        }
        return res;
    }
};
//==================================MonotonicQueue-

void moveHanoiTower(stack<int>& sour, stack<int>& buff, stack<int>& dest, int n)
{
//    1.n-1: sour -> buff
//    2.1  : sour -> dest
//    3.n-1: buff -> dest
    int x;
    switch(n) {
    case 0:
        return;
    case 1:
        dest.push(sour.top()); sour.pop();
        return;
    case 2:
        buff.push(x=sour.top()); sour.pop();
        dest.push(x=sour.top()); sour.pop();
        dest.push(x=buff.top()); buff.pop();
        return;
    }
    moveHanoiTower(sour, dest, buff, n-1);
    moveHanoiTower(sour, buff, dest, 1);
    moveHanoiTower(buff, sour, dest, n-1);
}

#if 0
int main(void)
{
    int n=7;
    stack<int> sour, buff, dest;

    for(auto i=n; i>0; i--) sour.push(i);
    moveHanoiTower(sour, buff, dest, n);
    while(!dest.empty()) {
        cout<<dest.top()<<' ';
        dest.pop();
    }
    cout<<endl<<"Hello 03";
    return 0;

}
#endif
