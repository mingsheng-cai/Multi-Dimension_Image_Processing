/**
 * @file TestPadding.h
 *
 * @brief Unit Tests for Padding Strategies in Image Processing.
 *
 * This header file declares the TestPadding class, which is focused on verifying the correctness and effectiveness of various padding strategies used in image processing tasks. The padding strategies under test include zero padding, edge replication, and reflection padding. These methods are critical for handling operations near image boundaries, especially in filtering and convolution tasks. The tests ensure that each padding strategy behaves as expected, by evaluating their effects on a hypothetical image window near the image boundaries. This rigorous testing of padding strategies is crucial for maintaining the integrity of image processing results, particularly in edge and corner cases.
 *
 * Usage:
 * Derived from the Test base class, the TestPadding class implements the runTests method to conduct all specified test cases, using the Test class's runTest template method for executing individual test functions. This structured approach allows for an exhaustive evaluation of padding methods, affirming their reliability and suitability for various image processing applications.
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
#include "Filters/Padding.h"

#include <vector>
#include <cassert>

class TestPadding : public Test {
public:
    /**
     * Tests the Zero Padding Strategy
     *
     * Verifies the behavior of the zero padding strategy when applied to an image. Zero padding is essential for
     * extending the borders of an image with zeros, particularly useful in convolution operations where filter kernels
     * overlap the image edges. This test ensures that pixels outside the original image boundaries are correctly set to zero,
     * maintaining the integrity of the image processing operation.
     */
    void testZeroPadding() {
        Image img(5, 5, 1, new unsigned char[25]{});
        auto window = Padding::getPixelWindow(img, 0, 0, 0, 3, PaddingType::ZeroPadding);

        // Expect the first element in the window to be zero
        assert(window[0] == 0 && "Zero padding at the corner failed.");

        // Expect the window size to be 9
        assert(window.size() == 9 && "Window size for zero padding incorrect.");
    }

    /**
     * Tests the Edge Replication Padding Strategy
     *
     * Examines the edge replication padding method, which replicates the edge pixels of an image to pad the border. This
     * strategy is crucial for operations that require a seamless transition at the image boundaries, like blurring or
     * edge detection. The test confirms that the padding correctly replicates the edge pixel values, ensuring accurate
     * processing results.
     */
    void testEdgeReplication() {
        Image img(5, 5, 1, new unsigned char[25]{});
        auto window = Padding::getPixelWindow(img, 0, 0, 0, 3, PaddingType::EdgeReplication);

        // Expect the edge pixel values to be replicated
        // Edge pixel value is img.getData()[0], which is the first pixel in the image
        assert(window[0] == img.getData()[0] && "Edge replication at the corner failed.");
    }

    /**
     * Tests the Reflect Padding Strategy
     *
     * Evaluates the reflect padding strategy, where the image is padded with mirror reflections of itself at the borders.
     * This method is particularly useful for preserving the structural continuity of the image at its edges. The test
     * ensures that the reflection padding accurately mirrors adjacent pixel values, thereby supporting effective image
     * processing techniques.
     */
    void testReflectPadding() {
        Image img(5, 5, 1, new unsigned char[25]{});
        auto window = Padding::getPixelWindow(img, 0, 0, 0, 3, PaddingType::ReflectPadding);

        // Expect the corner pixel value to be the same as the adjacent pixel value
        // Note: The first pixel in the image is img.getData()[0]
        assert(window[0] == img.getData()[1 + 5] && "Reflect padding at the corner failed.");
    }

    /**
     * Executes All Defined Test Cases for Padding Strategies
     *
     * Facilitates the execution of all unit tests concerning various padding strategies employed in image processing. By
     * rigorously testing zero padding, edge replication, and reflect padding, this suite confirms the reliability and
     * effectiveness of padding methods, ensuring their proper function in critical image processing tasks.
     */
    virtual void runTests() override {
        runTest<TestPadding>(&TestPadding::testZeroPadding, "Zero Padding");
        runTest<TestPadding>(&TestPadding::testEdgeReplication, "Edge Replication");
        runTest<TestPadding>(&TestPadding::testReflectPadding, "Reflect Padding");
    }
};
