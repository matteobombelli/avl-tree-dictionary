// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Matteo Bombelli
// St.# : 301550507
// Email: mgb10@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "a4_base.h"

using namespace std;

//
// Put the implementations of all the functions listed in a4_base.h here.
//

//
// Is Sorted algorithm
//
template <typename T>
bool is_sorted(vector<T> &v)
{
    if (v.empty())
    {
        return true;
    }

    for (int i = 0; i < v.size() - 1; ++i)
    {
        if (v[i] > v[i + 1])
        {
            return false;
        }
    }

    return true;
}


//
// Bubble Sort
// Moves through the list sequentially and swaps elements if they are unordered
//
template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

// 
// Insertion Sort
// Sequentially forms a sorted partition and inserts the next element
// maintaining order
//
template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 1; i < v.size(); ++i)
    {
        T temp = v[i]; // store next element
        int j = i - 1; 

        // Move elements >v[i] one position forward
        while (j >= 0 && v[j] > temp)
        {
            ++num_comps; // <--- num_comps is incremented here
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = temp;
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Insertion sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// Selection Sort
// find the minimum element in the list and move it to the correct
// location forming a sorted partition
//
template <typename T>
SortStats selection_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 0; i < v.size(); ++i)
    {
        int min_index= i;

        // find the index with the minimum unsorted value
        for (int j = i + 1; j < v.size(); ++j)
        {
            ++num_comps; // <--- num_comps is incremented here
            if (v[min_index] > v[j])
            {
                min_index = j;
            }
        }

        // swap min unsorted element with i
        swap(v[min_index], v[i]);
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// Merge Sort
//
template <typename T>
SortStats merge_sort(vector<T>& v)
{
    ulong num_comps = 0;
    clock_t start = clock();

    if (v.size() <= 1)
    {
        clock_t end = clock();
        double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
        ++num_comps;
        return SortStats{"Merge sort", v.size(), num_comps, elapsed_cpu_time_sec};
    }

    // Split the vector into left and right subvectors
    int mid = v.size() / 2;
    vector<T> left(v.begin(), v.begin() + mid);
    vector<T> right(v.begin() + mid, v.end());

    // Recursively sort the left and right subvectors
    SortStats left_stats = merge_sort(left);
    SortStats right_stats = merge_sort(right);

    // num_comps is updated here
    num_comps += left_stats.num_comparisons + right_stats.num_comparisons;

    // Merge the now sorted left and right subvectors
    vector<T> merged(v.size());
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        ++num_comps; // <--- num_comps is incremented here
        if (left[i] <= right[j])
        {
            merged[k] = left[i];
            ++i;
        }
        else
        {
            merged[k] = right[j];
            ++j;
        }
        ++k;
    }

    // Add any remaining elements from the subvectors
    while (i < left.size())
    {
        merged[k] = left[i];
        ++i;
        ++k;
    }

    while (j < right.size())
    {
        merged[k] = right[j];
        ++j;
        ++k;
    }

    v = merged;

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Merge sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// Quick Sort
//
template <typename T>
void quick_sort_algorithm(ulong &num_comps, vector<T> &v, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    // Choose pivot randomly
    int pivot_index = start + rand() % (end - start + 1); // Random pivot index
    T pivot = v[pivot_index];

    // Swap pivot with the last element
    swap(v[pivot_index], v[end]);

    int i = start;

    for (int j = start; j < end; j++)
    {
        ++num_comps; // <--- num_comps is incremented here
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            ++i;
        }
    }
    
    swap(v[i], v[end]);

    pivot_index = i;
    quick_sort_algorithm(num_comps, v, start, pivot_index - 1);
    quick_sort_algorithm(num_comps, v, pivot_index + 1, end);
}

template <typename T>
SortStats quick_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    quick_sort_algorithm(num_comps, v, 0, v.size() - 1);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Quick sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// Shell Sort
//
template <typename T>
SortStats shell_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int gap = v.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < v.size(); ++i)
        {
            T temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
            {
                ++num_comps; // <--- num_comps is incremented here
                v[j] = v[j - gap];
            }

            v[j] = temp;
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Shell sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// iQuick Sort
// threshold determined in helper function
//
template <typename T>
void insertion_sort_iq(ulong &num_comps, vector<T> &v, int start, int end)
{
    for (int i = start + 1; i <= end; ++i)
    {
        T temp = v[i]; // store next element
        int j = i - 1; 

        // Move elements >v[i] one position forward
        while (j >= start && v[j] > temp)
        {
            ++num_comps; // <--- num_comps is incremented here
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = temp;
    }
}

template <typename T>
void iquick_sort_algorithm(ulong &num_comps, vector<T> &v, int start, int end, int threshold)
{
    if (end - start <= threshold)
    {
        insertion_sort_iq(num_comps, v, start, end);
        return;
    }

    // Choose pivot randomly
    int pivot_index = start + rand() % (end - start + 1); // Random pivot index
    T pivot = v[pivot_index];

    // Swap pivot with the last element
    swap(v[pivot_index], v[end]);

    int i = start;

    for (int j = start; j < end; j++)
    {
        ++num_comps; // <--- num_comps is incremented here
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            ++i;
        }
    }
    
    swap(v[i], v[end]);

    pivot_index = i;
    iquick_sort_algorithm(num_comps, v, start, pivot_index - 1, threshold);
    iquick_sort_algorithm(num_comps, v, pivot_index + 1, end, threshold);
}

template <typename T>
SortStats iquick_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    int threshold = 27;

    iquick_sort_algorithm(num_comps, v, 0, v.size() - 1, threshold);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"iQuick Sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max)
{
    int rand_int;
    vector<int> v;
    while (v.size() < n)
    {   
        rand_int = rand() % (max - min + 1) + min;
        v.push_back(rand_int);
    }

    return v;
}