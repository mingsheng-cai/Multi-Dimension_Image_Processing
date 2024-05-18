/**
 * @file Algorithm.h
 *
 * @brief Implements a radix sort algorithm for efficient data sorting.
 *
 * The RadixSortAlgorithm class provides an implementation of the radix sort algorithm,
 * which is a non-comparative integer sorting algorithm. It sorts data with integer keys by
 * grouping keys by the individual digits which share the same significant position and value.
 * A radix sort can be applied to data that can be sorted lexicographically, be it integers or strings.
 * This implementation supports both least significant digit (LSD) and most significant digit (MSD) radix sorts.
 * It is part of the data sorting and manipulation toolkit developed by the Advanced Programming Group.
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

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_ALGORITHM_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_ALGORITHM_H

#include <vector>
#include <string>

class Algorithm {
public:
    /**
     * Finds the k-th smallest element in an array using the Quickselect algorithm.
     *
     * Quickselect is a selection algorithm to find the k-th smallest element in an unsorted array. It is related to the quicksort
     * sorting algorithm. Like quicksort, it is efficient in practice and has good average-case performance, but has poor worst-case
     * performance. Quickselect uses a partition method to recursively divide the array.
     *
     * @param arr: A reference to the vector of unsigned char to be processed.
     * @param left: The starting index of the array from which to find the k-th smallest element.
     * @param right: The ending index of the array.
     * @param k: The order of the smallest element to find.
     *
     * @return: The k-th smallest element in the specified array segment.
     */
    static unsigned char quickSelect(std::vector<unsigned char> &arr, int left, int right, int k);

    /**
     * Sorts a vector of strings using the Quicksort algorithm.
     *
     * Quicksort is a divide-and-conquer algorithm. It works by selecting a 'pivot' element from the array and partitioning the other
     * elements into two sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays are then
     * recursively sorted. This implementation uses the last element as the pivot.
     *
     * @param arr: A reference to the vector of strings to be sorted.
     * @param low: The starting index of the segment of the array to be sorted.
     * @param high: The ending index of the segment of the array to be sorted.
     *
     * @return: None.
     */
    static void quickSort(std::vector<std::string> &arr, int low, int high);

    /**
     * Partitions the array around a pivot element.
     *
     * This method rearranges the elements in the array such that all elements less than the pivot value come before the pivot,
     * while all elements greater than the pivot come after it. The pivot element itself is moved to its final position in the
     * sorted array. This partitioning is a key process in both quicksort and quickselect algorithms.
     *
     * @param arr: A reference to the vector of unsigned char to be partitioned.
     * @param left: The start index of the subarray to be partitioned.
     * @param right: The end index of the subarray to be partitioned.
     * @param pivotIndex: The index of the pivot element.
     *
     * @return: The index where the pivot element is finally placed.
     */
    static int partition(std::vector<unsigned char> &arr, int left, int right, int pivotIndex);

    /**
     * Partitions the array of strings around the last element as pivot.
     *
     * Rearranges the elements in the string vector such that all elements less than the pivot come before it and all elements greater
     * come after it, with the pivot itself moving to its correct sorted position. Primarily used in the quicksort algorithm.
     *
     * @param arr: A reference to the vector of strings to be partitioned.
     * @param low: The start index of the subarray to be partitioned.
     * @param high: The end index of the subarray to be partitioned.
     *
     * @return: The index where the pivot element is finally placed.
     */
    static int partition(std::vector<std::string> &arr, int low, int high);
};


#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_ALGORITHM_H
