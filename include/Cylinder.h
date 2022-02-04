#pragma once

#include <iostream>

#include "Object.h"

class Cylinder: public Object {
    public:

        // Constructors
        Cylinder(Vector3 position, Vector3 direction, float radius, float length, Vector3 color);

        // Calculate the first ray intersection time
        bool rayIntersect(Ray r, float& time) override;

        // Print sphere information
        void info() override;

        // Getters
        Vector3 getDirection();

        float getRadius();

        float getLength();

        // Setters
        void setDirection(Vector3 d);

        void setRadius(float r);

        void setLength(float l);

    private:
        Vector3 direction;
        float radius;
        float length;
};