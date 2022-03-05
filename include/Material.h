#pragma once

#include "MathUtils.h"
#include "Vector3.h"

class Material {
    public:
        /**
         * Constructor for a material.
         * 
         * The albedo, specular, K, and N components
         * of the material will be set to a default
         * configuration.
         */
        Material();

        /**
         * Constructor for a material.
         *
         * @param albedo The albedo color of the material.
         * @param specular The specular color of the material.
         * @param K A vector containing the K values ka, kd, ks of the material.
         * @param N The specular intensity of the material.
         */
        Material(Vector3 albedo, Vector3 specular, Vector3 K, float N);

        /**
         * Calculate shading of a point using the phong-blinn illumination model.
         *
         * @param N The surface normal of the object at the point.
         * @param L The direction of the light.
         * @param H The halfway vector.
         * @return the shaded color at the point.
         */
        Vector3 phongShade(Vector3 N, Vector3 L, Vector3 H);

        Vector3 getAlbedo();
        Vector3 getSpecular();
        Vector3 getK();
        float getN();

        /**
         * Retrieve the ambient color of the material.
         * 
         * This constant is calculated in the constructor to
         * save calculations.
         *
         * @return the ambient color of the material.
         */
        Vector3 getAmbient();
        

    private:
        Vector3 albedo;
        Vector3 specular;
        Vector3 K;
        float N;

        Vector3 ambient;
};