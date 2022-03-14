#pragma once

#include <iostream>

#include "Object.h"
#include "Plane.h"
#include "Triangle.h"

class FlatShadedTriangle: public Triangle {
    public:

        /**
         * Constructor for an triangle.
         *
         * @param material A pointer to triangle's material.
         * @param v0 The 0th triangle vertex.
         * @param v1 The 1th triangle vertex.
         * @param v2 The 2th triangle vertex.
         */
        FlatShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2);

        /**
         * Print triangle information.
         */
        void info() override;

    private:

};