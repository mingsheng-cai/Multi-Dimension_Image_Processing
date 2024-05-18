/**
 * @file TestGaussian2DFilter.h
 *
 * @brief Unit Tests for the Gaussian2DFilter Class.
 *
 * This header file contains the declaration of the TestGaussian2DFilter class, which is designed to perform
 * comprehensive unit tests on the Gaussian2DFilter class. This class is a key component of the image processing
 * library, responsible for applying Gaussian blurring to images. The tests verify the Gaussian filter's correctness
 * and effectiveness, focusing on aspects such as kernel generation, the application of Gaussian blur, the quantifiable
 * effect of blurring on image variance, and the impact of the sigma value on the blurring intensity. These tests
 * ensure that the Gaussian2DFilter behaves as expected, maintaining image brightness while achieving the desired
 * smoothing effect, and handling images with varying gradients and textures appropriately.
 *
 * Usage:
 * Derived from the Test base class, the TestGaussian2DFilter class implements the runTests method to execute all
 * defined test cases using the Test class's runTest template method. This structured approach enables a rigorous
 * evaluation of the Gaussian2DFilter class's functionality within the larger image processing framework.
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
#include "Filters/Gaussian2DFilter.h"
#include "Image.h"

#include <cassert>
#include <iostream>
#include <memory>

class TestGaussian2DFilter : public Test {
private:
    double calculateVariance(const Image &img) {
        double sum = 0.0;
        double sumSquared = 0.0;
        int pixelCount = img.getWidth() * img.getHeight();
        for (int i = 0; i < pixelCount; ++i) {
            double pixelValue = static_cast<double>(img.getData()[i]);
            sum += pixelValue;
            sumSquared += pixelValue * pixelValue;
        }
        double mean = sum / pixelCount;
        double variance = (sumSquared / pixelCount) - (mean * mean);
        return variance;
    }

public:
    /**
     * Tests the Generation of the Gaussian Kernel
     *
     * Verifies the Gaussian2DFilter's ability to generate a Gaussian kernel with specified dimensions and sigma value.
     * The kernel's sum must equal 1 to maintain image brightness, and its center value should be the maximum, reflecting
     * the characteristics of a Gaussian distribution. This test ensures the kernel is constructed correctly, which is
     * crucial for achieving the desired blurring effect.
     */
    void testKernelGeneration() {
        // Use a 5x5 kernel with σ=1.0
        Gaussian2DFilter filter(5, 1.0, PaddingType::ZeroPadding);
        auto kernel = filter.getKernel();

        // Check the sum of kernel elements is 1 to ensure it is a valid Gaussian kernel
        double sum = 0.0;
        for (const auto &row: kernel) {
            for (double value: row) {
                sum += value;
            }
        }
        assert(std::fabs(sum - 1.0) < 1e-5 && "The sum of Gaussian kernel elements is not 1.");

        // Check the center value is the maximum value in the kernel
        double centerValue = kernel[kernel.size() / 2][kernel[0].size() / 2];
        for (const auto &row: kernel) {
            for (double value: row) {
                assert(centerValue >= value && "Center value is not the maximum in the Gaussian kernel.");
            }
        }

        std::cout << "Gaussian kernel generation test passed." << std::endl;
    }

    /**
     * Tests Basic Application of Gaussian Blur
     *
     * Evaluates the Gaussian2DFilter's performance in applying a Gaussian blur to an image. This test uses a gradient
     * image to assess how well the filter smooths transitions between different intensity levels. The goal is to verify
     * the filter's effectiveness in reducing image sharpness while preserving overall image integrity.
     */
    void testApplyGaussianBlur() {
        // Create a simple 10x10 image with a gradient pattern
        std::unique_ptr<unsigned char[]> imgData(new unsigned char[100]);
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                imgData[y * 10 + x] = static_cast<unsigned char>(255 - (std::abs(x - 5) + std::abs(y - 5)) * 10);
            }
        }
        Image img(10, 10, 1, imgData.get());

        // Apply Gaussian blur with σ=1.0
        Gaussian2DFilter gaussianFilter(3, 1.0, PaddingType::ZeroPadding);
        gaussianFilter.apply(img);

        // Check if the blurring effect is as expected
        unsigned char* data = img.getData();

        // Check the blurring effect by comparing the central pixels with their neighbors
        bool blurEffectValid = true;
        for (int i = 11; i < 89; ++i) { // 避免边缘像素
            if (i % 10 == 0 || i % 10 == 9) continue; // 避免边缘像素

            unsigned char centerPixel = data[i];
            unsigned char sum = 0;
            int count = 0;

            // Calculate the average of the 3x3 neighborhood
            for (int j = -1; j <= 1; ++j) {
                for (int k = -1; k <= 1; ++k) {
                    int idx = i + j * 10 + k;
                    sum += data[idx];
                    count++;
                }
            }

            unsigned char average = sum / count;
            if (std::abs(centerPixel - average) >= 10) { // Simple check for blurring effect
                blurEffectValid = false;
                break;
            }
        }

        assert(blurEffectValid && "Blurring effect not as expected.");

        std::cout << "Gaussian blur application test passed." << std::endl;
    }

    /**
     * Quantifies the Blurring Effect of the Gaussian Filter
     *
     * Measures the impact of the Gaussian blur on an image's variance. By comparing the variance of pixel values before
     * and after applying the filter, this test quantifies the smoothing effect of the filter. A significant reduction
     * in variance indicates effective blurring, which is essential for applications requiring image smoothing.
     */
    void testBlurringEffect() {
        // Initialize a simple 5x5 image with a gradient pattern
        unsigned char testData[25];
        for (int i = 0; i < 25; ++i) {
            testData[i] = static_cast<unsigned char>((i * 10) % 256); // Use 0-240 range
        }
        Image img(5, 5, 1, testData);

        // Calculate the original variance of the image
        double originalVariance = calculateVariance(img);

        // Apply Gaussian blur with σ=1.0
        Gaussian2DFilter filter(5, 1.0, PaddingType::ZeroPadding);
        filter.apply(img);

        // Calculate the variance of the blurred image
        double blurredVariance = calculateVariance(img);

        // Check if the blurring effect is as expected
        assert(blurredVariance < originalVariance && "Blurring did not reduce the image variance as expected.");

        std::cout << "Gaussian blurring effect test passed. Original Variance: " << originalVariance << ", Blurred Variance: " << blurredVariance << std::endl;
    }

    /**
     * Evaluates the Impact of Sigma on Blurring Intensity
     *
     * Investigates how different sigma values influence the intensity of the Gaussian blur applied by the filter. The
     * test compares the effects of small and large sigma values on image smoothing, expecting a larger sigma to produce
     * a more pronounced blurring effect. This evaluation helps in understanding the filter's behavior across various
     * blurring strengths.
     */
    void testSigmaImpact() {
        int width = 5, height = 5, channels = 1;
        unsigned char originalData[25];
        // Use a simple gradient pattern for the test image
        for (int i = 0; i < 25; ++i) {
            originalData[i] = static_cast<unsigned char>(i * 10);
        }

        // First instantiate an image and apply a small σ value Gaussian filter
        Image img1(width, height, channels, originalData);
        Gaussian2DFilter filterSmallSigma(5, 0.5, PaddingType::ZeroPadding);
        filterSmallSigma.apply(img1);
        double smallSigmaVariance = calculateVariance(img1);

        // Second, apply a larger σ value Gaussian filter to the same image
        Image img2(width, height, channels, originalData);
        Gaussian2DFilter filterLargeSigma(5, 2.0, PaddingType::ZeroPadding);
        filterLargeSigma.apply(img2);
        double largeSigmaVariance = calculateVariance(img2);

        // Verify that the larger sigma results in more blurring
        assert(largeSigmaVariance < smallSigmaVariance && "A larger sigma did not result in more blurring.");

        std::cout << "Sigma impact on blurring effect test passed." << std::endl;
    }

    /**
     * Executes All Defined Test Cases for the Gaussian2DFilter
     *
     * Coordinates the execution of all test cases defined in the TestGaussian2DFilter class, focusing on the Gaussian
     * filter's kernel generation, application effectiveness, and the quantifiable impact of its use on images. This
     * comprehensive testing suite ensures the Gaussian2DFilter's reliability and efficacy in image processing tasks.
     */
    virtual void runTests() override {
        runTest<TestGaussian2DFilter>(&TestGaussian2DFilter::testKernelGeneration, "Kernel Generation");
        runTest<TestGaussian2DFilter>(&TestGaussian2DFilter::testApplyGaussianBlur, "Apply Gaussian Blur");
        runTest<TestGaussian2DFilter>(&TestGaussian2DFilter::testBlurringEffect, "Blurring Effect");
        runTest<TestGaussian2DFilter>(&TestGaussian2DFilter::testSigmaImpact, "Sigma Impact");
    }
};
