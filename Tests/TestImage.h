/**
 * @file TestImage.h
 *
 * @brief Unit Tests for the Image Class.
 *
 * This header file defines the TestImage class, aimed at performing unit tests on the Image class functionalities.
 * The tests encompass loading and saving images, handling nonexistent images, manipulating image attributes such as
 * width, height, and channels, as well as testing the data manipulation capabilities of the Image class. These tests
 * ensure the reliability and correctness of the Image class in loading, saving, and manipulating image data, which is
 * fundamental for any image processing application. Special attention is given to file operations, including verifying
 * the creation and deletion of image files, to ensure the Image class interacts correctly with the filesystem.
 *
 * Usage:
 * Derived from the Test base class, the TestImage class implements the runTests method to systematically execute all
 * specified test cases. Each test case targets specific functionality of the Image class, using assertions to validate
 * expected outcomes. This comprehensive testing approach verifies the Image class's capabilities in real-world image
 * processing scenarios.
 *
 * @date Created on March 21, 2024.
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

#include "Test.h"
#include "Image.h"

#include <cstring> // For memcmp
#include <filesystem> // C++17, for checking file existence
#include <cassert>

namespace fs = std::filesystem;

class TestImage : public Test {
public:
    /**
     * Tests Loading an Image from a File
     *
     * Verifies that an image can be successfully loaded from a specified file path. This test ensures that the Image
     * class can read image files correctly, setting the appropriate width, height, and channel attributes based on the
     * loaded image. It also checks for the successful loading of an image, ensuring the method returns true for valid
     * image paths and that the loaded image has valid dimensions.
     */
    void testLoadImage() {
        Image img;
        bool loaded = img.loadFromFile("../Images/vh_ct.png");
        assert(loaded);
        assert(img.getWidth() > 0 && img.getHeight() > 0); // Make sure the image has valid dimensions
    }

    /**
     * Tests Saving an Image to a File
     *
     * Confirms that an image object can be saved to a file. This test checks the saveToFile method's ability to write
     * the current image data to a specified file path, ensuring that the file is created in the filesystem. It involves
     * loading an existing image, saving it under a new name, and then verifying the existence of the newly saved file.
     */
    void testSaveImage() {
        // First, load an image to save
        Image img;
        img.loadFromFile("../Images/vh_ct.png");

        bool saved = img.saveToFile("../Images/test_vh_ct.png");
        assert(saved);

        // Verify that the file was created
        assert(fs::exists("../Images/test_vh_ct.png"));

        // Delete the saved file after the test
        fs::remove("../Images/test_vh_ct.png");
    }

    /**
     * Tests Loading a Nonexistent Image
     *
     * Evaluates the Image class's behavior when attempting to load an image from a nonexistent file path. This test
     * ensures that the method correctly returns false and handles the situation gracefully without causing errors or
     * exceptions, maintaining the robustness of the image processing application.
     */
    void testLoadNonexistentImage() {
        Image img;
        bool loaded = img.loadFromFile("../Images/nonexistent.png");
        assert(!loaded); // Make sure the image was not loaded
    }

    /**
     * Tests Manipulating Image Attributes
     *
     * Verifies the functionality for setting and getting image attributes such as width, height, and number of channels.
     * This test ensures that the Image class accurately reflects changes made to these attributes, which is critical for
     * the correct handling and manipulation of image data within the application.
     */
    void testImageAttributes() {
        Image img;

        // Test setting and getting width
        img.setWidth(100);
        assert(img.getWidth() == 100);

        // Test setting and getting height
        img.setHeight(200);
        assert(img.getHeight() == 200);

        // Test setting and getting channels
        img.setChannels(3);
        assert(img.getChannels() == 3);
    }

    /**
     * Tests Manipulating Image Data
     *
     * Checks the capability to manipulate the underlying image data directly through the updateData method. This test
     * involves loading an image, modifying its data buffer, and then validating that the changes are correctly reflected
     * in the Image object. It ensures the flexibility and correctness of direct image data manipulation.
     */
    void testImageData() {
        Image img;
        img.loadFromFile("../Images/vh_ct.png"); // Load an image for testing
        unsigned char* originalData = img.getData();

        // Assert that the image has valid dimensions
        int expectedWidth = 512;
        int expectedHeight = 512;
        int expectedChannels = 1; // Grey scale image

        assert(img.getWidth() == expectedWidth);
        assert(img.getHeight() == expectedHeight);
        assert(img.getChannels() == expectedChannels);

        // Test updating the image data
        unsigned char* newData = new unsigned char[expectedWidth * expectedHeight * expectedChannels];
        memset(newData, 0, expectedWidth * expectedHeight * expectedChannels);
        img.updateData(newData);

        // Check that the data was updated
        assert(img.getData() == newData);
    }

    /**
     * Executes All Defined Test Cases for the Image Class
     *
     * Coordinates the execution of all unit tests related to the Image class functionalities, including file operations,
     * attribute manipulation, and data handling. This comprehensive test suite verifies the reliability and correctness
     * of the Image class as a fundamental component of the image processing application.
     */
    virtual void runTests() override {
        runTest<TestImage>(&TestImage::testLoadImage, "Load Image");
        runTest<TestImage>(&TestImage::testSaveImage, "Save Image");
        runTest<TestImage>(&TestImage::testLoadNonexistentImage, "Load Nonexistent Image");
        runTest<TestImage>(&TestImage::testImageAttributes, "Image Attributes");
        runTest<TestImage>(&TestImage::testImageData, "Image Data");
    }
};
