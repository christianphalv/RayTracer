#pragma once

#include "Vector3.h"

#define PI 3.14159265

namespace MathUtils {

    /**
     * Convert radians to degrees.
     *
     * @param radians The value in radians.
     * @return the value in degrees.
     */
    float radiansToDegrees(float radians);

    /**
     * Convert degrees to radians.
     *
     * @param degrees The value in degrees.
     * @return the value in radians.
     */
    float degreesToRadians(float degrees);

    /**
     * Convert hexcode to an RGB vector.
     *
     * @param hex The color in hexcode.
     * @return the color in RGB values.
     */
    Vector3 hexToColor(int hex);

    /**
     * Clamp a float to a minimum and maximum value.
     *
     * @param x The value being clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return the clamped value.
     */
    float clamp(float x, float min, float max);
}
