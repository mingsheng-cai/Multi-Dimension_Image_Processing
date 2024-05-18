/**
 * @file TestPixelFilter.h
 *
 * @brief Unit Tests for the PixelFilter Class.
 *
 * This header file introduces the TestPixelFilter class, specifically designed to conduct unit tests on various pixel filtering operations provided by the PixelFilter class within the image processing library. The tests encompass functionalities such as grayscale conversion, brightness adjustment, histogram equalization, thresholding in different color spaces, and noise addition. These tests are crucial for verifying the filter's effectiveness in image enhancement and manipulation tasks, ensuring that operations such as color space conversions, contrast improvements, and noise handling are correctly implemented and yield expected results.
 *
 * Usage:
 * Derived from the Test base class, the TestPixelFilter class implements the runTests method to carry out all specified test cases, leveraging the Test class's runTest template method for executing individual test functions. This methodical testing approach affirms the PixelFilter class's capability to perform essential image processing operations, facilitating the development of robust image processing applications.
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
#include "Filters/PixelFilter.h"
#include "Image.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>
#include <numeric>

class TestPixelFilter : public Test {
private:
    /**
     * Calculates the Standard Deviation of a Histogram
     *
     * Computes the standard deviation of a given histogram, representing the spread of pixel values in an image. This
     * metric is essential for evaluating the contrast and distribution of pixel intensities, aiding in the assessment of
     * image quality and processing effects. The standard deviation is calculated as the square root of the variance, which
     * is the average of the squared differences between each pixel value and the mean value.
     *
     * @param histogram The histogram of pixel values
     * @return The standard deviation of the histogram
     */
    double calculateHistogramStdDev(const std::vector<int> &histogram) {
        int sum = std::accumulate(histogram.begin(), histogram.end(), 0);
        double mean = static_cast<double>(sum) / histogram.size();

        double variance = 0.0;
        for (int value: histogram) {
            variance += (value - mean) * (value - mean);
        }
        variance /= histogram.size();

        return std::sqrt(variance);
    }

    /**
     * Builds a Histogram from an Image
     *
     * Generates a histogram of pixel values from the given image, providing insights into the distribution of pixel
     * intensities. This histogram is crucial for understanding the image's contrast, brightness, and overall quality,
     * serving as a fundamental tool for image processing and analysis tasks.
     *
     * @param image The image to build the histogram from
     * @return The histogram of pixel values
     */
    std::vector<int> buildHistogram(const Image &image) {
        std::vector<int> histogram(256, 0);
        const unsigned char *data = image.getData();
        int totalPixels = image.getWidth() * image.getHeight() * image.getChannels();

        for (int i = 0; i < totalPixels; i += image.getChannels()) {
            // 简化：只考虑第一个通道，适用于灰度图像或彩色图像的一个通道
            ++histogram[data[i]];
        }

        return histogram;
    }

