#pragma once

#include <iostream>
#include <math.h>

class Vector3 {
    public:

        /**
         * Constructor for a Vector3.
         * 
         * The Vector3 is initialized to a unit
         * vector in the x-direction.
         */
        Vector3();

        /**
         * Constructor for a Vector3.
         * 
         * @param x The x-component.
         * @param y The y-component.
         * @param z The z-component.
         */
        Vector3(float x, float y, float z);

        /**
         * Print Vector3 information.
         */
        void info();

        /**
         * Copy the Vector3.
         *
         * @return a copy of the Vector3.
         */
        Vector3 copy();

        /**
         * Retrieve the length (magnitude) of the Vector3.
         *
         * @return the length of the Vector3.
         */
        float length();

        /**
         * Normalize a Vector3 to a unit vector.
         *
         * @return the normalized Vector3.
         */
        Vector3 normalized();

        float getX();
        float getY();
        float getZ();

        void setX(float x);
        void setY(float y);
        void setZ(float z);

    private:
        float x;
        float y;
        float z;
};

// --- Vector Math ---

/**
 * Vector3 addition.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the sum of the two vectors.
 */
Vector3 operator+(Vector3 u, Vector3 v);

/**
 * Vector3 subtraction.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the difference of the two vectors.
 */
Vector3 operator-(Vector3 u, Vector3 v);

/**
 * Vector3 negation.
 *
 * @param v The vector.
 * @return the negative of the vector.
 */
Vector3 operator-(Vector3 v);

/**
 * Vector3-scalar multiplication.
 *
 * @param v The vector.
 * @param c The scalar.
 * @return the scalar multiple of the vector.
 */
Vector3 operator*(Vector3 v, float c);

/**
 * Vector3-scalar multiplication.
 *
 * @param c The scalar.
 * @param v The vector.
 * @return the scalar multiple of the vector.
 */
Vector3 operator*(float c, Vector3 v);

/**
 * Vector3 dot product.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the dot product of the two vectors.
 */
float operator*(Vector3 u, Vector3 v);

/**
 * Vector3 cross product.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the cross product of the two vectors.
 */
Vector3 cross(Vector3 u, Vector3 v);

/**
 * Vector3-scalar division.
 *
 * @param v The vector.
 * @param c The scalar.
 * @return the scalar quotient of the vector.
 */
Vector3 operator/(Vector3 v, float c);

/**
 * Vector3 equality.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return true if the two vectors' (x, y, z) 
 * components are each equal.
 */
bool operator==(Vector3 u, Vector3 v);