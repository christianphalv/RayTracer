#pragma once

#include <iostream>

#include "Light.h"

class AttenuationLight: public Light {
    public:

        /**
         * Constructor for an attenuation point light.
         *
         * @param source The direction of the point light.
         * @param hue The hue of the point light.
         * @param cValues The constants to define attenuation.
         */
        AttenuationLight(Vector3 source, Vector3 hue, Vector3 cValues);

        /**
         * Retrieve the source direction of the attenuation point light.
         * 
         * For an attenuation point light, the source direction will depend on
         * the relative location of the light and the point.
         *
         * @param point The point at which the source direction is being calculated.
         * @return the source direction.
         */
        Vector3 sourceDirection(Vector3 point) override;

        Vector3 calculateHue(Vector3 point) override;

    private:
        Vector3 cValues;
};