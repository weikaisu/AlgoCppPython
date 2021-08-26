#include "leetcode.h"

//Total Hamming Distance
//Find the total Hamming distance between all pairs of the given numbers.
class lc477 { //Medium
public:
    int TotalHammingDistance(vector<int>& nums) {
        int res=0, cnt=0;
        for(int i=0,mask=1 ;i<32 ; i++,mask<<=1) {
            for(auto num:nums)
                if(num&mask) cnt++;
            res+=cnt*(nums.size()-cnt); // total HD of this bit
            //            cnt : num of bit is 1
            //nums.size()-cnt : num of bit is 0
        }
    }
};

//Hamming Distance
//Given two integers x and y, calculate the Hamming distance.
class lc461 { // Easy
public:
    int HammingDistance(int x, int y) {
        //time(1), space(1)
        int dis=0; int z=x^y;// z represents the different bits between x and y
        while(z) {
            dis+=z&1;
            z>>=1;
        }
        return dis;
    }
};

//Binary Number with Alternating Bits
//Given a positive integer, check whether it has alternating bits: namely,
//if two adjacent bits will always have different values.
class lc693 { //Easy
public:
    bool BinaryNumberWithAlternatingBits(int n) {
        int curr_bit=n&1;
        while((n>>=1)) {
            int next_bit=n&1;
            if(curr_bit==next_bit) return false;
            curr_bit=next_bit;
        }
        return true;
    }
};

//Number Complement
//Given a positive integer, output its complement number.
//The complement strategy is to flip the bits of its binary representation.
class lc476 { //Easy
public:
    int NumberComplement(int num) {
        int mask=~0;
        while(num&mask) mask<<=1; //find how many not-leading-zero bits
        return ~num^mask;
    }
};

//Majority Element
//Given an array of size n, find the majority element. The majority element is
//the element that appears more than floor(n/2) times. (more than half)
class lc169 { //Easy
public:
    int MajorityElement(vector<int>& nums) {
        int n=nums.size();
        //method 1, Hash table, time(N) space(N)
        unordered_map<int,int> cnt;
        for(auto num:nums) if(++cnt[num]>n/2) return num;
        return -1;

        //method 2 Randomization, time(N) space(N)
        srand(time(nullptr));
        while(true) {
            int cnt=0, majority=nums[rand()%n];
            for(auto num:nums) if(num==majority&&++cnt>n/2) return num;
        }
        return-1;
    }
};
