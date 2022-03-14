#pragma once

#include <iostream>

#include "Object.h"
#include "Plane.h"
#include "Triangle.h"
#include "Vector2.h"

class TexturedFlatShadedTriangle: public Triangle {
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
         */
        TexturedFlatShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2, Vector2 t0, Vector2 t1, Vector2 t2);

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
        Vector3 albedo(Vector3 point) override;

    private:
        Vector2 t0;
        Vector2 t1;
        Vector2 t2;
};