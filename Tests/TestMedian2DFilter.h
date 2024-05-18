/**
 * @file TestMedian2DFilter.h
 *
 * @brief Unit Tests for the Median2DFilter Class.
 *
 * This header file defines the TestMedian2DFilter class, which is responsible for conducting unit tests on the
 * Median2DFilter class within the image processing library. The tests aim to assess the filter's efficacy in
 * noise reduction, edge handling, and detail preservation in 2D images. By applying the median filter with
 * different padding strategies and kernel sizes, these tests evaluate the filter's performance across a variety
 * of scenarios, ensuring its reliability in enhancing image quality. Specific tests include verifying the
 * application of the filter on images with distinct patterns, analyzing the filter's noise reduction capabilities
 * on images with salt-and-pepper noise, examining the preservation of fine details, and assessing the handling
 * of image edges through different padding methods.
 *
 * Usage:
 * Derived from the Test base class, the TestMedian2DFilter class implements the runTests method to execute
 * all defined test cases, utilizing the Test class's runTest template method for each specific test function.
 * This methodological approach guarantees a thorough evaluation of the Median2DFilter's functionality, making
 * it an essential part of ensuring the quality and effectiveness of the image processing operations.
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
#include "Filters/Median2DFilter.h"

#include <vector>
#include <cassert>

class TestMedian2DFilter : public Test {
public:
    /**
     * Unit test for the application of the median filter on a grayscale image.
     *
     * Tests the application of the median filter on a grayscale image using a 3x3 kernel and zero padding.
     * This test verifies the filter's ability to correctly calculate the median value in a simple scenario
     * and apply it to a small image. It checks whether the median filter maintains or enhances image quality
     * by preserving significant details while reducing noise.
     */
    void testApplyMedianFilter() {
        // Create a simple 5x5 image with a distinct pattern
        Image img(5, 5, 1, new unsigned char[25]{
                10, 10, 80, 80, 10,
                10, 80, 80, 80, 10,
                80, 80, 80, 80, 80,
                10, 80, 80, 80, 10,
                10, 10, 80, 10, 10
        });

        // Apply the median filter with a 3x3 kernel and zero padding
        Median2DFilter medianFilter(3, PaddingType::ZeroPadding);
        medianFilter.apply(img);

        // Check the center pixel value after filtering
        unsigned char* data = img.getData();
        // Expected center value is 80, which is the median of the 3x3 kernel
        unsigned char expectedCenterValue = 80;
        assert(data[12] == expectedCenterValue && "Median filter application failed at center pixel.");

        std::cout << "Median2DFilter application test passed." << std::endl;
    }

    /**
     * Unit test for evaluating the median filter's edge handling capability with reflective padding.
     *
     * Evaluates the median filter's edge handling capability with reflective padding.
     * This test examines if the filter correctly handles image edges by ensuring that
     * reflective padding maintains the continuity and appearance of the image's edges,
     * thus avoiding the introduction of artifacts or distortions at the boundaries.
     */
    void testEdgeHandling() {
        // Image with a distinct pattern for edge handling test
        Image img(5, 5, 1, new unsigned char[25]{
                0, 255, 0, 255, 0,
                255, 0, 255, 0, 255,
                0, 255, 0, 255, 0,
                255, 0, 255, 0, 255,
                0, 255, 0, 255, 0
        });

        Median2DFilter filter(3, PaddingType::ReflectPadding);
        filter.apply(img);

        // Check the corner pixel values after filtering
        unsigned char* data = img.getData();
        assert(data[0] != 0 && data[0] != 255 && "Edge handling failed for top-left corner.");
        assert(data[24] != 0 && data[24] != 255 && "Edge handling failed for bottom-right corner.");
    }

    /**
     * Unit test for evaluating the median filter's noise reduction capability.
     *
     * Evaluates the median filter's noise reduction capability by applying it to an image with salt-and-pepper noise.
     * This test assesses the filter's effectiveness in reducing noise by checking if the filter successfully
     * replaces noisy pixels with the median value of the surrounding pixels, thereby enhancing image quality.
     */
    void testNoiseReduction() {
        Image img(5, 5, 1, new unsigned char[25]{
                255, 0, 255, 0, 255,
                0, 255, 0, 255, 0,
                255, 0, 255, 0, 255,
                0, 255, 0, 255, 0,
                255, 0, 255, 0, 255
        });

        Median2DFilter filter(3, PaddingType::ZeroPadding);
        filter.apply(img);

        // Check the middle row pixel values after filtering
        unsigned char* data = img.getData();
        for (int i = 6; i <= 8; ++i) {
            assert(data[i] == 255 && "Noise reduction failed in the middle row.");
        }
    }

    /**
     * Unit test for evaluating the median filter's detail preservation capability.
     *
     * Evaluates the median filter's detail preservation capability by applying it to an image with a thin line.
     * This test verifies if the filter maintains fine details in the image by checking if the filter retains
     * the line's presence after processing. The test ensures that the filter does not blur or distort the line,
     * demonstrating its ability to preserve essential image features during noise reduction.
     */
    void testDetailPreservation() {
        // Generate a 5x5 image with a thin line in the center
        Image img(5, 5, 1, new unsigned char[25]{
                255, 255, 255, 255, 255,
                255, 255, 255, 255, 255,
                0, 0, 0, 0, 0,
                255, 255, 255, 255, 255,
                255, 255, 255, 255, 255
        });

        Median2DFilter filter(3, PaddingType::ZeroPadding);
        filter.apply(img);

        // Check if the line is preserved after filtering
        unsigned char* data = img.getData();
        bool detailPreserved = false;
        for (int i = 10; i < 15; ++i) {
            if (data[i] != 255) {
                detailPreserved = true;
                break;
            }
        }
        assert(detailPreserved && "Detail preservation failed for the center line.");
    }

    /**
     * Executes all unit tests for the Median2DFilter class.
     *
     * Runs all defined test cases for the Median2DFilter class, including tests for applying the filter,
     * handling image edges, reducing noise, and preserving fine details. This method ensures a comprehensive
     * evaluation of the filter's performance in various scenarios, verifying its reliability and effectiveness
     * in enhancing image quality through noise reduction and detail preservation.
     */
    virtual void runTests() override {
        runTest<TestMedian2DFilter>(&TestMedian2DFilter::testApplyMedianFilter, "Apply Median2DFilter");
        runTest<TestMedian2DFilter>(&TestMedian2DFilter::testEdgeHandling, "Edge Handling");
        runTest<TestMedian2DFilter>(&TestMedian2DFilter::testNoiseReduction, "Noise Reduction");
        runTest<TestMedian2DFilter>(&TestMedian2DFilter::testDetailPreservation, "Detail Preservation");
    }
};
