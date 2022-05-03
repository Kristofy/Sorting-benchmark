
inline void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

//hoare partition
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

int medianOfThree(int arr[], int lo, int hi){
    int mid =  lo + 1 + rand() % (hi - lo - 1);
    if(arr[lo] > arr[mid]) swap(arr[lo], arr[mid]);
    if(arr[lo] > arr[hi]) swap(arr[lo], arr[hi]);
    if(arr[hi] < arr[mid]) swap(arr[hi], arr[mid]);
    return mid;
}

void quicksort(int arr[], int lo, int hi){
    if (hi - lo < 2){
        if(arr[hi] < arr[lo])
            swap(arr[hi], arr[lo]);
        return;
    }
    int pivot = medianOfThree(arr, lo, hi);
    int partitionPoint = partition(arr, lo + 1, hi - 1, arr[pivot]);
    quicksort(arr, lo, partitionPoint);
    quicksort(arr, partitionPoint + 1, hi);
}

void quicksort_all(int arr[], int size){
    quicksort(arr, 0, size - 1);
}