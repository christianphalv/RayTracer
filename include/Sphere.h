#pragma once

#include <iostream>

#include "Object.h"

class Sphere: public Object {
    public:

        // Constructors
        Sphere(Vector3 position, float radius, Vector3 color);

        // Calculate the first ray intersection time
        bool rayIntersect(Ray r, float& time) override;

        // Print sphere information
        void info() override;

        // Getters
        float getRadius();

        // Setters
        void setRadius(float r);

    private:
        float radius;
};