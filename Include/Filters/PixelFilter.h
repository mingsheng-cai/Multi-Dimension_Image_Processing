/**
 * @file PixelFilter.h
 *
 * @brief Defines the PixelFilter class for pixel-level image processing operations.
 *
 * PixelFilter, implementing the IFilter2D interface, offers a variety of pixel-level manipulations for 2D images,
 * including grayscale conversion, brightness adjustment, histogram equalization, thresholding, and noise addition.
 * It supports operations in different color spaces (HSL, HSV) and allows for configurable processing parameters such
 * as brightness level, threshold for pixelation, and noise percentage. This class facilitates detailed image editing
 * and enhancement tasks, making it a versatile tool in the Advanced Programming Group's image processing toolkit.
 * Whether for pre-processing steps or standalone adjustments, PixelFilter provides robust solutions for refining image aesthetics and quality.
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

#pragma once

#ifndef ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PIXELFILTER_H
#define ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PIXELFILTER_H

#include <Image.h>
#include <Filters/Filter.h>

#include <string>

class PixelFilter : public IFilter2D {
private:
    std::string filterType; // "grayscale", "brightness", "histogram", "threshold", "noise"
    int brightness = 128; // Default brightness
    std::string space; // "HSL" or "HSV"
    int threshold = 0; // Threshold value
    double percentage = 0; // Percentage of noise

    /**
     * Converts an image to grayscale.
     *
     * This method transforms a color image into grayscale by calculating the luminance of each pixel based on its red,
     * green, and blue components. The grayscale image replaces the original image data. This operation is performed only
     * if the image has more than one color channel.
     *
     * @param image: A reference to an Image object to be converted to grayscale. The image is modified in place.
     */
    void convertToGrayscale(Image &image);

    /**
     * Adjusts the brightness of an image.
     *
     * This method modifies the brightness of each pixel in the provided Image object based on a specified brightness
     * adjustment value. The brightness is adjusted by adding the brightness value to each pixel's intensity, with the
     * result clamped to the [0, 255] range. The operation affects all channels of the image equally.
     *
     * @param image: A reference to an Image object whose brightness will be adjusted. The image is modified in place.
     */
    void adjustBrightness(Image &image);

    /**
     * Equalizes the histogram of an image.
     *
     * This method applies histogram equalization to the provided Image object, enhancing the contrast of the image. It can
     * operate on different color spaces, including RGB, HSL, and HSV. For color images, the equalization is applied to the
     * luminance or value channel, preserving color integrity while improving contrast. This method is suitable for images
     * that suffer from poor contrast due to lighting conditions or exposure settings.
     *
     * @param image: A reference to an Image object whose histogram will be equalized. The image is modified in place.
     */
    void equalizeHistogram(Image &image);

    /**
     * Applies thresholding to an image.
     *
     * This method applies a thresholding operation to the provided Image object. Pixels with intensity above the threshold
     * are set to the maximum value (255), and those below are set to zero, effectively binarizing the image. The operation
     * can be applied to images in different color spaces, including RGB, HSL, and HSV, based on the specified parameters.
     *
     * @param image: A reference to an Image object to be thresholded. The image is modified in place.
     */
    void thresholdPixel(Image &image);

    /**
    * Adds salt-and-pepper noise to an image.
    *
    * This method introduces salt-and-pepper noise to the provided Image object by randomly selecting a specified percentage
    * of pixels and setting them to either the maximum value (255, salt) or the minimum value (0, pepper). This operation is
    * designed to simulate common types of noise found in digital images.
    *
    * @param image: A reference to an Image object that will have noise added. The image is modified in place.
    */
    void addNoise(Image &image);

    /**
     * Calculates the histogram and cumulative distribution function (CDF) for a given image channel.
     *
     * This helper function computes the histogram of the provided channel data and then calculates the cumulative
     * distribution function based on the histogram. These calculations are used in histogram equalization processes
     * to adjust the contrast of an image. The CDF is later used to map the original pixel values to their new values
     * for contrast enhancement.
     *
     * @param channel: A vector of floats representing the normalized intensity values of a single channel of the image.
     * @param histogram: A reference to a vector of ints where the histogram data will be stored.
     * @param cdf: A reference to a vector of ints where the CDF data will be stored.
     */
    void calculateHistogramAndCDF(const std::vector<float> &channel, std::vector<int> &histogram, std::vector<int> &cdf);

    /**
     * Applies the cumulative distribution function to a channel of image data.
     *
     * After calculating the cumulative distribution function (CDF) for an image channel, this method maps each pixel's
     * intensity in the channel to a new value based on the CDF. This mapping enhances the contrast of the channel according
     * to the histogram equalization process. This method is crucial for the final step of applying histogram equalization
     * to an image.
     *
     * @param channel: A reference to a vector of floats representing the normalized intensity values of a single channel of the image, to be modified in place.
     * @param cdf: A vector of ints representing the CDF, used to map the original intensities to their new values.
     */
    void applyCDF(std::vector<float> &channel, const std::vector<int> &cdf);

    /**
     * Converts RGB color space to HSV color space.
     *
     * This function converts the color of a pixel from the RGB color space to the HSV color space. The conversion process
     * takes into account the chroma and the lightness of the color to accurately represent it in HSV space. This conversion
     * is useful for operations that are more effectively performed in HSV space, such as thresholding based on color saturation
     * or value.
     *
     * @param r: The red component of the color.
     * @param g: The green component of the color.
     * @param b: The blue component of the color.
     * @param h: Reference to a float to store the hue component.
     * @param s: Reference to a float to store the saturation component.
     * @param v: Reference to a float to store the value component.
     */
    void RGBtoHSV(float r, float g, float b, float &h, float &s, float &v);

    /**
     * Converts HSV color space to RGB color space.
     *
     * This function converts the color of a pixel from the HSV color space back to the RGB color space. The conversion
     * allows changes made in the HSV space, such as contrast adjustments or thresholding, to be represented in the
     * conventional RGB color space for display or further processing. This method ensures that operations performed
     * in HSV space can be accurately reflected in the final image.
     *
     * @param h: The hue component of the color.
     * @param s: The saturation component of the color.
     * @param v: The value component of the color.
     * @param r: Reference to a float to store the red component.
     * @param g: Reference to a float to store the green component.
     * @param b: Reference to a float to store the blue component.
     */
    void HSVtoRGB(float h, float s, float v, float &r, float &g, float &b);

    /**
     * Converts RGB color space to HSL color space.
     *
     * This function transforms the RGB representation of a color into its HSL counterpart. HSL (Hue, Saturation, Lightness)
     * offers a more intuitive way to describe color adjustments such as changing brightness or saturation. This conversion
     * is particularly useful for image processing tasks that require manipulation of color properties distinct from their
     * brightness, like adjusting colors or performing color-based thresholding.
     *
     * @param r: The red component of the color.
     * @param g: The green component of the color.
     * @param b: The blue component of the color.
     * @param h: Reference to a float to store the hue component.
     * @param s: Reference to a float to store the saturation component.
     * @param l: Reference to a float to store the light
     * @param l: Reference to a float to store the lightness component.
     */
    void RGBtoHSL(float r, float g, float b, float &h, float &s, float &l);

    /**
     * Converts HSL color space to RGB color space.
     *
     * This function reverses the process of RGB to HSL conversion, translating colors from the HSL (Hue, Saturation, Lightness)
     * space back to RGB. This is crucial for displaying processed images on devices that use RGB color space or for further
     * processing in RGB. Adjustments made in HSL, which can be more intuitive for certain image manipulations, are accurately
     * reflected in the RGB output.
     *
     * @param h: The hue component in HSL space.
     * @param s: The saturation component in HSL space.
     * @param l: The lightness component in HSL space.
     * @param r: Reference to a float to store the calculated red component in RGB space.
     * @param g: Reference to a float to store the calculated green component in RGB space.
     * @param b: Reference to a float to store the calculated blue component in RGB space.
     */
    void HSLtoRGB(float h, float s, float l, float &r, float &g, float &b);

