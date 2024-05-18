/**
 * @file EdgeFilter.h
 *
 * @brief Implements edge detection filters for image processing.
 *
 * The EdgeFilter class enables edge detection in images through the application of various edge detection algorithms,
 * including Sobel, Prewitt, Scharr, and Roberts filters. It allows for customization of the filter type and padding strategy,
 * accommodating different requirements for edge detection tasks. This class facilitates the extraction of edges, which is
 * a crucial step in many image processing applications such as feature detection, image segmentation, and object recognition.
 * Developed by the Advanced Programming Group, this tool enhances the capabilities for image analysis and processing.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_EDGEFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_EDGEFILTER_H

#include "Image.h"
#include "Padding.h"

#include <vector>

enum class FilterType {
    Sobel,
    Prewitt,
    Scharr,
    Roberts
};

class EdgeFilter {
private:
    FilterType filterType; // Add filter type attribute
    PaddingType paddingType; // Add padding type attribute

    /**
     * Applies the Sobel edge detection algorithm to an image.
     *
     * This method implements the Sobel edge detection algorithm, which uses two 3x3 kernels to calculate the gradient magnitude
     * at each pixel in the provided grayscale image. The gradient magnitude represents the edge strength. The resulting edge map
     * replaces the original image data. This method is suitable for highlighting horizontal and vertical edges in the image.
     *
     * @param image: A constant reference to an Image object to which the Sobel filter will be applied. The image must be in
     * grayscale format.
     */
    void applySobel(Image &image) const;

    /**
     * Applies the Prewitt edge detection algorithm to an image.
     *
     * This method utilizes the Prewitt operator to detect edges in the provided grayscale image. Similar to the Sobel filter, it employs
     * horizontal and vertical kernels to compute the gradient magnitude at each pixel, effectively highlighting the edges. The Prewitt
     * operator is known for its simplicity and effectiveness in edge detection, making it suitable for various image processing tasks
     * where edge delineation is required.
     *
     * @param image: A constant reference to an Image object to which the Prewitt filter will be applied. The image should be in grayscale
     * format for the algorithm to function correctly.
     */
    void applyPrewitt(Image &image) const;

    /**
     * Applies the Scharr edge detection algorithm to an image.
     *
     * The Scharr method is an enhancement over the Sobel operator, offering better rotation symmetry and a higher weight to pixels
     * directly adjacent to the center pixel. This method applies Scharr's specific kernels to calculate the gradient magnitude at each
     * pixel of the provided grayscale image, aiming to accurately detect edges with a higher sensitivity to subtle changes in intensity,
     * thereby producing a more defined edge map.
     *
     * @param image: A constant reference to an Image object to which the Scharr filter will be applied. It is essential that the image is
     * in grayscale format to ensure the algorithm performs as expected.
     */
    void applyScharr(Image &image) const;

    /**
     * Applies the Roberts Cross edge detection algorithm to an image.
     *
     * The Roberts Cross operator is one of the earliest yet effective methods for edge detection, focusing on highlighting high-frequency
     * components in the image. It computes the gradient magnitude using a pair of 2x2 convolution kernels. This simplicity makes it
     * particularly fast and suitable for detecting edges in images with minimal computational resources. Despite its age, it remains
     * effective for applications where quick edge detection is more critical than precision.
     *
     * @param image: A constant reference to an Image object to which the Roberts Cross filter will be applied. The algorithm expects the
     * image to be in grayscale format for accurate edge detection.
     */
    void applyRoberts(Image &image) const;

    /**
     * Checks if an image is in grayscale format.
     *
     * This method determines whether the provided Image object is a grayscale image by checking its number of color channels. An
     * image is considered grayscale if it has only one channel.
     *
     * @param image: A constant reference to an Image object to be checked.
     * @return True if the image has only one channel, indicating it is a grayscale image; false otherwise.
     */
    bool isGrayscale(const Image &image) const;

public:
    /**
     * Constructs an EdgeFilter object with the specified filter type and padding type.
     *
     * This constructor initializes an EdgeFilter object with the specified edge detection filter type and padding type. The filter
     * type determines the edge detection algorithm to be applied, while the padding type specifies the padding strategy to handle
     * edge pixels during convolution. The constructed EdgeFilter object can be used to apply edge detection to grayscale images.
     *
     * @param type: The type of edge detection filter to be used (Sobel, Prewitt, Scharr, or Roberts).
     * @param paddingType: The padding strategy to be applied during convolution (ZeroPadding, ReplicatePadding, or ReflectPadding).
     */
    EdgeFilter(FilterType type, PaddingType paddingType = PaddingType::ZeroPadding);

    /**
     * Applies the configured edge detection filter to an image.
     *
     * This method applies the selected edge detection algorithm to the provided Image object if the image is in grayscale format.
     * It first checks if the image is suitable for edge detection by calling isGrayscale. If the image is not in grayscale, an error
     * message is printed, and the function returns without modifying the image. Otherwise, it proceeds to apply the chosen edge
     * detection algorithm, updating the image with the detected edges.
     *
     * @param image: A reference to an Image object on which the edge detection filter will be applied. The Image object must be
     * initialized and loaded with image data prior to calling this method.
     */
    void apply(Image &image);
};

#endif // ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_EDGEFILTER_H
