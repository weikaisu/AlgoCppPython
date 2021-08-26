

########## Easy ##########  ##########  ##########  ##########

class lc029 : #M
    def divide(self, dividend: int, divisor: int) -> int:
        max_val, min_val = 0x7fffffff, -(0x7fffffff+1)

        if not divisor :
            return max_val
        
        sign = (dividend < 0 and divisor > 0) or (dividend > 0 and divisor < 0)
        
        quo, dend, dsor = 0, abs(dividend), abs(divisor)
        subquo, subsum = 1, dsor
        while dend >= dsor :
            while (subsum<<1) <= dend :
                subquo<<=1
                subsum<<=1
            quo += subquo ; subquo = 1
            dend -= subsum ; subsum = dsor
        if sign :
            quo=-quo
        return min(max(quo, min_val), max_val)


##########  ##########  ##########  ##########  ##########

########## Medium ##########  ##########  ##########  ##########