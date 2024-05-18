/**
 * @file Median2DFilter.h
 *
 * @brief Implements a Median 2D filter for noise reduction in images.
 *
 * The Median2DFilter class applies a median filtering operation to 2D images to reduce noise
 * while preserving edges. This technique is particularly useful in pre-processing for other image
 * analysis tasks, as it helps to reduce salt-and-pepper noise without blurring sharp edges in the image.
 * The filter supports customizable kernel sizes and padding types, allowing for flexibility in handling
 * different types of images and noise levels. Part of the tools developed by the Advanced Programming
 * Group, this class enhances the suite of image processing capabilities with a focus on maintaining image
 * quality during noise reduction.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN2DFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN2DFILTER_H

#include "Image.h"
#include "Padding.h"

#include <vector>

class Median2DFilter {
private:
    int kernelSize; // Kernel size
    PaddingType paddingType; // Padding type

    /**
     * Calculates the median value of a pixel window.
     *
     * This helper function determines the median value within a given window of pixel values. It employs the quick select algorithm
     * to efficiently find the median, which is particularly effective for non-linear filtering operations like median filtering. The
     * function handles both odd and even-sized windows, returning the middle value for odd-sized windows or the average of the two
     * middle values for even-sized windows. This method ensures that the median filter can be applied consistently across the entire
     * image, including edge pixels.
     *
     * @param window: A vector of unsigned char representing the intensity values of pixels within the kernel window.
     * @return The median intensity value as an unsigned char.
     */
    static unsigned char median(std::vector<unsigned char> &window);

public:
    /**
     * Constructor for the Median2DFilter class.
     *
     * Initializes a Median2DFilter object with a specified kernel size and padding type. Ensures that the kernel size is odd,
     * which is necessary for symmetrically surrounding each pixel with neighbors. This requirement is crucial for the correct
     * application of the median filter. If an even kernel size is provided, an exception is thrown. The padding type determines
     * the strategy for handling pixels at the borders of the image, ensuring consistent filtering across the entire image.
     *
     * @param kernelSize: The size of the kernel, must be an odd number for symmetric application.
     * @param paddingType: The type of padding to use at the image borders, determining how edge pixels are treated.
     * @throws std::invalid_argument if the kernelSize is not an odd number.
     */
    Median2DFilter(int kernelSize, PaddingType paddingType = PaddingType::ZeroPadding);

    /**
     * Applies median filtering to an image.
     *
     * This method processes the provided Image object, applying median filtering to reduce noise while preserving edges. It operates
     * by sliding a window, defined by the kernel size, across the image and replacing each pixel's value with the median value of
     * its neighborhood. This approach is effective at removing salt-and-pepper noise. The method handles different channels of the
     * image separately, maintaining the color integrity of the original image.
     *
     * @param image: A reference to the Image object to be filtered. The image is modified in place, receiving the filtered output.
     */
    void apply(Image &image) const;

};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_MEDIAN2DFILTER_H
