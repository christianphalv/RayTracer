#include "../include/MathUtils.h"

float radiansToDegrees(float radians) {
    return radians * (180 / PI);
}

float degreesToRadians(float degrees) {
    return degrees * (PI / 180);
}

Vector3 hexToColor(int hex) {

    // Declare r g b values
    int r, g, b;

    // Extract r g b values from hex
    r = ((hex >> 16) & 0xFF) / 255.0;
    g = ((hex >> 8) & 0xFF) / 255.0;
    b = ((hex) & 0xFF) / 255.0;

    // Return color
    return Vector3(r, b, g);
}