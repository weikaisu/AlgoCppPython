

##########  ##########  ##########  ##########  ##########
class ListNode() :
    def __init__(self, val) :
        self.val = val
        self.nxt = None

def list_to_num(lst) :
    digit = 1
    num = 0
    while lst :
        num += lst.val*digit
        digit *= 10
        lst = lst.nxt
    print(num)

def num_to_list(num) :
    dummy=pivot=ListNode(-1)
    while num :
        pivot.nxt = ListNode(num%10)
        num //= 10
        pivot = pivot.nxt
    return dummy.nxt

def addNode(list, val) :
    # new node with data
    # new node point to what
    # what point to new node
    if list is None : return list
    dummy=tail=ListNode(-1)
    dummy.nxt=list
    while tail.nxt :
        tail=tail.nxt
    tail.nxt=ListNode(val)
    return dummy.nxt


def removeNode(list) :
    # find the node by node.nxt
    # modify the last node's next point

########## Easy ##########  ##########  ##########  ##########

class lc001 : #E, 2sum
    def n2 (self, nums, target) :
        for i, num_i in enumerate(nums) :
            for j, num_j in enumerate(nums[i:]) :
                if num_i+num_j == target :
                    return [i, j]
        return [-1, -1]
    
    def n (self, nums, target) :
        dic = {}
        for i, num in enumerate(nums) :
            if target-num in dic :
                return [dic[target-num], i]
            dic[num] = i
        return [-1, -1]


two_sum=lc001()
two_sum.n2([2, 7, 11, 15], 9)

##########  ##########  ##########  ##########  ##########

class lc013 : #E
    def n (self, s) :
        ans = 0
        values = {'M':1000, 'D':500, 'C':100, 'L':50, 'X':10, 'V':5, 'I':1}
        for i in range(0, len(s)-1) :
            c, c_nxt = s[i], s[i+1]
            if values[c] < values[c_nxt] :
                ans-=values[c]
            else :
                ans+=values[c]
        ans+=values[s[-1]]
        return ans


##########  ##########  ##########  ##########  ##########

class lc021 : #E
    def mergeTwoLists(self, lst1, lst2) :
        dummy=tail=ListNode(-1)
        while lst1 and lst2 :
            if lst1.val < lst2.val :
                tail.nxt=lst1
                lst1=lst1.nxt
            else :
                tail.nxt=lst2
                lst2=lst2.nxt
            tail=tail.nxt
        if lst1 :
            tail.nxt=lst1
        if lst2 :
            tail.nxt=lst2
        return dummy.nxt

##########  ##########  ##########  ##########  ##########

class lc026 : #E
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        if n<= 1 : return n
        
        idx, pre = 1, nums[0]

        for i in range(1, len(nums)) :
            if pre == nums[i] : n-=1
            else :
                nums[idx] = nums[i]
                idx+=1
            pre = nums[i]
        
        return n

##########  ##########  ##########  ##########  ##########

class lc027 : #E, Remove Element
    def removeElement(self, nums: List[int], val: int) -> int:
        idx = 0
        for i in range(len(nums)) :
            if nums[i] != val :
                nums[idx] = nums[i]
                idx+=1
        return idx

##########  ##########  ##########  ##########  ##########

class lc066 : #E, Plus One
    def plusOne(self, digits: List[int]) -> List[int]:
        carry = 1
        for i in reversed(range(len(digits))) :
            d = (digits[i]+carry)%10
            carry=1 if d<digits[i] else 0
            digits[i]=d
        if carry :
            return [1]+digits
        return digits

#########  ##########  ##########  ##########  ##########

class lc088 : #E, Merge Sorted Array
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        idx = m+n-1
        m, n = m-1, n-1
        
        while idx>=0 and m>=0 and n>=0 :
            if nums1[m] > nums2[n] :
                nums1[idx]=nums1[m]
                m-=1
            else :
                nums1[idx]=nums2[n]
                n-=1
            idx-=1
            
        while n>=0 :
            nums1[idx]=nums2[n]
            idx, n = idx-1, n-1

##########  ##########  ##########  ##########  ##########

