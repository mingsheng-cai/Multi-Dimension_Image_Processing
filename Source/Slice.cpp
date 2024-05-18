/**
 * @file Slice.cpp
 *
 * @brief Implements functionality to extract 2D slices from a 3D volume.
 *
 * The Slice class provides a method for extracting specific 2D slices from a 3D volumetric dataset, based on given dimensions,
 * raw data, and the desired orientation. The class supports extraction along the 'x-y', 'x-z', and 'y-z' planes, accommodating a
 * range of visualization and analysis needs. This flexibility allows users to examine the internal structure of the volume from
 * different perspectives, facilitating a deeper understanding of the data. The method validates the requested slice index and plane
 * orientation, ensuring the integrity of the returned slice. It serves as a crucial tool in domains where 3D volumetric data is
 * prevalent, such as medical imaging, geospatial analysis, and scientific research, by simplifying the process of volumetric data
 * exploration.
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

#include "Slice.h"
#include <cstring>
#include <iostream>
#include <string>

std::vector<unsigned char>
Slice::getPlaneSlice(int width, int height, int depth, const unsigned char *data, const std::string &plane,
                     int sliceIndex) {
    // Validate the slice index
    if (sliceIndex < 1) {
        std::cerr << "Slice index must be greater than 0." << std::endl;
        return {};
    }

    std::vector<unsigned char> slice;

    // Extract the desired slice based on the specified plane
    if (plane == "x-y") {
        if (sliceIndex > depth) {
            std::cerr << "Slice index out of range for x-y plane." << std::endl;
            return {};
        }
        // Compute the start of the desired slice in the data array
        const unsigned char *sliceStart = data + (sliceIndex - 1) * width * height;
        slice.resize(width * height);
        std::memcpy(slice.data(), sliceStart, width * height);

    } else if (plane == "x-z") {
        if (sliceIndex > height) {
            std::cerr << "Slice index out of range for x-z plane." << std::endl;
            return {};
        }
        // Copy the data for the desired slice into the slice vector
        slice.resize(width * depth);
        for (int z = 0; z < depth; ++z) {
            for (int x = 0; x < width; ++x) {
                slice[z * width + x] = data[z * width * height + (sliceIndex - 1) * width + x];
            }
        }

    } else if (plane == "y-z") {
        if (sliceIndex > width) {
            std::cerr << "Slice index out of range for y-z plane." << std::endl;
            return {};
        }
        // Copy the data for the desired slice into the slice vector
        slice.resize(height * depth);
        for (int z = 0; z < depth; ++z) {
            for (int y = 0; y < height; ++y) {
                slice[z * height + y] = data[z * width * height + y * width + (sliceIndex - 1)];
            }
        }

    } else {
        std::cerr << "Invalid plane specified. Valid planes are 'x-y', 'x-z', and 'y-z'." << std::endl;
    }

    return slice;
}
