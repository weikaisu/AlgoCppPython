#include "leetcode.h"

int  data[]={9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

void _01_selectSort(vector<int>&data)
{
    for(int i=0;i<data.size();i++)
        for(int j=i+1;j<data.size();j++)
            if(data[i]>data[j])
                swap(data[i], data[j]);
}
void _02_insertSort(vector<int>&data)
{
    int i, j, pivot;
    for(i=1; i<data.size(); i++) {
        pivot=data[i];
        for(j=i; j&&pivot<data[j-1]; j--)
            data[j]=data[j-1];
        data[j]=pivot;
    }
}
void _03_bubbleSort(vector<int>&data)
{
    bool swapped=true;

    while(swapped) {
        swapped=false;
        for(int i=0;i<data.size();i++)
            if(data[i]>data[i+1])
                { swap(data[i], data[i+1]); swapped=true; }
    }
}
int _04_divide(vector<int>&data, int l_idx, int r_idx)
{   // take the right most one as pivot,
    // one-side greater than it, one-side smaller than it
    int pivot=data[r_idx], i, j;

    for(i=j=l_idx;j<=r_idx-1;j++)
        if(data[j]<pivot)
            swap(data[i++], data[j]);
    swap(data[i], data[r_idx]);
    return i;
}
void _04_quickSort_iterative(vector<int>&data)
{
    stack<int> unSorted;
    int l_idx, m_idx, r_idx;

    unSorted.push(0);
    unSorted.push(data.size()-1);
    while(unSorted.size()) {
        r_idx=unSorted.top(); unSorted.pop();
        l_idx=unSorted.top(); unSorted.pop();
        m_idx=_04_divide(data, l_idx, r_idx);

        if(l_idx<m_idx-1) {
            unSorted.push(l_idx);
            unSorted.push(m_idx-1);
        }
        if (r_idx>m_idx+1) {
            unSorted.push(m_idx+1);
            unSorted.push(r_idx);
        }
    }
}
void _04_quickSort_recursive(vector<int>&data, int l_idx, int r_idx)
{
    if(l_idx<r_idx) {
        int m_idx=_04_divide(data, l_idx, r_idx);
        _04_quickSort_recursive(data, l_idx, m_idx-1);
        _04_quickSort_recursive(data, m_idx+1, r_idx);
    }
}
void _05_merge(vector<int>&data, int l_idx, int m_idx, int r_idx)
{
    vector<int> l_data, r_data;
    int i=0, j=0, k=l_idx;

    l_data.assign(data.begin()+l_idx, data.begin()+m_idx+1);
    r_data.assign(data.begin()+m_idx+1, data.begin()+r_idx+1);
    while(i<l_data.size()&&j<r_data.size())
        l_data[i]<=r_data[j] ? data[k++]=l_data[i++] : data[k++]=r_data[j++];
    while(i<l_data.size()) {data[k++]=l_data[i++];}
    while(j<r_data.size()) {data[k++]=r_data[j++];}
}
void _05_mergeSort_iterative(vector<int>& data)
{   // bottom up, no need to use another stack.
    int stride, l_idx, m_idx, r_idx;
    for(stride=1;stride<data.size()-1;stride<<=1) {
        for(l_idx=0;l_idx<data.size()-1;l_idx+=stride<<1) {
            m_idx = min(int(l_idx+stride-1), int(data.size()));
            r_idx = min(int(l_idx+(stride<<1)-1), int(data.size()));
            _05_merge(data, l_idx, m_idx, r_idx);
        }
    }
}
void _05_mergeSort_recursive(vector<int>&data, int l_idx, int r_idx)
{
    int m_idx=(l_idx+r_idx)>>1;
    if(l_idx<r_idx) {
        _05_mergeSort_recursive(data, l_idx, m_idx);
        _05_mergeSort_recursive(data, m_idx+1, r_idx);
        _05_merge(data, l_idx, m_idx, r_idx);
    }
}
void _06_heapify(vector<int>&data, int n, int i)
{   // n elements, i is the root, if its child is greater than it, swap.
    int root = i;
    int l_child = 2*i+1;
    int r_child = 2*i+2;

    if( l_child<n && data[l_child]>data[root])
        root=l_child;
    if( r_child<n && data[r_child]>data[root])
        root=r_child;
    if( root != i ) {
        swap(data[root], data[i]);
        _06_heapify(data, n, root);
    }
}
void _06_heapSort(vector<int>&data)
{   // create a max heap, keep removing the 1st element, the max one
    int i, n = data.size();
    for(i=n/2-1;i>=0;i--) //creates a Max heap, begin from the last node's parent i=n/2-1.
        _06_heapify(data, n, i);
    for(i=n-1;i>=0;i--) { // swaps first and last node
        swap(data[0], data[i]);
        _06_heapify(data, i, 0);
    }
}
#if 0
int main(void)
{
    vector<int> v;

    v.assign(data, data+(sizeof(data)/4));
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<' ';
    cout<<endl;

    //_01_selectSort(v);
    //_02_insertSort(v);
    //_03_bubbleSort(v);
    //_04_quickSort_recursive(v, 0, v.size()-1);
    //_04_quickSort_iterative(v);
    //_05_mergeSort_recursive(v, 0, v.size()-1);
    //_05_mergeSort_iterative(v);
    _06_heapSort(v);

    for(int i=0;i<v.size();i++)
        cout<<v[i]<<' ';
    cout<<endl;

    cout<<endl<<"Hello Sort";
    return 0;
}
#endif
