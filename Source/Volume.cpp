/**
 * @file Volume.cpp
 *
 * @brief Manages and manipulates 3D volumetric data.
 *
 * The Volume class encapsulates 3D volumetric data, providing functionalities to load data from multiple image files or a directory,
 * update internal data, and save specific slices or projections to files. It supports extracting slices along 'x-y', 'x-z', or 'y-z'
 * planes and computing various intensity projections such as Maximum, Minimum, Average, and Median Intensity Projections. This
 * functionality is essential for analyzing 3D data in medical imaging, scientific visualization, and other fields requiring volumetric
 * data manipulation. The class ensures efficient handling of large datasets and integrates with external libraries like stb_image for
 * reading and writing image files, making it a versatile tool for 3D data processing.
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

#include "Volume.h"
#include "Projection.h"
#include "Slice.h"
#include "Algorithm.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>
#include <filesystem>
#include <cstring>
#include <variant>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

namespace fs = std::filesystem;

// Constructors and Destructors
Volume::Volume() : width(0), height(0), depth(0), data(nullptr) {}

Volume::Volume(int width, int height, int depth) : width(width), height(height), depth(depth), data(nullptr) {}

Volume::Volume(int width, int height, int depth, unsigned char *data) : width(width), height(height), depth(depth),
                                                                        data(data) {}

Volume::~Volume() {}

// Getters
int Volume::getWidth() const {
    return width;
}

int Volume::getHeight() const {
    return height;
}

int Volume::getDepth() const {
    return depth;
}

unsigned char *Volume::getData() const {
    return data; // Return a pointer to the volume's data buffer
}

unsigned char Volume::getVoxel(int x, int y, int z) const {
    // Check if the coordinates are within the bounds of the volume
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        std::cerr << "Error: Voxel coordinates out of bounds." << std::endl;
        return 0;
    }

    // Calculate the index of the voxel in the volume's data array
    return data[z * width * height + y * width + x];
}

// Setters
void Volume::setWidth(int width) {
    this->width = width;
}

void Volume::setHeight(int height) {
    this->height = height;
}

void Volume::setDepth(int depth) {
    this->depth = depth;
}

void Volume::updateData(const std::vector<unsigned char> &newData) {
    // Ensure the new data size matches the volume size
    if (newData.size() != width * height * depth) {
        std::cerr << "Error: New data size does not match the volume size." << std::endl;
        return;
    }

    // Allocate new memory block if data is nullptr or reuse existing memory
    if (data == nullptr) {
        data = new unsigned char[newData.size()];
    }

    // Copy the new data into the volume's data array
    std::copy(newData.begin(), newData.end(), data);
}

bool Volume::loadFromFiles(const std::vector<std::string> &paths) {
    std::cout << "Loading volume from " << paths.size() << " files..." << std::endl;

    depth = paths.size();
    if (depth == 0) {
        std::cerr << "Error: No paths provided for volume loading." << std::endl;
        return false;
    }

    int channels;
    // Assuming all images have the same size and number of channels
    data = stbi_load(paths[0].c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading volume slice: " << paths[0] << std::endl;
        return false;
    }
    size_t sliceSize = width * height * channels;
    unsigned char *volumeData = (unsigned char *) malloc(sliceSize * depth);
    if (!volumeData) {
        std::cerr << "Failed to allocate memory for volume data." << std::endl;
        return false;
    }
    memcpy(volumeData, data, sliceSize);
    stbi_image_free(data);

    for (int i = 1; i < depth; ++i) {
        data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
        if (!data) {
            std::cerr << "Error loading volume slice: " << paths[i] << std::endl;
            free(volumeData);
            return false;
        }
        memcpy(volumeData + sliceSize * i, data, sliceSize);
        stbi_image_free(data);
    }

    data = volumeData;

    std::cout << "Volume loaded with size " << width << " x " << height << " x " << depth << " with " << channels
              << " channel(s)." << std::endl;

    return true;
}


bool Volume::loadFromDirectory(const std::string &directoryPath) {
    std::vector<std::string> paths;

    // Iterate over the directory and add the paths of all regular files to the vector
    try {
        for (const auto &entry: fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                paths.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }

    // Make sure at least one image file was found
    if (paths.empty()) {
        std::cerr << "Error: No image files found in the provided directory." << std::endl;
        return false;
    }

    // Sort the paths to ensure the images are loaded in the correct order
    Algorithm::quickSort(paths, 0, paths.size() - 1);

    // Use the loadFromFiles member function to load the volume from the collected paths
    return loadFromFiles(paths);
}

void Volume::save(const std::string &path, const std::string &plane) const {
    // Check if the plane is valid
    if (plane != "x-y" && plane != "x-z" && plane != "y-z") {
        std::cerr << "Invalid plane specified. Valid planes are 'x-y', 'x-z', and 'y-z'." << std::endl;
        return;
    }

    // Check if the output directory exists, and create it if it doesn't
    if (!fs::exists(path)) {
        if (!fs::create_directories(path)) { // create_directories 无错误时创建多级目录
            std::cerr << "Error: Failed to create output directory." << std::endl;
            return;
        }
    }

    // If no option is provided, save all slices based on the plane
    int numSlices = (plane == "x-y") ? depth : ((plane == "x-z") ? height : ((plane == "y-z") ? width : 0));

    for (int i = 1; i <= numSlices; ++i) {
        auto sliceData = Slice::getPlaneSlice(width, height, depth, data, plane, i);
        std::string fullPath = path + "/slice_" + std::to_string(i) + ".png";
        if (plane == "x-y") {
            stbi_write_png(fullPath.c_str(), width, height, 1, sliceData.data(), width);
        } else if (plane == "x-z") {
            // For x-z, height becomes the number of slices, width stays the same, and depth is the height of each slice.
            stbi_write_png(fullPath.c_str(), width, depth, 1, sliceData.data(), width);
        } else if (plane == "y-z") {
            // For y-z, width becomes the number of slices, height stays the same, and depth is the height of each slice.
            stbi_write_png(fullPath.c_str(), height, depth, 1, sliceData.data(), height);
        }
    }

}

void Volume::save(const std::string &path, const std::string &plane, int sliceIndex) const {
    // Check if the plane is valid
    if (plane != "x-y" && plane != "x-z" && plane != "y-z") {
        std::cerr << "Invalid plane specified. Valid planes are 'x-y', 'x-z', and 'y-z'." << std::endl;
        return;
    }

    // Check if the output directory exists, and create it if it doesn't
    if (!fs::exists(path)) {
        if (!fs::create_directories(path)) { // create_directories 无错误时创建多级目录
            std::cerr << "Error: Failed to create output directory." << std::endl;
            return;
        }
    }

    // Check the slice index
    if (sliceIndex < 1 || sliceIndex > (plane == "x-y" ? depth : (plane == "x-z" ? height : width))) {
        std::cerr << "Invalid slice index specified." << std::endl;
        return;
    }

    // Save a specific slice
    auto sliceData = Slice::getPlaneSlice(width, height, depth, data, plane, sliceIndex);
    std::string fullPath = path + "/slice_" + std::to_string(sliceIndex) + ".png";
    if (plane == "x-y") {
        stbi_write_png(fullPath.c_str(), width, height, 1, sliceData.data(), width);
    } else if (plane == "x-z") {
        stbi_write_png(fullPath.c_str(), width, depth, 1, sliceData.data(), width);
    } else if (plane == "y-z") {
        stbi_write_png(fullPath.c_str(), height, depth, 1, sliceData.data(), height);
    }
}

void Volume::save(const std::string &path, const std::string &plane, std::string projector) const {
    // Check if the plane is valid
    if (plane != "x-y") {
        std::cerr << "Invalid plane specified. Valid planes are 'x-y'." << std::endl;
        return;
    }

    // Check the projector type
    if (projector != "MIP" && projector != "MinIP" && projector != "AIP" && projector != "MedIP") {
        std::cerr << "Invalid projector specified. Valid projectors are 'MIP', 'MinIP', 'AIP', and 'MedIP'."
                  << std::endl;
        return;
    }

    // Check if the output directory exists, and create it if it doesn't
    if (!fs::exists(path)) {
        if (!fs::create_directories(path)) { // create_directories 无错误时创建多级目录
            std::cerr << "Error: Failed to create output directory." << std::endl;
            return;
        }
    }

    // Save a specific projection in the x-y plane, such as MIP, MinIP, AIP, or MedIP
    std::vector<unsigned char> projectionData;
    if (projector == "MIP") {
        projectionData = Projection::maximumIntensityProjection(width, height, depth, data);
    } else if (projector == "MinIP") {
        projectionData = Projection::minimumIntensityProjection(width, height, depth, data);
    } else if (projector == "AIP") {
        projectionData = Projection::averageIntensityProjection(width, height, depth, data);
    } else if (projector == "MedIP") {
        projectionData = Projection::medianIntensityProjection(width, height, depth, data);
    }
    std::string fullPath = path + "/" + projector + ".png";
    stbi_write_png(fullPath.c_str(), width, height, 1, projectionData.data(), width);
}

void Volume::save(const std::string &path, const std::string &plane, const std::string &projector, int begin,
                  int end) const {
    // Check if the plane is valid
    if (plane != "x-y") {
        std::cerr << "Currently, range-based projection is only supported for the x-y plane." << std::endl;
        return;
    }

    if (begin > end || begin < 1 || end > depth) {
        std::cerr << "Invalid range specified. Please ensure 1 <= begin <= end <= depth." << std::endl;
        return;
    }

    if (!fs::exists(path) && !fs::create_directories(path)) {
        std::cerr << "Error: Failed to create output directory." << std::endl;
        return;
    }

    // Adjust begin and end to zero-based indexing for internal use
    begin--;
    end--;

    // Prepare a vector to hold the selected slices' data
    std::vector<unsigned char> selectedSlicesData((end - begin + 1) * width * height);

    // Copy the data from the specified range
    for (int i = begin; i <= end; ++i) {
        std::memcpy(&selectedSlicesData[(i - begin) * width * height], &data[i * width * height], width * height);
    }

    std::vector<unsigned char> projectionData;
    if (projector == "MIP") {
        projectionData = Projection::maximumIntensityProjection(width, height, end - begin + 1,
                                                                selectedSlicesData.data());
    } else if (projector == "MinIP") {
        projectionData = Projection::minimumIntensityProjection(width, height, end - begin + 1,
                                                                selectedSlicesData.data());
    } else if (projector == "AIP") {
        projectionData = Projection::averageIntensityProjection(width, height, end - begin + 1,
                                                                selectedSlicesData.data());
    } else if (projector == "MedIP") {
        projectionData = Projection::medianIntensityProjection(width, height, end - begin + 1,
                                                               selectedSlicesData.data());
    } else {
        std::cerr << "Invalid projector specified. Valid projectors are 'MIP', 'MinIP', 'AIP', and 'MedIP'."
                  << std::endl;
        return;
    }

    std::string fullPath =
            path + "/" + projector + "_range_" + std::to_string(begin + 1) + "_" + std::to_string(end + 1) + ".png";
    stbi_write_png(fullPath.c_str(), width, height, 1, projectionData.data(), width);
}
