#include "timer.hpp"

#include <array>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "quicksort.hpp"
#include "mergesort.hpp"
#include "introsort.hpp"

constexpr int SAMPLE_SIZE = 50;
constexpr int MAX_SIZE = 200'000;
constexpr int ITERATIONS = 50;

void validate(int arr[], int s);

struct random{
    inline int operator()(int){
        static std::mt19937 gen = std::mt19937((std::random_device())());
        static std::uniform_int_distribution<int> distrib(-1'000'000, 1'000'000);
        return distrib(gen);
    }

    inline int operator()(){
        static std::mt19937 gen = std::mt19937((std::random_device())());
        static std::uniform_int_distribution<int> distrib(0, 500'000);
        return distrib(gen);
    }
} rnd;

template<typename SortingAlgorithm, typename ShuffleAlgorithm>
void benchmark(const std::string& name, std::ofstream& fout, int arr[], SortingAlgorithm sorting_algorithm, ShuffleAlgorithm shuffle_algorithm){
    TimeScope("Timing " + name);
    std::sort(arr, arr + MAX_SIZE);
    fout << name << ';';
    for(int i = 1; i <= ITERATIONS; i++){
        int size = i*MAX_SIZE/ITERATIONS;
        double total_time = 0;
        AutoTimer t("");
        for(int j = 0; j < SAMPLE_SIZE; j++){
            shuffle_algorithm(arr, size);
            t.restart();
            sorting_algorithm(arr, size);
            total_time += t.end();
            validate(arr, size);
        }
        double avg_time = total_time / SAMPLE_SIZE;
        fout << avg_time <<';';
        if(avg_time > 100.0){
            break;
        }
        std::cout << "size: " << size << " \t time: " << avg_time << "ms\n";
    }
    fout << std::endl; 
}

void random_shuffle(int arr[], int size){
    for(int i = 0; i < size; i++)
        std::swap(arr[i], arr[rnd() % size]);
}

void nearly_ordered_shuffle(int arr[], int size){
    // the array is already sorted
    for(int i = 0; i < size; i++)
        if(rnd() % 100 < 2)
            std::swap(arr[i], arr[rnd() % size]);
}

void ordered_shuffle(int arr[], int size){
    // the array is already sorted
}

void rotated_shuffle(int arr[], int size){
    // the array is already sorted
    std::rotate(arr, arr + rnd() % size , arr + size);
}

template<typename ShuffleAlgorithm>
void benchmark_all(std::ofstream& fout, int arr[], const std::string& name, ShuffleAlgorithm shuffle_algorithm){
    fout << name << "\n;";

    for(int i = 1; i <= ITERATIONS; i++) fout << i*(MAX_SIZE/ITERATIONS) <<';';
    fout << '\n';
    // benchmark("Introsort", fout, arr, sort, shuffle_algorithm);
    // benchmark("Quicksort lomuto", fout, arr, median_of_three::quicksort_all<lomuto::partition>, shuffle_algorithm);
    
    benchmark("Quicksort naive lomuto", fout, arr, naive::lomuto::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort naive hoare", fout, arr, naive::hoare::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort naive randomized lomuto", fout, arr, naive_randomized::lomuto::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort naive randomized hoare", fout, arr, naive_randomized::hoare::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort mo3 lomuto", fout, arr, median_of_three::lomuto::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort mo3 hoare", fout, arr, median_of_three::hoare::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort mo3 randomized lomuto", fout, arr, median_of_three_randomized::lomuto::quicksort_all, shuffle_algorithm);
    benchmark("Quicksort mo3 randomized hoare", fout, arr, median_of_three_randomized::hoare::quicksort_all, shuffle_algorithm);
    
    // benchmark("Merge sort", fout, arr, mergesort_all, shuffle_algorithm);
    // benchmark("Heapsort", fout, arr, heapsort_all, shuffle_algorithm);
    fout << '\n';
}

int main(){
    TimeFuncion();
    std::ofstream fout("output.csv");
    int arr[MAX_SIZE];
    {
        TimeScope("init");
        std::transform(arr, arr + MAX_SIZE, arr, random{});
    }

    benchmark_all(fout, arr, "random", random_shuffle);
    benchmark_all(fout, arr, "nearly ordered", nearly_ordered_shuffle);
    benchmark_all(fout, arr, "ordered", ordered_shuffle);
    benchmark_all(fout, arr, "rotated", rotated_shuffle);
    

    fout.close();
    return 0;
}

void validate(int arr[], int s){
    if(!std::is_sorted(arr, arr + s)) std::cout << "Sort did not work!\n";
}

