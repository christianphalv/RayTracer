#pragma once

#include <iostream>

#include "Object.h"
#include "Plane.h"

class Triangle: public Object {
    public:

        /**
         * Constructor for an triangle.
         *
         * @param material A pointer to triangle's material.
         * @param v0 The 0th triangle vertex.
         * @param v1 The 1th triangle vertex.
         * @param v2 The 2th triangle vertex.
         */
        Triangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2);

        /**
         * Calculate a ray-triangle intersection.
         *
         * @param r The ray.
         * @param min The minimum intersection time.
         * @param max The maximum intersection time.
         * @param time OUT The first intersection time.
         * @return true if intersection, otherwise false.
         */
        bool rayIntersect(Ray r, float min, float max, float& time) override;

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

    private:
        Vector3 v0;
        Vector3 v1;
        Vector3 v2;

        Plane* plane;
};