#include "../include/Material.h"

Material::Material() {
    this->albedo = Vector3(1.0, 0.0, 0.5);
    this->specular = Vector3(0.0, 0.0, 0.0);
    this->K = Vector3(1.0, 0.0, 0.0);
    this->N = 0.0;

    // Precalculate ambient
    this->ambient = this->K.getX() * this->albedo;
}

Material::Material(Vector3 albedo, Vector3 specular, Vector3 K, float N) {
    this->albedo = albedo;
    this->specular = specular;
    this->K = K;
    this->N = N;

    // Precalculate ambient
    this->ambient = albedo * this->K.getX();
}

Vector3 Material::phongShade(Vector3 N, Vector3 L, Vector3 H) {

    // Calculate diffuse factor
    Vector3 diffuse = this->K.getY() * this->albedo * MathUtils::clamp((N * L), 0, 1);

    // Calculate specular factor
    Vector3 specular = this->K.getZ() * this->specular * pow(MathUtils::clamp(N * H, 0, 1), this->N);

    // Combine illumination model
    return this->ambient + diffuse + specular;
}

Vector3 Material::getAlbedo() {
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

Vector3 Material::getAmbient() {
    return this->ambient;
}