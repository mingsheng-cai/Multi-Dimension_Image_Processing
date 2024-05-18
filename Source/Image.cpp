/**
 * @file Image.cpp
 *
 * @brief Implements basic image processing functionalities.
 *
 * The Image class provides fundamental functionalities for image processing, including loading, saving,
 * and converting images to grayscale. Leveraging the stb_image and stb_image_write libraries, this class
 * supports a wide range of image formats for both input and output operations. The convertToGrayscale method
 * utilizes the luminance method to transform color images into grayscale, reflecting human perception of color
 * brightness. This class is designed to serve as a foundation for more complex image processing tasks, offering
 * efficient and straightforward manipulation of image data.
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

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>
#include <filesystem>
#include <cstring>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

namespace fs = std::filesystem;

Image::Image() : width(0), height(0), channels(0), data(nullptr) {}

Image::Image(int width, int height, int channels, unsigned char *data)
        : width(width), height(height), channels(channels), data(nullptr) {
    if (data != nullptr) {
        this->data = new unsigned char[width * height * channels];
        memcpy(this->data, data, width * height * channels);
    }
}

Image::~Image() {
    // Free image data memory
    if (data) {
        stbi_image_free(data);
    }
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getChannels() const {
    return channels;
}

unsigned char *Image::getData() const {
    return data;
}

void Image::updateData(unsigned char *data) {
    // Free existing image data memory
    if (this->data) {
        delete[] this->data;
    }
    this->data = data;
}

void Image::setWidth(int width) {
    this->width = width;
}

void Image::setHeight(int height) {
    this->height = height;
}

void Image::setChannels(int channels) {
    this->channels = channels;
}

bool Image::loadFromFile(const std::string &path) {
    // Check if the image exists
    if (!fs::exists(path)) {
        std::cerr << "Error: Image file does not exist: " << path << std::endl;
        return false;
    }

    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading image: " << path << std::endl;
        return false;
    }
    return true;
}

bool Image::saveToFile(const std::string &path) const {
    // Check if image data exists
    if (!data) {
        std::cerr << "Error: No data to save" << std::endl;
        return false;
    }

    // Check if folder exists, if not create it
    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        std::string folder = path.substr(0, found);
        std::string command = "mkdir -p " + folder;
        system(command.c_str());
    }

    int success = stbi_write_png(path.c_str(), width, height, channels, data, width * channels);
    if (!success) {
        std::cerr << "Failed to save image to: " << path << std::endl;
        return false;
    }

    return true;
}
