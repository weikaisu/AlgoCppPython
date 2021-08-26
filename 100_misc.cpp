#include "leetcode.h"







int sciling(vector<int> nums, int key, int l, int r) {
    while(r-l>1) {
        int m = (l+r)/2; int num=nums[m];
        if(key<=nums[m])
            r = m;
        else
            l = m;
    }
    return nums[r]>=key ? nums[r] : -1;
}
int floor(vector<int> nums, int key, int l, int r) {
    while(r-l>1) {
        int m = (l+r)/2; int num=nums[m];
        if(key>=nums[m])
            l = m;
        else
            r = m;
    }
    return nums[l]<=key ? nums[l] : -1;
}
int sciling_(vector<int> nums, int key, int l, int r) {
    while(l<r) {
        int m = (l+r)/2; int num=nums[m];
        if(key>nums[m])
            l = m+1;
        else
            r = m;
    }
    //return nums[l]>=key ? nums[l] : -1;
    return nums[l];
}
int floor_(vector<int> nums, int key, int l, int r) {
    while(l<=r) {
        int m = (l+r)/2; int num=nums[m];
        if(key>=nums[m])
            l = m+1;
        else
            r = m-1;
    }
    //return nums[l]>=key ? nums[l] : -1;
    return nums[r];
}

int BurstBalloons(vector<int>& nums) {
    //c[i][j] : maxCoins(nums[i]~nums[j]), ans=c[1][n]
    //c[i][j] : c[i][k-1]+nums[i-1]*nums[k]*nums[j+1]+c[k+1][j], i<=k<=j
    int n=nums.size();
    // padding 1, right and left most
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    vector<vector<int>> c(n+2, vector<int>(n+2, 0));

    int i, j, k, len; //len: length between i and j, from 1 to n
    for(len=1;len<=n;len++)
        for(i=1;i<n-len+1;i++)
            for(j=i+len-1, k=i;k<=j;k++) {
                int x=c[i][j], y=c[i][k-1], z=c[k+1][j];
                c[i][j]=max(c[i][j], c[i][k-1]+nums[i-1]*nums[k]*nums[j+1]+c[k+1][j]);
                x=c[i][j], y=c[i][k-1], z=c[k+1][j];
            }
    return c[1][n];
}
int TargetSum(vector<int>& nums, int S, vector<int>& v) {
        //w[i][j] : # of ways to sum up to j using nums [0~i]
        //Let P denote a set of nums have + sign
        //Let N denote a set of nums have - sign
        //sum(P)-sum(N)=target, 出現在P的不會出現在N，所以這裡用-的
        //w[i][j]=w[i-1][j-nums[i]]+w[i-1][j+nms[i]], w[i][j]的值從這些pull過來
        //w[i+1][j+nums[i]]+=w[i][j]
        //w[i+1][j-nums[i]]+=w[i][j], 用w[i][j]去push(更新)那些值

        //以上會產生一個很大的sparse matrix來做為dp table, 以下做簡化
        //sum(P)-sum(N)=target
        //sum(P)-sum(N)+sum(P)+sum(N)=target+sum(P)+sum(N)
        //2sum(P)=target+sum(nums)
        // sum(P)=(target+sum(nums))/2
        // reduce to the 0/1 knapsack problem
        int n=nums.size();
        int tgt=abs(S), sum=accumulate(nums.begin(),nums.end(),0);
        int sumP=(tgt+sum)/2;
        if(sum<tgt||(sum+tgt)%2) return 0; //sum+tgt is a even num

        vector<int> w(tgt+1,0);
        w[0]=1;
        for(auto num:nums)
            for(int j=sumP;j>=num;j--) //從後往前算就可以不需要搬動上一state的資料
                w[j]+=w[j-num];
        return w[sumP];
}
#if 1
int main()
{
    //vector<int> nums{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> nums{1, 3, 4, 7, 9, 13, 18, 23};
    vector<int> w{10, 20, 30};
    vector<int> v{60, 100, 120};

    //0 1 2 3 4 5 6 7 8 9
    //sort(nums.begin(),nums.end());
    //0 1 2 3 4 5 6 7 8 9
    //sort(nums.begin(),nums.end(),[](int x,int y){return (x<y)?true:false;});
    //9 8 7 6 5 4 3 2 1 0
    //sort(nums.begin(),nums.end(),[](int x,int y){return (x>y)?true:false;});
    for(auto num:nums)
        cout<<num<<' ';

    //cout<<endl<<floor(nums, 7, 0, nums.size());
    //cout<<endl<<sciling_(nums, 8, 0, nums.size());
    //cout<<endl<<floor_(nums, 8, 0, nums.size());
    //BurstBalloons(nums);
    TargetSum(w,50,v);

    cout<<endl<<"Hello";
    return 0;
}
#endif
