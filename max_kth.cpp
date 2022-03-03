#include<bits/stdc++.h>

namespace max_kth {

int kth_1(int arr[], int n, int k) {
    //----排序找第k大值--O(NlogN)--//
    std::sort(arr, arr + n);
    return arr[n - k];
}
inline static int minheap_k(int arr[], int n, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int> > minheap;
    int _s = k;
    //应该维护 第k小
    for(int i = 0; i < n; i++) {
        minheap.push(arr[i]);
        if(minheap.size() > _s)
            minheap.pop();
    }
    return minheap.top();
}
inline static int maxheap_k(int arr[], int n, int k) {
    std::priority_queue<int>maxheap;
    int _s = n - k + 1;
    // 大根堆: n - k + 1, 第 n - k + 1 小 即为 第 k 大 //
    for(int i = 0; i < n; i++) {
        maxheap.push(arr[i]);
        if(maxheap.size() > _s)
            maxheap.pop();
    }
    return maxheap.top();
}
int kth_2(int arr[], int n, int k) {
    //--用堆维护--O(NlogK)--//
    if(n - k + 1 > k)
        return minheap_k(arr, n, k);
    else
        return maxheap_k(arr, n, k);    
}

inline static int __partition(int arr[], int lo, int hi, int pivot) {
    std::swap(arr[pivot], arr[lo]);
    pivot = lo;
    while(lo <= hi) {
        while(hi >= lo && arr[hi] >= arr[pivot]) hi--;
        std::swap(arr[hi], arr[pivot]);
        pivot = hi; hi--;
        while(lo <= hi && arr[lo] <= arr[pivot]) lo++;
        std::swap(arr[lo], arr[pivot]);
        pivot = lo, lo++;
    }
    return pivot;
}
inline static int partition(int arr[], int lo, int hi, int n, int k) {
    
    int mi = lo + rand() % (hi - lo + 1);
    int pivot = __partition(arr, lo, hi, mi);
    if(pivot == n - k) return arr[pivot];
    // 第k大即为 第 n - k + 1小, idx = n - k
    if(pivot > (n - k)) //下标在后面
        return partition(arr, lo, pivot, n, k);
    else
        return partition(arr, pivot, hi, n, k);  
    return 114514; //防 no-return      
}

int kth_3(int arr[], int n, int k) {
    //快排的partition 平均复杂度O(N),最坏O(NlogN)//
    return partition(arr, 0, n - 1, n, k);
}
inline static void __sort(int arr[], int lo, int hi) {
    for(int i = lo + 1; i <= hi; i++) {
        int val = arr[i];
        int idx = i;
        while(idx > lo && arr[idx - 1] > val)
            arr[idx] = arr[idx - 1], idx--;
        arr[idx] = val;    
    }
}
inline static int get_pivot(int arr[], int lo, int hi) {
    int i;
    int cnt = 0;
    for(i = lo; i < hi - 3; i += 5) {
        __sort(arr, i, i + 4);
        std::swap(arr[lo + cnt++], arr[i + 2]);
    }
    if(i < hi) {
        __sort(arr, i, hi);
        std::swap(arr[lo + cnt++], arr[(i + hi) >> 1]);
    }
    if(cnt > 1)
        return get_pivot(arr, lo, lo + cnt - 1);
    return arr[lo];      
}
inline static int partition_BFPRT(int arr[], int lo, int hi, int n, int k) {
    if(hi < lo) return -114514;
    
    int mi = get_pivot(arr, lo, hi);
    int pivot = __partition(arr, lo, hi, mi);
    if(pivot == n - k) return arr[pivot];
    // 第k大即为 第 n - k + 1小, idx = n - k
    if(pivot > (n - k)) //下标在后面
        return partition(arr, lo, pivot, n, k);
    else
        return partition(arr, pivot, hi, n, k);    
}

int kth_4(int arr[], int n, int k) {
    //改进后快排的partition 最坏时间复杂度O(N)//
    return partition_BFPRT(arr, 0, n - 1, n, k);
}
void verify() {
    int arr[] = {1, 2, 3, 4 ,5, 6, 7};
    int n = 7;
    std::cout << kth_4(arr, n, 3) << "\n";
}



};
int main () {
    max_kth::verify();
}