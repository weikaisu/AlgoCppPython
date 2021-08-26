def _com(nums, depth, m, curr, ans, start_pos) :
    if depth == m :
        ans.append(curr+[]); return;
    for i in range(start_pos,len(nums)) :
        curr.append(nums[i])
        _com(nums, depth+1, m, curr, ans, i+1)
        curr.pop()

# no append/pop
def _com(nums, depth, m, curr, ans, start_pos) :
    if depth == m :
        ans.append(curr); return;
    for i in range(start_pos,len(nums)) :
        _com(nums, depth+1, m, curr+[nums[i]], ans, i+1)

def combination(nums, m) :
    ans = []
    _com(nums, 0, m, [], ans, 0)
    pprint(ans)

class combination:
    def com(self, nums, m) :
        self.nums, self.ans, self.m = nums, [], m

        def _com(curr, start_pos, depth) :
            if depth == self.m :
                self.ans.append(curr)

            for i in range(start_pos, len(self.nums)) :
                _com(curr+[self.nums[i]], i+1, depth+1)

        _com([],0,0)
        return self.ans

########## Medium ##########  ##########  ##########  ##########

##########  ##########  ##########  ##########  ##########

class lc017 : #M
    def letterCombinations(self, digits) :

        if len(digits) == 0 : return []

        self.ans, self.curr, self.digits = [], [], digits
        self.phone = {1: "", 2: "abc", 3: "def", 4: "ghi", 5: "jkl", 6: "mno", 7: "pqrs", 8: "tuv", 9: "wxyz"}

        def _dfs(d) :
            if d==len(self.digits) : 
                self.ans.append("".join(self.curr))
                return
            
            for c in self.phone.get(int(self.digits[d]), []) :
                self.curr.append(c)
                _dfs(d+1)
                self.curr.pop()
        
        _dfs(0)
        return self.ans

##########  ##########  ##########  ##########  ##########

class lc022 : #M
    def generateParenthesis(self, n) : 
        self.ans, self.curr, self.n = [], [], n

        def _dfs(left) :
            if len(self.curr)==2*self.n :
                if left==0 : self.ans.append("".join(self.curr))
                return
            if left<self.n :
                self.curr.append('(')
                _dfs(left+1)
                self.curr.pop()
            if left>0 :
                self.curr.append(')')
                _dfs(left-1)
                self.curr.pop()
        
        _dfs(0)
        return self.ans

##########  ##########  ##########  ##########  ##########

class lc039 : #M
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        self.nums, self.ans = candidates, []

        def _com(curr, star_pos, tgt):
            if tgt == 0:
                self.ans.append(curr)

            for i in range(star_pos, len(self.nums)):
                if tgt - self.nums[i] >= 0:
                    # i : number can be chosen repeatedly
                    _com(curr + [self.nums[i]], i, tgt - self.nums[i])

        _com([], 0, target)

        return self.ans


##########  ##########  ##########  ##########  ##########

class lc040 : #M
        def combinationSum(self, candidates, target) :
        self.nums, self.ans = candidates, set() # init ans as a set (add/remove) for check duplicated items
        self.nums.sort()

        def _com(curr, star_pos, tgt):
            if tgt == 0:
                self.ans.add(tuple(curr)) # convert list to tuple then adding to set

            for i in range(star_pos, len(self.nums)):
                if tgt - self.nums[i] >= 0:
                    # i+1 : number can NOT be chosen repeatedly
                    _com(curr + [self.nums[i]], i+1, tgt - self.nums[i])

        _com([], 0, target)

        return [list(e) for e in self.ans] # convert tuple to list

##########  ##########  ##########  ##########  ##########