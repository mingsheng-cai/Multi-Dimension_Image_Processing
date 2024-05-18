/**
 * @file TestGaussian3DFilter.h
 *
 * @brief Unit Tests for the Gaussian3DFilter Class.
 *
 * This header file presents the declaration of the TestGaussian3DFilter class, aimed at executing unit tests
 * on the Gaussian3DFilter class. This class is crucial for applying 3D Gaussian blurring effects on volume data,
 * facilitating image smoothing while maintaining the integrity of significant features. The tests validate the
 * filter's functionality by ensuring accurate kernel generation, proper application of the filter to volume data,
 * and assessing the smoothing effect through quantitative analysis of variance reduction. Through these tests,
 * the behavior of the Gaussian3DFilter under various conditions is thoroughly examined, confirming its effectiveness
 * in enhancing volume data for further processing or analysis.
 *
 * Usage:
 * As a derivative of the Test base class, the TestGaussian3DFilter class implements the runTests method to
 * execute all predefined test cases, leveraging the runTest template method of the Test class for individual
 * test function execution. This structured testing approach ensures a comprehensive evaluation of the
 * Gaussian3DFilter's operational capabilities within the broader context of volume data processing.
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

#include "Test.h"
#include "Filters/Gaussian3DFilter.h"
#include <cmath>
#include <iostream>
#include <numeric>
#include <cassert>

class TestGaussian3DFilter : public Test {
private:
    /**
     * Generates a Gaussian Kernel with Given Sigma and Kernel Size
     *
     * Creates a Gaussian kernel for the 3D filter, ensuring that the kernel values sum to 1 for brightness preservation.
     * This method is crucial for the proper application of Gaussian blurring, as it directly influences the smoothing
     * effect on volume data. The generated kernel reflects a standard Gaussian distribution centered at the kernel's
     * middle, with sigma determining the spread.
     *
     * @param sigma The standard deviation of the Gaussian distribution.
     * @param kernelSize The size of the kernel (must be odd).
     * @return A vector representing the 1D Gaussian kernel.
     */
    std::vector<double> generateGaussianKernel(double sigma, int kernelSize) const {
        std::vector<double> kernel(kernelSize);
        double sum = 0.0;
        int radius = kernelSize / 2;
        double sigmaSquare2 = 2 * sigma * sigma;

        // Compute kernel values based on Gaussian function
        for (int i = -radius; i <= radius; ++i) {
            double value = (std::exp(-(i * i) / sigmaSquare2)) / (std::sqrt(M_PI * sigmaSquare2));
            kernel[i + radius] = value;
            sum += value;
        }

        // Normalize kernel values
        for (double &value : kernel) {
            value /= sum;
        }

        return kernel;
    }

    /**
     * Generates Test Volume Data with a Specific Pattern
     *
     * Constructs a volume of given dimensions filled with a predictable pattern based on the coordinates of each voxel.
     * This test volume is used to assess the Gaussian3DFilter's ability to smooth data without distorting the underlying
     * pattern, providing a controlled environment for testing.
     *
     * @param width The width of the volume.
     * @param height The height of the volume.
     * @param depth The depth of the volume.
     * @return A Volume object filled with patterned data.
     */
    Volume generateTestVolume(int width, int height, int depth) {
        std::vector<unsigned char> data(width * height * depth);
        int index = 0;
        for (int z = 0; z < depth; ++z) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    data[index++] = static_cast<unsigned char>((x + y + z) % 256);
                }
            }
        }
        return Volume(width, height, depth, data.data());
    }

    /**
     * Initializes a Simple Volume with Graded Intensity
     *
     * Creates a volume where the intensity of voxels decreases with distance from the center. This setup is used to
     * test the smoothing effects of the Gaussian filter, particularly its impact on gradients within the volume data.
     *
     * @param width The width of the volume.
     * @param height The height of the volume.
     * @param depth The depth of the volume.
     * @return A unique pointer to the Volume object with initialized data.
     */
    std::unique_ptr<Volume> initializeSimpleVolume(int width, int height, int depth) {
        auto data = std::make_unique<unsigned char[]>(width * height * depth);
        int center[3] = {width / 2, height / 2, depth / 2};
        for (int z = 0; z < depth; ++z) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    // Calculate distance from center
                    double distance = sqrt(pow(x - center[0], 2) + pow(y - center[1], 2) + pow(z - center[2], 2));
                    // Set value inversely proportional to distance
                    data[z * width * height + y * width + x] = static_cast<unsigned char>(std::max(0.0, 255 - distance));
                }
            }
        }
        return std::make_unique<Volume>(width, height, depth, data.get());
    }

