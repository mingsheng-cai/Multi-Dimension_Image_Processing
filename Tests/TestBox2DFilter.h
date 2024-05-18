/**
 * @file TestBox2DFilter.h
 *
 * @brief Unit Tests for the Box2DFilter Class.
 *
 * This header file declares the TestBox2DFilter class, designed to conduct unit tests specifically on the
 * Box2DFilter class, a component of the image processing library that applies a 2D box filter to images.
 * The tests aim to verify the filter's behavior under various conditions, including its application to
 * uniform images, images with gradients, and images requiring different padding strategies at the edges.
 * Key aspects such as the preservation of uniformity, the smoothing effect on gradients, and the effectiveness
 * of edge handling with different padding methods (zero padding and reflect padding) are evaluated. Additionally,
 * the impact of filter kernel size on image smoothing is assessed through variance calculations, ensuring the
 * filter's effectiveness across a range of scenarios.
 *
 * Usage:
 * Derived from the Test base class, the TestBox2DFilter class implements the runTests method to execute
 * all defined test cases using the Test class's runTest template method. This enables comprehensive testing
 * of the Box2DFilter class's functionalities within the broader image processing framework.
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

#include "Filters/Box2DFilter.h"
#include "Test.h"
#include "Image.h"

#include <cassert>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <cmath> // For std::pow and std::sqrt

class TestBox2DFilter : public Test {
private:
    /**
     * Calculates the Variance of Pixel Values in an Image
     *
     * Computes the variance of pixel values in an image to assess the distribution of pixel intensities. The variance
     * provides a measure of the spread of pixel values around the mean, indicating the level of contrast and detail
     * present in the image. This function calculates the variance by first computing the mean pixel value and then
     * summing the squared differences between each pixel value and the mean. The final variance is obtained by dividing
     * this sum by the total number of pixels.
     *
     * @param image The Image object for which to calculate the variance
     * @return The variance of pixel values in the image
     */
    double calculateVariance(const Image &image) {
        unsigned char *data = image.getData();
        int totalPixels = image.getWidth() * image.getHeight();
        int channels = image.getChannels();

        // Calculate the average pixel value
        double sum = 0.0;
        for (int i = 0; i < totalPixels; ++i) {
            // Only consider the first channel for simplicity
            sum += data[i * channels];
        }
        double mean = sum / totalPixels;

        // Calculate the variance
        double variance = 0.0;
        for (int i = 0; i < totalPixels; ++i) {
            variance += std::pow(data[i * channels] - mean, 2);
        }
        variance /= totalPixels;

        return variance;
    }

