#pragma once
#ifndef _QUICKSORT_H
#define _QUICKSORT_H


#include <iostream>
#include <string>
#include <vector>
using namespace std;



template <typename Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
    for (int p = left + 1; p <= right; p++)
    {
        Comparable tmp = a[p];
        int j;

        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

/**
         * Standard swap
         */
template <typename Comparable>
inline void swap(Comparable& obj1,
    Comparable& obj2)
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

/** Return median of left, center, and right.
           *   Order these and hide the pivot.
         */
template <typename Comparable>
const Comparable& median3(vector<Comparable>& a,
    int left, int right)
{
    int center = (left + right) / 2;
    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    // Place pivot at position right - 1
    swap(a[center], a[right - 1]);
    return a[right - 1];
}

template <typename Comparable>
void quicksort(vector<Comparable>& a,
    int left, int right)
{

    if (left + 10 <= right)
    {
        Comparable pivot = median3(a, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}

            while (pivot < a[--j]) {}

            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        swap(a[i], a[right - 1]);   // Restore pivot

        quicksort(a, left, i - 1);       // Sort small elements
        quicksort(a, i + 1, right);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}



template <typename Comparable>
void quickSort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}

#endif
