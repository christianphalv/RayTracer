#pragma once

#include <fstream>
#include <iostream>

#include "MathUtils.h"
#include "Vector3.h"

#define MAXPIXELVAL 255

class Image {
    public:

        /**
         * Constructor for an image.
         *
         * @param width The width of the image in pixels.
         * @param height The height of the image in pixels.
         */
        Image(int width, int height);

        /**
         * Cover the image with a single color.
         *
         * @param color The color to set every pixel to.
         */
        void coverImage(Vector3 color);

        /**
         * Generate a PPM file from the image.
         * 
         * Output PPM files can be found as
         * output/filename.ppm.
         *
         * @param filename The output filename.
         */
        void generatePPM(std::string filename);

        Vector3 getPixel(int x, int y);

        int getWidth();

        int getHeight();

        void setPixel(int x, int y, Vector3 color);

    private:
        Vector3** image;
        int width;
        int height;
};