/**
 * @file Gaussian2DFilter.cpp
 *
 * @brief Implementation of the Gaussian2DFilter class for applying a Gaussian blur to images.
 *
 * This file contains the implementation of the Gaussian2DFilter class, which is designed to apply a Gaussian blur
 * to images. The Gaussian blur is performed by convolving the image with a Gaussian kernel. The class allows for
 * custom kernel sizes and sigma values, providing flexibility in the strength and extent of the blur effect. The
 * Gaussian kernel is generated dynamically based on the provided sigma and kernel size, ensuring that the kernel
 * is properly normalized. The class also supports different padding types to handle image borders. This implementation
 * is part of the Advanced Programming Group's efforts to develop comprehensive tools for image manipulation and
 * processing, enhancing image quality and preparing images for further analysis or display.
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

#include "Filters/Gaussian2DFilter.h"
#include "Filters/Padding.h"

#include <cmath>
#include <vector>
#include <stdexcept>
#include <cstring>

Gaussian2DFilter::Gaussian2DFilter(int kernelSize, double sigma, PaddingType paddingType)
        : kernelSize(kernelSize), sigma(sigma), paddingType(paddingType) {
    // Ensure the kernel size is odd
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd.");
    }
    generateKernel();
}

std::vector<std::vector<double>> Gaussian2DFilter::getKernel() const {
    return kernel;
}

void Gaussian2DFilter::generateKernel() {
    // Generate the Gaussian kernel based on the specified sigma and kernel size
    kernel.resize(kernelSize, std::vector<double>(kernelSize));
    double sum = 0.0; // Used to normalize the kernel
    int offset = kernelSize / 2;

    for (int x = -offset; x <= offset; x++) {
        for (int y = -offset; y <= offset; y++) {
            double value = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[x + offset][y + offset] = value;
            sum += value;
        }
    }

    // Normalize the kernel
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }
}

void Gaussian2DFilter::apply(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char* originalData = new unsigned char[width * height * channels];
    memcpy(originalData, image.getData(), width * height * channels); // Copy original data for safe reading
    unsigned char* newData = new unsigned char[width * height * channels];

    int offset = kernelSize / 2;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                float sum = 0.0;
                auto window = Padding::getPixelWindow(image, x, y, c, kernelSize, paddingType); // Use the provided function to get the pixel window

                // Apply Gaussian kernel to the window
                int windowIndex = 0;
                for (int ky = -offset; ky <= offset; ky++) {
                    for (int kx = -offset; kx <= offset; kx++) {
                        sum += window[windowIndex++] * kernel[ky + offset][kx + offset];
                    }
                }

                // Assign the computed value to the new image data
                newData[(y * width + x) * channels + c] = static_cast<unsigned char>(std::min(std::max(int(sum), 0), 255));
            }
        }
    }

    // Update the image data with the blurred version
    image.updateData(newData);
    delete[] originalData; // Clean up the copied original data
}
