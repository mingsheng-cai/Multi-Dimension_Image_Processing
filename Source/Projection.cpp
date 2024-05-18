/**
 * @file Projection.cpp
 *
 * @brief Implements projection techniques for visualizing 3D volumetric data.
 *
 * The Projection class offers several methods to transform 3D volume data into 2D images through different types of
 * intensity projections: Maximum Intensity Projection (MIP), Minimum Intensity Projection (MinIP), Average Intensity
 * Projection (AIP), and Median Intensity Projection (MedIP). These methods facilitate the visualization of volumetric
 * data by projecting certain statistical characteristics of the data along a chosen axis, typically the depth (z-axis),
 * onto a 2D plane. Each projection technique highlights different aspects of the volume data, making them invaluable tools
 * for analysis and interpretation in fields such as medical imaging, scientific visualization, and data analysis. The
 * implementation is optimized to efficiently process large volumes of data, rendering meaningful 2D representations that
 * encapsulate the essence of the 3D volume.
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

#include "Projection.h"
#include "Algorithm.h"

std::vector<unsigned char> Projection::maximumIntensityProjection(int width, int height, int depth, const unsigned char* data) {
    // If the volume is empty (including empty data pointer), return an empty MIP image
    if (width == 0 || height == 0 || depth == 0 || !data) {
        return std::vector<unsigned char>();
    }

    // Initialize the MIP image with zeros
    std::vector<unsigned char> mip(width * height, 0); // Initialize with 0s

    // Iterate through the volume and update the MIP image
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = z * width * height + y * width + x;
                mip[y * width + x] = std::max(mip[y * width + x], data[index]);
            }
        }
    }

    return mip;
}

std::vector<unsigned char> Projection::minimumIntensityProjection(int width, int height, int depth, const unsigned char* data) {
    // If the volume is empty (including empty data pointer), return an empty MIP image
    if (width == 0 || height == 0 || depth == 0 || !data) {
        return std::vector<unsigned char>();
    }

    // Initialize the MinIP image with maximum intensity values
    std::vector<unsigned char> minip(width * height, 255); // Initialize with max value for unsigned char

    // Iterate through the volume and update the MinIP image
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = z * width * height + y * width + x;
                minip[y * width + x] = std::min(minip[y * width + x], data[index]);
            }
        }
    }

    return minip;
}

std::vector<unsigned char> Projection::averageIntensityProjection(int width, int height, int depth, const unsigned char* data) {
    // If the volume is empty (including empty data pointer), return an empty MIP image
    if (width == 0 || height == 0 || depth == 0 || !data) {
        return std::vector<unsigned char>();
    }

    // Initialize the sum vector to accumulate intensity values
    std::vector<unsigned long> sum(width * height, 0); // Use unsigned long for sum to avoid overflow
    std::vector<unsigned char> aip(width * height);

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = z * width * height + y * width + x;
                sum[y * width + x] += data[index];
            }
        }
    }

    for (size_t i = 0; i < sum.size(); ++i) {
        aip[i] = static_cast<unsigned char>(sum[i] / depth);
    }

    return aip;
}

std::vector<unsigned char> Projection::medianIntensityProjection(int width, int height, int depth, const unsigned char* data) {
    // If the volume is empty (including empty data pointer), return an empty MIP image
    if (width == 0 || height == 0 || depth == 0 || !data) {
        return std::vector<unsigned char>();
    }

    // Initialize the MIP image with zeros
    std::vector<unsigned char> mip(width * height);
    std::vector<unsigned char> pixelValues(depth);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Collect pixel values along the z-axis
            for (int z = 0; z < depth; ++z) {
                int index = z * width * height + y * width + x;
                pixelValues[z] = data[index];
            }

            // Use quickSelect to find the median
            int midIndex = (depth % 2 == 0) ? (depth / 2) - 1 : depth / 2;
            unsigned char median = Algorithm::quickSelect(pixelValues, 0, depth - 1, midIndex);

            mip[y * width + x] = median;
        }
    }

    return mip;
}
