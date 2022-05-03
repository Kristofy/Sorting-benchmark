#pragma once


inline void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

namespace lomuto {
    int partition(int arr[], int lo, int hi){
        int pivot = arr[hi];
        int i = lo;
    
        for (int j = lo; j < hi; j++)
            if (arr[j] < pivot)
                swap(arr[i++], arr[j]);
        
        swap(arr[i], arr[hi]);
        return i;
    }
}

namespace hoare {
    int partition(int arr[], int lo, int hi, int pivot)   
    {
        int i = lo-1, j = hi+1;
        while(true)
        {
            do i++; while(arr[i] < pivot);
            do j--; while(arr[j] > pivot);

            if(i >= j) return j;
            swap(arr[i], arr[j]);
        }
        return -1;
    }
}
