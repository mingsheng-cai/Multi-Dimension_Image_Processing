/**
 * @file TestAlgorithm.h
 *
 * @brief Unit Tests for the Algorithm Class.
 *
 * This header file contains the declaration of the TestAlgorithm class, which extends the Test class
 * to provide unit testing functionality for the Algorithm class. It focuses on verifying the correctness
 * and robustness of sorting and selection algorithms implemented within the Algorithm class, specifically
 * quick sort and quick select algorithms. The tests cover a range of scenarios including empty arrays,
 * single-element arrays, arrays with duplicates, and arrays with invalid indices. Through these tests,
 * the framework aims to ensure that the algorithms behave as expected under normal and edge-case conditions.
 * The use of assertions within each test case helps in validating the expected outcomes, and any exceptions
 * thrown by the algorithms are caught to verify error handling mechanisms.
 *
 * Usage:
 * Derived from the Test base class, the TestAlgorithm class implements the runTests method to execute
 * all defined test cases, leveraging the Test class's template method runTest for executing individual
 * test functions. This structure allows for comprehensive testing of the Algorithm class's functionalities.
 *
 * @date Created on March 21, 2024.
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

#include "../Include/Algorithm.h"
#include "Test.h"
#include <vector>
#include <algorithm> // For std::sort
#include <stdexcept> // For std::exception
#include <cassert>  // For assert

class TestAlgorithm : public Test {
public:
    /**
     * Tests QuickSelect on an Empty Array
     *
     * Verifies the behavior of the QuickSelect algorithm when applied to an empty array. The test ensures that
     * QuickSelect appropriately handles the edge case by either throwing an exception or safely returning without
     * altering the state. This test case is crucial for validating the algorithm's robustness and error handling
     * capabilities.
     */
    void testEmptyArray() {
        std::vector<unsigned char> emptyArr;
        try {
            auto result = Algorithm::quickSelect(emptyArr, 0, emptyArr.size() - 1, 0);
            assert(false && "QuickSelect did not throw an error on empty array.");
        } catch (const std::exception&) {
            // Test passed
        }

        std::vector<std::string> emptyArrStr;
        Algorithm::quickSort(emptyArrStr, 0, emptyArr.size() - 1);
        // If it reaches here without throwing, it's considered passed for empty arrays.
    }

    /**
     * Tests QuickSelect with a Single Element Array
     *
     * Evaluates QuickSelect's functionality on an array containing a single element. The test confirms that
     * QuickSelect correctly identifies the sole element as the 'kth' element regardless of the 'k' value provided.
     * Similarly, QuickSort is tested to verify it can sort an array of a single element without errors.
     */
    void testSingleElementArray() {
        std::vector<unsigned char> singleArr = {42};
        auto result = Algorithm::quickSelect(singleArr, 0, singleArr.size() - 1, 0);
        assert(result == 42 && "QuickSelect Test Failed on single element array.");

        std::vector<std::string> singleStrArr = {"single"};
        Algorithm::quickSort(singleStrArr, 0, singleStrArr.size() - 1);
        assert(singleStrArr[0] == "single" && "QuickSort Test Failed on single element array.");
    }

    /**
     * Tests Handling of Arrays with Duplicates
     *
     * Checks QuickSelect and QuickSort algorithms' ability to handle arrays containing duplicate elements.
     * For QuickSelect, the test verifies that the correct 'kth' element is selected from among duplicates.
     * For QuickSort, it ensures that the algorithm can sort arrays with duplicates into the correct order.
     */
    void testArrayWithDuplicates() {
        std::vector<unsigned char> duplicateArr = {5, 3, 5, 4, 5, 5, 6};
        auto kthElement = Algorithm::quickSelect(duplicateArr, 0, duplicateArr.size() - 1, 4);
        assert(kthElement == 5 && "QuickSelect Test Failed with duplicates.");

        std::vector<std::string> strArr = {"apple", "banana", "apple", "cherry", "banana"};
        std::vector<std::string> sortedStrArr = strArr;
        std::sort(sortedStrArr.begin(), sortedStrArr.end());
        Algorithm::quickSort(strArr, 0, strArr.size() - 1);
        assert(strArr == sortedStrArr && "QuickSort Test Failed with duplicates.");
    }

    /**
     * Tests QuickSelect with Invalid 'k' Values
     *
     * Evaluates QuickSelect's error handling when provided with invalid 'k' values, such as a negative index or an
     * index exceeding the array bounds. The test ensures that QuickSelect throws an exception or otherwise signals
     * an error, demonstrating proper input validation.
     */
    void testInvalidKValues() {
        std::vector<unsigned char> arr = {9, 3, 2, 4, 8, 5, 6, 7};
        try {
            auto result = Algorithm::quickSelect(arr, 0, arr.size() - 1, -1); // Invalid k
            assert(false && "QuickSelect did not throw an error for invalid k value.");
        } catch (const std::exception&) {
            // Test passed
        }

        try {
            auto result = Algorithm::quickSelect(arr, 0, arr.size() - 1, arr.size()); // k out of bounds
            assert(false && "QuickSelect did not throw an error for k value out of bounds.");
        } catch (const std::exception&) {
            // Test passed
        }
    }

    /**
     * Comprehensive Tests for QuickSelect and QuickSort
     *
     * These additional tests cover the core functionalities of QuickSelect and QuickSort, ensuring they perform
     * as expected under typical usage scenarios. QuickSelect's test verifies it can accurately find the 'kth' smallest
     * element in a mixed array, while QuickSort's test confirms the algorithm successfully sorts a variety of strings.
     */
    void testQuickSelect() {
        std::vector<unsigned char> arr = {9, 3, 2, 4, 8, 5, 6, 7};
        int k = 4; // Looking for the 4th smallest element, which is 5
        auto kthElement = Algorithm::quickSelect(arr, 0, arr.size() - 1, k - 1); // k - 1 because indices are 0-based
        assert(kthElement == 5 && "QuickSelect Test Failed.");
    }

    /**
     * Tests QuickSort on a String Array
     *
     * Validates QuickSort's ability to sort an array of strings in lexicographical order. The test compares the
     * sorted array produced by QuickSort with the expected sorted array generated using the standard library's
     * sort function. If the two arrays match, the test considers QuickSort to have passed successfully.
     */
    void testQuickSort() {
        std::vector<std::string> arr = {"banana", "apple", "mango", "cherry", "orange"};
        std::vector<std::string> sortedArr = arr;
        std::sort(sortedArr.begin(), sortedArr.end());

        Algorithm::quickSort(arr, 0, arr.size() - 1);
        assert(arr == sortedArr && "QuickSort Test Failed.");
    }

    /**
     * Executes all defined test cases for the Algorithm class.
     *
     * This method runs all test cases defined within the TestAlgorithm class, using the runTest template method
     * from the Test base class to execute each test function. The results of the tests are printed to the console
     * to provide feedback on the success or failure of each test case. The method serves as a comprehensive test
     * suite for the Algorithm class, covering a range of scenarios to ensure the correctness and robustness of the
     * implemented sorting and selection algorithms.
     */
    virtual void runTests() override {
        runTest<TestAlgorithm>(&TestAlgorithm::testEmptyArray, "EmptyArray");
        runTest<TestAlgorithm>(&TestAlgorithm::testSingleElementArray, "SingleElementArray");
        runTest<TestAlgorithm>(&TestAlgorithm::testArrayWithDuplicates, "ArrayWithDuplicates");
        runTest<TestAlgorithm>(&TestAlgorithm::testInvalidKValues, "InvalidKValues");
        runTest<TestAlgorithm>(&TestAlgorithm::testQuickSelect, "QuickSelect");
        runTest<TestAlgorithm>(&TestAlgorithm::testQuickSort, "QuickSort");
    }
};
