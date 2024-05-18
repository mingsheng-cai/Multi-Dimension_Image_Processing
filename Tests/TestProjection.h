/**
 * @file TestProjection.h
 *
 * @brief Unit Tests for the Projection Class.
 *
 * This header file declares the TestProjection class, focused on verifying the functionality and accuracy of the Projection class within the image processing library. The Projection class offers various methods for transforming 3D volume data into 2D images through techniques such as maximum, minimum, average, and median intensity projection. These projections are essential for visualizing 3D volume data in a 2D format, aiding in the analysis and interpretation of the data. The tests encompass scenarios including different projection techniques, handling of edge cases such as single-layer volumes, null data pointers, and volumes filled with zero intensity values, ensuring that the Projection class behaves as expected under a wide range of conditions.
 *
 * Usage:
 * Derived from the Test base class, the TestProjection class implements the runTests method to execute all specified test cases, using the Test class's runTest template method for each test function. This comprehensive testing strategy ensures the reliability and effectiveness of the Projection class's functionality, crucial for accurate 2D visualization of 3D volume data in various applications.
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
#include "Projection.h"
#include <vector>
#include <algorithm>  // For std::sort
#include <cassert>
#include <numeric>    // For std::accumulate

class TestProjection : public Test {
public:
    /**
     * Tests Maximum Intensity Projection
     *
     * Verifies the behavior of the maximum intensity projection method in the Projection class. This test ensures that the
     * maximum intensity projection produces the correct result by comparing the output to the expected projection from a
     * given 2x2x2 volume data. By testing the maximum intensity projection, the method confirms that the Projection class
     * correctly computes the maximum intensity values for each pixel in the projection, providing an accurate representation
     * of the input volume data.
     */
    void testMaximumIntensityProjection() {
        const int width = 2, height = 2, depth = 2;
        std::vector<unsigned char> data = {
                1, 2,
                3, 4,

                5, 6,
                7, 8
        };  // 2x2x2 Volume Data

        auto mip = Projection::maximumIntensityProjection(width, height, depth, data.data());
        std::vector<unsigned char> expectedMIP = {5, 6, 7, 8};

        assert(mip == expectedMIP);
    }

    /**
     * Tests Minimum Intensity Projection
     *
     * Verifies the behavior of the minimum intensity projection method in the Projection class. This test ensures that the
     * minimum intensity projection produces the correct result by comparing the output to the expected projection from a
     * given 2x2x2 volume data. By testing the minimum intensity projection, the method confirms that the Projection class
     * correctly computes the minimum intensity values for each pixel in the projection, providing an accurate representation
     * of the input volume data.
     */
    void testMinimumIntensityProjection() {
        const int width = 2, height = 2, depth = 2;
        std::vector<unsigned char> data = {
                1, 2,
                3, 4,

                5, 6,
                7, 8
        };  // 2x2x2 Volume Data

        auto minip = Projection::minimumIntensityProjection(width, height, depth, data.data());
        std::vector<unsigned char> expectedMinIP = {1, 2, 3, 4};

        assert(minip == expectedMinIP);
    }

    /**
     * Tests Average Intensity Projection
     *
     * Verifies the behavior of the average intensity projection method in the Projection class. This test ensures that the
     * average intensity projection produces the correct result by comparing the output to the expected projection from a
     * given 2x2x2 volume data. By testing the average intensity projection, the method confirms that the Projection class
     * correctly computes the average intensity values for each pixel in the projection, providing an accurate representation
     * of the input volume data.
     */
    void testAverageIntensityProjection() {
        const int width = 2, height = 2, depth = 2;
        std::vector<unsigned char> data = {
                1, 2,
                3, 4,

                5, 6,
                7, 8
        };  // 2x2x2 Volume Data

        auto aip = Projection::averageIntensityProjection(width, height, depth, data.data());
        std::vector<unsigned char> expectedAIP = {3, 4, 5, 6};

        assert(aip == expectedAIP);
    }

    /**
     * Tests Median Intensity Projection
     *
     * Verifies the behavior of the median intensity projection method in the Projection class. This test ensures that the
     * median intensity projection produces the correct result by comparing the output to the expected projection from a
     * given 2x2x2 volume data. By testing the median intensity projection, the method confirms that the Projection class
     * correctly computes the median intensity values for each pixel in the projection, providing an accurate representation
     * of the input volume data.
     */
    void testMedianIntensityProjection() {
        const int width = 2, height = 2, depth = 2;
        std::vector<unsigned char> data = {
                1, 6,
                3, 8,

                5, 2,
                7, 4
        };  // 2x2x2 Volume Data

        auto medip = Projection::medianIntensityProjection(width, height, depth, data.data());
        std::vector<unsigned char> expectedMedIP = {3, 4, 5, 6};  // Sorted: 1, 2, 3, 4, 5, 6, 7, 8

        assert(medip == expectedMedIP);
    }

    /**
     * Tests Single Layer Volume Projection
     *
     * Verifies the behavior of the projection methods when provided with a single-layer volume. This test ensures that the
     * projection results for maximum, minimum, average, and median intensity projections are consistent when applied to a
     * single-layer volume. By testing this scenario, the method confirms that the Projection class correctly handles single-
     * layer volumes, producing accurate projections that reflect the input data's characteristics.
     */
    void testSingleLayerVolumeProjection() {
        const int width = 2, height = 2, depth = 1;
        std::vector<unsigned char> data = {
                10, 20,
                30, 40
        };  // 2x2x1 Volume Data

        // All projections should be the same as the input data
        auto mip = Projection::maximumIntensityProjection(width, height, depth, data.data());
        auto minip = Projection::minimumIntensityProjection(width, height, depth, data.data());
        auto aip = Projection::averageIntensityProjection(width, height, depth, data.data());
        auto medip = Projection::medianIntensityProjection(width, height, depth, data.data());

        assert(mip == data && minip == data && aip == data && medip == data);
    }

    /**
     * Tests Handling Null Data Pointer
     *
     * Verifies the behavior of the projection methods when provided with a null data pointer. This test ensures that the
     * projection methods correctly handle the null pointer scenario, returning an empty vector as the projection result.
     * By testing this scenario, the method confirms that the Projection class gracefully handles null data pointers, avoiding
     * potential crashes or undefined behavior in the application.
     */
    void testNullDataProjection() {
        const int width = 2, height = 2, depth = 2;

        // The data pointer is null
        auto mip = Projection::maximumIntensityProjection(width, height, depth, nullptr);
        auto minip = Projection::minimumIntensityProjection(width, height, depth, nullptr);
        auto aip = Projection::averageIntensityProjection(width, height, depth, nullptr);
        auto medip = Projection::medianIntensityProjection(width, height, depth, nullptr);

        // 预期所有方法返回空向量
        assert(mip.empty() && minip.empty() && aip.empty() && medip.empty());
    }

    /**
     * Tests Handling Zero Volume Data
     *
     * Verifies the behavior of the projection methods when provided with volume data containing zero intensity values.
     * This test ensures that the projection results are correctly computed and reflect the zero intensity values in the
     * input data. By testing this scenario, the method confirms that the Projection class handles zero intensity values
     * appropriately, producing accurate projections that align with the input data's characteristics.
     */
    void testZeroVolumeDataProjection() {
        const int width = 2, height = 2, depth = 2;
        std::vector<unsigned char> zeroData(width * height * depth, 0); // All zeros

        auto mip = Projection::maximumIntensityProjection(width, height, depth, zeroData.data());
        auto minip = Projection::minimumIntensityProjection(width, height, depth, zeroData.data());
        auto aip = Projection::averageIntensityProjection(width, height, depth, zeroData.data());
        auto medip = Projection::medianIntensityProjection(width, height, depth, zeroData.data());

        // For all projection methods, the result should be a projection of zeros
        std::vector<unsigned char> expectedProjection(width * height, 0);
        assert(mip == expectedProjection && minip == expectedProjection && aip == expectedProjection && medip == expectedProjection);
    }

    /**
     * Executes All Defined Test Cases for the Image Class
     *
     * This method runs all the test cases defined within the TestProjection class to verify the correctness and
     * reliability of the Projection class's functionality. The tests cover various scenarios, including different
     * projection techniques, handling of edge cases such as single-layer volumes, null data pointers, and volumes
     * filled with zero intensity values. By executing all test cases, this method ensures that the Projection class
     * behaves as expected under a wide range of conditions, providing confidence in its accuracy and robustness.
     */
    virtual void runTests() override {
        runTest<TestProjection>(&TestProjection::testMaximumIntensityProjection, "Maximum Intensity Projection");
        runTest<TestProjection>(&TestProjection::testMinimumIntensityProjection, "Minimum Intensity Projection");
        runTest<TestProjection>(&TestProjection::testAverageIntensityProjection, "Average Intensity Projection");
        runTest<TestProjection>(&TestProjection::testMedianIntensityProjection, "Median Intensity Projection");
        runTest<TestProjection>(&TestProjection::testSingleLayerVolumeProjection, "Single Layer Volume Projection");
        runTest<TestProjection>(&TestProjection::testNullDataProjection, "Null Data Projection");
        runTest<TestProjection>(&TestProjection::testZeroVolumeDataProjection, "Zero Volume Data Projection");
    }
};
