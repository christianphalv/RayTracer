#pragma once

#include <iostream>

#include "Light.h"

class DirectionalLight: public Light {
    public:

        /**
         * Constructor for a directional light.
         *
         * @param source The direction of the directional light.
         * @param hue The hue of the light.
         */
        DirectionalLight(Vector3 source, Vector3 hue);

        /**
         * Retrieve the source direction of the directional light.
         * 
         * For a directional light, the source direction will be the same
         * for any point in the scene.
         *
         * @param point The point at which the source direction is being calculated.
         * @return the source direction.
         */
        Vector3 sourceDirection(Vector3 point) override;

};