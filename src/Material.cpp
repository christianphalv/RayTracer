#include "../include/Material.h"

Material::Material() {
    this->albedo = Vector3(1.0, 0.0, 0.5);
    this->specular = Vector3(0.0, 0.0, 0.0);
    this->K = Vector3(1.0, 0.0, 0.0);
    this->N = 0.0;
    this->opacity = 1;
    this->refraction = 1;
}

Material::Material(Vector3 albedo, Vector3 specular, Vector3 K, float N, float opacity, float refraction) {
    this->albedo = albedo;
    this->specular = specular;
    this->K = K;
    this->N = N;
    this->opacity = opacity;
    this->refraction = refraction;
}

Vector3 Material::phongShade(Vector3 N, Vector3 L, Vector3 H) {

    // Calculate ambient factor
    Vector3 ambient = this->K.getX() * this->albedo;

    // Calculate diffuse factor
    Vector3 diffuse = this->K.getY() * this->albedo * MathUtils::clamp((N * L), 0, 1);

    // Calculate specular factor
    Vector3 specular = this->K.getZ() * this->specular * pow(MathUtils::clamp(N * H, 0, 1), this->N);

    // Combine illumination model
    return ambient + diffuse + specular;
}

Vector3 Material::getAlbedo(Vector2 uv) {
    return this->albedo;
}

Vector3 Material::getSpecular() {
    return this->specular;
}

Vector3 Material::getK() {
    return this->K;
}

float Material::getN() {
    return this->N;
}

float Material::getOpacity() {
    return this->opacity;
}
float Material::getRefraction() {
    return this->refraction;
}