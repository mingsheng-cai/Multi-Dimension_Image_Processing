/**
 * @file TestEdgeFilter.h
 *
 * @brief Unit Tests for the EdgeFilter Class.
 *
 * This header file declares the TestEdgeFilter class, aimed at conducting unit tests on the EdgeFilter class,
 * which is responsible for applying various edge detection filters to images. It includes tests for Sobel, Prewitt,
 * Scharr, and Roberts edge detection algorithms, each evaluated through a simplified verification method focused on
 * detecting changes in the image's central region post-filter application. This method of testing serves as a proxy
 * for assessing the effectiveness of the edge detection algorithms in highlighting or identifying edges within an image.
 * While this testing approach provides a basic level of validation, more detailed and scenario-specific tests may be
 * necessary to fully ascertain the performance and reliability of each edge detection algorithm within the EdgeFilter class.
 *
 * Usage:
 * Derived from the Test base class, the TestEdgeFilter class implements the runTests method to execute all
 * defined test cases using the Test class's runTest template method. This facilitates a structured and comprehensive
 * evaluation of the EdgeFilter class's functionality within the broader image processing framework.
 *
 * @date Created on March 22, 2024.
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
#include "Filters/EdgeFilter.h"

#include <vector>
#include <cassert>
#include <iostream>

class TestEdgeFilter : public Test {
public:
    /**
     * Tests the Application of Edge Detection Algorithms
     *
     * Evaluates the EdgeFilter class's functionality by applying various edge detection algorithms to a simple grayscale
     * image with a clear edge pattern. This test verifies the algorithm's ability to highlight or identify edges within
     * the image. It focuses on the change in the image's central region as a simplified metric of effectiveness.
     *
     * @param filterType The type of edge detection filter to apply (e.g., Sobel, Prewitt, Scharr, Roberts).
     */
    void testEdgeDetection(FilterType filterType) {
        // Create a simple 5x5 image with a white border and a black center
        unsigned char imageData[25] = {
                255, 255, 255, 255, 255,
                255, 0,   0,   0,   255,
                255, 0,   255, 0,   255,
                255, 0,   0,   0,   255,
                255, 255, 255, 255, 255,
        };
        Image img(5, 5, 1, imageData);

        EdgeFilter edgeFilter(filterType, PaddingType::ZeroPadding);
        edgeFilter.apply(img);

        // Simple verification: check if the center pixel has been modified
        // After applying edge detection, the center pixel should not be 255
        assert(imageData[12] != 255 && "Edge detection failed to modify the image as expected.");
    }

    /**
     * Tests the Sobel Edge Detection Algorithm
     *
     * Initiates the edge detection test using the Sobel filter. This function specifically targets the Sobel algorithm's
     * capability in detecting edges within an image, using a predefined grayscale image with a clear edge pattern.
     */
    void testApplySobel() {
        testEdgeDetection(FilterType::Sobel);
    }

    /**
     * Tests the Prewitt Edge Detection Algorithm
     *
     * Initiates the edge detection test using the Prewitt filter. This function assesses the Prewitt algorithm's
     * performance in highlighting image edges, employing a straightforward test image to evaluate effectiveness.
     */
    void testApplyPrewitt() {
        testEdgeDetection(FilterType::Prewitt);
    }

    /**
     * Tests the Scharr Edge Detection Algorithm
     *
     * Initiates the edge detection test using the Scharr filter. This function evaluates the Scharr algorithm's
     * edge detection capabilities, using a simple test image to gauge how well it accentuates edges.
     */
    void testApplyScharr() {
        testEdgeDetection(FilterType::Scharr);
    }

    /**
     * Tests the Roberts Edge Detection Algorithm
     *
     * Initiates the edge detection test using the Roberts filter. This test examines the Roberts algorithm's
     * effectiveness in edge detection, employing a basic grayscale image with distinct edges for assessment.
     */
    void testApplyRoberts() {
        testEdgeDetection(FilterType::Roberts);
    }

    /**
     * Executes All Defined Test Cases for the EdgeFilter
     *
     * This function orchestrates the execution of all test cases defined in the TestEdgeFilter class. It utilizes
     * the runTest template method to execute each test case individually, focusing on the application of different
     * edge detection algorithms and their effectiveness in identifying edges within an image.
     */
    virtual void runTests() override {
        runTest<TestEdgeFilter>(&TestEdgeFilter::testApplySobel, "Apply Sobel Filter");
        runTest<TestEdgeFilter>(&TestEdgeFilter::testApplyPrewitt, "Apply Prewitt Filter");
        runTest<TestEdgeFilter>(&TestEdgeFilter::testApplyScharr, "Apply Scharr Filter");
        runTest<TestEdgeFilter>(&TestEdgeFilter::testApplyRoberts, "Apply Roberts Filter");
    }
};
