#pragma once

#include <iostream>

#include "Vector3.h"

class Ray {
    public:
        
        /**
         * Constructor for a ray.
         *
         * @param origin The origin of the ray.
         * @param direction The direction of the ray.
         */
        Ray(Vector3 origin, Vector3 direction);

        /**
         * Calculate the point at a time along the ray.
         *
         * @param t The time along the ray.
         * @return the point along the ray.
         */
        Vector3 calculatePoint(float t);

        Vector3 getOrigin();
        Vector3 getDirection();

        void setOrigin(Vector3 v);
        void setDirection(Vector3 v);

    private:
        Vector3 origin;
        Vector3 direction;
};