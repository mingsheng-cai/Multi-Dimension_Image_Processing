/**
 * @file Box2DFilter.cpp
 *
 * @brief Implementation of the Box2DFilter class for image processing.
 *
 * This file provides the implementation of the Box2DFilter class. The Box2DFilter applies a simple yet effective
 * 2D box filtering operation to images. It is designed to perform spatial averaging, which can be particularly useful
 * for blurring or smoothing images. The implementation supports custom kernel sizes (must be odd) and handles edges
 * through various padding strategies defined in the PaddingType enum. A noteworthy feature planned for future
 * implementation is the use of the integral image technique to significantly speed up the computation.
 * This contribution is part of the tools developed by the Advanced Programming Group for advanced image manipulation
 * and processing.
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

#include "Filters/Box2DFilter.h"
#include "Filters/Padding.h"

#include <stdexcept>
#include <numeric>  // For std::accumulate

Box2DFilter::Box2DFilter(int kernelSize, PaddingType paddingType) : kernelSize(kernelSize), paddingType(paddingType) {
    // Validate the kernel size
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd.");
    }
}

void Box2DFilter::apply(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *originalData = image.getData();
    unsigned char *blurredData = new unsigned char[width * height * channels];

    // Apply the box filter to each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                auto window = Padding::getPixelWindow(image, x, y, c, kernelSize, paddingType);
                unsigned int sum = std::accumulate(window.begin(), window.end(), 0);
                blurredData[(y * width + x) * channels + c] = sum / window.size();
            }
        }
    }

    image.updateData(blurredData);
}
