#include "../include/Image.h"

Image::Image() {

    this->width = 100;
    this-> height = 100;

    for (int j = 0; j < height; j++) {
        this->image.push_back(std::vector<Vector3>());
        for (int i = 0; i < width; i++) {
            this->image[j].push_back(Vector3(0, 0, 0));
        }
    }
}

Image::Image(int width, int height) {

    this->width = width;
    this-> height = height;

    for (int j = 0; j < height; j++) {
        this->image.push_back(std::vector<Vector3>());
        for (int i = 0; i < width; i++) {
            this->image[j].push_back(Vector3(0, 0, 0));
        }
    }
}

Image::Image(std::string textureFilename) {

    // Open stream to input file
    std::ifstream textureFile(textureFilename, std::ios::in | std::ios::binary);

    // Check if valid file
    if (!textureFile.is_open()) {
        std::cout << "Error: Invalid texture file. \n";
        exit(0);
    }

    // Read the header of the file
    std::string line;
    std::getline(textureFile, line);
    std::istringstream iss(line);

    // Declare header values
    std::string fileType;
    int width;
    int height;
    int maxPixelValue;

    // Stream header values
    iss >> fileType;
    iss >> width;
    iss >> height;
    iss >> maxPixelValue;

    // Set image size
    this->width = width;
    this-> height = height;

    // Initialize image
    for (int j = 0; j < height; j++) {
        this->image.push_back(std::vector<Vector3>());
        for (int i = 0; i < width; i++) {
            this->image[j].push_back(Vector3(0, 0, 0));
        }
    }

    // Initialize values
    std::vector<int> values;

    // Read each line of the input file
    while (std::getline(textureFile, line)) {

        // Stream each line deliminating by spaces
        std::istringstream iss(line);

        float value;
        while (iss >> value) {
            // Try to read float from stream
            try {
                //iss >> value;
            } catch (...) {
                std::cout << "Error: Could not convert input string to integer.\n";
                exit(0);
            }

            // Add value to values vector
            values.push_back(value);
        }
    }

    // Check if correct number of values
    if (values.size() % 3 != 0) {
        std::cout << "Error: Incorrect number of values.\n";
        exit(0);
    }

    // Initialize colors
    std::vector<Vector3> colors;

    // Create each pixel from the values
    for (int i = 0; i < values.size(); i += 3) {
        
        // Initialize pixel
        colors.push_back(Vector3(values[i], values[i + 1], values[i + 2]) / maxPixelValue);
    }

    for (int i = 0; i < colors.size(); i++) {

        // Set pixel in image
        image[i / width][i % width] = colors[i];
    }
}

void Image::coverImage(Vector3 color) {

    // Loop through each pixel
    for (int j = 0; j < this->height; j++) {
        for (int i = 0; i < this->width; i++) {

            // Set each pixel's value to a copy of color
            this->image[j][i] = color.copy();
        }
    }
}

void Image::generatePPM(std::string filename) {

    // Append PPM file type
    filename.append(".ppm");

    // Open stream to output file
    std::ofstream outputFile(filename, std::ios::out);

    // Write file header
    outputFile << "P3" << " "<< this->width << " " << this->height << " " << MAXPIXELVAL << "\n";

    // Write pixel colors
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            outputFile << static_cast<int>(this->image[j][i].getX() * MAXPIXELVAL) << " " 
            << static_cast<int>(this->image[j][i].getY() * MAXPIXELVAL)  << " " 
            << static_cast<int>(this->image[j][i].getZ() * MAXPIXELVAL)  << "\n";
        }
    }

    // Close output file
    outputFile.close();
}

Vector3 Image::getSample(Vector2 uv) {

    // Calculate x and y
    float x = uv.getX() * (this->width - 1);
    float y = uv.getY() * (this->height - 1);

    // Calculate i and j
    int i = (int) x;
    int j = (int) y;

    i = MathUtils::clamp(i, 0, this->width - 2);
    j = MathUtils::clamp(j, 0, this->height - 2);

    // Calculate alpha and beta
    float alpha = x - (float) i;
    float beta = y - (float) j;

    // Calculate components
    Vector3 c0 = (1 - alpha) * (1 - beta) * image[j][i];
    Vector3 c1 = (alpha) * (1 - beta) * image[j][i + 1];
    Vector3 c2 = (1 - alpha) * (beta) * image[j + 1][i];
    Vector3 c3 = (alpha) * (beta) * image[j + 1][i + 1];

    // Return sum of color components
    return c0 + c1 + c2 + c3;
}

Vector3 Image::getPixel(int x, int y) {
    return this->image[y][x];
}

int Image::getWidth() {
    return this->width;
}

int Image::getHeight() {
    return this -> height;
}

void Image::setPixel(int x, int y, Vector3 color) {
    this->image[y][x] = Vector3(MathUtils::clamp(color.getX(), 0, 1), MathUtils::clamp(color.getY(), 0, 1), MathUtils::clamp(color.getZ(), 0, 1));
}