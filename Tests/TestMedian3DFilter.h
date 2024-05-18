/**
 * @file TestMedian3DFilter.h
 *
 * @brief Unit Tests for the Median3DFilter Class.
 *
 * This header file defines the TestMedian3DFilter class, designed for executing unit tests on the Median3DFilter class within the image processing library. The tests focus on assessing the filter's ability to effectively reduce noise in 3D volume data while preserving significant edges, a critical aspect for medical imaging and other applications requiring volume data processing. By employing a combination of statistical analysis and edge detection algorithms, the tests validate the filter's performance in enhancing data quality. Special attention is given to evaluating the filter's noise reduction efficacy and its capacity to maintain edge strength, ensuring the filter's applicability across various scenarios.
 *
 * Usage:
 * As an extension of the Test base class, the TestMedian3DFilter class implements the runTests method to systematically carry out all specified test cases, utilizing the Test class's runTest template method for individual test function execution. This approach facilitates a comprehensive and rigorous evaluation of the Median3DFilter's operational effectiveness in real-world volume data processing tasks.
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
#include "Filters/Median3DFilter.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <numeric>
#include <algorithm>

class TestMedian3DFilter : public Test {
private:
    /**
     * Calculates the Standard Deviation of Volume Data for Noise Level Assessment
     *
     * Determines the standard deviation of the provided 3D volume data, serving as a metric to evaluate the noise
     * level within the data. This calculation is fundamental in assessing the effectiveness of noise reduction
     * techniques applied to the volume data. A lower standard deviation post-filter application indicates a reduction
     * in noise, thereby enhancing the data quality for subsequent processing or analysis.
     *
     * @param data: A vector of unsigned chars representing the intensity values of voxels in the volume data.
     *
     * @return: The standard deviation of the volume data as a double.
     */
    double calculateStandardDeviation(const std::vector<unsigned char> &data) {
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0, std::plus<double>(),
                                           [mean](double a, double b) { return (a - mean) * (b - mean); });
        return std::sqrt(sq_sum / data.size());
    }

    /**
     * Estimates Edge Strength in Volume Data
     *
     * Utilizes Sobel operators to calculate the edge strength across the volume data. This method is pivotal
     * in assessing the Median3DFilter's ability to preserve edges while reducing noise. Edge strength, represented
     * as the gradient magnitude, provides insight into the filter's performance in maintaining critical structural
     * details within the volume data, which is especially crucial for applications like medical imaging.
     *
     * @param volume: The 3D volume data to evaluate for edge strength.
     *
     * @return: The average edge strength across the volume data as a double.
     */
    double calculateEdgeStrength(const Volume& volume) {
        double edgeStrength = 0.0;

        // Sobel kernels for X, Y, and Z directions
        int sobelX[3][3][3] = {
                {{-1, 0, 1}, {-3, 0, 3}, {-1, 0, 1}},
                {{-3, 0, 3}, {-6, 0, 6}, {-3, 0, 3}},
                {{-1, 0, 1}, {-3, 0, 3}, {-1, 0, 1}}
        };
        int sobelY[3][3][3] = {
                {{-1, -3, -1}, {0, 0, 0}, {1, 3, 1}},
                {{-3, -6, -3}, {0, 0, 0}, {3, 6, 3}},
                {{-1, -3, -1}, {0, 0, 0}, {1, 3, 1}}
        };
        int sobelZ[3][3][3] = {
                {{-1, -3, -1}, {-3, -6, -3}, {-1, -3, -1}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                {{1, 3, 1}, {3, 6, 3}, {1, 3, 1}}
        };

        for (int z = 1; z < volume.getDepth() - 1; ++z) {
            for (int y = 1; y < volume.getHeight() - 1; ++y) {
                for (int x = 1; x < volume.getWidth() - 1; ++x) {
                    double gx = 0, gy = 0, gz = 0;

                    // Apply Sobel kernels to the neighborhood of the voxel
                    for (int dz = -1; dz <= 1; ++dz) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            for (int dx = -1; dx <= 1; ++dx) {
                                unsigned char voxel = volume.getVoxel(x + dx, y + dy, z + dz);
                                gx += voxel * sobelX[dz + 1][dy + 1][dx + 1];
                                gy += voxel * sobelY[dz + 1][dy + 1][dx + 1];
                                gz += voxel * sobelZ[dz + 1][dy + 1][dx + 1];
                            }
                        }
                    }

                    // Calculate the magnitude of the gradient
                    double magnitude = sqrt(gx * gx + gy * gy + gz * gz);

                    // Add the magnitude to the total edge strength
                    edgeStrength += magnitude;
                }
            }
        }

        return edgeStrength / (volume.getWidth() * volume.getHeight() * volume.getDepth());
    }

