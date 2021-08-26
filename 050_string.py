

########## Easy ##########  ##########  ##########  ##########

class lc007 : #E
    def reverse(self, val) :
        sign = val<0 and -1 or 1
        ans, val = 0, abs(val)
        while val :
            ans = ans*10 + val%10
            val//=10
        return sign*ans if ans<=0x7fffffff else 0

##########  ##########  ##########  ##########  ##########

class lc009 : #E
    def isPalindrome(self, val) :
        forward, backward = val, 0
        while val > 0 :
            backward = backward*10 + val%10
            val//=10
        return forward == backward

##########  ##########  ##########  ##########  ##########

class lc014 : #E
    def longestCommonPrefix(self, strs) :
        if len(strs) == 0 : return ""

        line_idx, char_idx, end_idx = 0, 0, 0
        while line_idx<len(strs) and char_idx<len(strs[char_idx]) :
            if line_idx==0 : char=strs[line_idx][char_idx]
            elif char != strs[line_idx][char_idx] : break
            
            if line_idx == len(strs)-1 :
                line_idx=0
                char_idx+=1
                end_idx+=1
            else :
                line_idx+=1
        return strs[line_ix][:end_idx]

##########  ##########  ##########  ##########  ##########

class lc020 : #E
    def isValid(self, strs) :
        stack = []
        table = ['()', '[]', '{}']

        for i in range(0,len(strs)) :
            stack.append(strs[i])
            if len(stack)>=2 and stack[-2]+stack[-1] in table :
                stack.pop()
                stack.pop()
        
        return len(stack)==0

##########  ##########  ##########  ##########  ##########

class lc028 : #E
    def strStr(self, haystack: str, needle: str) -> int:
        h_len, n_len = len(haystack), len(needle)

        if h_len == n_len:
            if haystack == needle:
                return 0
            else:
                return -1

        for i in range(h_len-n_len+1) :
            if haystack[i:i+n_len] == needle :
                return i
        
        return -1

##########  ##########  ##########  ##########  ##########

class lc038 : #E
    def countAndSay(self, n: int) -> str:
        # recursive way
        def _recursive(n) :
            if n < 1: return ''
            if n == 1: return '1'

            seq = _recursive(n - 1) + '*'
            ret, cnt = '', 1
            for i in range(len(seq)-1):
                if seq[i] == seq[i + 1]:
                    cnt += 1
                else:
                    ret += (str(cnt) + seq[i])
                    cnt = 1
            return ret

        return _recursive(n)

        # interactive
        def _interactive(n):
            res, n = '1', n - 1
            while n > 0:
                res, res_tmp, cnt = (res+'*'), '', 1
                for i in range(len(res) - 1):
                    if res[i] == res[i + 1]:
                        cnt += 1
                    else:
                        res_tmp += (str(cnt) + res[i])
                        cnt = 1
                res, n = res_tmp, n - 1
            return res

        return _interactive(n)

##########  ##########  ##########  ##########  ##########

class lc058 : #E, Length of Last Word
    def lengthOfLastWord(self, s: str) -> int:
        ########## solution 1
        s = s.split()
        if len(s) > 0:
          return len(s[-1])
        return 0

        ########## solution 2
        ans, last_char = 0, len(s)-1

        # skip the space char after last word
        while last_char >= 0:
            if s[last_char] == ' ':
                last_char-=1
            else :
                break

        while last_char >= 0:
            if s[last_char] != ' ':
                ans += 1
                last_char-=1
            else:
                break
        return ans

##########  ##########  ##########  ##########  ##########

class lc067 : #E, Add Binary
    def addBinary(self, a: str, b: str) -> str:
        ans = ''
        a_idx, b_idx, carry = len(a)-1, len(b)-1, 0

        while a_idx>=0 or b_idx>=0 or carry==1 :
            carry += int(a[a_idx]) if a_idx>=0 else 0
            carry += int(b[b_idx]) if b_idx>=0 else 0
            ans = str((carry%2)) + ans
            a_idx, b_idx, carry = a_idx-1, b_idx-1, carry//2
        return ans

##########  ##########  ##########  ##########  ##########

class lc125 : #E, Valid Palindrome
    def isPalindrome(self, s: str) -> bool:
        l_idx, r_idx = 0, len(s) - 1
        while l_idx < r_idx:
            while not s[l_idx].isalnum() and l_idx < r_idx : l_idx+=1
            while not s[r_idx].isalnum() and l_idx < r_idx : r_idx-=1
            if (s[l_idx].lower() != s[r_idx].lower()) :
                return False
            l_idx, r_idx = l_idx + 1, r_idx - 1
        return True

##########  ##########  ##########  ##########  ##########

########## Medium ##########  ##########  ##########  ##########

import collections
class lc003 : #M
    def lenOfLongestSubstring_1(self, s):
        # use a dit to record whether a char exist in the analyzing substring
        d = collections.defaultdict(int)
        l = ans = 0
        for i, c in enumerate(s): # check every char in the input string
            # if new char exists in analyzing substring, find how many prefix chars need to remove
            # l>0 : analyzing substring still exists len
            # d[c]>0 : still not found the position of the last repeated char
            while l > 0 and d[c] > 0:
                d[s[i - l]] -= 1 # remove the prefix char
                l -= 1 # reduce the len of the analyzing substring
            d[c] += 1
            l += 1
            ans = max(ans, l)
        return ans

    def lenOfLongestSubstring_2(self, s):
        # use a dic to record the position of each char in the input string
        d, start, end, ans = {}, 0, 0, 0
        for i, c in enumerate(s):
            if c in d:
                # move the start next to the 1st repeated char
                start = max(start, d[c] + 1)
            d[c] = i # record the new position of the char
            ans = max(ans, i - start + 1)
        return ans

substring=lc003()
print(substring.lenOfLongestSubstring_2('abcabcbcdefghib'))

##########  ##########  ##########  ##########  ##########

class lc005 : #M palindrome

##########  ##########  ##########  ##########  ##########

class lc006 : #M zigzag

##########  ##########  ##########  ##########  ##########

class lc008 : #M
    def _atoi(self, str) :
        str = str.strip()
        if not str :
            return 0
        
        sign=1
        if str[0] in ['+','-'] :
            if str[0] is '-' :
                sign=-1
            str = str[1:]
        
        ans=0
        for c in str :
            if c.isdigit() :
                ans = ans*10 + int(c)
            else :
                ans = 0; break
        
        ans*=sign
        if ans > 2147483647 : return 2147483647
        if ans < -2147483647 : return -2147483647
        return ans

##########  ##########  ##########  ##########  ##########

class lc043 : #M, Multiply Strings
    def multiply(self, num1: str, num2: str) -> str:
        val1, val2 = 0, 0
        for c in num1 :
            val1 = val1*10 + (ord(c)-ord('0'))
        for c in num2 :
            val2 = val2*10 + (ord(c)-ord('0'))
        return str(val1*val2)

##########  ##########  ##########  ##########  ##########

########## Hard ##########  ##########  ##########  ##########

class lc010 : #H
    def isMatch(self, s: str, p: str) -> bool:

##########  ##########  ##########  ##########  ##########

class lc030 : #H
    def findSubstring(self, s: str, words: List[str]) -> List[int]:

##########  ##########  ##########  ##########  ##########

class lc032 : #H
    def longestValidParentheses(self, s: str) -> int:

##########  ##########  ##########  ##########  ##########