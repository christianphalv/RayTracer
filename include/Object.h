#pragma once

#include <iostream>

#include "Ray.h"
#include "Vector3.h"

class Object {
    public:

        // Calculate the first ray intersection time
        virtual bool rayIntersect(Ray r, float& time) = 0;

        // Print object information
        virtual void info() = 0;

        // Getters
        Vector3 getPosition();
        //Vector3 getRotation();
        Vector3 getColor();

        // Setters
        void setPosition(Vector3 v);
        //void setRotation(Vector3 v);
        void setColor(Vector3 v);


    protected:
        Vector3 position;
        //Vector3 rotation;
        Vector3 color;
};