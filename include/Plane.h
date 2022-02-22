#pragma once

#include <iostream>

#include "Object.h"

class Plane: public Object {
    public:

        /**
         * Constructor for an plane.
         *
         * @param material A pointer to plane's material.
         * @param v0 The 0th vertex.
         * @param v1 The 1th vertex.
         * @param v2 The 2th vertex.
         */
        Plane(Material* material, Vector3 v0, Vector3 v1, Vector3 v2);

        /**
         * Constructor for an plane.
         *
         * @param material A pointer to plane's material.
         * @param normal The normal of the plane.
         * @param vertex A vertex in the plane.
         */
        Plane(Material* material, Vector3 normal, Vector3 vertex);

        /**
         * Calculate a ray-plane intersection.
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
         * Print plane information.
         */
        void info() override;

    private:
        Vector3 normal;
        float D;
};