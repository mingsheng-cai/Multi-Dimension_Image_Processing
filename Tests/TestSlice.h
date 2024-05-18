/**
 * @file TestSlice.h
 *
 * @brief Unit Tests for the Slice Class.
 *
 * This header file details the TestSlice class, tasked with evaluating the Slice class's capabilities in extracting specific slices from 3D volume data. The tests span a range of scenarios, including valid slices across different planes (x-y, x-z, y-z), handling of invalid slice indices, out-of-bounds requests, and negative indices. These tests verify the Slice class's functionality in navigating and manipulating 3D data structures, ensuring accurate extraction of 2D planes crucial for analysis, visualization, and further processing in various applications.
 *
 * Usage:
 * As an extension of the Test base class, the TestSlice class implements the runTests method to systematically execute all specified test cases, using the Test class's runTest template method for each test function. This structured approach facilitates thorough validation of the Slice class's performance, emphasizing its reliability and precision in slicing 3D volume data.
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

#include "Test.h"
#include "Slice.h"

#include <vector>
#include <cassert>

class TestSlice : public Test {
public:
    /**
     * Tests the Extraction of a Valid Slice
     *
     * Verifies that the getPlaneSlice method correctly extracts a valid slice from the 3D volume data. This test
     * ensures that the extracted slice matches the expected data and size, validating the Slice class's ability to
     * navigate and retrieve specific 2D planes from the 3D volume.
     */
    void testValidSlice() {
        std::vector<unsigned char> volumeData(100); // A 10x10x1 volume
        for (int i = 0; i < 100; ++i) {
            volumeData[i] = i;
        }

        auto slice = Slice::getPlaneSlice(10, 10, 1, volumeData.data(), "x-y", 1);
        assert(!slice.empty()); // Ensure the slice is not empty
        assert(slice.size() == 100); // Ensure the slice has the correct size
        for (size_t i = 0; i < slice.size(); ++i) {
            assert(slice[i] == i); // Ensure the slice data matches the volume data
        }
    }

    /**
     * Tests the Handling of an Invalid Slice Index
     *
     * Verifies that the getPlaneSlice method correctly handles an invalid slice index by returning an empty slice.
     * This test ensures that the Slice class can detect and respond to out-of-bounds slice requests, preventing
     * potential memory access violations or incorrect data extraction.
     */
    void testInvalidSliceIndex() {
        std::vector<unsigned char> volumeData(100);
        auto slice = Slice::getPlaneSlice(10, 10, 1, volumeData.data(), "x-y", 2); // 无效的切片索引
        assert(slice.empty()); // Return an empty slice
    }

    /**
     * Tests the Handling of an Invalid Plane
     *
     * Verifies that the getPlaneSlice method correctly handles an invalid plane request by returning an empty slice.
     * This test ensures that the Slice class can detect and respond to unsupported plane types, preventing potential
     * data extraction errors or misinterpretation of the volume data.
     */
    void testInvalidPlane() {
        std::vector<unsigned char> volumeData(100);
        auto slice = Slice::getPlaneSlice(10, 10, 1, volumeData.data(), "invalid-plane", 1); // 无效的平面
        assert(slice.empty()); // Return an empty slice
    }

    /**
     * Tests the Extraction of an XY Plane Slice
     *
     * Verifies the getPlaneSlice method's ability to extract a specific XY plane slice from the 3D volume data. This
     * test focuses on the correct retrieval of the XY plane slice at a given depth, ensuring that the extracted slice
     * matches the expected data and dimensions for further analysis or visualization.
     */
    void testXYPlaneSlice() {
        std::vector<unsigned char> volumeData(27);
        // Initialize volume data
        for (int i = 0; i < 27; ++i) {
            volumeData[i] = i;
        }

        // Get the second row slice (index 2), note that in the x-y plane, "row" corresponds to the y direction
        auto slice = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-y", 2);
        assert(slice.size() == 9);
        for (int i = 0; i < 9; ++i) {
            assert(slice[i] == 9 + i);  // Expected values to be calculated based on the arrangement
        }
    }

    /**
     * Tests the Extraction of an XZ Plane Slice
     *
     * Verifies the getPlaneSlice method's ability to extract a specific XZ plane slice from the 3D volume data. This
     * test focuses on the correct retrieval of the XZ plane slice at a given height, ensuring that the extracted slice
     * matches the expected data and dimensions for further analysis or visualization.
     */
    void testXZPlaneSlice() {
        std::vector<unsigned char> volumeData(27);
        // Initialize volume data
        for (int i = 0; i < 27; ++i) {
            volumeData[i] = i;
        }

        // Get the third column slice (index 2), note that in the x-z plane, "column" corresponds to the z direction
        auto slice = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-z", 2);
        assert(slice.size() == 9);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assert(slice[i * 3 + j] == 3 * j + i + 3);  // Slice data expected to be every three jumps
            }
        }
    }

    /**
     * Tests the Extraction of a YZ Plane Slice
     *
     * Verifies the getPlaneSlice method's ability to extract a specific YZ plane slice from the 3D volume data. This
     * test focuses on the correct retrieval of the YZ plane slice at a given width, ensuring that the extracted slice
     * matches the expected data and dimensions for further analysis or visualization.
     */
    void testYZPlaneSlice() {
        std::vector<unsigned char> volumeData(27);
        // Initialize volume data
        for (int i = 0; i < 27; ++i) {
            volumeData[i] = i;
        }

        // Get the second column slice (index 1), note that in the y-z plane, "column" corresponds to the z direction
        auto slice = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "y-z", 1);
        assert(slice.size() == 9);
        for (int i = 0; i < 9; ++i) {
            assert(slice[i] == i * 3);  // Expected values to be every three jumps
        }
    }

    /**
     * Tests the Handling of an Out-of-Bounds Slice Index
     *
     * Verifies that the getPlaneSlice method correctly handles an out-of-bounds slice index request by returning an
     * empty slice. This test ensures that the Slice class can detect and respond to invalid slice indices that exceed
     * the volume's dimensions, preventing potential memory access violations or incorrect data extraction.
     */
    void testOutOfBoundsSliceIndex() {
        std::vector<unsigned char> volumeData(27);  // 3x3x3 Volume
        for (int i = 0; i < 27; ++i) {
            volumeData[i] = i;
        }

        // Try to get an out-of-bounds XY plane slice
        auto sliceXY = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-y", 4);
        assert(sliceXY.empty());  // Expected to return an empty vector

        // Try to get an out-of-bounds XZ plane slice
        auto sliceXZ = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-z", 4);
        assert(sliceXZ.empty());  // Expected to return an empty vector

        // Try to get an out-of-bounds YZ plane slice
        auto sliceYZ = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "y-z", 4);
        assert(sliceYZ.empty());  // Expected to return an empty vector
    }

    /**
     * Tests the Handling of a Negative Slice Index
     *
     * Verifies that the getPlaneSlice method correctly handles a negative slice index request by returning an empty
     * slice. This test ensures that the Slice class can detect and respond to negative slice indices, preventing
     * potential data extraction errors or misinterpretation of the volume data.
     */
    void testNegativeSliceIndex() {
        std::vector<unsigned char> volumeData(27);  // 3x3x3 Volume
        for (int i = 0; i < 27; ++i) {
            volumeData[i] = i;
        }

        // Try to get a negative XY plane slice
        auto sliceXY = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-y", -1);
        assert(sliceXY.empty());  // Return an empty vector

        auto sliceXZ = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "x-z", -1);
        assert(sliceXZ.empty());  // Return an empty vector

        auto sliceYZ = Slice::getPlaneSlice(3, 3, 3, volumeData.data(), "y-z", -1);
        assert(sliceYZ.empty());  // Return an empty vector
    }

    /**
     * Executes the Test Cases for the Slice Class
     *
     * Runs all the test cases defined for the Slice class to validate its functionality in extracting specific slices
     * from 3D volume data. The test cases cover a range of scenarios, including valid slices across different planes
     * (x-y, x-z, y-z), handling of invalid slice indices, out-of-bounds requests, and negative indices.
     */
    virtual void runTests() override {
        runTest<TestSlice>(&TestSlice::testValidSlice, "Valid Slice");
        runTest<TestSlice>(&TestSlice::testInvalidSliceIndex, "Invalid Slice Index");
        runTest<TestSlice>(&TestSlice::testInvalidPlane, "Invalid Plane");
        runTest<TestSlice>(&TestSlice::testXYPlaneSlice, "XY Plane Slice");
        runTest<TestSlice>(&TestSlice::testXZPlaneSlice, "XZ Plane Slice");
        runTest<TestSlice>(&TestSlice::testYZPlaneSlice, "YZ Plane Slice");
        runTest<TestSlice>(&TestSlice::testOutOfBoundsSliceIndex, "Out of Bounds Slice Index");
        runTest<TestSlice>(&TestSlice::testNegativeSliceIndex, "Negative Slice Index");
    }
};
