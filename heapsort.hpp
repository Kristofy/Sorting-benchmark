#pragma once
#include "util.hpp"

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2;
 
    if (left < n && arr[left] > arr[largest])
        largest = left;
 
    if (right < n && arr[right] > arr[largest])
        largest = right;
 
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void make_heap(int arr[], int size){
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
}
 
void heapsort(int arr[], int size)
{
    make_heap(arr, size);
 
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
void heapsort_all(int arr[], int size){
    heapsort(arr, size);
}