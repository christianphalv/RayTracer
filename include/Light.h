#pragma once

#include "Vector3.h"

class Light {
    public:
        
        /**
         * Constructor for a light.
         *
         * @param source The source of the light.
         * @param hue The hue of the light.
         */
        Light(Vector3 source, Vector3 hue);

        /**
         * Retrieve the source direction of the light.
         *
         * @param point The point at which the source direction is being calculated.
         * @return the source direction.
         */
        virtual Vector3 sourceDirection(Vector3 point) = 0;

        Vector3 getHue();

    protected:
        Vector3 source;
        Vector3 hue;
};