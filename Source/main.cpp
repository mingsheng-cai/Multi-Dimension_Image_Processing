/**
 * @file main.cpp
 *
 * @brief Main entry point for the Data Processing Program.
 *
 * This program provides an interface for processing both 2D and 3D image data through a variety of filters.
 * Users can choose to process 2D images with operations such as brightness adjustment, grayscale conversion,
 * histogram equalization, thresholding, and adding salt-and-pepper noise. For 3D volume data, the program offers
 * Gaussian and Median filtering to enhance or manipulate the data. The program leverages libraries such as STB for
 * image reading and writing, and utilizes the filesystem library for directory operations. Users interact with the
 * program via the console, selecting options to load, process, and save image data in various formats. This main file
 * orchestrates the flow of operations based on user input, leveraging classes designed for specific image processing tasks.
 *
 * @date Created on 20/03/2024.
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

#include <filesystem>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "Volume.h"
#include "Filters/Gaussian3DFilter.h"
#include "Filters/Median3DFilter.h"
#include "Filters/PixelFilter.h"
#include "Filters/Median2DFilter.h"
#include "Filters/Box2DFilter.h"
#include "Filters/Gaussian2DFilter.h"
#include "Filters/EdgeFilter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

namespace fs = std::filesystem;

int main() {
    std::cout << "Welcome to the Data Processing Program!" << std::endl;
    std::cout << "Please select the operation you want to perform:" << std::endl;
    std::cout << "1. Process 2D image data" << std::endl;
    std::cout << "2. Process 3D image data" << std::endl;
    std::cout << "3. Cancel" << std::endl;

    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: {
            // TODO: Process 2D image data
            Image img;
            std::string path;
            std::cout << "Enter image load path: ";
            std::cin >> path;
            //path="../Images/gracehopper.png";   //需要修改
            while (!img.loadFromFile(path)) {
                std::cout << "Incorrect path!\n" << std::endl;

                std::cout << "Enter image load path: ";
                std::cin >> path;
            }
            std::cout << "Image loaded successfully." << std::endl;

            int choice=4;
            std::cout << "Choose an option:\n1-modifiers\n2-image blur\n3-edge detection(only can process greyscale image)\n4-cancel\nOnce you have applied your desired filters, output the image by typing -1\n";
            std::cin >> choice;
            while (choice!=-1){

                if (choice == 1) {
                    int modifierChoice;
                    std::cout << "1-greyscale\n2-brightness\n3-histogram equalisation\n4-thresholding\n5-salt and pepper Noise\n";
                    std::cin >> modifierChoice;

                    switch (modifierChoice) {
                        case 1:
                            {
                                PixelFilter greyFilter("Grayscale");
                            greyFilter.apply(img);
                            break;
                            }
                        case 2:{
                            int brightChange;
                            std::cout << "Enter brightness change (-255 to 255): ";
                            std::cin >> brightChange;
                            PixelFilter brightnessFilter("Brightness",brightChange);
                            brightnessFilter.apply(img);
                            break;
                            }
                        case 3:{
                            std::cout << "1-HSL\n2-HSV\n3-GREY\n";
                            int colorSpace;
                            std::cin >> colorSpace;
                            if (colorSpace == 3) {
                                PixelFilter equalizeHistogram("Equalisation", std::nullopt, "GREY",0);
                                equalizeHistogram.apply(img);
                            } 
                            else if (colorSpace == 1) {
                                PixelFilter equalizeHistogram("Equalisation", std::nullopt, "HSL",0);
                                equalizeHistogram.apply(img);
                            }
                            else if (colorSpace == 2) {
                                PixelFilter equalizeHistogram("Equalisation", std::nullopt, "HSV",0);
                                equalizeHistogram.apply(img);
                            }
                            break;
                            }
                        case 4:{
                            std::cout << "1-HSL\n2-HSV\n3-GREY\n";
                            int colorSpace;
                            std::cin >> colorSpace;
                            if (colorSpace == 3) {
                                PixelFilter equalizeHistogram("Thresholding", std::nullopt, "GREY",0);
                                equalizeHistogram.apply(img);
                            } 
                            else if (colorSpace == 1) {
                                int threshold;
                                std::cout << "Enter threshold (-255 to 255): ";
                                std::cin >> threshold;
                                PixelFilter equalizeHistogram("Thresholding", std::nullopt, "HSL",threshold);
                                equalizeHistogram.apply(img);
                            }
                            else if (colorSpace == 2) {
                                int threshold;
                                std::cout << "Enter threshold (-255 to 255): ";
                                std::cin >> threshold;
                                PixelFilter equalizeHistogram("Thresholding", std::nullopt, "HSV",threshold);
                                equalizeHistogram.apply(img);
                            }
                            break;
                            }
                        case 5:
                            {float salt;
                            std::cout << "Enter salt and pepper noise level (0.0 to 1.0): ";
                            std::cin >> salt;
                            PixelFilter noise("SaltAndPepperNoise", std::nullopt, "", 0, salt);
                            noise.apply(img);
                            break;}
                    }
                } else if (choice == 2) {
                    int blurChoice;
                    std::cout << "1-Median blur\n2-Box blur\n3-Gaussian blur\n";
                    std::cin >> blurChoice;

                    int kernelSize;
                    std::cout << "Enter kernel size (odd number): ";
                    std::cin >> kernelSize;

                    int paddingType;
                    std::cout << "Choose padding type:\n0-ZeroPadding\n1-EdgeReplication\n2-ReflectPadding\n";
                    std::cin >> paddingType;

                    switch (blurChoice) {
                        case 1: {
                            Median2DFilter mf(kernelSize, static_cast<PaddingType>(paddingType));
                            mf.apply(img);
                            break;
                        }
                        case 2: {
                            Box2DFilter bf(kernelSize, static_cast<PaddingType>(paddingType));
                            bf.apply(img);
                            break;
                        }
                        case 3: {
                            double sigma;
                            std::cout << "Enter sigma for Gaussian blur: ";
                            std::cin >> sigma;
                            Gaussian2DFilter gf(kernelSize, sigma, static_cast<PaddingType>(paddingType));
                            gf.apply(img);
                            break;
                        }
                        case 4: {
                            std::cerr << "Process terminated." << std::endl;
                            return 1;
                        }
                    }
                } 
                else if (choice == 3) {
                int edgeDetectionChoice;
                std::cout << "Choose edge detection method:\n1-Sobel\n2-Prewitt\n3-Scharr\n4-Roberts\n5-cancel";
                std::cin >> edgeDetectionChoice;

                FilterType filterType;
                switch (edgeDetectionChoice) {
                    case 1:
                        filterType = FilterType::Sobel;
                        break;
                    case 2:
                        filterType = FilterType::Prewitt;
                        break;
                    case 3:
                        filterType = FilterType::Scharr;
                        break;
                    case 4:
                        filterType = FilterType::Roberts;
                        break;
                    case 5: 
                        std::cerr << "Process terminated." << std::endl;
                        return 1;
                    default:
                        std::cerr << "Invalid choice. Defaulting to Sobel." << std::endl;
                        filterType = FilterType::Sobel;
                }

                int paddingChoice;
                std::cout << "Choose padding type:\n0-ZeroPadding\n1-EdgeReplication\n2-ReflectPadding\n3-Cancel";
                std::cin >> paddingChoice;

                PaddingType paddingType = PaddingType::ZeroPadding; // 默认为零填充
                switch (paddingChoice) {
                    case 0:
                        paddingType = PaddingType::ZeroPadding;
                        break;
                    case 1:
                        paddingType = PaddingType::EdgeReplication;
                        break;
                    case 2:
                        paddingType = PaddingType::ReflectPadding;
                        break;
                    case 3:
                        std::cerr << "Process terminated." << std::endl;
                        return 1;
                    default:
                        std::cerr << "Invalid choice. Defaulting to ZeroPadding." << std::endl;
                        paddingType = PaddingType::ZeroPadding;
                }

                EdgeFilter edgeFilter(filterType, paddingType);
                edgeFilter.apply(img);
                std::cout << "Edge detection applied successfully." << std::endl;
            }
                else if (choice == 4) {
                    std::cerr << "Process terminated." << std::endl;
                    return 1;
            }

            std::cout << "Choose an option:\n1-modifiers\n2-image blur\n3-edge detection(only can process greyscale image)\n4-cancel\nOnce you have applied your desired filters, output the image by typing -1\n";
            std::cin >> choice;
        }

            std::string savepath;
            std::cout << "Enter image save path: ";
            std::cin >> savepath;
            //savepath="../Output/try.png";
            if (!img.saveToFile(savepath)) {
                std::cout << "Save failed!" << std::endl;
            } else {
                std::cout << "Save successful. Path: " << savepath << std::endl;
            }
            break;
        }
        case 2: {
            // Get 3D data path
            std::string directoryPath;
            std::cout << "Please enter the directory path of the 3D image data:" << std::endl;
            std::cin >> directoryPath;

            // Create a Volume object and load the volume data from the directory
            Volume volume;
            while (!volume.loadFromDirectory(directoryPath)) {
                std::cout << "Error: Failed to load volume data from the directory.\n" << std::endl;
                std::cout << "Please enter the directory path of the 3D image data: " << std::endl;
                std::cin >> directoryPath;
            }

            // Get the user's choice of 3D filter
            std::cout << "Please select the 3D filter you want to apply:" << std::endl;
            std::cout << "1. Gaussian 3D filter" << std::endl;
            std::cout << "2. Median 3D filter" << std::endl;
            std::cout << "3. No filter (skip to projection)" << std::endl;
            std::cin >> choice;

            int kernelSize;

            std::string outputDir;
            std::string plane;

            switch (choice) {
                case 1: {
                    // Get the user's choice of sigma and kernel size
                    double sigma;
                    std::cout << "Please enter the sigma value for the Gaussian filter:" << std::endl;
                    std::cin >> sigma;
                    std::cout << "Please enter the kernel size for the Gaussian filter:" << std::endl;
                    std::cin >> kernelSize;

                    // Create a Gaussian3DFilter object
                    Gaussian3DFilter filter(sigma, kernelSize);

                    // Apply filter to the volume data
                    filter.apply(volume);

                    std::cout << "Please select the operation you want to perform:" << std::endl;
                    std::cout << "1. Save filtered data as 2D images" << std::endl;
                    std::cout << "2. Save filtered data slice as 2D images" << std::endl;
                    std::cout << "3. Apply Projection to the volume data" << std::endl;
                    std::cout << "4. Cancel" << std::endl;
                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            // Get output directory path
                            std::cout << "Please enter the directory path to save the filtered 2D images:" << std::endl;
                            std::cin >> outputDir;

                            // Choose which plane to save
                            std::string input;
                            std::cout << "Please select the plane to save the filtered 2D images:" << std::endl;
                            std::cout << "1. x-y plane" << std::endl;
                            std::cout << "2. x-z plane" << std::endl;
                            std::cout << "3. y-z plane" << std::endl;
                            std::cin >> input;

                            if (input == "1") {
                                plane = "x-y";
                            } else if (input == "2") {
                                plane = "x-z";
                            } else if (input == "3") {
                                plane = "y-z";
                            } else {
                                std::cerr << "Error: Invalid choice." << std::endl;
                                return 1;
                            }

                            // Save the filtered volume data as a series of 2D images
                            volume.save(outputDir, plane);

                            std::cout << "Volume processing and saving completed." << std::endl;

                            break;
                        }
                        case 2: {
                            // Get output directory path
                            std::cout << "Please enter the directory path to save the filtered 2D images:" << std::endl;
                            std::cin >> outputDir;

                            // Choose which plane to save
                            std::string input;
                            std::cout << "Please select the plane to save the filtered 2D images:" << std::endl;
                            std::cout << "1. x-y plane" << std::endl;
                            std::cout << "2. x-z plane" << std::endl;
                            std::cout << "3. y-z plane" << std::endl;
                            std::cin >> input;

                            if (input == "1") {
                                plane = "x-y";
                            } else if (input == "2") {
                                plane = "x-z";
                            } else if (input == "3") {
                                plane = "y-z";
                            } else {
                                std::cerr << "Error: Invalid choice." << std::endl;
                                return 1;
                            }

                            // Choose the slice index
                            int sliceIndex;
                            std::cout << "Please enter the slice index to save:" << std::endl;
                            std::cin >> sliceIndex;

                            // Save the filtered volume data slice
                            volume.save(outputDir, plane, sliceIndex);

                            std::cout << "Volume processing and saving completed." << std::endl;

                            break;
                        }
                        case 3: {
                            // Apply projection to the volume data
                            std::cout << "Please select the projection type (default on x-y plane):" << std::endl;
                            std::cout << "1. Maximum Intensity Projection" << std::endl;
                            std::cout << "2. Minimum Intensity Projection" << std::endl;
                            std::cout << "3. Average Intensity Projection" << std::endl;
                            std::cout << "4. Median Intensity Projection" << std::endl;
                            std::cin >> choice;

                            // Get output directory path
                            std::cout << "Please enter the directory path to save the projection images:" << std::endl;
                            std::cin >> outputDir;

                            switch (choice) {
                                case 1:
                                    volume.save(outputDir, "x-y", "MIP");
                                    break;
                                case 2:
                                    volume.save(outputDir, "x-y", "MinIP");
                                    break;
                                case 3:
                                    volume.save(outputDir, "x-y", "AIP");
                                    break;
                                case 4:
                                    volume.save(outputDir, "x-y", "MedIP");
                                    break;
                                default:
                                    std::cerr << "Error: Invalid choice." << std::endl;
                                    return 1;
                            }
                            break;
                        }

                        case 4: {
                            std::cerr << "Process terminated." << std::endl;
                            return 1;
                        }

                        default:
                            std::cerr << "Error: Invalid choice." << std::endl;
                            return 1;
                    }
                    break;
                }
                case 2: {
                    // Get the user's choice of kernel size
                    std::cout << "Please enter the kernel size for the Median filter (must be an odd number): :" << std::endl;
                    std::cin >> kernelSize;

                    // Create a Median3DFilter object
                    Median3DFilter medianFilter(kernelSize);

                    // Apply filter to the volume data
                    medianFilter.apply(volume);

                    std::cout << "Please select the operation you want to perform:" << std::endl;
                    std::cout << "1. Save filtered data as 2D images" << std::endl;
                    std::cout << "2. Save filtered data slice as 2D images" << std::endl;
                    std::cout << "3. Apply Projection to the volume data" << std::endl;
                    std::cout << "4. Cancel" << std::endl;
                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            // Get output directory path
                            std::cout << "Please enter the directory path to save the filtered 2D images:" << std::endl;
                            std::cin >> outputDir;

                            // Choose which plane to save
                            std::string input;
                            std::cout << "Please select the plane to save the filtered 2D images:" << std::endl;
                            std::cout << "1. x-y plane" << std::endl;
                            std::cout << "2. x-z plane" << std::endl;
                            std::cout << "3. y-z plane" << std::endl;
                            std::cin >> input;

                            if (input == "1") {
                                plane = "x-y";
                            } else if (input == "2") {
                                plane = "x-z";
                            } else if (input == "3") {
                                plane = "y-z";
                            } else {
                                std::cerr << "Error: Invalid choice." << std::endl;
                                return 1;
                            }

                            // Save the filtered volume data as a series of 2D images
                            volume.save(outputDir, plane);

                            std::cout << "Volume processing and saving completed." << std::endl;

                            break;
                        }
                        case 2: {
                            // Get output directory path
                            std::cout << "Please enter the directory path to save the filtered 2D images:" << std::endl;
                            std::cin >> outputDir;

                            // Choose which plane to save
                            std::string input;
                            std::cout << "Please select the plane to save the filtered 2D images:" << std::endl;
                            std::cout << "1. x-y plane" << std::endl;
                            std::cout << "2. x-z plane" << std::endl;
                            std::cout << "3. y-z plane" << std::endl;
                            std::cin >> input;

                            if (input == "1") {
                                plane = "x-y";
                            } else if (input == "2") {
                                plane = "x-z";
                            } else if (input == "3") {
                                plane = "y-z";
                            } else {
                                std::cerr << "Error: Invalid choice." << std::endl;
                                return 1;
                            }

                            // Choose the slice index
                            int sliceIndex;
                            std::cout << "Please enter the slice index to save:" << std::endl;
                            std::cin >> sliceIndex;

                            // Save the filtered volume data slice
                            volume.save(outputDir, plane, sliceIndex);

                            std::cout << "Volume processing and saving completed." << std::endl;

                            break;
                        }
                        case 3: {
                            // Apply projection to the volume data
                            std::cout << "Please select the projection type (default on x-y plane):" << std::endl;
                            std::cout << "1. Maximum Intensity Projection" << std::endl;
                            std::cout << "2. Minimum Intensity Projection" << std::endl;
                            std::cout << "3. Average Intensity Projection" << std::endl;
                            std::cout << "4. Median Intensity Projection" << std::endl;
                            std::cin >> choice;

                            // Get output directory path
                            std::cout << "Please enter the directory path to save the projection images:" << std::endl;
                            std::cin >> outputDir;

                            switch (choice) {
                                case 1:
                                    volume.save(outputDir, "x-y", "MIP");
                                    break;
                                case 2:
                                    volume.save(outputDir, "x-y", "MinIP");
                                    break;
                                case 3:
                                    volume.save(outputDir, "x-y", "AIP");
                                    break;
                                case 4:
                                    volume.save(outputDir, "x-y", "MedIP");
                                    break;
                                default:
                                    std::cerr << "Error: Invalid choice." << std::endl;
                                    return 1;
                            }
                            break;
                        }
                        case 4: {
                            std::cerr << "Process terminated." << std::endl;
                            return 1;
                        }

                        default:
                            std::cerr << "Error: Invalid choice." << std::endl;
                            return 1;
                    }

                    break;
                }
                case 3: {

                    std::cout << "Please select the operation you want to perform:" << std::endl;
                    std::cout << "1. Apply Projection to the volume data" << std::endl;
                    std::cout << "2. Cancel" << std::endl;
                    std::cin >> choice;

                    switch (choice) {
                    case 1: {
                        std::cout << "Please select the projection type (default on x-y plane):" << std::endl;
                        std::cout << "1. Maximum Intensity Projection" << std::endl;
                        std::cout << "2. Minimum Intensity Projection" << std::endl;
                        std::cout << "3. Average Intensity Projection" << std::endl;
                        std::cout << "4. Median Intensity Projection" << std::endl;
                        std::cin >> choice;

                        std::cout << "Please enter the directory path to save the projection images:" << std::endl;
                        std::cin >> outputDir;

                        switch (choice) {
                        case 1:
                            volume.save(outputDir, "x-y", "MIP");
                            break;
                        case 2:
                            volume.save(outputDir, "x-y", "MinIP");
                            break;
                        case 3:
                            volume.save(outputDir, "x-y", "AIP");
                            break;

                        case 4:
                            volume.save(outputDir, "x-y", "MedIP");
                            break;

                        default:
                            std::cerr << "Error: Invalid choice." << std::endl;
                            return 1;
                        }
                        break;

                    }

                    case 2: {
                        std::cerr << "Process terminated." << std::endl;
                        return 1;
                    }

                    default:
                        std::cerr << "Error: Invalid choice." << std::endl;
                        return 1;
                    }

                    break;
                }

                default:
                    std::cerr << "Error: Invalid choice." << std::endl;
                    return 1;
            }
            break;
        }

        case 3: {
            std::cerr << "Process terminated." << std::endl;
            return 1;
        }

        default:
            std::cerr << "Error: Invalid choice." << std::endl;
            return 1;
    }

    return 0;
}
