#pragma once

#include <iostream>

#include "Object.h"
#include "Plane.h"
#include "Triangle.h"
#include "Vector2.h"

class TexturedSmoothShadedTriangle: public Triangle {
    public:

        /**
         * Constructor for an triangle.
         *
         * @param material A pointer to triangle's material.
         * @param v0 The 0th triangle vertex.
         * @param v1 The 1th triangle vertex.
         * @param v2 The 2th triangle vertex.
         * @param t0 The 0th triangle texture coordinate.
         * @param t1 The 1th triangle texture coordinate.
         * @param t2 The 2th triangle texture coordinate.
         * @param n0 The 0th vertex normal.
         * @param n1 The 1th vertex normal.
         * @param n2 The 2th vertex normal.
         */
        TexturedSmoothShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2, Vector2 t0, Vector2 t1, Vector2 t2, Vector3 n0, Vector3 n1, Vector3 n2);

        /**
         * Calculate the normal at a surface point.
         *
         * @param point The the surface point.
         * @return normal at the surface point.
         */
        Vector3 calculateNormal(Vector3 point) override;

        /**
         * Print triangle information.
         */
        void info() override;

        /**
         * Calculate the albedo at a surface point.
         *
         * @param point The the surface point.
         * @return albedo at the surface point.
         */
        virtual Vector3 albedo(Vector3 point);

    private:
        Vector2 t0;
        Vector2 t1;
        Vector2 t2;

        Vector3 n0;
        Vector3 n1;
        Vector3 n2;
};