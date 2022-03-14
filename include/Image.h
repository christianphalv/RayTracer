#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "MathUtils.h"
#include "Vector2.h"
#include "Vector3.h"

#define MAXPIXELVAL 255

class Image {
    public:

        /**
         * Constructor for an image.
         *
         * Creates a default 100x100 pixel image.
         */
        Image();

        /**
         * Constructor for an image.
         *
         * @param width The width of the image in pixels.
         * @param height The height of the image in pixels.
         */
        Image(int width, int height);

        /**
         * Constructor for an image.
         *
         * @param textureFilename The name of the texture file.
         */
        Image(std::string textureFilename);

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

        /**
         * Retrieve a sample from the image using bilinear interpolation.
         *
         * @param uv The normalized uv coordinate of the sample.
         */
        Vector3 getSample(Vector2 uv);

        Vector3 getPixel(int x, int y);

        int getWidth();

        int getHeight();

        void setPixel(int x, int y, Vector3 color);

    private:
        //Vector3** image;
        std::vector<std::vector<Vector3>> image;
        int width;
        int height;
};