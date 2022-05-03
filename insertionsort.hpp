#pragma once

void insertionsort(int arr[], int lo, int hi){
    for(int i = lo + 1; i <= hi; i++){
        if(arr[i - 1] > arr[i]){
            int ind = i-1;
            int elem = arr[i];
            while(ind >= lo && arr[ind] > elem){
                arr[ind+1] = arr[ind];
                ind--;
            }
            arr[ind+1] = elem;
        }
    }
}