/**
 * @file PaddingType.h
 *
 * @brief Defines padding strategies for image processing and a utility class for applying padding.
 *
 * This file introduces an enumeration for different types of padding strategies, including Zero Padding,
 * Edge Replication, and Reflect Padding. These strategies are crucial for handling border effects in filter
 * operations on images. The Padding class provides a static method to retrieve a pixel window around a specified
 * point in an image, applying the chosen padding strategy. This functionality is essential for image filtering
 * tasks that require consideration of edge and corner pixels. Developed as part of the Advanced Programming
 * Group's initiatives, this component enhances image processing capabilities by offering flexible handling
 * of image borders during various operations.
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

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PADDINGTYPE_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PADDING_H

#include "Image.h"

#include <vector>

enum class PaddingType {
    ZeroPadding, // Zero padding
    EdgeReplication, // Edge replication
    ReflectPadding // Reflect padding
};

class Padding {
public:
    /**
     * Retrieves a pixel window around a specified location in an image, applying the selected padding strategy.
     *
     * This function extracts a window of pixel values centered around a specified pixel location (x, y) in the provided image.
     * The size of the window is determined by the kernelSize parameter. The function supports various padding strategies to handle
     * pixels near the image borders effectively. These strategies include zero padding (padding with zeros), edge replication (replicating
     * the edge pixels), and reflect padding (mirroring the pixels near the edge). This functionality is crucial for filter operations
     * that require contextual information about a pixel's neighborhood, ensuring consistent processing across the entire image, including
     * its edges.
     *
     * @param image: A constant reference to the Image object from which the pixel window will be extracted.
     * @param x: The x-coordinate of the central pixel in the window.
     * @param y: The y-coordinate of the central pixel in the window.
     * @param c: The channel of the image to be processed.
     * @param kernelSize: The size of the window to be extracted, which determines how far from the central pixel the window extends.
     * @param paddingType: The padding strategy to be applied when the window extends beyond the image boundaries.
     * @return A vector of unsigned char values representing the pixel intensities within the window. The vector size corresponds to
     * the total number of pixels within the window, adjusted for the selected padding strategy as necessary.
     * @throws std::invalid_argument if an unsupported padding type is specified.
     */
    static std::vector<unsigned char>
    getPixelWindow(const Image &image, int x, int y, int c, int kernelSize, PaddingType paddingType);
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PADDINGTYPE_H