public:
    /**
     * Constructor for the PixelFilter class.
     *
     * Initializes a PixelFilter object with specified parameters for different filtering operations. The type parameter
     * dictates the filter operation to be applied (e.g., grayscale conversion, brightness adjustment). Optional parameters
     * like brightness adjustment value, color space for histogram equalization, threshold for thresholding, and noise percentage
     * for adding salt-and-pepper noise can also be specified. The constructor validates input parameters to ensure they are within
     * acceptable ranges for the specified filter type.
     *
     * @param type: The type of filter operation to be applied.
     * @param brightness: Optional parameter specifying the brightness adjustment value (applicable if type is "Brightness").
     * @param space: Optional parameter specifying the color space for histogram equalization (applicable if type is "Equalisation").
     * @param threshold: Optional parameter specifying the threshold value for thresholding operations (applicable if type is "Thresholding").
     * @param percentage: Optional parameter specifying the percentage of pixels affected by salt-and-pepper noise (applicable if type is "SaltAndPepperNoise").
     * @throws std::invalid_argument if any parameter is outside its expected range based on the filter type.
     */
    PixelFilter(const std::string &type, const std::optional<int> &brightness = std::nullopt,
                const std::string &space = "", int threshold = 0, double percentage = 0);

    /**
     * Applies the specified filtering operation to an image.
     *
     * Based on the filter type specified during object construction, this method applies the corresponding image processing
     * operation to the provided Image object. Operations include grayscale conversion, brightness adjustment, histogram
     * equalization, thresholding, and adding salt-and-pepper noise. The method ensures that operations are applied correctly
     * based on the provided parameters and the image's properties. Unsupported filter types result in an exception.
     *
     * @param image: A reference to an Image object that will be modified by the filter operation.
     * @throws std::invalid_argument if the filter type is unsupported.
     */
    void apply(Image &image) override;
};

#endif //ADVANCED_PROGRAMMING_GROUP_RADIX_SORT_PIXELFILTER_H