class lc141 : #E
    def n(self, head) :
        fast=slow=head
        while fast and fast.nxt :
            fast = fast.nxt.nxt
            slow = slow.nxt
            if fast == slow :
                return True
        
        return False

##########  ##########  ##########  ##########  ##########

class lc561 : #E
    def n(self, lst) :
        total=0
        for i,x in enumerate(sorted(lst)) :
            if not i%2 :
                total += x
        return total

        return sum([c for i,c in enumerate(sorted(lst)) if not i%2])

##########  ##########  ##########  ##########  ##########

class lc566 : #E
    def rc(self, nums, r, c) :
        m=len(nums)
        n=len(num[0])
        if not m*n : return nums
        if r*c != m*n : return nums
        
        res = [[0]*c for _ in range(r)]
        for i in range(r*c) :
            res[i//c][i%c] = nums[i//n][i%n]
        
        return res


##########  ##########  ##########  ##########  ##########

class lc747 : #E
    def n(self, lst) :
        max1 = max2 = -1
        for i,x in enumerate(lst) :
            if x>max1 : 
                max1, max2 = x, max1
            elif x>max2 : 
                max2=x
        if max1 > 2*max2 : return True
        else : return False
        

########## Medium ##########  ##########  ##########  ##########

class lc002 : #M
    def n (self, lst1, lst2) :
        dummy=pivot=ListNode(-1)
        carry=0
        while lst1 or lst2 or carry :
            val = (lst1 and lst1.val or 0) + (lst2 and lst2.val or 0) + carry
            pivot.nxt = ListNode(val%10)
            carry = val//10
            lst1 = lst1 and lst1.nxt
            lst2 = lst2 and lst2.nxt
            pivot = pivot.nxt
        return dummy.nxt

lst_add=lc002()
list_to_num(lst_add.n(num_to_list(342),num_to_list(465)))

##########  ##########  ##########  ##########  ##########

class lc011 : #M
    def n (self, height) :
        l, r, ans = 0, len(height)-1, 0
        while l<r :
            ans = max(ans, (r-l)*min(height[l], height[r]))
            if height[l]<=height[r] : l+=1
            else : r-=1
        return ans

##########  ##########  ##########  ##########  ##########

class lc012 : #M
    def c (self, num) :
        ans = ""
        values  = {'M':1000, 'D':500, 'C':100, 'L':50, 'X':10, 'V':5, 'I':1}
        literals= ['M', 'D', 'C', 'L', 'X', 'V', 'I']
        for idx in [0,2,4] :
            quo = num//values[literals[idx]]
            rem = (num%values[literals[idx]])//values[literals[idx+2]]

            ans += quo*literals[idx]
            if rem==9 : ans += literals[idx + 2] + literals[idx]
            elif rem==4 : ans += literals[idx + 2] + literals[idx + 1]
            elif rem>=5 : ans += literals[idx + 1] + (rem - 5) * literals[idx + 2]
            else : ans += rem * literals[idx + 2]
            
            num %= values[literals[idx + 2]]
        return ans

##########  ##########  ##########  ##########  ##########

class lc015 : #M, 3sum
    def nlogn (self, nums) :
        ans = []
        nums.sort()
        for i in range(0,len(nums)) :
            if i>0 and nums[i]==nums[i-1] : # only unique triplets allowed
                continue
            two_sum, l_idx, r_idx = 0-nums[i], i+1, len(nums)-1
            while l_idx<r_idx :
                if nums[l_idx]+nums[r_idx] > two_sum :
                    r_idx-=1
                elif nums[l_idx]+nums[r_idx] < two_sum :
                    l_idx+=1
                else :
                    ans.append((nums[i], nums[l_idx], nums[r_idx]))
                    l_idx, r_idx = l_idx+1, r_idx-1
                    while l_idx<r_idx and nums[l_idx]==nums[l_idx-1] : l_idx+=1
                    while l_idx<r_idx and nums[r_idx]==nums[r_idx+1] : r_idx-=1
        return ans

##########  ##########  ##########  ##########  ##########

class lc016 : #M, 3sum-closest
    def nlogn(self, nums, target):
        ans, diff = 0, float("inf")
        nums.sort()
        for i in range(0,len(nums)) :
            l_idx, r_idx = i+1, len(nums)-1
            while l_idx<r_idx :
                three_sum=nums[i]+nums[l_idx]+nums[r_idx]
                dist = abs(three_sum-target)
                if dist < diff : 
                  diff, ans = dist, three_sum
                if three_sum > target :
                    r_idx-=1
                else :
                    l_idx+=1
        return ans

##########  ##########  ##########  ##########  ##########

class lc018 : #M, 4sum
    def fourSum(self, nums, target) :
        ans = []
        nums.sort()
        for i in range(0,len(nums)) :
            if i>0 and nums[i]==nums[i-1] :
                continue
            for j in range(i+1,len(nums)) :
                if j>0 and nums[j]==nums[j-1] :
                    continue
                
                two_sum, l_idx, r_idx = target-nums[i]-nums[j], j+1, len(nums)-1
                while l_idx<r_idx :
                    if nums[l_idx]+nums[r_idx]<two_sum :
                        l_idx+=1
                    elif nums[l_idx]+nums[r_idx]>two_sum :
                        r_idx-=1
                    else :
                        ans.append((nums[i],nums[j],nums[l_idx],nums[r_idx]))
                        l_idx,  r_idx = l_idx+1, r_idx-1
                        while l_idx<r_idx and nums[l_idx]==nums[l_idx-1] : l_idx+=1
                        while l_idx<r_idx and nums[r_idx]==nums[r_idx+1] : r_idx-=1
        return ans

##########  ##########  ##########  ##########  ##########

class lc019 : #M,
    def removeNthFromEnd(self, head, n) :
        slow=fast=dummy=ListNode(-1)
        dummy.nxt=head
        
        while n and fast :
            fast=fast.nxt
            n-=1
        
        if not fast : return dummy.nxt
        
        while slow.nxt and fast.nxt :
            slow=slow.nxt
            fast=fast.nxt
        
        slow.nxt=slow.nxt.nxt
        return dummy.nxt

##########  ##########  ##########  ##########  ##########

class lc024 : #M, lc025 #H
    def swapPairs(self, head: ListNode) -> ListNode:
        
        # https://www.geeksforgeeks.org/reverse-a-linked-list/
        # https://www.geeksforgeeks.org/reverse-a-list-in-groups-of-given-size/
        def reverseList(head, k):
            pre, cur, nxt, cnt = None, head, None, 0

            # ======================= #
            # check if has enough k node in this group
            # if not enough, don't do reverse
            while cur :
                cur = cur.nxt
                cnt += 1
            
            if cnt < k : return head
            else : cur, cnt = head, 0
            # ======================= #

            while cur and cnt<k :
                nxt = cur.nxt
                cur.nxt = pre
                pre, cur = cur, nxt
                cnt+=1

            if nxt:
                head.nxt = reverseList(nxt, k)

            return pre

        return reverseList(head, 2)

##########  ##########  ##########  ##########  ##########

class lc031 : #M,
    def nextPermutation(self, nums: List[int]) -> None:

##########  ##########  ##########  ##########  ##########

class lc036 : #M,
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        _row = [[0]*9 for _ in range(0,9)]
        _col = [[0]*9 for _ in range(0,9)]
        _box = [[0]*9 for _ in range(0,9)]
        
        for row_idx in range(0,9):
            for col_idx in range(0,9):
                if board[row_idx][col_idx] == '.' : 
                    continue
                val = int(board[row_idx][col_idx])-1
                box_idx = (row_idx//3)*3+(col_idx//3)
                if _row[row_idx][val] or _col[col_idx][val] or _box[box_idx][val] : 
                    return False
                _row[row_idx][val] = _col[col_idx][val] = _box[box_idx][val] = True
        return True

########## Hard ##########  ##########  ##########  ##########

class lc004 : #H
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

##########  ##########  ##########  ##########  ##########

class lc023 : #H
    def mergeKLists_heap(self, lists):
        import heapq
        heap = []
        dummy = tail = ListNode(-1)
        [heapq.heappush(heap, (n.val, i)) for i, n in enumerate(lists) if n]

        while heap:
            val, lists_idx = heapq.heappop(heap)
            tail.nxt = node = lists[lists_idx]
            tail = tail.nxt
            if node.nxt:
                lists[lists_idx] = node = node.nxt
                heapq.heappush(heap, (node.val, lists_idx))
        return dummy.nxt
    
    def mergeKLists_merge(self, lists):
        
        def mergeTwoLists(lst1, lst2) :
            dummy=tail=ListNode(-1)
            while lst1 and lst2 :
                if lst1.val < lst2.val :
                    tail.nxt=lst1
                    lst1=lst1.nxt
                else :
                    tail.nxt=lst2
                    lst2=lst2.nxt
                tail=tail.nxt
            if lst1 :
                tail.nxt=lst1
            if lst2 :
                tail.nxt=lst2
            return dummy.nxt
      
      dummy = lists[0]
      for i in range(1, len(lists)) :
            dummy = mergeTwoLists(dummy, lists[i])
      return dummy

##########  ##########  ##########  ##########  ##########

class lc037 : #H
    def solveSudoku(self, board: List[List[str]]) -> None:
        _row = [[0]*9 for _ in range(9)]
        _col = [[0]*9 for _ in range(9)]
        _box = [[0]*9 for _ in range(9)]

        for row_idx in range(len(board)) :
            for col_idx in range(len(board)) :
                if board[row_idx][col_idx] != '.' :
                    box_idx = (row_idx//3)*3 + col_idx//3
                    val = int(board[row_idx][col_idx]) - 1
                    _row[row_idx][val]=_col[col_idx][val]=_box[box_idx][val]=True

        self.board, self._row, self._col, self._box = board, _row, _col, _box

        def _backtrack(row_idx, col_idx) :
            board, _row, _col, _box = self.board, self._row, self._col, self._box

            if board[row_idx][col_idx] != '.' :
                if row_idx==col_idx==len(board)-1 : return True
                if col_idx + 1 < len(board):
                    if _backtrack(row_idx, col_idx+1) : return True
                elif row_idx+1 < len(board) :
                    if _backtrack(row_idx+1, 0) : return True
            else :
                box_idx = (row_idx // 3) * 3 + col_idx // 3
                for val in range(0,9) :
                    if _row[row_idx][val]==True or _col[col_idx][val]==True or _box[box_idx][val]==True :
                        continue

                    # make move
                    _row[row_idx][val] = _col[col_idx][val] = _box[box_idx][val] = True
                    board[row_idx][col_idx] = str(val+1)

                    # backtrack
                    if row_idx==col_idx==len(board)-1 : return True
                    if col_idx+1 < len(board) :
                        if _backtrack(row_idx, col_idx+1) : return True
                    elif row_idx+1 < len(board) :
                        if _backtrack(row_idx+1, 0) : return True

                    # unmake move
                    _row[row_idx][val] = _col[col_idx][val] = _box[box_idx][val] = False
                    board[row_idx][col_idx] = '.'

            return False

        _backtrack(0,0)

##########  ##########  ##########  ##########  ##########

class lc041 : #H
    def firstMissingPositive(self, nums: List[int]) -> int:
        i = 0
        while i<len(nums) :
            if 0<nums[i]<=len(nums) and nums[i]!=nums[nums[i]-1] :
                # !!! INCORRECT !!! 
                # nums[i], nums[nums[i] - 1] = nums[nums[i] - 1], nums[i]
                # nums[i] will be modified first therefore affect the value of nums[nums[i] - 1]
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1]
            else :
                i+=1
        
        for i in range(len(nums)) :
            if nums[i] != i+1 :
                return i+1
        
        return len(nums)+1


##########  ##########  ##########  ##########  ##########

class lc042 : #H, Trapping Rain Water
    def trap(self, height: List[int]) -> int:
        l_idx, r_idx, ans = 0, len(height)-1, 0
        l_max, r_max = float('-inf'), float('-inf')

        while l_idx<=r_idx :
            # 從左右兩邊開始比我當前高度低的才能積水
            if l_max<=r_max :
                ans += max(0,l_max-height[l_idx])
                l_max = max(l_max, height[l_idx])
                l_idx+=1
            else :
                ans += max(0,r_max-height[r_idx])
                r_max = max(r_max, height[r_idx])
                r_idx-=1
        return ans


##########  ##########  ##########  ##########  ##########