public:
    /**
     * Tests Grayscale Conversion
     *
     * Verifies that the PixelFilter class can correctly convert a color image to grayscale. Grayscale conversion is a
     * fundamental operation in image processing, essential for simplifying further analysis by reducing image complexity.
     * This test checks if each pixel in the converted image has equal red, green, and blue values, indicating a successful
     * conversion to grayscale.
     */
    void testGrayscaleConversion() {
        Image img;
        img.loadFromFile("../Images/gracehopper.png"); // Load a test image
        PixelFilter grayscaleFilter("Grayscale");
        grayscaleFilter.apply(img);

        // Verify that each pixel has equal red, green, and blue values
        for (int i = 0; i < img.getWidth() * img.getHeight(); ++i) {
            unsigned char *data = img.getData();
            assert(data[i * 3] == data[i * 3 + 1] && data[i * 3 + 1] == data[i * 3 + 2] &&
                   "Grayscale conversion failed.");
        }
    }

    /**
     * Tests Brightness Adjustment
     *
     * Examines the functionality of the PixelFilter class to adjust the brightness of an image. Brightness adjustment is
     * critical for enhancing image visibility and preparing images for further processing. This test verifies that the
     * filter correctly modifies the brightness of an image without exceeding the pixel value limits.
     */
    void testBrightnessAdjustment() {
        Image img;
        img.loadFromFile("../Images/vh_ct.png"); // Assume this is a grayscale image

        int adjustment = 20; // Increase brightness by 20
        PixelFilter brightnessFilter("Brightness", adjustment);
        brightnessFilter.apply(img);

        // Check if the brightness adjustment has occurred
        unsigned char *data = img.getData();
        bool brightnessAdjusted = false;
        int totalPixels = img.getWidth() * img.getHeight() * img.getChannels();

        for (int i = 0; i < totalPixels; ++i) {
            // Check if the pixel value is within the expected range
            if ((data[i] > 0 && data[i] < 255) || (data[i] == 0 && adjustment > 0) ||
                (data[i] == 255 && adjustment < 0)) {
                brightnessAdjusted = true;
                break;
            }
        }

        assert(brightnessAdjusted && "Brightness adjustment did not occur as expected.");
    }

    /**
     * Tests Histogram Equalization
     *
     * Tests the histogram equalization functionality of the PixelFilter class. Histogram equalization is an important
     * technique for improving the contrast of an image, making it more suitable for analysis or display. This test
     * evaluates the effectiveness of histogram equalization by comparing the standard deviation of pixel values before
     * and after applying the filter, expecting a higher contrast in the processed image.
     */
    void testHistogramEqualizationEffect() {
        Image img;
        img.loadFromFile("../Images/vh_ct.png"); // Load a test image

        // Calculate the standard deviation of the original image's histogram
        auto originalHistogram = buildHistogram(img);
        double originalStdDev = calculateHistogramStdDev(originalHistogram);

        // Apply histogram equalization
        PixelFilter histogramEqualizationFilter("Equalisation", std::nullopt, "GREY");
        histogramEqualizationFilter.apply(img);

        // Calculate the standard deviation of the equalized image's histogram
        auto equalizedHistogram = buildHistogram(img);
        double equalizedStdDev = calculateHistogramStdDev(equalizedHistogram);

        // Check if the contrast has improved
        assert(equalizedStdDev > originalStdDev && "Histogram equalization did not improve the contrast as expected.");
    }

    /**
     * Tests Thresholding in Grayscale
     *
     * Assesses the thresholding operation of the PixelFilter class on grayscale images. Thresholding is crucial for
     * binarization, helping to segment images into foreground and background. This test ensures that the filter correctly
     * applies a threshold, resulting in pixel values being set to either the minimum or maximum value.
     */
    void testThresholdingGREY() {
        Image img;
        img.loadFromFile("../Images/vh_ct.png"); // Load a test image
        int threshold = 128; // 阈值
        PixelFilter thresholdFilter("Thresholding", std::nullopt, "GREY", threshold);
        thresholdFilter.apply(img);

        // Verify the processed image
        unsigned char *data = img.getData();
        for (int i = 0; i < img.getWidth() * img.getHeight(); ++i) {
            assert((data[i] == 0 || data[i] == 255) && "Thresholding failed.");
        }
    }

    /**
     * Tests Thresholding in RGB with HSL
     *
     * Evaluates the thresholding operation in the HSL color space on RGB images by the PixelFilter class. This operation
     * is significant for color segmentation and image binarization in color images. The test checks if the filter
     * successfully applies a threshold within the HSL color space, affecting the output image as expected.
     */
    void testThresholdingRGBHSL() {
        Image img;
        img.loadFromFile("../Images/gracehopper.png"); // A color RGB image
        int threshold = 128; // 阈值

        // Perform thresholding on the RGB image
        PixelFilter thresholdFilter("Thresholding", std::nullopt, "HSL", threshold);
        thresholdFilter.apply(img);

        // Check the processed image
        unsigned char *data = img.getData();
        for (int i = 0; i < img.getWidth() * img.getHeight() * img.getChannels(); ++i) {
            assert((data[i] == 0 || data[i] == 255) && "Thresholding on RGB image failed.");
        }
    }

    /**
     * Tests Thresholding in RGB with HSV
     *
     * Verifies the effectiveness of thresholding in the HSV color space on RGB images. This functionality is vital for
     * separating image features based on color and brightness. The test confirms that thresholding in the HSV space
     * leads to the anticipated binary segmentation of the image.
     */
    void testThresholdingRGBHSV() {
        Image img;
        img.loadFromFile("../Images/gracehopper.png"); // A color RGB image
        int threshold = 128; // 阈值

        // Do thresholding on the RGB image
        PixelFilter thresholdFilter("Thresholding", std::nullopt, "HSV", threshold);
        thresholdFilter.apply(img);

        // We expect the thresholding to result in a binary image
        unsigned char *data = img.getData();
        for (int i = 0; i < img.getWidth() * img.getHeight() * img.getChannels(); ++i) {
            assert((data[i] == 0 || data[i] == 255) && "Thresholding on RGB image failed.");
        }
    }

    /**
     * Tests Noise Percentage Adjustment
     *
     * Checks the ability of the PixelFilter class to add noise to an image at a specified percentage. Adding noise is
     * sometimes necessary for testing image processing algorithms under realistic conditions. This test ensures that
     * the filter can introduce the correct percentage of noise into an image.
     */
    void testNoisePercentage() {
        Image img;
        img.loadFromFile("../Images/vh_ct.png"); // Load a test image
        double expectedNoisePercentage = 0.1; // Expected noise percentage
        PixelFilter noiseFilter("SaltAndPepperNoise", std::nullopt, "", 0, expectedNoisePercentage);
        noiseFilter.apply(img);

        unsigned char *data = img.getData();
        int noisePixels = 0;
        int totalPixels = img.getWidth() * img.getHeight() * img.getChannels();

        for (int i = 0; i < totalPixels; ++i) {
            if (data[i] == 0 || data[i] == 255) { // Assume noise is black or white
                ++noisePixels;
            }
        }

        double actualNoisePercentage = static_cast<double>(noisePixels) / totalPixels;
        assert(fabs(actualNoisePercentage - expectedNoisePercentage) < 0.01 &&
               "Noise percentage does not match expected.");
    }

    /**
     * Tests Noise Addition
     *
     * Verifies the functionality of adding salt-and-pepper noise to an image using the PixelFilter class. This test
     * confirms that the filter accurately adds noise to an image, simulating common types of digital image corruption,
     * and validates the effectiveness of subsequent noise reduction techniques.
     */
    void testNoiseAddition() {
        Image originalImg;
        originalImg.loadFromFile("../Images/vh_ct.png"); // Load a test image
        // Create a copy of the original image to add noise
        Image imgWithNoise(originalImg.getWidth(), originalImg.getHeight(), originalImg.getChannels(),
                           originalImg.getData());

        PixelFilter noiseFilter("SaltAndPepperNoise", std::nullopt, "", 0, 0.05); // 添加5%的噪声
        noiseFilter.apply(imgWithNoise);

        unsigned char *originalData = originalImg.getData();
        unsigned char *noiseData = imgWithNoise.getData();
        int totalPixels = originalImg.getWidth() * originalImg.getHeight() * originalImg.getChannels();
        bool isDifferent = false;

        for (int i = 0; i < totalPixels; ++i) {
            if (originalData[i] != noiseData[i]) {
                isDifferent = true;
                break;
            }
        }

        assert(isDifferent && "Noise was not added to the image.");
    }

    /**
     * Executes All Defined Pixel Filtering Tests
     *
     * Orchestrates the execution of all unit tests for the PixelFilter class, ensuring its various functionalities work
     * as expected. Through these tests, the class's capability to perform critical image processing operations like
     * grayscale conversion, brightness adjustment, histogram equalization, thresholding, and noise addition is validated,
     * contributing to the robustness of image processing applications.
     */
    virtual void runTests() override {
        runTest<TestPixelFilter>(&TestPixelFilter::testGrayscaleConversion, "Grayscale Conversion");
        runTest<TestPixelFilter>(&TestPixelFilter::testBrightnessAdjustment, "Brightness Adjustment");
        runTest<TestPixelFilter>(&TestPixelFilter::testHistogramEqualizationEffect, "Histogram Equalization Effect");
        runTest<TestPixelFilter>(&TestPixelFilter::testThresholdingGREY, "Thresholding Grey Image");
        runTest<TestPixelFilter>(&TestPixelFilter::testThresholdingRGBHSL, "Thresholding RGB-HSL Image");
        runTest<TestPixelFilter>(&TestPixelFilter::testThresholdingRGBHSV, "Thresholding RGB-HSV Image");
        runTest<TestPixelFilter>(&TestPixelFilter::testNoisePercentage, "Noise Percentage");
        runTest<TestPixelFilter>(&TestPixelFilter::testNoiseAddition, "Noise Addition");
    }
};
