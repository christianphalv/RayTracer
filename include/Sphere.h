#pragma once

#include <iostream>

#include "Object.h"

class Sphere: public Object {
    public:

        /**
         * Constructor for an sphere.
         *
         * @param material A pointer to sphere's material.
         * @param position The center position of the sphere.
         * @param radius The radius of the sphere.
         */
        Sphere(Material* material, Vector3 position, float radius);

        /**
         * Calculate a ray-sphere intersection.
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
         * Print sphere information.
         */
        void info() override;

        /**
         * Calculate the albedo at a surface point.
         *
         * @param point The the surface point.
         * @return albedo at the surface point.
         */
        Vector3 albedo(Vector3 point) override;

        float getRadius();

        void setRadius(float r);

    private:
        Vector3 position;
        float radius;
};