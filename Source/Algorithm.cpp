/**
 * @file Algorithm.cpp
 *
 * @brief Provides implementations of sorting and selection algorithms.
 *
 * This source file contains the implementation of several algorithms including Quickselect and Quicksort,
 * tailored for both numerical data and strings. The Quickselect algorithm is designed to efficiently find
 * the k-th smallest element in an unordered list, while the Quicksort algorithm sorts elements of an array
 * or a vector in ascending order. Both algorithms employ a partitioning approach to organize data around a
 * pivot value, facilitating rapid sorting and retrieval operations. These algorithms are optimized for performance
 * and flexibility, making them suitable for a wide range of applications requiring efficient data organization
 * and retrieval.
 *
 * @date Created on March 19, 2024
 *
 * @authors
 * Advanced Programming Group Radix Sort:
 *   - Benjamin Duncan (edsml-bd1023)
 *   - Boyang Hu (edsml-bh223)
 *   - Chawk Chamoun (edsml-cc8915)
 *   - Mingsheng Cai (acse-sc4623)
 *   - Moyu Zhang (acse-mz223)
 *   - Ryan Benney (acse-rgb123)
 */

#include "Algorithm.h"

#include <stdexcept>

int Algorithm::partition(std::vector<unsigned char>& arr, int left, int right, int pivotIndex) {
    // Partition the array of unsigned char around the pivot element
    unsigned char pivotValue = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[right]);  // Move pivot to end
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    std::swap(arr[storeIndex], arr[right]);  // Move pivot to its final place
    return storeIndex;
}

int Algorithm::partition(std::vector<std::string> &arr, int low, int high) {
    // Partition the array of strings around the last element as pivot
    std::string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}


unsigned char Algorithm::quickSelect(std::vector<unsigned char>& arr, int left, int right, int k) {
    // If the array is empty or k is out of bounds
    if (arr.empty() || k < 0 || k >= arr.size()) {
        throw std::invalid_argument("Invalid array or k value");
    }

    if (left == right) {  // If the array contains only one element
        return arr[left];  // Return that element
    }
    int pivotIndex = left + (right - left) / 2;  // Optimized pivot selection
    pivotIndex = partition(arr, left, right, pivotIndex);
    // Recur for the left or right subarray
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

void Algorithm::quickSort(std::vector<std::string> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
