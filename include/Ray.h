#pragma once

#include <iostream>

#include "Vector3.h"

class Ray {
    public:
        // Constructors
        Ray(Vector3 origin, Vector3 direction);

        // Calculate point at time t along ray
        Vector3 calculatePoint(float t);

        // Getters
        Vector3 getOrigin();
        Vector3 getDirection();

        // Setters
        void setOrigin(Vector3 v);
        void setDirection(Vector3 v);

    private:
        Vector3 origin;
        Vector3 direction;
};