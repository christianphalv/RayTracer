#include "../include/Scene.h"

Scene::Scene(std::string inputFilename) {

    // Default settings
    float min = -10000;
    float max = 10000;
    this->mtlColor = Vector3(0, 0, 0);
    

    // Open stream to input file
    std::ifstream inputFile(inputFilename, std::ios::in);

    // Read each line of the input file
    std::string line;
    while (std::getline(inputFile, line)) {

        // Stream each line deliminating by spaces
        std::istringstream iss(line);
        iss.exceptions(std::ios::failbit);

        // Stream keywork
        std::string keyword;
        iss >> keyword;

        // Stream rest of line based on keyword
        if (keyword.compare("eye") == 0) {
            this->eye = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("viewdir") == 0) {
            this->viewDir = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("updir") == 0) {
            this->upDir = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("vfov") == 0) {
            this->vfov = safeStreamFloat(iss, 0, 180);

        } else if (keyword.compare("imsize") == 0) {
            this->imageWidth = safeStreamInt(iss, 0, max);
            this->imageHeight = safeStreamInt(iss, 0, max);

        } else if (keyword.compare("bkgcolor") == 0) {
            this->bkgColor = safeStreamVector3(iss, 0, 1);

        } else if (keyword.compare("mtlcolor") == 0) {
            this->mtlColor = safeStreamVector3(iss, 0, 1);

        } else if (keyword.compare("sphere") == 0) {
            this->objects.push_back(new Sphere(safeStreamVector3(iss, min, max), safeStreamFloat(iss, min, max), this->mtlColor));
        } 
    }
}

Vector3 Scene::getEye() {
    return this->eye;
}

Vector3 Scene::getViewDirection() {
    return this->viewDir;
}

Vector3 Scene::getUpDirection() {
    return this->upDir;
}

float Scene::getVerticalFov() {
    return this->vfov;
}

int Scene::getImageWidth() {
    return this->imageWidth;
}

int Scene::getImageHeight() {
    return this->imageHeight;
}

Vector3 Scene::getBackgroundColor() {
    return this->bkgColor;
}

std::vector<Object*> Scene::getObjects() {
    return this->objects;
}

float Scene::safeStreamFloat(std::istringstream& iss, float min, float max) {

    // Try to read float from stream
    float value;
    try {
        iss >> value;
    } catch (...) {
        std::cout << "Error: Could not convert input string to float.\n";
        exit(0);
    }

    // Check if value is within valid range
    if (value < min || value > max) {
        std::cout << "Error: Value not within valid range.\n";
        exit(0);
    }

    return value;
}

int Scene::safeStreamInt(std::istringstream& iss, int min, int max) {

    // Try to read float from stream
    int value;
    try {
        iss >> value;
    } catch (...) {
        std::cout << "Error: Could not convert input string to int.\n";
        exit(0);
    }

    // Check if value is within valid range
    if (value < min || value > max) {
        std::cout << "Error: Value not within valid range.\n";
        exit(0);
    }

    return value;
}

Vector3 Scene::safeStreamVector3(std::istringstream& iss, float min, float max) {

    // Try to read floats from stream
    float x;
    float y;
    float z;
    try {
        iss >> x;
        iss >> y;
        iss >> z;

    } catch (...) {
        std::cout << "Error: Could not convert input string to float.\n";
        exit(0);
    }

    // Check if x value is within valid range
    if (x < min || x > max) {
        std::cout << "Error: Value not within valid range.\n";
        exit(0);
    }

    // Check if y value is within valid range
    if (y < min || y > max) {
        std::cout << "Error: Value not within valid range.\n";
        exit(0);
    }

    // Check if z value is within valid range
    if (z < min || z > max) {
        std::cout << "Error: Value not within valid range.\n";
        exit(0);
    }

    return Vector3(x, y, z);
}
