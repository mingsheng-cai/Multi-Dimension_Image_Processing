/**
 * @file Volume.h
 *
 * @brief Manages 3D volumetric data for processing and analysis.
 *
 * The Volume class is designed to encapsulate 3D volumetric data, providing functionalities
 * for loading, saving, and manipulating this data. It supports loading volume data from individual
 * files or an entire directory and saving processed data with flexible options. This class plays a
 * crucial role in applications involving 3D data visualization, medical imaging analysis, and scientific
 * research, where handling and analyzing volumetric data efficiently is essential. By preventing copy
 * construction and assignment, it ensures that volume data management is both safe and efficient. The
 * Volume class is a foundational component of the data manipulation toolkit developed by the Advanced
 * Programming Group, aimed at facilitating sophisticated 3D data processing and analysis tasks.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_VOLUME_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_VOLUME_H

#include <vector>
#include <optional>
#include <variant>
#include <string>

class Volume {
private:
    int width, height, depth; // Size of the volume
    unsigned char *data; // Volume data

    /**
     * @brief Load volume data from a single file.
     *
     * This function loads volume data from a single file and updates the volume's data field.
     *
     * @param path The path to the file containing the volume data.
     */
    Volume(const Volume &) = delete;

    /**
     * @brief Prevents assignment of volume data.
     *
     * This function prevents the assignment of volume data by deleting the assignment operator.
     *
     * @param volume The volume to assign to.
     *
     * @return The assigned volume.
     */
    Volume &operator=(const Volume &) = delete;

