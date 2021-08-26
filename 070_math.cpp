#include "leetcode.h"

//Reach a Number
class lc754 { //Medium
public:
    int ReachANumber(int target) {
        int sum=0, k=0, d=0;
        //sum=1+2+3+...+k=target+d
        target=abs(target); // target could be negative
        while(sum<target) sum+=(k++);
        d=sum-target;
        if(d%2) return k+1+(k%2); //d is odd
        else return k;           //d is even
    }
};

//Ugly Number II
class lc264 { //Medium
public:
    int UglyNumberII(int n) {
        vector<int> nums;
        int i2=0, i3=0, i5=0;
        int n2=0, n3=0, n5=0, next;

        nums.push_back(1);
        while(nums.size()<n) {
            n2=nums[i2]*2;
            n3=nums[i3]*3;
            n5=nums[i5]*5;
            next=min(n2, min(n3, n5));
            if(next==n2) i2++;
            if(next==n3) i3++;
            if(next==n5) i5++;
            nums.push_back(next);
        }
        return nums[n-1];
    }
};

//Ugly Number
class lc263 { //Easy
public:
    bool UglyNumber(int num) {
        vector<int> factors{2,3,5};
        for(auto factor:factors)
            while(num&&!(num%factor)) num/=factor;
        return num==1;
    }
};

//Self Dividing Numbers
class lc728 { //Easy
public:
    vector<int> SelfDividingNumbers(int left, int right) {
        vector<int> res;
        for(int num=left; num<=right; num++) {
            int tmp_num=num;
            bool valid=true;
            while(tmp_num && valid) {
                int divisor=num%10;
                if(!divisor||num%divisor) valid=false;
                tmp_num/=10;
            }
            if(valid) res.push_back(num);
        }
        return res;
    }
};

//Sum of Square Numbers
//Given a non-negative integer c, your task is to decide whether
//there're two integers a and b such that a^2 + b^2 = c.
class lc633 { //Easy
public:
    bool SumOfSquareNumbers(int c) {
        // time(sqrt(c))
        int a,b;
        for(a=0; a<=sqrt(c); a++) {
            b=round(sqrt(c-a*a)); // need to do round, since sqrt(5-1) could be 1.999999
            if(a*a+b*b==c) return true;
        }
        return false;
    }
};

//Maximum Product of Three Numbers
//Given an integer array, find three numbers whose product
//is maximum and output the maximum product.
class lc628 { //Easy
public:
    int MaximumProductOfThreeNumbers(vector<int>& nums) {
        //須考慮負數，兩個大負數相乘結果是大正數
#if 1
        //time(N)
        int max1, max2, max3, min1, min2;
        max1=max2=max3=INT_MIN;
        min1=min2=INT_MAX;
        for(const int num:nums) {
            if(num>max1) {
                max3=max2;max2=max1;max1=num;
            }else if(num>max2) {
                max3=max2;max2=num;
            }else if(num>max3) {
                max3=num;
            }
            if(num<min1) {
                min2=min1;min1=num;
            }else if(num<min2) {
                min2=num;
            }
        }
        return max(max1*max2*max3, max1*min1*min2);
#else
        //time(NlogN)
        int n=nums.size();
        sort(nums.begin(),nums.end(),greater<int>());
        return max(nums[0]*num[1]*num[2], num[0]*num[n-1]*num[n-2]);
#endif // 1
    }
};

//Missing Number
//Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
//find the one that is missing from the array.
class lc268 { //Easy
public:
    int MissingNumber(vector<int>& nums) {
        //time(N), space(1), method 1: Sum
        int n=nums.size();
        return (0+n)*(n+1)/2 - accumulate(nums.begin(),nums.end(),0);

        //method 2: XOR, a^b^b=a
        int res=0;
        for(auto i=1; i<=n; i++) res=res^i^nums[i-1]; // since x=0, i starts from 1
        return res;
    }
};

//Count Primes
//Count the number of prime numbers less than a non-negative number, n
class lc204 { //Easy
public:
    int CountPrimes(int n) {
        //time(N^1.5)
        //if n is not a prime, n=axb, a<=b. => a<=sqrt(n)
        //===========
        //time(NloglogN)~(N), space(N)
        if(n<3) return 0;
        vector<char> num(n,1); num[0]=num[1]=0;
        for(auto i=2; i<=sqrt(n); i++) {
            if(!num[i]) continue;
            for(auto j=i*i; j<n; j+=i) num[j]=0;
        }
        return accumulate(num.begin(), num.end(), 0);
    }
};

//================================== Geometry+
//Employee Free Time
class lc759 { //Hard

public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
    }
};

//Falling Squares
class lc699 { //Hard
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {

    }
};

//Max Points on a Line
class lc149 { //Hard
public:
    int maxPoints(vector<Point>& points) {

    }
};

//Insert Interval
class lc057 { //Hard
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {

    }
};

//Merge Intervals
class lc056 { //Medium
public:
    vector<Interval> merge(vector<Interval>& intervals) {

    }
};
//================================== Geometry-
