#pragma once

#include <iostream>
#include <math.h>

class Vector2 {
    public:

        /**
         * Constructor for a Vector2.
         * 
         * The Vector3 is initialized to a unit
         * vector in the x-direction.
         */
        Vector2();

        /**
         * Constructor for a Vector3.
         * 
         * @param x The x-component.
         * @param y The y-component.
         */
        Vector2(float x, float y);

        /**
         * Print Vector3 information.
         */
        void info();

        /**
         * Copy the Vector2.
         *
         * @return a copy of the Vector2.
         */
        Vector2 copy();

        /**
         * Retrieve the length (magnitude) of the Vector2.
         *
         * @return the length of the Vector2.
         */
        float length();

        /**
         * Normalize a Vector2 to a unit vector.
         *
         * @return the normalized Vector2.
         */
        Vector2 normalized();

        float getX();
        float getY();

        void setX(float x);
        void setY(float y);

    private:
        float x;
        float y;
};

// --- Vector Math ---

/**
 * Vector2 addition.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the sum of the two vectors.
 */
Vector2 operator+(Vector2 u, Vector2 v);

/**
 * Vector2 subtraction.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the difference of the two vectors.
 */
Vector2 operator-(Vector2 u, Vector2 v);

/**
 * Vector2 negation.
 *
 * @param v The vector.
 * @return the negative of the vector.
 */
Vector2 operator-(Vector2 v);

/**
 * Vector2-scalar multiplication.
 *
 * @param v The vector.
 * @param c The scalar.
 * @return the scalar multiple of the vector.
 */
Vector2 operator*(Vector2 v, float c);

/**
 * Vector2-scalar multiplication.
 *
 * @param c The scalar.
 * @param v The vector.
 * @return the scalar multiple of the vector.
 */
Vector2 operator*(float c, Vector2 v);

/**
 * Vector2 dot product.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the dot product of the two vectors.
 */
float operator*(Vector2 u, Vector2 v);

/**
 * Vector2 cross product.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return the cross product of the two vectors.
 */
float cross(Vector2 u, Vector2 v);

/**
 * Vector2-scalar division.
 *
 * @param v The vector.
 * @param c The scalar.
 * @return the scalar quotient of the vector.
 */
Vector2 operator/(Vector2 v, float c);

/**
 * Vector2 equality.
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return true if the two vectors' (x, y, z) 
 * components are each equal.
 */
bool operator==(Vector2 u, Vector2 v);