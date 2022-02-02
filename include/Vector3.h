#pragma once

#include <iostream>
#include <math.h>

class Vector3 {
    public:

        // Constructors
        Vector3();
        Vector3(float x, float y, float z);

        // Print vector3 information
        void info();

        // Return a copy of the Vector3
        Vector3 copy();

        // Return the length of the Vector3
        float length();

        // Return a normalized Vector3
        Vector3 normalized();

        // Getters
        float getX();
        float getY();
        float getZ();

        // Setters
        void setX(float x);
        void setY(float y);
        void setZ(float z);

    private:
        float x;
        float y;
        float z;
};

// --- Vector Math ---

// Vector addition
Vector3 operator+(Vector3 u, Vector3 v);

// Vector subtraction
Vector3 operator-(Vector3 u, Vector3 v);

// Scalar multiplication
Vector3 operator*(Vector3 v, float c);

// Scalar multiplication
Vector3 operator*(float c, Vector3 v);

// Dot product
float operator*(Vector3 u, Vector3 v);

// Scalar division
Vector3 operator/(Vector3 v, float c);

// Vector equality
bool operator==(Vector3 u, Vector3 v);