#pragma once

#include <fstream>
#include <iostream>

#include "Vector3.h"

#define MAXPIXELVAL 255

class Image {
    public:
        Image(int width, int height);

        // Cover entire image with one color
        void coverImage(Vector3 color);

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