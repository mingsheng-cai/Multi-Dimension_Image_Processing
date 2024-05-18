/**
 * @file Gaussian3DFilter.cpp
 *
 * @brief Implements a 3D Gaussian filter for volumetric data smoothing.
 *
 * The Gaussian3DFilter class applies a Gaussian smoothing operation to 3D volume data. Designed to reduce noise and
 * smooth transitions without significantly blurring the edges, this filter replaces each voxel's value with a weighted
 * average of its neighbors' values, where the weights are determined by a Gaussian distribution. The class allows for
 * customization of the standard deviation (sigma) and the kernel size, enabling fine control over the extent of smoothing.
 * Efficient convolution operations along each axis (X, Y, and Z) ensure that the filter is applied thoroughly across the
 * entire volume. This class is essential for preprocessing in applications such as medical imaging, where enhancing the
 * clarity of features within volumetric data is crucial.
 *
 * @date Created on March 18, 2024
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

#include "Filters/Gaussian3DFilter.h"
#include "Volume.h"

#include <cmath>
#include <iostream>

Gaussian3DFilter::Gaussian3DFilter(double sigma, int kernelSize) : sigma(sigma), kernelSize(kernelSize) {
    // Validate the kernel size
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be an odd number.");
    }
}

std::vector<double> Gaussian3DFilter::computeGaussian1DKernel() const {
    // Compute the Gaussian kernel coefficients
    std::vector<double> kernel(kernelSize);
    int halfSize = kernelSize / 2;
    double sum = 0.0;
    double factor = 1.0 / (sqrt(2.0f * M_PI) * sigma);

    // Calculate the kernel coefficients
    for (int i = -halfSize; i <= halfSize; ++i) {
        kernel[i + halfSize] = factor * exp(-(i * i) / (2.0f * sigma * sigma));
        sum += kernel[i + halfSize];
    }

    // Normalize kernel
    for (auto &value: kernel) {
        value /= sum;
    }

    return kernel;
}

void Gaussian3DFilter::applyGaussian1DFilter_X(std::vector<unsigned char> &data, int width, int height, int depth) {
    // Compute the 1D Gaussian kernel
    auto kernel = computeGaussian1DKernel();
    int halfSize = kernelSize / 2;
    std::vector<unsigned char> temp(data.size(), 0);

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double weightedSum = 0.0;
                for (int k = -halfSize; k <= halfSize; ++k) {
                    int xk = std::max(0, std::min(x + k, width - 1));
                    weightedSum +=
                            static_cast<double>(data[z * width * height + y * width + xk]) * kernel[k + halfSize];
                }
                temp[z * width * height + y * width + x] =
                        static_cast<unsigned char>(std::max(0.0, std::min(255.0, std::round(weightedSum))));
            }
        }
    }

    data = std::move(temp);
}

void Gaussian3DFilter::applyGaussian1DFilter_Y(std::vector<unsigned char> &data, int width, int height, int depth) {
    // Compute the 1D Gaussian kernel
    auto kernel = computeGaussian1DKernel();
    int halfSize = kernelSize / 2;
    std::vector<unsigned char> temp(data.size(), 0);

    for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                double weightedSum = 0.0;
                for (int k = -halfSize; k <= halfSize; ++k) {
                    int yk = std::max(0, std::min(y + k, height - 1));
                    weightedSum +=
                            static_cast<double>(data[z * height * width + yk * width + x]) * kernel[k + halfSize];
                }
                temp[z * height * width + y * width + x] =
                        static_cast<unsigned char>(std::max(0.0, std::min(255.0, std::round(weightedSum))));
            }
        }
    }

    data = std::move(temp);
}

void Gaussian3DFilter::applyGaussian1DFilter_Z(std::vector<unsigned char> &data, int width, int height, int depth) {
    // Compute the 1D Gaussian kernel
    auto kernel = computeGaussian1DKernel();
    int halfSize = kernelSize / 2;
    std::vector<unsigned char> temp(data.size(), 0);

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double weightedSum = 0.0;
                for (int k = -halfSize; k <= halfSize; ++k) {
                    int zk = std::max(0, std::min(z + k, depth - 1));
                    weightedSum +=
                            static_cast<double>(data[zk * height * width + y * width + x]) * kernel[k + halfSize];
                }
                temp[z * height * width + y * width + x] =
                        static_cast<unsigned char>(std::max(0.0, std::min(255.0, std::round(weightedSum))));
            }
        }
    }

    data = std::move(temp);
}

void Gaussian3DFilter::apply(Volume &volume) {
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();

    // Get the original data
    const unsigned char *originalData = volume.getData();

    // Copy the original data to a new vector
    std::vector<unsigned char> data(originalData, originalData + width * height * depth);

    std::cout << "Applying Gaussian filter on X-axis..." << std::endl;
    applyGaussian1DFilter_X(data, width, height, depth);
    std::cout << "Completed X-axis filtering." << std::endl;

    std::cout << "Applying Gaussian filter on Y-axis..." << std::endl;
    applyGaussian1DFilter_Y(data, width, height, depth);
    std::cout << "Completed Y-axis filtering." << std::endl;

    std::cout << "Applying Gaussian filter on Z-axis..." << std::endl;
    applyGaussian1DFilter_Z(data, width, height, depth);
    std::cout << "Completed Z-axis filtering." << std::endl;

    volume.updateData(data);

    std::cout << "Gaussian 3D Filter application completed." << std::endl;
}
