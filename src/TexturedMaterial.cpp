#include "../include/TexturedMaterial.h"

TexturedMaterial::TexturedMaterial(Image* texture): Material() {
    this->texture = texture;
}

TexturedMaterial::TexturedMaterial(Image* texture, Vector3 specular, Vector3 K, float N): Material(Vector3(0, 0, 0), specular, K, N) {
    this->texture = texture;
}

Vector3 TexturedMaterial::phongShade(Vector3 N, Vector3 L, Vector3 H) {

    // Calculate ambient factor
    Vector3 ambient = this->K.getX() * this->albedo;

    // Calculate diffuse factor
    Vector3 diffuse = this->K.getY() * this->albedo * MathUtils::clamp((N * L), 0, 1);

    // Calculate specular factor
    Vector3 specular = this->K.getZ() * this->specular * pow(MathUtils::clamp(N * H, 0, 1), this->N);

    // Combine illumination model
    return ambient + diffuse + specular;
}

Vector3 TexturedMaterial::getAlbedo(Vector2 uv) {
    return this->texture->getSample(uv);
}
