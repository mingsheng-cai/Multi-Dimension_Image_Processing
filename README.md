# Multi-Dimension Image Processing Library

This is an implementation for the **Advanced Programming Group Project**.

This project provides a comprehensive toolkit for 2D/3D image processing, including utilities for loading, manipulating, and saving both 2D and 3D image data. It is designed to facilitate advanced image processing tasks such as filtering, projection, slicing of volumetric data, and edge detection. This library is particularly suited for applications in medical imaging, scientific visualization, 3D data analysis, and real-time image enhancement.

For more details, please check:

- Webpage document: [Our Website](https://acse-sc4623.github.io/MultiImgProc) or `./Docs/html/index.html`

- User manual: `./Docs/Manual_Multi-Dimension_Image_Processing_Library.pdf`

## Features

- **Image Loading and Saving**: Supports loading and saving images in various formats through the integration of the `stb_image` and `stb_image_write` libraries.
- **Volume Manipulation**: Allows the construction of a 3D volume from a series of 2D slices, along with the capability to save slices or projections of the volume back to disk.
- **Filtering**: Implements median, Gaussian, edge detection, and pixel-level filtering for noise reduction, smoothing, and edge enhancement of volumetric data.
- **Projections**: Offers functions for maximum, minimum, average, and median intensity projections, which are essential for visualizing structural information in volumetric data.
- **Slicing**: Provides functionality to extract arbitrary slices from a volume, facilitating the examination of cross-sectional data.
- **Edge Detection**: Incorporates edge detection algorithms such as Sobel and Prewitt, enabling the identification of edges within images for analysis and processing.

## Project Structure

```mathematica
plaintextCopy code
<Multi-Dimension Image Processing Library>/
│
├── CMakeLists.txt               - Project build script.
├── README.md                    - Project documentation.
│
├── Docs/                        - Documentation files.
│
├── Images/                      - Sample images for testing.
│
├── Include/                     - Header files.
│   ├── Algorithm.h
│   ├── Box2DFilter.h
│   ├── EdgeFilter.h
│   ├── Filters/                 - Filter headers.
│   ├── Gaussian2DFilter.h
│   ├── Gaussian3DFilter.h
│   ├── Image.h
│   ├── Median2DFilter.h
│   ├── Median3DFilter.h
│   ├── Padding.h
│   ├── PixelFilter.h
│   ├── Projection.h
│   ├── Slice.h
│   ├── Volume.h
│   ├── stb_image.h
│   └── stb_image_write.h
│
├── Output/                      - Output directory for processed images.
│
├── Scans/                       - Input directory for volume scans.
│
├── Source/                      - Source files.
│   ├── Algorithm.cpp
│   ├── Box2DFilter.cpp
│   ├── EdgeFilter.cpp
│   ├── Filters/                 - Filter source files.
│   ├── Gaussian2DFilter.cpp
│   ├── Gaussian3DFilter.cpp
│   ├── Image.cpp
│   ├── Median2DFilter.cpp
│   ├── Median3DFilter.cpp
│   ├── Padding.cpp
│   ├── PixelFilter.cpp
│   ├── Projection.cpp
│   ├── Slice.cpp
│   ├── Volume.cpp
│   └── main.cpp
├── Tests/                       - Unit tests.
├── RunExecutable                - Executable file for the project.
├── RunMain.sh                   - Script to cmake, build and run the main program.
└── RunTest.sh                   - Script to cmake, build and run the test framwork.
```

## Getting Started

### 3D Datasets

Download CT Scan datasets here:

https://imperiallondon-my.sharepoint.com/:u:/g/personal/tmd02_ic_ac_uk/EafXMuNsbcNGnRpa8K62FjkBvIKvCswl1riz7hPDHpHdSQ

### Prerequisites

Ensure you have a modern C++ compiler that supports C++17 and the CMake build system installed on your system. This project also requires the `filesystem` library for directory operations.

### Building the Project

We have scripts to automatically run the build commands, do the unit tests and start the command line user interface.

If you prefer using CMake and want to build the project manually, Please follow:

1. Clone the repository to your local machine.

2. Navigate to the project directory and create a build directory:

   ```bash
   mkdir Build && cd Build
   ```

3. Run CMake to configure the project:

   ```bash
   cmake ..
   ```

4. Compile the project:

   ```bash
   cmake --build .
   ```

The CMakeList files have turned on the compilation optimization by default.

## Usage

We prefer users to operate through the interface we've provided. Please follow the instructions below to build and run the project.

**Run Executable**

We have included a executable file (Linux platform) in the root directory.

```bash
./RunExecutable
```

**Run Unit Tests** 

Make sure 3D datases are downloaded and put to `./Scans`.

```bash
./RunTest.sh
```

**Run Main User Interface**

```bash
./RunMain.sh
```

To use the library in your project, include the necessary header files from the `Include` directory and link against the compiled library.

Here's an example demonstrating how to load a image / volume from disk, apply various filters, and save a filtered file / maximum intensity projection:

```cpp
#include "Volume.h"
#include "Image.h"
#include "Filters/Gaussian3DFilter.h"
#include "Filters/Gaussian2DFilter.h"
#include "Projection.h"
#include "Filters/EdgeFilter.h"
#include "Filters/PixelFilter.h"

int main() {
  	// Demo for 2D images
  	Image image;
  	image.loadFromFile("/path/to/your/image");
  
  	// Apply Greyscale filter to image
  	PixelFilter pixelFilter("Grayscale");
  	pixelFilter.apply(image);
  
  	// Apply a 2D Gaussian filter with sigma = 2.0 and kernel size = 5
 		Gaussian2DFilter gaussianFilter2D(5, 2.0);
  	gaussianFilter2D.apply(image);
  
  	// Apply Sobel edge filter
  	EdgeFilter edgeFilter(FilterType::Sobel);
  	edgeFilter.apply(image);
  
  	// Save filtered image
  	image.saveToFile("/path/and/name/of/your/image.png");
  
  
  	// Demo for 3D images
    Volume volume;
    volume.loadFromDirectory("/path/to/your/images_directory");

    // Apply a 3D Gaussian filter with sigma = 2.0 and kernel size = 5
    Gaussian3DFilter gaussianFilter3D(2.0, 5);
    gaussianFilter3D.apply(volume);

    // Save a maximum intensity projection to disk
		volume.save("/path/to/your/directory", "x-y", "MIP");

    return 0;
}
```

## Contributing

Contributions to enhance the functionality or performance of this library are welcome. Please follow the standard fork-branch-PR workflow.

## Developers

This project is developed by:

- Benjamin Duncan (edsml-bd1023)
- Boyang Hu (edsml-bh223)
- Chawk Chamoun (edsml-cc8915)
- Mingsheng Cai (acse-sc4623)
- Moyu Zhang (acse-mz223)
- Ryan Benney (acse-rgb123)

The group name is **Advanced Programming Group Radix Sort**.

## License

This project is open source and available under the MIT License. See the LICENSE file for more details.

## Acknowledgments

- Special thanks to Sean Barrett for the `stb_image` and `stb_image_write` libraries, which are used for image I/O operations in this project.
- Appreciation to all contributors and the Advanced Programming Group Radix Sort for their efforts and collaboration in building this comprehensive image processing toolkit.
- Thanks to generative AI tools like ChatGPT and Google Gemini for the help in coding.

