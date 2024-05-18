/**
 * @file Median2DFilter.cpp
 *
 * @brief Implementation of the Median2DFilter class for applying median filtering to images.
 *
 * This file contains the implementation of the Median2DFilter class, which applies a median filter to images for noise reduction.
 * Median filtering is a non-linear process useful in reducing salt-and-pepper noise while preserving edges in the image.
 * This class supports custom kernel sizes and incorporates various padding strategies to handle image borders effectively.
 * The median value is computed using a quick select algorithm to find the middle value in the intensity distribution of
 * the pixels within the kernel window. This approach ensures that the filtering process is both efficient and effective,
 * making it suitable for real-time image processing applications. Part of the tools developed by the Advanced Programming
 * Group, this implementation aims to provide a robust solution for enhancing image quality.
 *
 * @date Created on March 21, 2024
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

#include "Filters/Median2DFilter.h"
#include "Filters/Padding.h"
#include "Algorithm.h"

#include <vector>
#include <stdexcept>

Median2DFilter::Median2DFilter(int kernelSize, PaddingType paddingType) : kernelSize(kernelSize), paddingType(paddingType) {
    // Validate kernel size
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd.");
    }
}

void Median2DFilter::apply(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char* originalData = image.getData();

    // Allocate memory for filtered image data
    unsigned char* filteredData = new unsigned char[width * height * channels];

    // Apply median filter to each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                auto window = Padding::getPixelWindow(image, x, y, c, kernelSize, paddingType);
                filteredData[(y * width + x) * channels + c] = median(window);
            }
        }
    }

    image.updateData(filteredData);
}

unsigned char Median2DFilter::median(std::vector<unsigned char>& window) {
    // Calculate median value of pixel window
    size_t size = window.size();

    if (size % 2 == 0) {
        // For even-length windows, return the average of the two middle values
        unsigned char a = Algorithm::quickSelect(window, 0, size - 1, size / 2);
        unsigned char b = Algorithm::quickSelect(window, 0, size - 1, size / 2 - 1);
        return (a + b) / 2;
    } else {
        // For odd-length windows, return the middle value
        return Algorithm::quickSelect(window, 0, size - 1, size / 2);
    }
}
