/**
 * @file Filter.h
 *
 * @brief Defines interfaces for 2D and 3D filtering operations on images and volume data.
 *
 * This file contains the IFilter2D and IFilter3D interfaces, which establish the foundational
 * structure for implementing filters on 2D images and 3D volume data, respectively. These interfaces
 * are designed to enforce a uniform approach to applying various filtering techniques across different
 * data dimensions. They are integral to the Advanced Programming Group's efforts in standardizing and
 * enhancing the tools available for image and volume data manipulation and processing.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_FILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_FILTER_H

#include "Image.h"
#include "Volume.h"

// Interface for 3D filters
class IFilter3D {
public:
    /**
     * Destructor for IFilter3D.
     *
     * The destructor is declared as virtual to ensure that the destructor of any derived class is called when
     * an object of the derived class is deleted through a pointer to the base class.
     */
    virtual ~IFilter3D() = default;

    /**
     * Applies a filter to a 3D volume.
     *
     * This method applies a filter to a 3D volume, modifying the volume data in place.
     *
     * @param volume: The volume to which the filter will be applied.
     */
    virtual void apply(Volume &volume) = 0;
};

// Interface for 2D filters
class IFilter2D {
public:
    /**
     * Destructor for IFilter2D.
     *
     * The destructor is declared as virtual to ensure that the destructor of any derived class is called when
     * an object of the derived class is deleted through a pointer to the base class.
     */
    virtual ~IFilter2D() = default;

    /**
     * Applies a filter to a 2D image.
     *
     * This method applies a filter to a 2D image, modifying the image data in place.
     *
     * @param image: The image to which the filter will be applied.
     */
    virtual void apply(Image &image) = 0;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_FILTER_H
