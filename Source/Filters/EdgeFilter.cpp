/**
 * @file EdgeFilter.cpp
 *
 * @brief Implementation of the EdgeFilter class for edge detection in images.
 *
 * This file defines the methods of the EdgeFilter class, including various edge detection algorithms such as Sobel,
 * Prewitt, Scharr, and Roberts. Edge detection is performed on grayscale images, where the input image is checked
 * for its color channels to ensure it's suitable for edge detection. Each edge detection method applies a specific
 * kernel to highlight edges in the image by calculating the gradient magnitude at each pixel. This implementation
 * allows for flexible edge detection through the choice of algorithm and padding method, catering to diverse image
 * processing needs. The EdgeFilter class is part of the Advanced Programming Group's efforts to provide robust tools
 * for image analysis and manipulation.
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

#include "Filters/EdgeFilter.h"

#include <cmath>
#include <iostream>

EdgeFilter::EdgeFilter(FilterType filterType, PaddingType paddingType) : filterType(filterType),
                                                                         paddingType(paddingType) {}

bool EdgeFilter::isGrayscale(const Image &image) const {
    // If the image has only one channel, it is grayscale
    return image.getChannels() == 1;
}

void EdgeFilter::apply(Image &image) {
    // Check if the image is in grayscale
    if (!isGrayscale(image)) {
        std::cerr << "Image must be in grayscale to apply edge detection." << std::endl;
        return;
    }

    // Apply the selected edge detection filter
    switch (filterType) {
        case FilterType::Sobel:
            applySobel(image);
            break;
        case FilterType::Prewitt:
            applyPrewitt(image);
            break;
        case FilterType::Scharr:
            applyScharr(image);
            break;
        case FilterType::Roberts:
            applyRoberts(image);
            break;
        default:
            std::cerr << "Unknown filter type." << std::endl;
            break;
    }
}

void EdgeFilter::applySobel(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    auto *data = new unsigned char[width * height];

    // Sobel kernels
    const std::vector<std::vector<int>> Gx = {{-1, 0, 1},
                                              {-2, 0, 2},
                                              {-1, 0, 1}};
    const std::vector<std::vector<int>> Gy = {{-1, -2, -1},
                                              {0,  0,  0},
                                              {1,  2,  1}};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    auto window = Padding::getPixelWindow(image, x + kx, y + ky, 0, 3, paddingType);
                    if (window.size() == 9) { // Ensure window size is correct for a 3x3 kernel
                        int pos = (ky + 1) * 3 + (kx + 1);
                        sumX += Gx[ky + 1][kx + 1] * window[pos];
                        sumY += Gy[ky + 1][kx + 1] * window[pos];
                    }
                }
            }
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            data[y * width + x] = static_cast<unsigned char>(std::min(std::max(magnitude, 0), 255));
        }
    }

    image.updateData(data);
}

void EdgeFilter::applyPrewitt(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    auto *data = new unsigned char[width * height];

    // Prewitt kernels
    const std::vector<std::vector<int>> Gx = {{-1, 0, 1},
                                              {-1, 0, 1},
                                              {-1, 0, 1}};
    const std::vector<std::vector<int>> Gy = {{-1, -1, -1},
                                              {0,  0,  0},
                                              {1,  1,  1}};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    auto window = Padding::getPixelWindow(image, x + kx, y + ky, 0, 3, paddingType);
                    if (window.size() == 9) {
                        int pos = (ky + 1) * 3 + (kx + 1);
                        sumX += Gx[ky + 1][kx + 1] * window[pos];
                        sumY += Gy[ky + 1][kx + 1] * window[pos];
                    }
                }
            }
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            data[y * width + x] = static_cast<unsigned char>(std::min(std::max(magnitude, 0), 255));
        }
    }

    image.updateData(data);
}

void EdgeFilter::applyScharr(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    auto *data = new unsigned char[width * height];

    // Scharr kernels
    const std::vector<std::vector<int>> Gx = {{-3,  0, 3},
                                              {-10, 0, 10},
                                              {-3,  0, 3}};
    const std::vector<std::vector<int>> Gy = {{-3, -10, -3},
                                              {0,  0,   0},
                                              {3,  10,  3}};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    auto window = Padding::getPixelWindow(image, x + kx, y + ky, 0, 3, paddingType);
                    if (window.size() == 9) {
                        int pos = (ky + 1) * 3 + (kx + 1);
                        sumX += Gx[ky + 1][kx + 1] * window[pos];
                        sumY += Gy[ky + 1][kx + 1] * window[pos];
                    }
                }
            }
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            data[y * width + x] = static_cast<unsigned char>(std::min(std::max(magnitude, 0), 255));
        }
    }

    image.updateData(data);
}

void EdgeFilter::applyRoberts(Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    auto *originalData = image.getData();
    auto *data = new unsigned char[width * height];

    // Initialize the data array with zeros
    std::fill_n(data, width * height, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Roberts Cross kernels used for edge detection
            auto window = Padding::getPixelWindow(image, x, y, 0, 2, paddingType);

            // Make sure the window is of the correct size
            if (window.size() >= 4) {
                // Calculate the gradient using the Roberts Cross operator
                int gx = window[0] - window[3]; // Difference between two diagonal pixels
                int gy = window[1] - window[2]; // Difference between the other two diagonal pixels

                // Calculate the magnitude of the gradient
                int magnitude = static_cast<int>(sqrt(gx * gx + gy * gy));

                // Store the magnitude in the data array
                data[y * width + x] = static_cast<unsigned char>(std::min(std::max(magnitude, 0), 255));
            }
        }
    }

    // Update the image data with the edge-detected version
    image.updateData(data);
}