public:
    /**
     * Tests Median Filtering on Volume Data
     *
     * Examines the Median3DFilter's performance in reducing noise within 3D volume data while preserving essential
     * edges. This test involves creating volume data with known noise patterns, applying median filtering, and
     * manually inspecting specific regions to confirm noise reduction and edge preservation. It validates the filter's
     * core functionality and its suitability for processing volume data in various applications.
     */
    void testApplyMedianFilter() {
        // Create a 5x5x5 volume with random noise
        int width = 5, height = 5, depth = 5;
        std::vector<unsigned char> data(width * height * depth);
        // Initialize the volume with random noise
        // Create a 5x5x5 volume with random noise
        for (int i = 0; i < width * height * depth; ++i) {
            data[i] = rand() % 256; // Random noise
        }
        Volume volume(width, height, depth, data.data());

        // Apply the median filter
        Median3DFilter medianFilter(3); // Use a 3x3x3 kernel
        medianFilter.apply(volume);

        // Check the values near the center to ensure noise has been reduced
        const unsigned char *filteredData = volume.getData();

        // Check that the center value is closer to the neighbor value
        unsigned char centerValue = filteredData[62]; // Select a central point for comparison
        unsigned char neighborValue = filteredData[37];

        // Simple verification: check if the center value is closer to the neighbor value
        assert(abs(centerValue - neighborValue) < 20 && "Median filter did not reduce noise as expected.");

        std::cout << "Median3DFilter application test passed." << std::endl;
    }

    /**
     * Evaluates the Effectiveness of Median Filtering
     *
     * Conducts a quantitative analysis on the impact of median filtering on 3D volume data. By comparing standard
     * deviations and edge strengths before and after filtering, this test assesses the filter's effectiveness in
     * noise reduction and edge preservation. The results confirm the Median3DFilter's capability in enhancing
     * volume data quality, which is essential for accurate image analysis and interpretation.
     */
    void testMedianFilterEffectiveness() {
        // Initialize a 10x10x10 volume with random noise
        int width = 10, height = 10, depth = 10;
        std::vector<unsigned char> noisyData(width * height * depth);
        // Random noise initialization
        std::generate(noisyData.begin(), noisyData.end(), []() { return rand() % 256; });

        Volume noisyVolume(width, height, depth, noisyData.data());

        // Calculate the standard deviation and edge strength before filtering
        double stdDevBefore = calculateStandardDeviation(noisyData);
        // Calculate the edge strength before filtering
        double edgeStrengthBefore = calculateEdgeStrength(noisyVolume);

        // Apply the median filter
        Median3DFilter filter(3); // 使用3x3x3的核心大小
        filter.apply(noisyVolume);

        // Extract the filtered data
        const unsigned char *filteredData = noisyVolume.getData();

        // Calculate the standard deviation and edge strength after filtering
        double stdDevAfter = calculateStandardDeviation(std::vector<unsigned char>(filteredData, filteredData + width * height * depth));
        double edgeStrengthAfter = calculateEdgeStrength(noisyVolume);

        // Check that the standard deviation has decreased after filtering
        assert(stdDevBefore > stdDevAfter && "Median filter did not effectively reduce noise.");

        // Check that the edge strength has been preserved after filtering
        // After filtering, the edge strength should be greater or equal to the original value
        assert(edgeStrengthAfter >= edgeStrengthBefore && "Median filter did not preserve edge strength.");

        std::cout << "Test passed: Median filter effectively reduces noise while preserving edges." << std::endl;
    }

    /**
     * Executes All Defined Test Cases for the Median3DFilter Class
     *
     * Coordinates the execution of all unit tests related to the Median3DFilter class's functionalities, focusing
     * on noise reduction and edge preservation in 3D volume data. This comprehensive test suite verifies the filter's
     * effectiveness and reliability, ensuring its suitability for enhancing volume data quality in various processing
     * tasks and applications.
     */
    virtual void runTests() override {
        runTest<TestMedian3DFilter>(&TestMedian3DFilter::testApplyMedianFilter, "Apply Median3DFilter");
        runTest<TestMedian3DFilter>(&TestMedian3DFilter::testMedianFilterEffectiveness, "Test Median filter effectiveness");
    }
};


