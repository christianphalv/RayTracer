#pragma once

#include <iostream>

#include "Light.h"

class PointLight: public Light {
    public:

        /**
         * Constructor for a point light.
         *
         * @param source The direction of the point light.
         * @param hue The hue of the point light.
         */
        PointLight(Vector3 source, Vector3 hue);

        /**
         * Retrieve the source direction of the point light.
         * 
         * For a point light, the source direction will depend on
         * the relative location of the light and the point.
         *
         * @param point The point at which the source direction is being calculated.
         * @return the source direction.
         */
        Vector3 sourceDirection(Vector3 point) override;

};