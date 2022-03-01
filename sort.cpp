#include<bits/stdc++.h>

const int MAX_V = 1110;
int* arr; //数组
int n; //长度
template<typename F>
void swap(F& f1, F& f2) {
    F tmp = f1;
    f1 = f2;
    f2 = tmp;
}
namespace sort {
void init(int*&arr, int len) {

    srand(time(NULL));

    //if(arr) delete [] arr;
    arr = new int[len];
    for (int i = 0; i < len; i++)
        
        arr[i] = ( rand() % MAX_V );
    n = len;
}

void print(int arr[], int n) {
    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    puts("");
}

void shuffle() {
    for(int i = n - 1; ~i; i--) {
        swap(arr[i], arr[n % rand()]);
    }
}
//----排序算法----

void bubble_sort(int arr[], int n) {
    /*
        冒泡排序 每次 -比较交换- 两个相邻元素,交换
    */
    for(int i = n - 1; i; i--) {
        for(int j = 0; j < i; j++) {
            if(arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
}

void select_sort(int arr[], int n) {
    /*
        选择排序 每次找到序列中最大值，放到末尾
    */

    for(int i = n - 1; i; i--) {
        int maxid = i;

        for(int j = 0; j < i; j++) {
            if(arr[maxid] < arr[j])
                maxid = j;
        }
        if(maxid != i)
            std::swap(arr[maxid], arr[i]);
    }
}
void insert_sort(int arr[], int n) {
   /*
    插入排序: 向一段单调的序列中插入新值
   */
     for(int i = 1; i < n; i++) {
        int tmp = arr[i];
        for(int j = i; ~j; j--) {
            if(j > 0 && arr[j - 1] > tmp)
                arr[j] = arr[j - 1];
            else {
                arr[j] = tmp;
                break;
            }
        }

    }
}
/*----------O(NlogN)-------------*/
static void __mergesort(int arr[], int tmp[],int lo, int hi) {
    if(lo >= hi)
        return;
    int mi = (lo + hi) >> 1;    
    __mergesort(arr, tmp, lo , mi);
    __mergesort(arr, tmp, mi + 1, hi);

    memcpy(tmp + lo, arr + lo, sizeof(int) * (mi - lo + 1));
    int i = lo, j = mi + 1, k = lo;
    while(i <= mi && j <= hi) {
        if(tmp[i] < arr[j])
            arr[k++] = tmp[i++];
        else 
            arr[k++] = arr[j++];    
    }
    while(i <= mi)
        arr[k++] = tmp[i++];
    while(j <= hi)
        arr[k++] = arr[j++];

    
}
void merge_sort(int arr[], int n) {
    // 归并排序 //
    int* tmp = new int[n];
    __mergesort(arr, tmp, 0, n - 1);
    delete [] tmp;
}
inline static int partition(int arr[], int lo, int hi, int pivot) {
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
inline static void __quicksort(int arr[], int lo, int hi) {
    // 被调用 //
    if(lo >= hi) return;
    int mi = lo + rand() % (hi - lo + 1);
    int pivot = partition(arr, lo, hi, mi);
    __quicksort(arr, lo, pivot);
    __quicksort(arr, pivot + 1, hi);

}
void quick_sort(int arr[], int n) {
    // 快速排序 //
    __quicksort(arr, 0, n - 1);
}


};


int main () {
   
}