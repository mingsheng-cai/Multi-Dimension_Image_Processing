/**
 * @file Image.h
 *
 * @brief Provides an Image class for basic image processing operations.
 *
 * The Image class supports basic image processing functionalities including loading, saving,
 * and converting images to grayscale. It is designed with a focus on handling image data
 * efficiently while providing a simple interface for image manipulation. This class handles
 * images as arrays of unsigned char, representing pixel data, and provides methods to load images
 * from files, save images to files, and convert color images to grayscale. The class also explicitly
 * bans copy construction and assignment to avoid unintentional deep copies of image data.
 * It is a part of the utility toolkit developed by the Advanced Programming Group.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_IMAGE_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_IMAGE_H

#include <string>

class Image {
private:
    int width, height, channels; // Size of the image
    unsigned char *data; // Image data

    /**
     * Private constructor to prevent copy construction.
     *
     * The copy constructor is declared private to prevent unintentional deep copies of image data.
     *
     * @param other The Image object to copy
     */
    Image(const Image &) = delete;

    /**
     * Private assignment operator to prevent assignment.
     *
     * The assignment operator is declared private to prevent unintentional deep copies of image data.
     *
     * @param other The Image object to assign
     * @return The reference to the assigned Image object
     */
    Image &operator=(const Image &) = delete;

public:
    /**
     * Default constructor for the Image class.
     *
     * The default constructor initializes the image dimensions and data to zero.
     */
    Image();

    /**
     * Constructor for the Image class with specified dimensions and data.
     *
     * This constructor initializes the image with the specified dimensions and data.
     *
     * @param width The width of the image
     * @param height The height of the image
     * @param channels The number of color channels in the image
     * @param data The image data as an array of unsigned char
     */
    Image(int width, int height, int channels, unsigned char *data);

    /**
     * Destructor for the Image class.
     *
     * The destructor frees the memory allocated for the image data.
     */
    ~Image();

    /**
     * Get the width of the image.
     *
     * This member function returns the width of the image.
     *
     * @return The width of the image
     */
    int getWidth() const;

    /**
     * Get the height of the image.
     *
     * This member function returns the height of the image.
     *
     * @return The height of the image
     */
    int getHeight() const;

    /**
     * Get the number of color channels in the image.
     *
     * This member function returns the number of color channels in the image.
     *
     * @return The number of color channels in the image
     */
    int getChannels() const;

    /**
     * Get the image data.
     *
     * This member function returns a pointer to the image data.
     *
     * @return A pointer to the image data
     */
    unsigned char *getData() const;

    /**
     * Update the image data.
     *
     * This member function updates the image data with the specified data.
     *
     * @param data The new image data as an array of unsigned char
     */
    void updateData(unsigned char *data);

    /**
     * Set the width of the image.
     *
     * This member function sets the width of the image.
     *
     * @param width The new width of the image
     */
    void setWidth(int width);

    /**
     * Set the height of the image.
     *
     * This member function sets the height of the image.
     *
     * @param height The new height of the image
     */
    void setHeight(int height);

    /**
     * Set the number of color channels in the image.
     *
     * This member function sets the number of color channels in the image.
     *
     * @param channels The new number of color channels in the image
     */
    void setChannels(int channels);

    /**
     * Loads an image from a file
     *
     * This member function of the Image class loads an image from the specified file path into the object's data buffer
     * using the stb_image library. It sets the image's width, height, and channels based on the loaded image's properties.
     * If the image cannot be loaded, it prints an error message to standard error.
     *
     * @param path: A string representing the path to the image file to be loaded.
     *
     * @return: A boolean value indicating the success (true) or failure (false) of loading the image.
     */
    bool loadFromFile(const std::string &path);

    /**
     * Saves the image to a file
     *
     * This const member function of the Image class attempts to save the current image data to a file at the specified path.
     * It uses the stb_image_write library to write the image in PNG format. Before attempting to save, it checks if the image
     * data buffer is not empty. If there is no data, or if the save operation fails, it prints an error message to standard error.
     *
     * @param path: A string representing the file path where the image should be saved. The image will be saved in PNG format.
     *
     * @return: A boolean value indicating the success (true) or failure (false) of the save operation.
     */
    bool saveToFile(const std::string &path) const;

};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_IMAGE_H
