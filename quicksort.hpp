#pragma once
#include<functional>
#include "util.hpp"

namespace naive{
    namespace lomuto {
        void quicksort(int arr[], int lo, int hi){
            if (hi - lo <= 0) return;
            int pivot = lo;//ChoosePivot(arr, lo, hi);
            swap(arr[pivot], arr[hi]);
            int partitionPoint = ::lomuto::partition(arr, lo, hi);
            quicksort(arr, lo, partitionPoint - 1);
            quicksort(arr, partitionPoint + 1, hi);
        }
        
        void quicksort_all(int arr[], int size){
            quicksort(arr, 0, size - 1);
        }
    }

    namespace hoare {
        void quicksort(int arr[], int lo, int hi){
            if (hi - lo <= 0) return;
            int partitionPoint = ::hoare::partition(arr, lo, hi, arr[lo]);
            quicksort(arr, lo, partitionPoint);
            quicksort(arr, partitionPoint + 1, hi);
        }
        
        void quicksort_all(int arr[], int size){
            quicksort(arr, 0, size - 1);
        }
    }
}


namespace naive_randomized{

    static uint32_t state;

    /* The state word must be initialized to non-zero */
    uint32_t xorshift32()
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }

    namespace lomuto {
        void quicksort(int arr[], int lo, int hi){
            if (hi - lo <= 0) return;
            int pivot = lo + xorshift32() % (hi - lo + 1);
            swap(arr[pivot], arr[hi]);
            int partitionPoint = ::lomuto::partition(arr, lo, hi);
            quicksort(arr, lo, partitionPoint - 1);
            quicksort(arr, partitionPoint + 1, hi);
        }
        
        void quicksort_all(int arr[], int size){
            naive_randomized::state = time(NULL);
            quicksort(arr, 0, size - 1);
        }
    }

    namespace hoare {
        void quicksort(int arr[], int lo, int hi){
            if (hi - lo <= 0) return;
            int pivot = lo + xorshift32() % (hi - lo + 1);
            int partitionPoint = ::hoare::partition(arr, lo, hi, arr[pivot]);
            quicksort(arr, lo, partitionPoint);
            quicksort(arr, partitionPoint + 1, hi);
        }
        
        void quicksort_all(int arr[], int size){
            naive_randomized::state = time(NULL);
            quicksort(arr, 0, size - 1);
        }
    }
}

namespace median_of_three{
    int medianOfThree(int arr[], int lo, int hi){
        int mid = (lo + hi) / 2;
        if(arr[lo] > arr[mid]) swap(arr[lo], arr[mid]);
        if(arr[lo] > arr[hi]) swap(arr[lo], arr[hi]);
        if(arr[hi] < arr[mid]) swap(arr[hi], arr[mid]);
        return mid;
    }
    namespace lomuto {

        void quicksort(int arr[], int lo, int hi){
            if (hi - lo < 2){
                if(arr[hi] < arr[lo])
                    swap(arr[hi], arr[lo]);
                return;
            }
            int pivot = medianOfThree(arr, lo, hi);
            swap(arr[pivot], arr[hi-1]);
            int partitionPoint = ::lomuto::partition(arr, lo + 1, hi - 1);
            quicksort(arr, lo, partitionPoint - 1);
            quicksort(arr, partitionPoint + 1, hi);
        }

        void quicksort_all(int arr[], int size){
            quicksort(arr, 0, size - 1);
        }

    }

    namespace hoare {

        void quicksort(int arr[], int lo, int hi){
            if (hi - lo < 2){
                if(arr[hi] < arr[lo])
                    swap(arr[hi], arr[lo]);
                return;
            }
            int pivot = medianOfThree(arr, lo, hi);
            int partitionPoint = ::hoare::partition(arr, lo + 1, hi - 1, arr[pivot]);
            quicksort(arr, lo, partitionPoint);
            quicksort(arr, partitionPoint + 1, hi);
        }

        void quicksort_all(int arr[], int size){
            quicksort(arr, 0, size - 1);
        }

    }
}


namespace median_of_three_randomized{

    static uint32_t state;

    uint32_t xorshift32()
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }

    int medianOfThree(int arr[], int lo, int hi){
        int mid =  lo + 1 + xorshift32() % (hi - lo - 1);
        if(arr[lo] > arr[mid]) swap(arr[lo], arr[mid]);
        if(arr[lo] > arr[hi]) swap(arr[lo], arr[hi]);
        if(arr[hi] < arr[mid]) swap(arr[hi], arr[mid]);
        return mid;
    }
    namespace lomuto {

        void quicksort(int arr[], int lo, int hi){
            if (hi - lo < 2){
                if(arr[hi] < arr[lo])
                    swap(arr[hi], arr[lo]);
                return;
            }
            int pivot = medianOfThree(arr, lo, hi);
            swap(arr[pivot], arr[hi-1]);
            int partitionPoint = ::lomuto::partition(arr, lo + 1, hi - 1);
            quicksort(arr, lo, partitionPoint - 1);
            quicksort(arr, partitionPoint + 1, hi);
        }

        void quicksort_all(int arr[], int size){
            median_of_three_randomized::state = time(NULL);
            quicksort(arr, 0, size - 1);
        }

    }

    namespace hoare {

        void quicksort(int arr[], int lo, int hi){
            if (hi - lo < 2){
                if(arr[hi] < arr[lo])
                    swap(arr[hi], arr[lo]);
                return;
            }
            int pivot = medianOfThree(arr, lo, hi);
            int partitionPoint = ::hoare::partition(arr, lo + 1, hi - 1, arr[pivot]);
            quicksort(arr, lo, partitionPoint);
            quicksort(arr, partitionPoint + 1, hi);
        }

        void quicksort_all(int arr[], int size){
            median_of_three_randomized::state = time(NULL);
            quicksort(arr, 0, size - 1);
        }

    }
}