/**
 * @file Median3DFilter.h
 *
 * @brief Implements a 3D Median filter for volume data processing.
 *
 * The Median3DFilter class applies a median filtering operation to 3D volume data.
 * It is designed to reduce noise within the volume data while preserving edges by
 * replacing each voxel's value with the median value within a specified neighborhood around that voxel.
 * The class supports customizable kernel sizes and efficiently computes the median values using precomputed
 * neighborhood offsets. This class is a part of the volume data manipulation toolkit developed by the
 * Advanced Programming Group.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN3DFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN3DFILTER_H

#include "Filter.h"

#include <vector>

class Median3DFilter : public IFilter3D {
private:
    int kernelSize; // The size of the kernel.
    std::vector<std::vector<int>> neighborhoodOffsets; // The offsets of the neighborhood.

    /**
     * Calculates the median value from a neighborhood of voxel values.
     *
     * This method finds the median value in a given vector of unsigned chars representing the intensity values
     * of voxels in a neighborhood. If the size of the neighborhood is odd, the median is the middle element. If
     * it is even, the median is the average of the two middle elements. This calculation is critical for the median
     * filtering process, providing the capability to reduce noise while preserving edges in the volume.
     *
     * @param neighborhood: A reference to a vector of unsigned chars representing voxel values in a neighborhood.
     *
     * @return: The median value as an unsigned char.
     */
    unsigned char calculateMedian(std::vector<unsigned char> &neighborhood);

    /**
     * Precomputes the offsets for the filter's neighborhood based on the kernel size.
     *
     * This method calculates the offsets from each voxel within the kernel's neighborhood, taking into account the
     * dimensions of the volume to ensure that the offsets stay within bounds. The offsets are stored in a vector for
     * quick access during the filtering process. This precomputation step optimizes the median filtering operation by
     * avoiding repeated boundary checks for each voxel during the filter application.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     */
    void precomputeNeighborhoodOffsets(int width, int height, int depth);

public:
    /**
     * Constructor for the Median3DFilter class.
     *
     * Initializes a Median3DFilter object with a specified kernel size for the median filter. The kernel size
     * determines the size of the neighborhood around each voxel from which the median is calculated. The
     * kernel size must be an odd number to ensure there is a central voxel.
     *
     * @param kernelSize: An integer specifying the size of the kernel. Must be an odd number.
     * @throws std::invalid_argument if kernelSize is not an odd number.
     */
    explicit Median3DFilter(int kernelSize);

    /**
     * Applies the median filter to a volume.
     *
     * This method applies the median filter to a 3D volume represented by a Volume object. The filter iterates
     * through each voxel in the volume and replaces its value with the median value from the neighborhood around
     * that voxel. The neighborhood size is determined by the kernel size specified during object creation. The
     * median filter is a powerful tool for reducing noise in volume data while preserving structural details.
     * This method efficiently computes the median values using precomputed neighborhood offsets to enhance the
     * performance of the filtering operation. Histogram equalization is a critical step in enhancing the contrast
     * of images and improving their visual quality.
     *
     * @param volume: A reference to a Volume object representing the 3D data to which the median filter will be applied.
     */
    void apply(Volume &volume) override;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN3DFILTER_H
