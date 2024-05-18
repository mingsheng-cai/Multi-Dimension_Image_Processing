/**
 * @file Median3DFilter.cpp
 *
 * @brief Implements a 3D median filter for volumetric data noise reduction.
 *
 * The Median3DFilter class applies a median filtering operation to 3D volume data, aiming to reduce noise while preserving
 * edges. This filter replaces each voxel's value with the median value within a specified neighborhood around that voxel,
 * effectively smoothing the volume data and enhancing the visibility of structural details. The class supports customizable
 * kernel sizes and efficiently computes the median values using a quick select algorithm to handle large datasets. This
 * approach is particularly beneficial in applications like medical imaging and scientific visualization, where maintaining
 * the integrity of structural boundaries in the presence of noise is critical. The Median3DFilter is an essential component
 * of the volumetric data processing toolkit developed by the Advanced Programming Group.
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

#include "Filters/Median3DFilter.h"
#include "Algorithm.h"

#include <iostream>
#include <vector>

Median3DFilter::Median3DFilter(int kernelSize) : kernelSize(kernelSize) {
    // Ensure the kernel size is an odd number
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be an odd number.");
    }
}

void Median3DFilter::precomputeNeighborhoodOffsets(int width, int height, int depth) {
    // Calculate the offset for the neighborhood
    int offset = kernelSize / 2;
    neighborhoodOffsets.clear();

    // Iterate through each possible offset within the kernel's neighborhood
    for (int dz = -offset; dz <= offset; ++dz) {
        for (int dy = -offset; dy <= offset; ++dy) {
            for (int dx = -offset; dx <= offset; ++dx) {
                // Ensure we're within bounds when applying offsets
                if (dx >= -width && dx < width && dy >= -height && dy < height && dz >= -depth && dz < depth) {
                    neighborhoodOffsets.push_back({dx, dy, dz});
                }
            }
        }
    }
}

unsigned char Median3DFilter::calculateMedian(std::vector<unsigned char>& neighborhood) {
    // Calculate the median value from the neighborhood
    int n = neighborhood.size();

    // Use the quick select algorithm to find the median
    if (n % 2 == 1) {  // Odd length，take the middle value
        return Algorithm::quickSelect(neighborhood, 0, n - 1, n / 2);
    } else {  // Even length, take the average of the two middle values
        unsigned char v1 = Algorithm::quickSelect(neighborhood, 0, n - 1, n / 2 - 1);
        unsigned char v2 = Algorithm::quickSelect(neighborhood, 0, n - 1, n / 2);
        return (v1 + v2) / 2;
    }
}

void Median3DFilter::apply(Volume& volume) {
    std::cout << "Applying median filter with histogram optimization..." << std::endl;
    precomputeNeighborhoodOffsets(volume.getWidth(), volume.getHeight(), volume.getDepth());

    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    std::vector<unsigned char> filteredData(width * height * depth, 0);

    // Initialize histogram
    std::vector<int> histogram(256, 0);
    int medianIdx = (kernelSize * kernelSize * kernelSize) / 2;

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::fill(histogram.begin(), histogram.end(), 0);

                // Build histogram for current neighborhood
                for (const auto& offset : neighborhoodOffsets) {
                    int nx = x + offset[0];
                    int ny = y + offset[1];
                    int nz = z + offset[2];

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth) {
                        int voxelValue = volume.getData()[nz * width * height + ny * width + nx];
                        histogram[voxelValue]++;
                    }
                }

                // Find median from histogram
                int count = 0;
                for (int i = 0; i < 256; ++i) {
                    count += histogram[i];
                    if (count > medianIdx) {
                        filteredData[z * width * height + y * width + x] = i;
                        break;
                    }
                }
            }
        }
    }

    volume.updateData(filteredData);
    std::cout << "Median filter applied with histogram optimization." << std::endl;
}