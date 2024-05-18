/**
 * @file main.cpp
 *
 * @brief Entry Point for the Unit Testing Framework.
 *
 * This file acts as the entry point for the comprehensive unit testing framework designed to verify the
 * correctness and functionality of various image processing algorithms and utilities. It includes tests
 * for classes such as TestAlgorithm, TestImage, TestProjection, TestSlice, TestVolume, TestPadding,
 * TestPixelFilter, TestBox2DFilter, TestGaussian2DFilter, TestMedian2DFilter, TestEdgeFilter,
 * TestGaussian3DFilter, TestMedian3DFilter, and other related test classes. Each class targets specific
 * functionalities within the image processing library, ensuring that operations such as filtering, projection,
 * slicing, and volume manipulation work as expected. The STB Image library is utilized for image reading and
 * writing operations, underlining the framework's reliance on external libraries for handling image data.
 * The main function orchestrates the initiation and execution of all unit tests, aggregating and presenting
 * the results to provide a clear overview of the test outcomes.
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


#include "TestAlgorithm.h"
#include "TestImage.h"
#include "TestProjection.h"
#include "TestSlice.h"
#include "TestVolume.h"
#include "TestPadding.h"
#include "TestPixelFilter.h"
#include "TestBox2DFilter.h"
#include "TestGaussian2DFilter.h"
#include "TestMedian2DFilter.h"
#include "TestEdgeFilter.h"
#include "TestGaussian3DFilter.h"
#include "TestMedian3DFilter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

int main() {
    // Create test objects
    TestAlgorithm testAlgorithm;
    TestBox2DFilter testBox2DFilter;
    TestEdgeFilter testEdgeFilter;
    TestGaussian2DFilter testGaussian2DFilter;
    TestGaussian3DFilter testGaussian3DFilter;
    TestImage testImage;
    TestMedian2DFilter testMedian2DFilter;
    TestMedian3DFilter testMedian3DFilter;
    TestPadding testPadding;
    TestPixelFilter testPixelFilter;
    TestProjection testProjection;
    TestSlice testSlice;
    TestVolume testVolume;

    // Run tests
    testAlgorithm.runTests();
    testBox2DFilter.runTests();
    testEdgeFilter.runTests();
    testGaussian2DFilter.runTests();
    testGaussian3DFilter.runTests();
    testImage.runTests();
    testMedian2DFilter.runTests();
    testMedian3DFilter.runTests();
    testPadding.runTests();
    testPixelFilter.runTests();
    testProjection.runTests();
    testSlice.runTests();
    testVolume.runTests();

    Test::summarize();  // Output test results

    return 0;
}