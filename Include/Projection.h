/**
 * @file Projection.h
 *
 * @brief Provides projection techniques for 3D data visualization.
 *
 * The Projection class encompasses methods to generate various types of projections from 3D data,
 * facilitating the visualization of volumetric data in a 2D format. It supports maximum, minimum,
 * average, and median intensity projections, each offering a different perspective on the 3D data's
 * structure and composition. These projection methods are crucial for analyzing and interpreting
 * volumetric datasets in fields such as medical imaging, scientific visualization, and computer graphics.
 * Implementing efficient algorithms for these projections, the class aims to deliver high-performance
 * tools as part of the visualization toolkit developed by the Advanced Programming Group.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PROJECTION_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PROJECTION_H

#include <vector>

class Projection {
public:
    /**
     * Computes the Maximum Intensity Projection (MIP) of a 3D volume
     *
     * This static member function of the Projection class calculates the Maximum Intensity Projection of a given 3D volume.
     * MIP is a volume rendering method that projects the voxel with the highest intensity value along a particular direction,
     * in this case, the z-axis (depth), onto a 2D plane. This function iterates through each voxel in the volume and, for each
     * (x, y) position on the projection plane, it selects the maximum intensity value found along the z-axis. The result is a
     * 2D image (represented as a vector of unsigned char) where each pixel corresponds to the maximum intensity value found
     * at that (x, y) position through the entire depth of the volume. This technique is commonly used in medical imaging to
     * highlight areas of highest density or intensity in volumetric data.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     * @param data: A pointer to the volume's raw data.
     *
     * @return: A vector of unsigned char representing the 2D MIP image.
     */
    static std::vector<unsigned char>
    maximumIntensityProjection(int width, int height, int depth, const unsigned char *data);

    /**
     * Computes the Minimum Intensity Projection (MinIP) of a 3D volume
     *
     * This static member function of the Projection class calculates the Minimum Intensity Projection of a given 3D volume.
     * MinIP is a volume rendering technique that projects the voxel with the lowest intensity value along a specific direction,
     * in this case, the z-axis (depth), onto a 2D plane. This function iterates through each voxel in the volume and, for each
     * (x, y) position on the projection plane, it selects the minimum intensity value found along the z-axis. The result is a
     * 2D image (represented as a vector of unsigned char) where each pixel corresponds to the minimum intensity value found
     * at that (x, y) position throughout the entire depth of the volume. This technique can be useful for visualizing low-density
     * areas in volumetric data.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     * @param data: A pointer to the volume's raw data.
     *
     * @return: A vector of unsigned char representing the 2D MinIP image.
     */
    static std::vector<unsigned char>
    minimumIntensityProjection(int width, int height, int depth, const unsigned char *data);

    /**
     * Computes the Average Intensity Projection (AIP) of a 3D volume
     *
     * This static member function of the Projection class calculates the Average Intensity Projection of a given 3D volume.
     * AIP is a volume rendering method that projects the average intensity value of voxels along a particular direction,
     * in this case, the z-axis, onto a 2D plane. It iterates through each voxel in the volume, accumulates the intensity values
     * for each (x, y) position on the projection plane, and divides the total by the depth of the volume. The result is a 2D
     * image where each pixel represents the average intensity value found at that (x, y) position through the entire depth
     * of the volume. AIP is useful for visualizing the general structure and distribution of densities within the volume.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     * @param data: A pointer to the volume's raw data.
     *
     * @return: A vector of unsigned char representing the 2D AIP image.
     */
    static std::vector<unsigned char>
    averageIntensityProjection(int width, int height, int depth, const unsigned char *data);

    /**
     * Computes the Median Intensity Projection (MedIP) of a 3D volume
     *
     * This static member function of the Projection class calculates the Median Intensity Projection of a given 3D volume.
     * MedIP is a volume rendering technique that projects the median intensity value of voxels along a specific direction,
     * in this case, the z-axis, onto a 2D plane. This function iterates through each voxel in the volume and, for each (x, y)
     * position on the projection plane, it selects the median intensity value found along the z-axis from the depth of the
     * volume. The median is determined using the quickselect algorithm for efficiency. The result is a 2D image where each
     * pixel represents the median intensity value at that (x, y) position throughout the entire depth of the volume. MedIP
     * can provide a balanced visualization that may reduce the impact of outliers in highly variable volumetric data.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     * @param data: A pointer to the volume's raw data.
     *
     * @return: A vector of unsigned char representing the 2D MedIP image.
     */
    static std::vector<unsigned char>
    medianIntensityProjection(int width, int height, int depth, const unsigned char *data);
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PROJECTION_H
