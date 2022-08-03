#pragma once
#ifndef _INSSORT_H
#define _INSSORT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename Comparable>
void insertionSort(vector<Comparable>& arr)
{   
    int i, j, size = arr.size();
    Comparable key;
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
#endif