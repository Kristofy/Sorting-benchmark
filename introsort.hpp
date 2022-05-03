#pragma once
#include <cmath>
#include "insertionsort.hpp"
#include "heapsort.hpp"
#include "util.hpp"

int medianOfThree(int arr[], int lo, int hi){
    int mid = (lo + hi) / 2;
    if(arr[lo] > arr[mid]) swap(arr[lo], arr[mid]);
    if(arr[lo] > arr[hi]) swap(arr[lo], arr[hi]);
    if(arr[hi] < arr[mid]) swap(arr[hi], arr[mid]);
    return mid;
}

void introsort(int arr[], int lo, int hi, int maxdepth){

    if (hi - lo < 16){
        insertionsort(arr, lo, hi);
        return;
    }

    if(maxdepth == 0){
        heapsort(arr, lo, hi);
        return;
    }

    int pivot = medianOfThree(arr, lo, hi);
    swap(arr[pivot], arr[hi-1]);
    int partitionPoint = lomuto::partition(arr, lo + 1, hi - 1);
    introsort(arr, lo, partitionPoint - 1, maxdepth - 1);
    introsort(arr, partitionPoint + 1, hi, maxdepth - 1);
}

void sort(int arr[], int size){
    int maxdepth = std::ceil(std::log2f(size)) * 8;
    introsort(arr, 0, size -1, maxdepth);
}