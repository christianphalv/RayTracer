#include "../include/Image.h"

Image::Image(int width, int height) {

    this->width = width;
    this-> height = height;

    // Initialize 2D array of Vector3
    this->image = (Vector3**) malloc(this->width * sizeof(Vector3*));
    for (int i = 0; i < this->width; i++) {
        this->image[i] = (Vector3*) malloc(this->height * sizeof(Vector3));
    }

    // Set each pixel to black
    this->coverImage(Vector3(0, 0, 0));

}

void Image::coverImage(Vector3 color) {

    // Loop through each pixel
    for (int j = 0; j < this->height; j++) {
        for (int i = 0; i < this->width; i++) {

            // Set each pixel's value to a copy of color
            this->image[i][j] = color.copy();
        }
    }
}

void Image::generatePPM(std::string filename) {

    // Append PPM file type
    filename.append(".ppm");

    // Open stream to output file
    std::ofstream outputFile(filename, std::ios::out);

    // Write file header
    outputFile << "P3" << "\n"
        << this->width << " " << this->height << "\n"
        << MAXPIXELVAL << "\n";

    // Write pixel colors
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            outputFile << static_cast<int>(this->image[i][j].getX() * MAXPIXELVAL) << " " 
            << static_cast<int>(this->image[i][j].getY() * MAXPIXELVAL)  << " " 
            << static_cast<int>(this->image[i][j].getZ() * MAXPIXELVAL)  << "\n";
        }
    }

    // Close output file
    outputFile.close();
}

Vector3 Image::getPixel(int x, int y) {
    return this->image[x][y];
}

int Image::getWidth() {
    return this->width;
}

int Image::getHeight() {
    return this -> height;
}

void Image::setPixel(int x, int y, Vector3 color) {
    this->image[x][y] = Vector3(MathUtils::clamp(color.getX(), 0, 1), MathUtils::clamp(color.getY(), 0, 1), MathUtils::clamp(color.getZ(), 0, 1));
}