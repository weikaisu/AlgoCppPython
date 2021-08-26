

data = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]

# finding the minimum value in a given list and 
# move it to a sorted list.
def select_sort(data) :
    for i in range(len(data)) :
        min_idx = i
        for j in range(i+1, len(data)) :
            if data[i] > data[j] :
                min_idx = j
        
        data[i], data[min_idx] = data[min_idx], data[i]

# finding the right place for a given element in a sorted list
def insert_sort(data) :
    for i in range(1,len(data)) :
        pivot = data[i]
        j = i-1
        while j>=0 and data[j]>pivot :
            print(j,i,data[j-1],data[j])
            data[j+1]=data[j]
            j-=1
        data[j+1] = pivot

# each pair of adjacent elements is compared and 
# the elements are swapped if they are not in order.
def bubble_sort(data) :
    swapped=True
    while swapped :
        swapped=False
        for i in range(len(data)-1) :
            if data[i] > data[i+1] :
                data[i],data[i+1] = data[i+1],data[i]
                swapped=True

# take the right most one as pivot,
# one-side greater than it, one-side smaller than it
def _divide(data, l_idx, r_idx) :
    pivot=data[r_idx]
    i=j=l_idx
    while j<=r_idx-1 :
        if data[j]<pivot :
            data[i],data[j]=data[j],data[i]
            i+=1
        j+=1
    data[i],data[r_idx]=data[r_idx],data[i]
    return i

def quick_sort_recursive(data, l_idx, r_idx) :
    if(l_idx<r_idx) :
        m_idx = _divide(data, l_idx, r_idx)
        print(l_idx,m_idx,r_idx)
        quick_sort_recursive(data, l_idx, m_idx-1)
        quick_sort_recursive(data, m_idx+1, r_idx)

def quick_sort_iterative(data) :
    stack = [len(data)-1,0]

    while len(stack) :
        l_idx=stack[-1]
        stack.pop()
        r_idx=stack[-1]
        stack.pop()
        m_idx=_divide(data,l_idx,r_idx)

        if(l_idx<m_idx-1) :
            stack.append(m_idx-1)
            stack.append(l_idx)
        
        if(r_idx>m_idx+1) :
            stack.append(r_idx)
            stack.append(m_idx+1)

def _merge(data, l_idx, m_idx, r_idx):
    print(l_idx, m_idx, r_idx)
    l_data = data[l_idx:m_idx+1]
    r_data = data[m_idx+1:r_idx+1]

    i, j, k = 0, 0, l_idx

    while i < len(l_data) and j < len(r_data):
        if l_data[i] < r_data[j]:
            data[k] = l_data[i]; i += 1
        else:
            data[k] = r_data[j]; j += 1
        k += 1
    while i < len(l_data):
        data[k] = l_data[i]; k += 1; i += 1
    while j < len(r_data):
        data[k] = r_data[j]; k += 1; j += 1

    print(data)

def merge_sort_iterative(data) :
    stride, l_idx, m_idx, r_idx, size = 1, 0, 0, 0, len(data)

    while stride<size :
        while l_idx<size :
            m_idx=min(l_idx+stride-1, size)
            r_idx=min(l_idx+(stride<<1)-1, size)
            _merge(data, l_idx, m_idx, r_idx)
            l_idx+=(stride<<1)
        l_idx=0
        stride<<=1

def merge_sort_recursive(data, l_idx, r_idx) :

    if l_idx>=r_idx : return
    
    m_idx=(l_idx+r_idx)>>1
    merge_sort_recursive(data, l_idx, m_idx)
    merge_sort_recursive(data, m_idx+1, r_idx)
    _merge(data, l_idx, m_idx, r_idx)

def _heapify(data, n, r) :
    # n elements, r is the root, if its child is greater than it, swap.
    root, l_child, r_child = r, 2*r+1, 2*r+2

    if l_child<n and data[l_child]>data[root] :
        root=l_child
    if r_child<n and data[r_child]>data[root] :
        root=r_child
    if root != r :
        data[root], data[r] = data[r], data[root]
        _heapify(data, n, root)

def heap_sort(data) :
    n = len(data)
    # // create a max heap, keep removing the 1st element, the max one
    i = (n>>1)-1
    while i>=0 : # creates a Max heap, begin from the last node's parent i=n/2-1.
        _heapify(data, n, i); i-=1
    
    i = n-1
    while i>=0 : # swaps first and last node
        data[0], data[i] = data[i], data[0]
        _heapify(data, i, 0); i-=1
    