public:
    /**
     * Tests the Application of the Box2DFilter on a Uniform Image
     *
     * Evaluates the Box2DFilter's ability to maintain the uniformity of an image when applied. The test involves applying
     * the filter to an image filled entirely with a single pixel value (e.g., all white) and verifying that the output
     * remains uniform. This test is crucial for ensuring that the filter does not inadvertently introduce gradients or
     * artifacts into images that are expected to remain constant.
     */
    void testUniformImage() {
        Image img(5, 5, 1, new unsigned char[25]); // Create a 5x5 image
        std::fill_n(img.getData(), 25, 255); // Set all pixels to white

        Box2DFilter filter(3, PaddingType::ZeroPadding);
        filter.apply(img);

        // If the input image is uniform, the output should also be uniform
        for (int i = 0; i < 25; ++i) {
            assert(img.getData()[i] == 255 && "Filtering a uniform image failed to produce uniform output.");
        }
    }

    /**
     * Tests Edge Padding Strategies with the Box2DFilter
     *
     * Examines how the Box2DFilter handles image edges using different padding strategies, such as zero padding and
     * reflect padding. The test checks whether the filter's edge handling preserves image content accurately or introduces
     * distortions. This aspect is vital for ensuring that the filter performs well even at the boundaries of the image,
     * where padding becomes necessary.
     */
    void testEdgePadding() {
        // Create a simple test image with a clear gradient from left to right
        Image img(3, 3, 1, new unsigned char[9]{255, 255, 255, 255, 0, 255, 255, 255, 255});
        Box2DFilter filter(3, PaddingType::ZeroPadding); // Use zero padding
        filter.apply(img);

        // Apply the filter and check the edge pixels
        assert(img.getData()[4] <= 0 && "Edge padding with zero padding did not produce expected results.");
    }

    /**
     * Tests the Effectiveness of the Box2DFilter on an Image with a Gradient
     *
     * Assesses the Box2DFilter's ability to smooth out gradients in an image. This test involves applying the filter to
     * an image with a linear gradient and examining the smoothness of the result. The goal is to confirm that the filter
     * effectively reduces the sharpness of gradients, indicative of its smoothing capabilities.
     */
    void testGradientImage() {
        // Create a simple gradient image with 5 pixels
        Image img(5, 1, 1, new unsigned char[5]{0, 64, 128, 192, 255});
        Box2DFilter filter(3, PaddingType::ZeroPadding);
        filter.apply(img);

        // Validate the output image by checking the smoothed gradient
        assert(img.getData()[2] >= 120 && img.getData()[2] <= 136 &&
               "Filtering a gradient image did not produce smoothed output as expected.");
    }

    /**
     * Evaluates the Impact of Large Kernel Sizes on Image Smoothing
     *
     * Investigates how increasing the kernel size of the Box2DFilter affects its smoothing effect on images. The test
     * compares the variance of the image's pixel values before and after applying the filter with a large kernel, with
     * the expectation that a larger kernel will result in more significant smoothing and thus a lower variance.
     */
    void testLargeKernelFiltering() {
        // 初始化具有某种模式的图像数据，这里使用一个简单的5x5图像进行示例
        unsigned char imageData[25] = {
                10, 20, 30, 40, 50,
                60, 70, 80, 90, 100,
                110, 120, 130, 140, 150,
                160, 170, 180, 190, 200,
                210, 220, 230, 240, 250
        };
        Image img(5, 5, 1, imageData);

        // 计算应用滤波器前的图像方差
        double originalVariance = calculateVariance(img);

        // 使用5x5的核心尺寸进行滤波
        Box2DFilter filter(5, PaddingType::ZeroPadding); // 使用5x5的核心尺寸
        filter.apply(img);

        // 计算应用滤波器后的图像方差
        double filteredVariance = calculateVariance(img);

        // 对结果进行某种形式的定量验证
        // 预期方差较原始图像降低，这里假设阈值为原始方差的一定比例，例如0.5
        double expectedThreshold = originalVariance * 0.5;
        assert(filteredVariance < expectedThreshold && "Large kernel size did not smooth the image as expected.");

        std::cout << "TestLargeKernelFiltering passed: Image smoothing with large kernel size verified." << std::endl;
    }

    /**
     * Tests Reflect Padding Edge Handling with the Box2DFilter
     *
     * Focuses on the Box2DFilter's ability to handle image edges using reflect padding. This padding strategy mirrors the
     * image content around the edges to fill the kernel window. The test verifies that reflect padding maintains visual
     * consistency at the edges, without introducing artifacts that could detract from image quality.
     */
    void testReflectPaddingEdgeHandling() {
        // 创建一个简单的测试图像，边缘和中心有明显的差异
        Image img(3, 3, 1, new unsigned char[9]{255, 255, 255, 255, 0, 255, 255, 255, 255});
        Box2DFilter filter(3, PaddingType::ReflectPadding); // 使用反射填充策略
        filter.apply(img);

        // 对反射填充处理后的边缘像素进行检查，预期与相邻中心像素相似
        assert(img.getData()[0] == img.getData()[4] && "Reflect padding did not handle edges as expected.");
    }

    /**
     * Executes All Defined Test Cases for the Box2DFilter
     *
     * This function orchestrates the execution of all test cases defined in the TestBox2DFilter class. It leverages
     * the runTest template method to execute each test case individually, providing a name for each test that is used
     * in logging and reporting test outcomes. The tests conducted aim to thoroughly evaluate the Box2DFilter class's
     * functionality, focusing on its application to uniform images, handling of images with gradients, and effectiveness
     * of different edge padding strategies. By running these tests, the framework ensures that the Box2DFilter behaves
     * consistently and correctly under a variety of conditions.
     */
    virtual void runTests() override {
        runTest<TestBox2DFilter>(&TestBox2DFilter::testUniformImage, "Box Filter on a Uniform Image");
        runTest<TestBox2DFilter>(&TestBox2DFilter::testEdgePadding, "Box Filter with Edge Padding");
        runTest<TestBox2DFilter>(&TestBox2DFilter::testGradientImage, "Box Filter on a Gradient Image");
        runTest<TestBox2DFilter>(&TestBox2DFilter::testLargeKernelFiltering, "Box Filter with Large Kernel Size");
        runTest<TestBox2DFilter>(&TestBox2DFilter::testReflectPaddingEdgeHandling, "Box Filter with Reflect Padding");
    }
};
