#pragma once
#ifndef _HEAPSORT_H
#define _HEAPSORT_H


#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

template <typename Comparable>
void percDown(vector<Comparable>& arr, int n, int i)
{	
	
	/*auto a = std::chrono::high_resolution_clock::now();*/
	int largest = i; //largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);

		percDown(arr, n, largest);
	}
	/*auto x = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - a);
	cout << "\nTime: " << x.count() << " nanosecond(s) Heap Sort" << "\n";*/
}
template <typename Comparable>
void heapSort(vector<Comparable>& arr)
{	
	int size = arr.size();
	// Build heap (rearrange array)
	for (int i = size / 2 - 1; i >= 0; i--)
		percDown(arr, size, i);
	// sort
	for (int i = size - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		percDown(arr, i, 0);
	}
	
}

#endif