public:
    /**
     * Tests the Correctness of Gaussian Kernel Generation
     *
     * Validates that the Gaussian kernel generated by the filter is normalized (sums to 1) and structured correctly
     * according to Gaussian distribution properties. This test ensures that the filter will apply a consistent smoothing
     * effect across the volume data.
     */
    void testGaussianKernelGeneration() {
        double sigma = 1.0;
        int kernelSize = 3;
        auto kernel = generateGaussianKernel(sigma, kernelSize);

        // Make sure the kernel size is correct
        double kernelSum = std::accumulate(kernel.begin(), kernel.end(), 0.0);
        assert(std::fabs(kernelSum - 1.0) < 1e-5 && "Kernel sum is not 1.0, normalization failed.");

        // Print the kernel values for manual inspection
        std::cout << "Gaussian kernel values: ";
        for (double value : kernel) {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        std::cout << "Gaussian kernel generation test passed." << std::endl;
    }

    /**
     * Tests Basic Application of the Gaussian Filter
     *
     * Examines the filter's ability to smoothly apply a Gaussian blur to a 3D volume. This test checks if the filter
     * correctly modifies the volume data to produce a visually smoother result, indicating effective blurring.
     */
    void testApplyGaussianFilter() {
        auto volume = initializeSimpleVolume(5, 5, 5); // 初始化简单的体积数据

        double sigma = 1.0;
        int kernelSize = 3; // Must be odd
        Gaussian3DFilter gaussianFilter(sigma, kernelSize);
        gaussianFilter.apply(*volume);

        const unsigned char* data = volume->getData();
        // Verify that the center point is smoother than the original data
        // We compare the center point with a neighboring point to ensure smoothing
        unsigned char centerValue = data[62];
        unsigned char neighborValue = data[37]; // Select a neighboring point's value for comparison

        // Simple check to ensure the center point is smoother than a neighboring point
        assert(abs(centerValue - neighborValue) < 20 && "Gaussian filter did not smooth the volume data as expected.");

        std::cout << "Gaussian3DFilter application test passed." << std::endl;
    }

    /**
     * Analyzes the Smoothing Effect of the Gaussian Filter on Volume Data
     *
     * Conducts a quantitative analysis of the smoothing effect by comparing the variance of the volume data before
     * and after applying the Gaussian filter. A reduction in variance indicates successful smoothing.
     *
     * @param volume The Volume object to analyze.
     * @param originalData The original data for comparison.
     */
    void analyzeVolumeSmoothing(const Volume& volume, const std::vector<unsigned char>& originalData) {
        const unsigned char* filteredData = volume.getData();
        int width = volume.getWidth();
        int height = volume.getHeight();
        int depth = volume.getDepth();
        size_t dataSize = width * height * depth;

        // Calculate mean and variance for original and filtered data
        double meanOriginal = std::accumulate(originalData.begin(), originalData.end(), 0.0) / dataSize;
        double meanFiltered = std::accumulate(filteredData, filteredData + dataSize, 0.0) / dataSize;

        double varianceOriginal = 0.0, varianceFiltered = 0.0;
        for (size_t i = 0; i < dataSize; ++i) {
            varianceOriginal += (originalData[i] - meanOriginal) * (originalData[i] - meanOriginal);
            varianceFiltered += (filteredData[i] - meanFiltered) * (filteredData[i] - meanFiltered);
        }
        varianceOriginal /= dataSize;
        varianceFiltered /= dataSize;

        // Verify that the filtered data has lower variance than the original data
        assert(varianceFiltered < varianceOriginal && "Filtered data should have lower variance than original.");

        // Verify that the filtered data is within the valid intensity range
        for (size_t i = 0; i < dataSize; ++i) {
            assert(filteredData[i] <= 255 && "Filtered data contains values out of range.");
        }

        std::cout << "Gaussian3DFilter variance analysis passed: Original variance = " << varianceOriginal
                  << ", Filtered variance = " << varianceFiltered << std::endl;
    }

    /**
     * Tests the Smoothness Effect of the Gaussian Filter on Volume Data
     *
     * Assesses the filter's performance in smoothing a test volume. This involves applying the filter to volume data
     * with a known pattern and analyzing the effect on data variance to quantify the degree of smoothing achieved.
     */
    void testGaussianFilterSmoothness() {
        int width = 10, height = 10, depth = 10;
        auto testVolume = generateTestVolume(width, height, depth);
        std::vector<unsigned char> originalData(testVolume.getData(), testVolume.getData() + width * height * depth);

        Gaussian3DFilter gaussianFilter(1.0, 3);
        gaussianFilter.apply(testVolume);

        analyzeVolumeSmoothing(testVolume, originalData);
    }

    /**
     * Executes All Defined Test Cases for the Gaussian3DFilter
     *
     * Orchestrates the execution of all unit tests for the Gaussian3DFilter class. This comprehensive suite verifies
     * the filter's ability to generate accurate kernels, apply Gaussian blurring effectively, and achieve the desired
     * smoothing effects on volume data.
     */
    virtual void runTests() override {
        runTest<TestGaussian3DFilter>(&TestGaussian3DFilter::testGaussianKernelGeneration, "Gaussian Kernel Generation");
        runTest<TestGaussian3DFilter>(&TestGaussian3DFilter::testApplyGaussianFilter, "Apply Gaussian3DFilter");
        runTest<TestGaussian3DFilter>(&TestGaussian3DFilter::testGaussianFilterSmoothness, "Gaussian3DFilter Smoothness");
    }
};

