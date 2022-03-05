#pragma once

#include <iostream>

#include "Material.h"
#include "Ray.h"
#include "Vector3.h"

class Object {
    public:

        /**
         * Constructor for an object.
         *
         * @param material A pointer to object's material.
         */
        Object(Material* material);

        /**
         * Calculate a ray-object intersection.
         *
         * @param r The ray.
         * @param min The minimum intersection time.
         * @param max The maximum intersection time.
         * @param time OUT The first intersection time.
         * @return true if intersection, otherwise false.
         */
        virtual bool rayIntersect(Ray r, float min, float max, float& time) = 0;

        /**
         * Calculate the normal at a surface point.
         *
         * @param point The the surface point.
         * @return normal at the surface point.
         */
        virtual Vector3 calculateNormal(Vector3 point) = 0;

        /**
         * Print object information.
         */
        virtual void info() = 0;
        
        Material* getMaterial();

    protected:

        Material* material;
};