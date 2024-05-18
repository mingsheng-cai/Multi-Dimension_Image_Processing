/**
 * @file Slice.h
 *
 * @brief Facilitates extraction of 2D slices from 3D volume data.
 *
 * The Slice class is specifically designed to extract 2D slices from 3D volumetric data along
 * specified planes (axial, coronal, or sagittal). This functionality is critical in medical imaging,
 * scientific research, and 3D data analysis, where examining specific cross-sections of a dataset
 * can provide insightful information about its internal structure. By offering a method to obtain
 * plane slices at given indices, the class enables detailed examination and manipulation of 3D volume data.
 * The Slice class is an integral part of the data processing toolkit developed by the Advanced Programming Group,
 * focusing on high efficiency and precision in handling volumetric data.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_SLICE_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_SLICE_H

#include "Volume.h"

#include <vector>
#include <string>

class Slice {
public:
    /**
     * Retrieves a specific slice from a 3D volume
     *
     * This static member function of the Slice class extracts and returns a specific slice from a 3D volume, given the volume's
     * dimensions, the raw data, the desired plane for slicing ('x-y', 'x-z', 'y-z'), and the slice index. The function first checks
     * the validity of the slice index and the specified plane. Depending on the plane, it computes the starting position of the slice
     * in the volume's data array and copies the relevant data into a vector of unsigned char, which it then returns. If the slice index
     * is out of range for the specified plane or if an invalid plane is specified, the function will print an error message and return
     * an empty vector. This function allows for flexible access to different orientations of slices within the volume, facilitating
     * various analyses and visualizations of 3D data.
     *
     * @param width: The width of the volume.
     * @param height: The height of the volume.
     * @param depth: The depth of the volume.
     * @param data: A pointer to the volume's raw data.
     * @param plane: A string specifying the plane of the slice ('x-y', 'x-z', 'y-z').
     * @param sliceIndex: An integer indicating the index of the slice to retrieve, starting from 1.
     *
     * @return: A vector of unsigned char containing the data of the requested slice. Returns an empty vector if an error occurs.
     */
    static std::vector<unsigned char>
    getPlaneSlice(int width, int height, int depth, const unsigned char *data, const std::string &plane,
                  int sliceIndex);

private:
    /**
     * Default constructor for the Slice class.
     *
     * The default constructor of the Slice class is private and deleted to prevent the creation of Slice objects. The Slice class
     * provides a static member function for extracting slices from 3D volumes and does not require instantiation. By making the
     * constructor private and deleted, the class enforces this design pattern and ensures that no Slice objects can be created.
     */
    Slice() = delete;

    /**
     * Destructor for the Slice class.
     *
     * The destructor of the Slice class is private and deleted to prevent the destruction of Slice objects. Since the Slice class
     * does not have any member variables or instance-specific functionality, there is no need to create or destroy Slice objects.
     * By making the destructor private and deleted, the class enforces this design pattern and ensures that no Slice objects can be
     * destroyed, maintaining the static nature of the Slice class.
     */
    ~Slice() = delete;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_SLICE_H