public:
    /**
     * @brief Default constructor for the Volume class.
     *
     * This constructor initializes a Volume object with default values.
     */
    Volume();

    /**
     * @brief Constructor for the Volume class.
     *
     * This constructor initializes a Volume object with the specified width, height, and depth.
     *
     * @param width The width of the volume.
     * @param height The height of the volume.
     * @param depth The depth of the volume.
     */
    Volume(int width, int height, int depth);

    /**
     * @brief Constructor for the Volume class.
     *
     * This constructor initializes a Volume object with the specified width, height, depth, and data.
     *
     * @param width The width of the volume.
     * @param height The height of the volume.
     * @param depth The depth of the volume.
     * @param data The volume data.
     */
    Volume(int width, int height, int depth, unsigned char *data);

    /**
     * @brief Destructor for the Volume class.
     *
     * This destructor deallocates the memory used by the volume data.
     */
    ~Volume();

    /**
     * @brief Get the width of the volume.
     *
     * This function returns the width of the volume.
     *
     * @return The width of the volume.
     */
    int getWidth() const;

    /**
     * @brief Get the height of the volume.
     *
     * This function returns the height of the volume.
     *
     * @return The height of the volume.
     */
    int getHeight() const;

    /**
     * @brief Get the depth of the volume.
     *
     * This function returns the depth of the volume.
     *
     * @return The depth of the volume.
     */
    int getDepth() const;

    /**
     * @brief Get the volume data.
     *
     * This function returns the volume data.
     *
     * @return The volume data.
     */
    unsigned char *getData() const;

    /**
     * @brief Get the voxel value at the specified coordinates.
     *
     * This function returns the voxel value at the specified coordinates.
     *
     * @param x The x-coordinate of the voxel.
     * @param y The y-coordinate of the voxel.
     * @param z The z-coordinate of the voxel.
     *
     * @return The voxel value at the specified coordinates.
     */
    unsigned char getVoxel(int x, int y, int z) const;

    /**
     * @brief Set the width of the volume.
     *
     * This function sets the width of the volume.
     *
     * @param width The width of the volume.
     */
    void setWidth(int width);

    /**
     * @brief Set the height of the volume.
     *
     * This function sets the height of the volume.
     *
     * @param height The height of the volume.
     */
    void setHeight(int height);

    /**
     * @brief Set the depth of the volume.
     *
     * This function sets the depth of the volume.
     *
     * @param depth The depth of the volume.
     */
    void setDepth(int depth);

    /**
     * Updates the volume data with new data
     *
     * This member function of the Volume class updates the volume's data array with new data provided via the newData parameter.
     * Before proceeding with the update, it checks if the size of the new data matches the expected size of the volume (calculated
     * as width * height * depth). If the sizes do not match, it prints an error message and aborts the update. If the volume's data
     * pointer is null (indicating that the volume has not been initialized with data), it allocates new memory to store the newData.
     * Otherwise, it reuses the existing memory block and copies the newData into the volume's data array. This function ensures that
     * the volume's data is kept up-to-date with any changes or transformations applied externally.
     *
     * @param newData: A constant reference to a vector of unsigned char, representing the new data to be copied into the volume's data array.
     *
     * @return: None
     */
    void updateData(const std::vector<unsigned char> &newData);

    /**
     * Loads a 3D volume from multiple image files
     *
     * This member function of the Volume class loads a series of images from the specified file paths to construct a 3D
     * volume. The images are assumed to have the same dimensions and number of channels. The function initializes the
     * volume's depth based on the number of paths provided, checks if at least one path is provided, and then loads each
     * image in sequence. The images are concatenated into a single data buffer representing the 3D volume. If any image
     * fails to load, or if memory allocation for the entire volume data fails, it prints an error message to standard error
     * and cleans up any allocated resources.
     *
     * @param paths: A vector of strings representing the paths to the image files that comprise the volume.
     *
     * @return: A boolean value indicating the success (true) or failure (false) of loading the volume.
     */
    bool loadFromFiles(const std::vector<std::string> &paths);

    /**
     * Loads a 3D volume from image files located in a specified directory
     *
     * This member function of the Volume class loads a series of image files from a given directory to construct a 3D volume.
     * It iterates through the directory, collecting paths of all regular files. These paths are then sorted to ensure that
     * the images are loaded in the correct order, which is crucial for correctly assembling the 3D volume. The function
     * leverages the loadFromFiles member function to load the images into the volume. If the directory cannot be read
     * or contains no image files, the function prints an error message and returns false.
     *
     * @param directoryPath: A string representing the path to the directory containing the image files to be loaded.
     *
     * @return: A boolean value indicating the success (true) or failure (false) of loading the volume from the directory.
     */
    bool loadFromDirectory(const std::string &directoryPath);

    /**
     * Saves all slices along a specified plane to files
     *
     * This member function of the Volume class saves all slices along the specified plane to files in the specified directory. The
     * function first checks if the plane is valid, if the output directory exists, and if the plane is valid. If any of these checks
     * fail, it prints an error message and returns. If the output directory does not exist, the function attempts to create it. It then
     * iterates through all slices along the specified plane, extracts each slice from the volume's data, saves the result to a file in the
     * specified directory, and uses the stb_image_write library to write the slice data to a PNG file.
     *
     * @param path: A string representing the path to the directory where the slices will be saved.
     * @param plane: A string representing the plane along which the slices will be extracted. Valid planes are 'x-y', 'x-z', and 'y-z'.
     *
     * @return: None
     */
    void save(const std::string &path, const std::string &plane) const;

    /**
     * Saves a specific slice to a file
     *
     * This member function of the Volume class saves a specific slice along the specified plane to a file. The function first checks
     * if the plane is valid, if the output directory exists, and if the slice index is within the bounds of the volume. If any of these
     * checks fail, it prints an error message and returns. If the output directory does not exist, the function attempts to create it.
     * It then extracts the specified slice from the volume's data, saves the result to a file in the specified directory, and uses the
     * stb_image_write library to write the slice data to a PNG file.
     *
     * @param path: A string representing the path to the directory where the slice will be saved.
     * @param plane: A string representing the plane along which the slice will be extracted. Valid planes are 'x-y', 'x-z', and 'y-z'.
     * @param sliceIndex: An integer representing the index of the slice to be saved.
     *
     * @return: None
     */
    void save(const std::string &path, const std::string &plane, int sliceIndex) const;

    /**
     * Saves a specific projection to a file
     *
     * This member function of the Volume class computes a specific projection along the specified plane and saves the result to a file.
     * The function first checks if the plane and projector are valid, and if the output directory exists. If any of these checks fail,
     * it prints an error message and returns. If the output directory does not exist, the function attempts to create it. It then computes
     * the specified projection using the Projection class and saves the result to a file in the specified directory. The function uses the
     * stb_image_write library to write the projection data to a PNG file.
     *
     * @param path: A string representing the path to the directory where the projection will be saved.
     * @param plane: A string representing the plane along which the projection will be computed. Valid planes are 'x-y', 'x-z', and 'y-z'.
     * @param projector: A string representing the type of projection to be computed. Valid projectors are 'MIP', 'MinIP', 'AIP', and 'MedIP'.
     *
     * @return: None
     */
    void save(const std::string &path, const std::string &plane, std::string projector) const;

    /**
     * Saves a range-based projection to a file
     *
     * This member function of the Volume class computes a range-based projection along the specified plane and saves the result to a file.
     * The function first checks if the plane and projector are valid, and if the specified range is within the bounds of the volume. If any
     * of these checks fail, it prints an error message and returns. If the output directory does not exist, the function attempts to create it.
     * It then extracts the specified range of slices from the volume's data, computes the projection using the specified projector, and saves the
     * result to a file in the specified directory. The function uses the stb_image_write library to write the projection data to a PNG file.
     *
     * @param path: A string representing the path to the directory where the projection will be saved.
     * @param plane: A string representing the plane along which the projection will be computed. Valid planes are 'x-y', 'x-z', and 'y-z'.
     * @param projector: A string representing the type of projection to be computed. Valid projectors are 'MIP', 'MinIP', 'AIP', and 'MedIP'.
     * @param begin: An integer representing the starting index of the range of slices to be projected.
     * @param end: An integer representing the ending index of the range of slices to be projected.
     *
     * @return: None
     */
    void
    save(const std::string &path, const std::string &plane, const std::string &projector, int begin, int end) const;

};


#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_VOLUME_H
