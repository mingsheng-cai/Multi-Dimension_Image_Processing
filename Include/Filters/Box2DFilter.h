/**
 * @file Box2DFilter.h
 *
 * @brief Implements a 2D box filter for image processing.
 *
 * The Box2DFilter class provides functionality for applying a 2D box filtering operation on images.
 * It supports various padding strategies to handle edge cases. The primary purpose of this filter is to perform
 * spatial averaging across an image, which can be useful for blurring or smoothing. This implementation allows
 * for customization of the kernel size and padding type, making it versatile for different image processing needs.
 * This class is a contribution of the Advanced Programming Group, aimed at enhancing tools available for image
 * manipulation and processing tasks.
 *
 * @date Created on March 21, 2024
 *
 * @authors
 * Advanced Programming Group Radix Sort
 *   - Benjamin Duncan (edsml-bd1023)
 *   - Boyang Hu (edsml-bh223)
 *   - Chawk Chamoun (edsml-cc8915)
 *   - Mingsheng Cai (acse-sc4623)
 *   - Moyu Zhang (acse-mz223)
 *   - Ryan Benney (acse-rgb123)
 */

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_BOX2DFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_BOX2DFILTER_H

#include "Image.h"
#include "Padding.h"

#include <vector>

class Box2DFilter {
private:
    int kernelSize; // Size of the kernel
    PaddingType paddingType; // Padding strategy

public:
    /**
     * Constructor for the Box2DFilter class.
     *
     * Initializes a Box2DFilter object with a specified kernel size and padding type. The constructor checks that the kernel size is
     * an odd number, ensuring a symmetric area around each pixel for the filter application. This symmetry is critical for the
     * uniform application of the filter across the image. If the kernel size is not odd, an exception is thrown, as the filter
     * operation requires a central pixel. The padding type determines how the filter handles pixels at the image boundaries, allowing
     * for flexible handling of edge cases.
     *
     * @param kernelSize: The size of the kernel, which must be an odd number to ensure symmetry around each pixel.
     * @param paddingType: The padding strategy to use when the filter kernel overlaps the image boundaries.
     * @throws std::invalid_argument if the kernelSize is not an odd number, ensuring proper filter application.
     */
    Box2DFilter(int kernelSize, PaddingType paddingType = PaddingType::ZeroPadding);

    /**
     * Applies a 2D box filter to an image.
     *
     * This method implements the spatial averaging of pixel values across a specified neighborhood around each pixel in the image,
     * based on the kernel size and padding type provided during the object's construction. The process involves iterating over
     * each pixel in the image, collecting pixel values from its neighborhood as defined by the kernel size, and then calculating
     * the average of these values. The result is a blurred or smoothed version of the original image, with the degree of blurring
     * dependent on the size of the kernel. Edge pixels are handled according to the specified padding strategy, which determines
     * how pixels outside the image boundaries are treated for the purposes of the filter.
     *
     * @param image: A reference to an Image object representing the image to be processed. The Image object must be initialized
     * and loaded with data prior to calling this method. The method modifies the Image object in place, replacing its pixel data
     * with the filtered results.
     */
    void apply(Image &image) const;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_BOX2DFILTER_H
