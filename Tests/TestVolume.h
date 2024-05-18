/**
 * @file TestVolume.h
 *
 * @brief Unit Tests for the Volume Class.
 *
 * This header file contains the definition of the TestVolume class, which is designed to conduct comprehensive
 * unit tests on the Volume class. It evaluates the correctness and functionality of the Volume class through
 * various test scenarios. These tests include verifying the construction of Volume objects with specific dimensions,
 * assessing the accuracy of getters and setters for volume properties, validating the update of volume data through
 * direct manipulation, and ensuring the reliability of loading from and saving to files using filesystem operations.
 * The program utilizes the C++ Standard Library for assertions, vector operations, and filesystem interactions, aiming
 * to guarantee the robustness and reliability of the Volume class in handling 3D volume data processing tasks.
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
#include "Volume.h"

#include <vector>
#include <cassert>
#include <filesystem>

namespace fs = std::filesystem;

class TestVolume : public Test {
public:
    /**
     * Tests the Construction of Volume Objects
     *
     * Verifies that Volume objects can be constructed with specific dimensions, setting the width, height, and depth
     * properties accordingly. This test ensures that the Volume class can create volume objects with the desired
     * dimensions, allowing for the manipulation and processing of 3D volume data in image processing applications.
     */
    void testVolumeConstruction() {
        Volume vol(100, 100, 100);
        assert(vol.getWidth() == 100 && "Constructor width set failed.");
        assert(vol.getHeight() == 100 && "Constructor height set failed.");
        assert(vol.getDepth() == 100 && "Constructor depth set failed.");
    }

    /**
     * Tests the Getters and Setters for Volume Properties
     *
     * Evaluates the correctness of the Volume class's getter and setter methods for volume properties, including width,
     * height, and depth. This test ensures that the Volume class can accurately retrieve and modify the dimensions of
     * volume objects, enabling the manipulation and processing of 3D volume data in image processing applications.
     */
    void testVolumeGettersAndSetters() {
        Volume vol;
        vol.setWidth(50);
        vol.setHeight(60);
        vol.setDepth(70);

        assert(vol.getWidth() == 50 && "setWidth failed.");
        assert(vol.getHeight() == 60 && "setHeight failed.");
        assert(vol.getDepth() == 70 && "setDepth failed.");
    }

    /**
     * Tests the Update of Volume Data
     *
     * Validates the updateData method of the Volume class, which allows for the direct manipulation of volume data by
     * replacing the existing data with new values. This test ensures that the updateData method can successfully modify
     * the volume data, setting all voxel values to a specific intensity level. It verifies that the volume data is
     * correctly updated, enabling the manipulation and processing of 3D volume data in image processing applications.
     */
    void testUpdateData() {
        Volume vol(10, 10, 10);
        std::vector<unsigned char> newData(1000, 42); // All values set to 42
        vol.updateData(newData);

        const unsigned char *data = vol.getData();
        for (int i = 0; i < 1000; i++) {
            assert(data[i] == 42 && "updateData failed.");
        }
    }

    /**
     * Tests Loading and Saving Volume Data
     *
     * Verifies the functionality of the Volume class's loadFromFiles and save methods, which enable the loading of volume
     * data from image files and the saving of volume data to image files, respectively. This test evaluates the ability
     * of the Volume class to load volume data from image files and save volume data to image files, ensuring that the
     * filesystem operations are correctly performed and that the volume data is accurately read and written to files.
     */
    void testLoadAndSave() {
        // Attention: This test requires filesystem operations, so it may not work on all systems.
        Volume vol;
        bool loaded = vol.loadFromFiles({"../Scans/fracture/granite1_0325.png"});
        assert(loaded && "loadFromFiles failed.");

        // Test saving functionality, also requires filesystem operations
         vol.save("../Scans/fracture", "x-y"); // Example: Save operation

        // Verify the filesystem results
        assert(fs::exists("../Scans/fracture/slice_1.png"));

        // Delete the saved file for the next test
        fs::remove("../Scans/fracture/slice_1.png");

        // Test saving functionality, also requires filesystem operations
        vol.save("../Scans/fracture", "x-y", 1); // Example: Save operation

        // Re-verify the filesystem results
        assert(fs::exists("../Scans/fracture/slice_1.png"));

        // Delete the saved file for the next test
        fs::remove("../Scans/fracture/slice_1.png");

        // Test saving functionality, also requires filesystem operations
        vol.save("../Scans/fracture", "x-y", "MIP"); // Example: Save operation
        vol.save("../Scans/fracture", "x-y", "MinIP", 1, 1);
        vol.save("../Scans/fracture", "x-y", "AIP");
        vol.save("../Scans/fracture", "x-y", "MedIP", 1, 1);

        // Re-verify the filesystem results
        assert(fs::exists("../Scans/fracture/MIP.png"));
        assert(fs::exists("../Scans/fracture/MinIP.png"));
        assert(fs::exists("../Scans/fracture/AIP.png"));
        assert(fs::exists("../Scans/fracture/MedIP.png"));

        // Delete the saved files for the next test
        fs::remove("../Scans/fracture/MIP.png");
        fs::remove("../Scans/fracture/MinIP_range_1_1.png");
        fs::remove("../Scans/fracture/AIP.png");
        fs::remove("../Scans/fracture/MedIP_range_1_1.png");
    }

    /**
     * Runs the Volume Unit Tests
     *
     * Executes all the unit tests for the Volume class, including tests for volume construction, getters and setters,
     * data update, and loading and saving volume data. This function runs each test method and reports the results
     * to the console, indicating whether the tests passed or failed. It provides a comprehensive evaluation of the
     * Volume class's functionality and reliability in handling 3D volume data processing tasks.
     */
    virtual void runTests() override {
        runTest<TestVolume>(&TestVolume::testVolumeConstruction, "Volume Construction");
        runTest<TestVolume>(&TestVolume::testVolumeGettersAndSetters, "Volume Getters and Setters");
        runTest<TestVolume>(&TestVolume::testUpdateData, "Update Data");
        runTest<TestVolume>(&TestVolume::testLoadAndSave, "Load and Save");
    }
};
