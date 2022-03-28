#pragma once

#include "Image.h"
#include "Material.h"
#include "MathUtils.h"
#include "Vector3.h"

class TexturedMaterial : public Material {
    public:
        /**
         * Constructor for a textured material.
         * 
         * The albedo, specular, K, and N components
         * of the material will be set to a default
         * configuration.
         */
        TexturedMaterial(Image* texture);

        /**
         * Constructor for a textured material.
         *
         * @param texture The texture of the material.
         * @param specular The specular color of the material.
         * @param K A vector containing the K values ka, kd, ks of the material.
         * @param N The specular intensity of the material.
         */
        TexturedMaterial(Image* texture, Vector3 specular, Vector3 K, float N, float opacity, float refraction);

        /**
         * Calculate shading of a point using the phong-blinn illumination model.
         *
         * @param N The surface normal of the object at the point.
         * @param L The direction of the light.
         * @param H The halfway vector.
         * @return the shaded color at the point.
         */
        Vector3 phongShade(Vector3 N, Vector3 L, Vector3 H);

        Vector3 getAlbedo(Vector2 uv) override;

    private:
        Vector3 albedo;
        Vector3 specular;
        Vector3 K;
        float N;

        Image* texture;
};