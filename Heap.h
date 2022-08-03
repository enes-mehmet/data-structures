#pragma once
#ifndef _HEAP_H
#define _HEAP_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template<class Comparable>
class Heap
{
private:
	vector<Comparable> arr;
	int size;

	int left(const int& index) { 
		if ((index * 2) > size)
			return -1;
		else
			return (index * 2);
	}
	int right(const int& index) {
		if ((index * 2 + 1) > size)
			return -1;
		else
			return (index * 2 + 1);
	}
	int parent(const int& i) {
		if (i >= 1)
			return i / 2;
		else
			return -1;
		
	}
	void swap(const int& i, const int& j) {
		Comparable temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	void percDown(const int& index) {
		if (index <= (size/2)-1) {
			if (arr[index] > arr[left(index)] && arr[index] > arr[right(index)]) {
				if (arr[left(index)] < arr[right(index)]) {
					swap(index, left(index));
					percDown(left(index));
				}
				else {
					swap(index, right(index));
					percDown(right(index));
				}
			}
			else if (arr[index] > arr[left(index)]) {
				swap(index, left(index));
				percDown(left(index));
			}
			else if (arr[index] > arr[right(index)]) {
				swap(index, right(index));
					percDown(right(index));
			}
		}
	}
	void percUp(const int& index) {
		if (parent(index) != -1 && arr[index] < arr[parent(index)]) {
			swap(index, parent(index));
			percUp(parent(index));
		}
	}
	
	void percUp() {
		percUp(size);
	}


public:
	Heap() :arr(vector<Comparable>(1, 0)), size(0) {
		arr.reserve(128);
	}
	Comparable deleteMin() {
		if (size > 0) {
			Comparable result = arr[1];
			arr[1] = arr[size];
			size--;
			percDown(1);
			return result;
		}
		else {
			cout << "deleteMin unsuccesful" << endl;
		}
	}
	void insert(const Comparable& insert) {
		size++;
		if (arr.size() - 1 <= size) {
			arr.push_back(insert);
			percUp();
		}
		else {
			arr[size] = insert;
			percUp();
		}
	}
	Comparable kthMin(int k) {
		vector<Comparable> temp;
		for (int i = 0; i < k; i++) {
			temp.push_back(deleteMin());
		}

		Comparable result = temp[temp.size()-1];

		for (int i = 0; i < k; i++) {
			insert(temp[i]);
		}
		return result;
	}


};
#endif

