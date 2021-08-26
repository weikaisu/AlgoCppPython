##########  ##########  ##########  ##########  ##########

class lc053 : #E, Maximum Subarray
    def maxSubArray(self, nums: List[int]) -> int:
        if not len(nums) : return 0
        
        sPre = sCurr = nums[0]
        
        for i in range(1, len(nums)) :
            sPre = max(sPre+nums[i], nums[i])
            sCurr = max(sCurr, sPre)
        return sCurr