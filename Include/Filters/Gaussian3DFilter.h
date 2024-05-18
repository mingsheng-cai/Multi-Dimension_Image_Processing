/**
 * @file Gaussian3DFilter.h
 *
 * @brief Implements a 3D Gaussian filter for smoothing volume data.
 *
 * The Gaussian3DFilter class applies a Gaussian smoothing operation to 3D volume data.
 * It performs the smoothing separately along the X, Y, and Z axes using a 1D Gaussian kernel.
 * This class is part of the tools developed by the Advanced Programming Group to facilitate
 * volume data manipulation and processing.
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

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_GAUSSIAN3DFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_GAUSSIAN3DFILTER_H

#include "Filters/Filter.h"
#include "Volume.h"

#include <vector>

class Gaussian3DFilter : public IFilter3D {
private:
    double sigma; // Standard deviation of the Gaussian
    int kernelSize; // Size of the kernel

    /**
     * Computes a 1D Gaussian kernel.
     *
     * This member function calculates the coefficients of a 1D Gaussian kernel based on the class's sigma (standard deviation)
     * and kernel size. The coefficients are computed using the Gaussian formula and are then normalized to ensure that the
     * sum of the kernel coefficients is 1. This normalization is essential for maintaining the original amplitude of the signal
     * after filtering. The computed kernel is symmetric and centered, suitable for convolution operations in one dimension.
     *
     * @return: A vector of doubles containing the normalized coefficients of the 1D Gaussian kernel.
     */
    std::vector<double> computeGaussian1DKernel() const;

    /**
     * Applies the Gaussian filter along the X-axis of the volume.
     *
     * This method convolves the volume data with the Gaussian kernel along the X-axis, effectively smoothing the volume
     * along this direction. It uses the precomputed 1D Gaussian kernel for convolution, applying the kernel to each voxel's
     * neighborhood along the X-axis and updating the voxel's value based on the weighted sum of its neighbors. The process
     * results in a volume that is blurred along the X-axis while retaining its structure along the Y and Z axes.
     *
     * @param data: A reference to a vector of unsigned char representing the volume data to be filtered.
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     */
    void applyGaussian1DFilter_X(std::vector<unsigned char> &data, int width, int height, int depth);

    /**
     * Applies the Gaussian filter along the Y-axis of the volume.
     *
     * Similar to applyGaussian1DFilter_X, but the convolution is performed along the Y-axis. This method smooths the volume
     * data along the Y-axis, applying the Gaussian kernel to each voxel's neighborhood in this direction. The resulting volume
     * exhibits blurring along the Y-axis, with its characteristics along the X and Z axes preserved.
     *
     * @param data: A reference to a vector of unsigned char representing the volume data to be filtered.
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     */
    void applyGaussian1DFilter_Y(std::vector<unsigned char> &data, int width, int height, int depth);

    /**
     * Applies the Gaussian filter along the Z-axis of the volume.
     *
     * This method extends the Gaussian smoothing process to the Z-axis, convolving the volume data with the Gaussian kernel
     * along this direction. It smooths the volume along the Z-axis, applying the kernel to each voxel's neighborhood and
     * updating the voxel's value accordingly. The operation blurs the volume along the Z-axis, maintaining its dimensions
     * along the X and Y axes.
     *
     * @param data: A reference to a vector of unsigned char representing the volume data to be filtered.
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     */
    void applyGaussian1DFilter_Z(std::vector<unsigned char> &data, int width, int height, int depth);

public:
    /**
     * Constructor for the Gaussian3DFilter class.
     *
     * Initializes a Gaussian3DFilter object with a specified standard deviation (sigma) and kernel size. The kernel size
     * determines the extent of the neighborhood around each voxel to be considered for filtering, and it must be an odd
     * number to ensure a central voxel. Sigma determines the spread of the Gaussian kernel and thereby the extent of
     * smoothing. This constructor validates the kernel size and throws an exception if the kernel size is not odd.
     *
     * @param sigma: The standard deviation of the Gaussian distribution used for the kernel.
     * @param kernelSize: The size of the kernel. It must be an odd number.
     * @throws std::invalid_argument if kernelSize is not an odd number.
     */
    Gaussian3DFilter(double sigma, int kernelSize);

    /**
     * Applies the Gaussian filter to the entire volume.
     *
     * This method orchestrates the application of the Gaussian filter to a 3D volume, smoothing the volume along all three
     * axes (X, Y, and Z) sequentially. It achieves this by calling the applyGaussian1DFilter_X, applyGaussian1DFilter_Y,
     * and applyGaussian1DFilter_Z methods in succession, each applying the Gaussian kernel along one axis. The process
     * results in a volume that is uniformly smoothed, reducing noise while preserving important structural information.
     *
     * @param volume: A reference to the Volume object representing the 3D data to be filtered.
     */
    void apply(Volume &volume) override;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_GAUSSIAN3DFILTER_H
