/**
 * @file Padding.cpp
 *
 * @brief Implementation of padding strategies for image processing.
 *
 * This file contains the implementation of various padding strategies used in image processing operations, particularly
 * in the context of applying filters such as median, Gaussian, and edge detection filters. The `getPixelWindow` function
 * provided in this file facilitates the retrieval of pixel values from a specified window around a target pixel, applying
 * padding as necessary according to the chosen padding strategy. Supported padding types include zero padding, edge replication,
 * and reflect padding, each suitable for different image processing needs. This functionality is essential for handling
 * image borders when applying filters that require neighborhood information. Part of the tools developed by the Advanced
 * Programming Group, this implementation aims to enhance the flexibility and effectiveness of image manipulation tasks.
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

#include "Filters/Padding.h"
#include "Image.h"
#include <stdexcept>
#include <vector>
#include <stdexcept>

std::vector<unsigned char>
Padding::getPixelWindow(const Image &image, int x, int y, int c, int kernelSize, PaddingType paddingType) {
    // Get image properties
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *data = image.getData();
    int offset = kernelSize / 2;

    // Initialize the window vector to store pixel values
    std::vector<unsigned char> window;

    // Iterate over the window centered at (x, y) and apply the selected padding strategy
    for (int ky = -offset; ky <= offset; ++ky) {
        for (int kx = -offset; kx <= offset; ++kx) {
            int newX = x + kx;
            int newY = y + ky;

            // Apply the selected padding strategy
            switch (paddingType) {
                case PaddingType::ZeroPadding:
                    // Zero Padding
                    if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
                        window.push_back(0);
                    } else {
                        window.push_back(data[(newY * width + newX) * channels + c]);
                    }
                    break;
                case PaddingType::EdgeReplication:
                    // Edge Replication
                    newX = std::max(0, std::min(newX, width - 1));
                    newY = std::max(0, std::min(newY, height - 1));
                    window.push_back(data[(newY * width + newX) * channels + c]);
                    break;
                case PaddingType::ReflectPadding:
                    // Reflect Padding
                    if (newX < 0) newX = -newX - 1 + offset % 2; // Reflect around 0
                    if (newY < 0) newY = -newY - 1 + offset % 2; // Reflect around 0
                    if (newX >= width) newX = width - (newX - width) - 1 - offset % 2;
                    if (newY >= height) newY = height - (newY - height) - 1 - offset % 2;
                    window.push_back(data[(newY * width + newX) * channels + c]);
                    break;
                default:
                    throw std::invalid_argument("Unsupported padding type.");
            }
        }
    }

    return window;
}
