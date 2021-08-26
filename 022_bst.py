
########## Easy ##########  ##########  ##########  ##########

##########  ##########  ##########  ##########  ##########
class lc035 : #E,
    def searchInsert(self, nums: List[int], target: int) -> int:

        l, r = 0, len(nums)
        while l<r :
            m = l+(r-l)//2
            if target > nums[m] :
                l = m + 1
            elif target < nums[m] :
                r = m
            else :
                return m
        
        return l

########## Medium ##########  ##########  ##########  ##########

##########  ##########  ##########  ##########  ##########
class lc033 : #M,
    def search(self, nums: List[int], target: int) -> int:

        l, r = 0, len(nums)-1
        while l<=r :
            m = l+(r-l)//2
            if nums[m]==target :
                return m
            elif nums[l] <= nums[m] :
                if nums[l]<=target<=nums[m] :
                    r=m-1
                else :
                    l=m+1
            else :
                if nums[m]<=target<=nums[r] :
                    l=m+1
                else :
                    r=m-1
        return -1

##########  ##########  ##########  ##########  ##########
# https://kkc.github.io/2019/03/28/learn-loop-invariant-from-binary-search/
# https://www.zhihu.com/question/36132386
class lc034 : #M,
    def searchRange(self, nums: List[int], target: int) -> List[int]:

        '''
        do binary search one time, when find it, extend the start and end
        index from m.
        '''
        l, r, key = 0, len(nums), target
        start=end=-1
        while l<r :
            m = l + (r-l)//2
            if nums[m]==key :
                start=end=m
                while start-1>=0 and nums[start-1]==key : start-=1
                while end+1<len(nums) and nums[end+1]==key : end+=1
                return [start,end]
            elif nums[m]<key :
                l = m + 1
            else :
                r = m
        return [start,end]

        '''
        use binary search to find the lower/upper bound
        '''
        # find lower bound
        l, r, start = 0, len(nums)-1, -1
        while l<=r :
            m = l + (r-l)//2
            if nums[m]==key :
                start=m
                # modify the right most index to find lower bound
                r = m - 1  # the only line of code difference
            elif nums[m]>key :
                r = m - 1
            else :
                l = m + 1

        # find upper bound
        l, r, end = 0, len(nums)-1, -1
        while l<=r :
            m = l + (r-l)//2
            if nums[m]==key :
                end=m
                # modify the left most index to find upper bound
                l = m + 1 # the only line of code difference
            elif nums[m]>key :
                r = m - 1
            else :
                l = m + 1

        return [start, end]

        '''
        find lower boud of key and key+1
        '''
        def _lower(nums, key) :
            l, r = 0, len(nums)
            while l < r:
                m = l + (r - l) // 2
                if nums[m] < key:
                    l = m + 1
                else:
                    r = m
            return l
        
        if len(nums) == 0: return [-1, -1]
        s, e, key = -1, -1, target
        idx = _lower(nums, key)
        if 0<=idx<=len(nums)-1 and nums[idx]==key :
            s=idx
        idx = _lower(nums, key+1)-1
        if 0<=idx<=len(nums)-1 and nums[idx]==key :
            e=idx

        return [s, e]




##########  ##########  ##########  ##########  ##########