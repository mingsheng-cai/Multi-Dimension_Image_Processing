/**
 * @file PixelFilter.cpp
 *
 * @brief Implementation of the PixelFilter class for various pixel-level image filtering operations.
 *
 * This file defines the implementation of the PixelFilter class, which supports a range of image processing operations
 * including grayscale conversion, brightness adjustment, histogram equalization, thresholding, and the addition of salt-and-pepper
 * noise. These operations can be applied to images in different color spaces such as RGB, HSL, and HSV, depending on the filter type.
 * The class is designed to be flexible, allowing for optional parameters and ensuring that input values are within expected ranges
 * for each filter type. Part of the Advanced Programming Group's toolkit, this implementation aims to provide a comprehensive solution
 * for image enhancement and manipulation, facilitating both basic and advanced image processing tasks.
 *
 * @date Created on March 20, 2024
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

#include "Filters/PixelFilter.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>

PixelFilter::PixelFilter(const std::string &type, const std::optional<int> &brightness,
                         const std::string &space, int threshold, double percentage) :
        filterType(type), brightness(brightness.value_or(128)),
        space(space), threshold(threshold), percentage(percentage) {
    // Check for invalid arguments
    if (type == "Brightness" && brightness.has_value() && (brightness.value() < -255 || brightness.value() > 255)) {
        throw std::invalid_argument("Brightness value out of range.");
    } else if (type == "Equalisation" && (space != "HSL" && space != "HSV" && space != "GREY")) {
        throw std::invalid_argument("Invalid space for Equalisation.");
    } else if (type == "Thresholding" &&
               (space != "HSL" && space != "HSV" && space != "GREY" || threshold < 0 || threshold > 255)) {
        throw std::invalid_argument("Invalid parameters for Thresholding.");
    } else if (type == "SaltAndPepperNoise" && (percentage < 0.0 || percentage > 1.0)) {
        throw std::invalid_argument("Invalid percentage for Noise.");
    }
}

void PixelFilter::apply(Image &image) {
    // Implement the pixel-level image filtering operations
    if (filterType == "Grayscale") {
        // Grayscale conversion
        convertToGrayscale(image);
    } else if (filterType == "Brightness") {
        // Adjust brightness
        adjustBrightness(image);
    } else if (filterType == "Equalisation") {
        // Equalize histogram
        equalizeHistogram(image);
    } else if (filterType == "Thresholding") {
        // Threshold pixel values
        thresholdPixel(image);
    } else if (filterType == "SaltAndPepperNoise") {
        // Add salt-and-pepper noise
        addNoise(image);
    } else {
        throw std::invalid_argument("Unsupported filter type.");
    }
}

void PixelFilter::convertToGrayscale(Image &image) {
    // Implement the conversion of an RGB image to grayscale
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *data = image.getData();

    if (channels < 3) return; // If the image is already grayscale, return directly

    unsigned char *newData = new unsigned char[width * height]; // Allocate memory for the new grayscale image data
    for (int i = 0; i < width * height; i++) {
        int index = i * channels;
        unsigned char r = data[index];
        unsigned char g = data[index + 1];
        unsigned char b = data[index + 2];
        // Calculate the grayscale value using the luminance method
        newData[i] = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);
    }

    image.updateData(newData); // Update the image data
    image.setChannels(1); // Update the number of channels
}

void PixelFilter::adjustBrightness(Image &image) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *originalData = image.getData();

    // Create a temporary buffer to store the modified pixel values
    unsigned char *tempData = new unsigned char[width * height * channels];

    for (int i = 0; i < width * height * channels; i++) {
        int value = static_cast<int>(originalData[i]) + brightness; // Adjust brightness
        value = std::max(0, std::min(255, value)); // Clamp to [0, 255]
        tempData[i] = static_cast<unsigned char>(value);
    }

    // Update the image data with the modified pixel values
    image.updateData(tempData);
}

void PixelFilter::thresholdPixel(Image &image) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *data = image.getData();

    // Process grayscale images
    if (channels == 1) {
        for (int i = 0; i < width * height; ++i) {
            data[i] = data[i] >= threshold ? 255 : 0;
        }
    }
    // Process RGB images
    else if (channels >= 3) {
        for (int i = 0; i < width * height; ++i) {
            float r = data[i * channels] / 255.0f;
            float g = data[i * channels + 1] / 255.0f;
            float b = data[i * channels + 2] / 255.0f;
            float h, s, l_v;

            // Transform to the specified color space
            if (space == "HSV") {
                RGBtoHSV(r, g, b, h, s, l_v);
                l_v = l_v >= (float) threshold / 255.0f ? 1.0f : 0.0f;
                HSVtoRGB(h, s, l_v, r, g, b);
            } else if (space == "HSL") {
                RGBtoHSL(r, g, b, h, s, l_v);
                l_v = l_v >= (float) threshold / 255.0f ? 1.0f : 0.0f;
                HSLtoRGB(h, s, l_v, r, g, b);
            }

            // Update the pixel values
            data[i * channels] = static_cast<unsigned char>(r * 255);
            data[i * channels + 1] = static_cast<unsigned char>(g * 255);
            data[i * channels + 2] = static_cast<unsigned char>(b * 255);
        }
    }
}

void PixelFilter::addNoise(Image &image) {
    // random seed
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize random number generator

    int pixelCount = image.getWidth() * image.getHeight();
    int noisePixels = static_cast<int>(pixelCount *
                                       this->percentage); // Calculate number of pixels to be noised based on percentage

    unsigned char *imageData = image.getData();

    for (int i = 0; i < noisePixels; ++i) {
        int idx = rand() % pixelCount; // Randomly choose a pixel position
        bool pepper = rand() % 2 == 0; // Decide whether to add black or white

        for (int c = 0; c < image.getChannels(); ++c) {
            // Set pixel data to either 255 (white) or 0 (black)
            imageData[idx * image.getChannels() + c] = pepper ? 255 : 0;
        }
    }
}

void PixelFilter::equalizeHistogram(Image &image) {
    // Implement histogram equalization for grayscale and RGB images
    if (image.getChannels() == 1) {
        // Handle grayscale images
        std::vector<float> channel(image.getWidth() * image.getHeight());
        for (int i = 0; i < image.getWidth() * image.getHeight(); ++i) {
            channel[i] = image.getData()[i] / 255.0f;
        }

        std::vector<int> histogram(256, 0), cdf(256, 0);
        calculateHistogramAndCDF(channel, histogram, cdf);
        applyCDF(channel, cdf);

        for (int i = 0; i < image.getWidth() * image.getHeight(); ++i) {
            image.getData()[i] = static_cast<unsigned char>(channel[i] * 255);
        }
    } else if (image.getChannels() >= 3) {
        // For RGB images, convert to HSV/HSL, equalize the V/L channel, then convert back to RGB
        std::vector<float> hChannel(image.getWidth() * image.getHeight()),
                sChannel(image.getWidth() * image.getHeight()),
                vChannel(image.getWidth() * image.getHeight());

        for (int i = 0; i < image.getWidth() * image.getHeight(); i++) {
            float r = image.getData()[i * image.getChannels()] / 255.0f;
            float g = image.getData()[i * image.getChannels() + 1] / 255.0f;
            float b = image.getData()[i * image.getChannels() + 2] / 255.0f;
            float h, s, v;
            if (space == "HSL") {
                RGBtoHSL(r, g, b, h, s, v); // Assuming v is Luminance (L) for HSL
            } else {
                RGBtoHSV(r, g, b, h, s, v); // v is Value for HSV
            }
            hChannel[i] = h;
            sChannel[i] = s;
            vChannel[i] = v;
        }

        std::vector<int> histogram(256, 0), cdf(256, 0);
        calculateHistogramAndCDF(vChannel, histogram, cdf);
        applyCDF(vChannel, cdf);

        for (int i = 0; i < image.getWidth() * image.getHeight(); i++) {
            float r, g, b;
            if (space == "HSL") {
                HSLtoRGB(hChannel[i], sChannel[i], vChannel[i], r, g, b); // Assuming v is Luminance (L) for HSL
            } else {
                HSVtoRGB(hChannel[i], sChannel
                [i], vChannel[i], r, g, b); // v is Value for HSV
            }
            image.getData()[i * image.getChannels()] = static_cast<unsigned char>(r * 255);
            image.getData()[i * image.getChannels() + 1] = static_cast<unsigned char>(g * 255);
            image.getData()[i * image.getChannels() + 2] = static_cast<unsigned char>(b * 255);
        }
    }
}

void PixelFilter::calculateHistogramAndCDF(const std::vector<float> &channel, std::vector<int> &histogram,
                                           std::vector<int> &cdf) {
    // Calculate the histogram and cumulative distribution function (CDF) for a given channel
    std::fill(histogram.begin(), histogram.end(), 0);

    // Calculate the histogram
    for (auto intensity: channel) {
        histogram[static_cast<int>(intensity * 255.0)]++;
    }
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    // Normalize the CDF
    int minCdf = *std::find_if(cdf.begin(), cdf.end(), [](int value) { return value > 0; });
    for (int &value: cdf) {
        if (value > 0) {
            value = static_cast<int>((static_cast<float>(value - minCdf) / (channel.size() - minCdf)) * 255.0f);
        }
    }
}

void PixelFilter::applyCDF(std::vector<float> &channel, const std::vector<int> &cdf) {
    // Apply the cumulative distribution function (CDF) to the channel
    for (auto &value: channel) {
        int idx = static_cast<int>(value * 255.0f);
        value = cdf[idx] / 255.0f;
    }
}

void PixelFilter::RGBtoHSV(float r, float g, float b, float &h, float &s, float &v) {
    // Convert RGB color space to HSV color space
    float K = 0.f;
    if (g < b) {
        std::swap(g, b);
        K = -1.f;
    }
    if (r < g) {
        std::swap(r, g);
        K = -2.f / 6.f - K;
    }

    // Calculate hue, saturation, and value
    float chroma = r - std::min(g, b);
    h = fabs(K + (g - b) / (6.f * chroma + 1e-20f));
    s = chroma / (r + 1e-20f);
    v = r;
}

void PixelFilter::HSVtoRGB(float h, float s, float v, float &r, float &g, float &b) {
    // Convert HSV color space to RGB color space
    if (s == 0.f) {
        r = g = b = v;
        return;
    }

    int i = static_cast<int>(h * 6.f);
    float f = h * 6.f - i;
    float p = v * (1.f - s);
    float q = v * (1.f - f * s);
    float t = v * (1.f - (1.f - f) * s);

    // Calculate RGB values based on the hue
    switch (i % 6) {
        case 0:
            r = v, g = t, b = p;
            break;
        case 1:
            r = q, g = v, b = p;
            break;
        case 2:
            r = p, g = v, b = t;
            break;
        case 3:
            r = p, g = q, b = v;
            break;
        case 4:
            r = t, g = p, b = v;
            break;
        case 5:
            r = v, g = p, b = q;
            break;
    }
}

void PixelFilter::RGBtoHSL(float r, float g, float b, float &h, float &s, float &l) {
    float max = std::max({r, g, b}), min = std::min({r, g, b});
    l = (max + min) / 2.0f;

    // Calculate hue and saturation
    if (max == min) {
        h = s = 0; // achromatic
    } else {
        float d = max - min;
        s = l > 0.5 ? d / (2.0 - max - min) : d / (max + min);

        if (max == r) {
            h = (g - b) / d + (g < b ? 6 : 0);
        } else if (max == g) {
            h = (b - r) / d + 2;
        } else if (max == b) {
            h = (r - g) / d + 4;
        }
        h /= 6.0f;
    }
}

void PixelFilter::HSLtoRGB(float h, float s, float l, float &r, float &g, float &b) {
    // Convert HSL color space to RGB color space
    auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0.f)
            t += 1.f;
        if (t > 1.f)
            t -= 1.f;
        if (t < 1.f / 6.f)
            return p + (q - p) * 6.f * t;
        if (t < 1.f / 2.f)
            return q;
        if (t < 2.f / 3.f)
            return p + (q - p) * (2.f / 3.f - t) * 6.f;
        return p;
    };

    // Calculate RGB values based on the hue
    if (s == 0.f) {
        r = g = b = l; // achromatic
    } else {
        float q = l < 0.5f ? l * (1.f + s) : l + s - l * s;
        float p = 2.f * l - q;
        r = hue2rgb(p, q, h + 1.f / 3.f);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.f / 3.f);
    }
}
